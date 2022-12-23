#include "getWords.h"

pthread_mutex_t lock;
sem_t semaphore;
int threadId = 0;


/* ============================================== START OF MEMORY ALLOCATION CODE =============================================== */
char** createCharArray() {
	char** threadWordArray = malloc(sizeof(char*) * WORDS_TO_RETRIEVE);
	
	int i;
	for(i = 0; i < WORDS_TO_RETRIEVE; i++) {
		threadWordArray[i] = malloc(sizeof(char));
	}

	return threadWordArray;
}


void freeCharArray(char** array) {
	int i;
	for(i = 0; i < WORDS_TO_RETRIEVE; i++) {
		free(array[i]);
	}

	free(array);
}


void freeList(Node* args) {
	if (args == NULL) return;

	Node* head = args;
	while(head->next != NULL) {
		Node* tmp = head;
		head = head->next;

		free(tmp->word);
		free(tmp);
	}
}


/* =============================================== END OF MEMORY ALLOCATION CODE ============================================== */


int get_words(char*** words, int threadIdx, long int* offSet) {
	char** threadWordList = *words;

	char* filename = malloc(sizeof(FILENAME));
	sprintf(filename, FILENAME, threadIdx);

	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("Unable to find file\n");
		pthread_exit(NULL);
	}
	
	fseek(fp, *offSet, SEEK_CUR);

	int idx = 0;
	char* token;
	char* newBuffer;
	char string[60];
	
	while(fgets(string, 100, fp)) {
		int strLen = strlen(string);

		if (idx == 10) break;
        if (strLen == 0) break;
        
		*(offSet) += strLen;

        if (string[strLen - 1] == '\n') {
		    token = strtok(string, "\n");
            if (token == NULL) break;
		    strLen = strlen(token);

        } else {
            token = strtok(string, NULL);
        }

		newBuffer = realloc(threadWordList[idx], strlen(token) + 1);
		if (realloc == NULL) {
			printf("Unable to reallocate for threadWordList[%d]\n", idx);
			pthread_exit(NULL);
		} else {
			threadWordList[idx] = newBuffer;
			newBuffer = NULL;
		}
	
		strcpy(threadWordList[idx], token);
		idx++;
	}

	fclose(fp);
	free(filename);
	return idx;
}


void increaseWordCount(Node* head, char* word) {

	Node* current = head;
	while(current->next != NULL) {
		if (strcmp(current->word, word) == 0) {
			sem_wait(&semaphore);
			pthread_mutex_lock(&lock);
			current->count++;
			pthread_mutex_unlock(&lock);
			sem_post(&semaphore);
			return;
		}
		current = current->next;
	}

	return;
}


int searchWord(Node* head, char* word) {
	if (head == NULL) return 0;
	
	Node* current = head;
	while(current->next != NULL) {
		if (strcmp(current->word, word) == 0) return 1;
		current = current->next;
	}

	return 0;
}


void addWord(Node** head_ref, char* word) {
	int newWordLength = strlen(word);

	/* 1. allocate space for new node */
	Node* newNode = malloc(sizeof(Node));

	/* 2. allocate space for any pointers in new node */
	newNode->word = malloc(sizeof(char) * newWordLength);

	/* 3. insert data into the new node */
	strcpy(newNode->word, word);
	newNode->count = 1;
	newNode->next = NULL;

	/* 4. checked to see if the linked list is empty */
	if (*head_ref == NULL) {
		*head_ref = newNode;
		return;
	}

	/* 5. travel to the last node */
	Node* last = *head_ref; 
    int size = 1;
	while(last->next != NULL)
        last = last->next;

	/* 6. change the last->next to the new node */
	last->next = newNode;
}


void* routine(void* arg) {
	
	int i;
	Node** args = (Node**) arg;

	int threadIdx;
	long int offSet = 0;
	char** threadWordArray = createCharArray();
	if(threadWordArray == NULL) {
		perror("Unable to allocate memory for threadWordArra\n");
		pthread_exit(NULL);
	}
    
    pthread_mutex_lock(&lock);
    threadId += 1;
    threadIdx = threadId;
    pthread_mutex_unlock(&lock);

	/* MAIN THREAD LOGIC START */
	int idx = 1;
	do {
		idx = get_words(&threadWordArray, threadIdx, &offSet);

		for(i = 0; i < idx; i++) {
            int inList = searchWord(*args, threadWordArray[i]);

            if (!inList) {
                pthread_mutex_lock(&lock);
        	    addWord(args, threadWordArray[i]);
                pthread_mutex_unlock(&lock);
            } else {
                increaseWordCount(*args, threadWordArray[i]);
            }
        }
	} while(idx);
	/* MAIN THREAD LOGIC END */

	freeCharArray(threadWordArray);
	pthread_exit(NULL);
}

int main() {
	int i;

    pthread_t threads[NUM_THREADS];
	pthread_mutex_init(&lock, NULL);
	sem_init(&semaphore, 0, 1);
  
    Node* args = NULL;

    // RUN THREADS 1 AND 2 FIRST
	for(i = 0; i < NUM_THREADS; i++) {
		if (pthread_create(&threads[i], NULL, routine, (void*) &args)) {
			perror("Error; return code from pthread_create() when creating thread\n");
		    return EXIT_FAILURE;
		}
	}

	for(i = 0; i < NUM_THREADS; i++) 
		pthread_join(threads[i], NULL);

    // PRINT OUT THREADS
    if (args == NULL) {
		printf("printList(): Head is null\n");
		return EXIT_SUCCESS;
	}


	Node* current = args;
	int count = 1;
	while(current->next != NULL) {
		if (current->count == 1) {
			printf("%d) %s\n", count, current->word, current->count);
			count++;
		}
		
        current = current->next;
	}		
    printf("%d) %s\n", count, current->word, current->count);


	freeList(args);
	pthread_mutex_destroy(&lock);
    sem_destroy(&semaphore);
	return EXIT_SUCCESS;
}
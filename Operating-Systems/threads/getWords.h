#ifndef GET_WORDS_H
#define GET_WORDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 4
#define HALF_NUM_THREADS 2
#define WORDS_TO_RETRIEVE 10
#define FILENAME "txtFiles/dictionary%d.txt"
// #define FILENAME "txtFiles/%d.txt"

typedef struct Node {
	char* word;
	int count;
	struct Node* next;
} Node;

void increaseWordCount(Node*, char*);

void addWord(Node**, char*);

int searchWord(Node*, char*);

int get_words(char***, int, long int*);

void* routine(void* arg);

char** createCharArray();

void freeCharArray(char** array);

void freeList(Node*);

#endif
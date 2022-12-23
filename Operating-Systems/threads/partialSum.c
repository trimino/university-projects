/*
 * In your multithreaded program, there is a shared array (int A[9] containing 9 numbers (10, 20, 30, ... 90).
 * Your program will create three child threads. One thread will obtain the sum of the first three numbers and 
 * place the sum at A[2] (i.e.: A[2] = A[0] + A[1] + A[2]). Another thread will do similarly for the next three
 * numbers (i.e: A[5] = A[3] + A[4] + A[5]). The third thread will do two things:
 * 	(1) get the partial sum of the last three numbers A[8] = A[6] + A[7] + A[8]
 * 	(2) get and print the total sum A[8] = A[2] + A[5] + A[8]
 * Note that the third thread has to make sure the partial sms are available before it can compute the total sum
 *
 * 
 * REPORT
 * To synchronze the threads we use thread barrier. Before ending the beginning threads, the program has them
 * wait at the barrier before deallocating and exiting the thread. Also having the last thread wait at the 
 * barrier BEFORE computing the sum. Once all threads are waiting at the barrier the beginning threads can
 * terminate/exit while the last thread can calculate the sum then exit. 
 *
 *
 * gcc -pthread -o partialSum partialSum.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3
#define ARRAY_SIZE 9

pthread_barrier_t barrierCalculate;

typedef struct Data{
	int *array;
	int begin;
	int end;
	int pthreadIndex;
}Data;


void* SumArray(void* arg) {
	Data* data = (Data*) arg;				/* Process argument passed into thread func			*/
	int partialSum = 0;					/* Partial sum (will be stored in array)			*/
	
	int i;
	for(i = data->begin; i < data->end; i++)
		partialSum += data->array[i];

	data->array[data->end - 1] = partialSum;		/* Update array with sum at every third index			*/
	if (data->pthreadIndex == NUM_THREADS - 1) {		/* Only have the last thread run this code			*/
		
		pthread_barrier_wait(&barrierCalculate);	/* Barrier for the last thread to wait before calculating sum	*/
		
		int idx = ARRAY_SIZE / NUM_THREADS - 1;
		int endIdx = data->end - 1;

		data->array[endIdx] = data->array[idx] + data->array[idx + NUM_THREADS] + data->array[endIdx]; 
		printf("Sum of Array: %d\n", data->array[endIdx]);
		
		free(arg);
		pthread_exit(NULL);		
	}

	pthread_barrier_wait(&barrierCalculate);		/* Have the first two threads wait at barrier			*/
	free(arg);						/* Free allocated threaData memory				*/
	pthread_exit(NULL);					/* Exit thread with no return value				*/
}


int main() {
	int integerArray[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };
	pthread_t threads[NUM_THREADS];				/* Creating thread array 					*/
	Data data[NUM_THREADS];					/* Struct to represent the data pass to thread			*/
	
	pthread_barrier_init(&barrierCalculate, NULL, NUM_THREADS);

	int x;
	for(x = 0; x < NUM_THREADS; x++) {
		Data* threadData  = (Data*) malloc(sizeof(Data));
		threadData->array = integerArray;
		threadData->begin = x * 3;
		threadData->end   = x * 3 + 3;
		threadData->pthreadIndex = x;

		if (pthread_create(&threads[x], NULL, SumArray, (void*) threadData)) {
			perror("Error; return code from pthread_create() when creating thread\n");
		       	return EXIT_FAILURE;	
		}
	}

	for(x = 0; x < NUM_THREADS; x++) 
		pthread_join(threads[x], NULL);
	
	return EXIT_SUCCESS;
}
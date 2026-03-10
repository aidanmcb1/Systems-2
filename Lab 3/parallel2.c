#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define ARRAY_SIZE 1000000
#define THREAD_NO 10

int sum = 0;
pthread_mutex_t lock;

void *compute(void *args){
    int *num =(int *)args;
    int localsum = 0;
    for(int i=0; i<ARRAY_SIZE/THREAD_NO; i++){
	pthread_mutex_lock(&lock);
	sum += num[i];
	pthread_mutex_unlock(&lock);
    }
}






int main(){
    int num[THREAD_NO][ARRAY_SIZE/THREAD_NO];
    pthread_t p[THREAD_NO];
    srand(100);
    pthread_mutex_init(&lock, NULL);
    //initialize arrays
    for(int i=0; i< THREAD_NO; i++){
	for(int j=0; j< ARRAY_SIZE/THREAD_NO; j++){
            num[i][j] = rand() % 100;
	}
    }

    //create threads. Give each thread an array.
    for(int i=0; i<THREAD_NO; i++)
	pthread_create(&p[i], NULL, compute, num[i]); 

    //wait for all threads to complete.
    for(int i=0; i<THREAD_NO; i++)
	pthread_join(p[i], NULL);

    pthread_mutex_destroy(&lock);

    printf("sum = %d\n", sum);
    return 0;
}

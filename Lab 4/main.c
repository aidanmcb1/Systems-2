#include "bounded_buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct bounded_buffer queue;

void *producer(void *ptr);
void *consumer(void *ptr);

int main() {
    /* initialize the queue */
    bounded_buffer_init(&queue, size);
    /* create producer and consumer threads */

    pthread_t producers[producerMessageCount];
    pthread_t consumers[consumerMessageCount];
    int message = 1;
    int ctc = 1;

    for (int i = 0; i < producerCount; i++) {
        int* msg = malloc(sizeof(int));
        *msg = message;
        pthread_create(&producers[i], NULL, producer, msg);
        message += producerMessageCount;
    }

    for (int i = 0; i < consumerCount; i++) {
        int* id = malloc(sizeof(int));
        *id = ctc++;
        pthread_create(&consumers[i], NULL, consumer, id);
    }

    sleep(5);

    bounded_buffer_destroy(&queue);
    exit(0);
}

/* this is the function executed by the producer thread. 
   It should generate a number of messages and push them into the queue */
void* producer(void* ptr) {
    int* base = ptr;
    for (int i = 0; i < producerMessageCount; ++i) {
        int* msg = malloc(sizeof(int));
        *msg = *base + i;   // actual message value
        bounded_buffer_push(&queue, msg);
        printf("Created message %d\n", *msg);
    }
    free(base);
    return NULL;
}

/* this is the function executed by the consumer thread. 
   It should pop messages from the queue and print them */
void* consumer(void* ptr) {
    int* id = ptr;
    for (int i = 0; i < consumerMessageCount; ++i) {
        int* popped = bounded_buffer_pop(&queue);
        printf("Thread %d consumed %d\n", *id, *popped);
        free(popped);
    }
    free(id);
    return NULL;
}

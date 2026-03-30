#include "bounded_buffer.h"
#include <stdio.h>
#include <stdlib.h>

#define size 5
#define producerMessageCount 10
#define consumerMessageCount 15
#define producerCount 3
#define consumerCount 2

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
    int* messageptr = nullptr;
    int ctc = 1;
    int* ctcptr = nullptr;

    for (int i = 0; i < producerCount; i++) {
        *messageptr = message;
        pthread_create(producers, nullptr, producer, messageptr);
        message += producerMessageCount;
    }

    for (int i = 0; i < consumerCount; i++) {
        *ctcptr = ctc;
        pthread_create(consumers, nullptr, consumer, ctcptr);
        ctc++;
    }

    bounded_buffer_destroy(&queue);
    return 0;
}

/* this is the function executed by the producer thread. 
   It should generate a number of messages and push them into the queue */
void *producer(void *ptr){
    int* number = (int*) ptr;
    for (int i = 0; i < producerMessageCount; ++i) {
        bounded_buffer_push(&queue, number);
        printf("Created message %i\n", *number);
        number++;
    }
    return NULL;
}

/* this is the function executed by the consumer thread. 
   It should pop messages from the queue and print them */
void *consumer(void *ptr){
    const int* number = (int*) ptr;
    for (int i = 0; i < consumerMessageCount; ++i) {
        const int* popped = bounded_buffer_pop(&queue);
        printf("Thread %i consumed %i\n", *number, *popped);
    }
    return NULL;
}

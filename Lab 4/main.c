#include "bounded_buffer.h"
#include <stdio.h>
#include <stdlib.h>

#define size 20
#define producerMessageCount 10
#define consumerMessageCount 10

struct bounded_buffer queue;

void *producer(void *ptr);
void *consumer(void *ptr);

int main() {
    /* initialize the queue */
    bounded_buffer_init(&queue, size);
    /* create producer and consumer threads */

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
    }
    return NULL;
}

/* this is the function executed by the consumer thread. 
   It should pop messages from the queue and print them */
void *consumer(void *ptr){
    for (int i = 0; i < consumerMessageCount; ++i) {
        const int* popped = bounded_buffer_pop(&queue);
        printf("Consumed %i\n", *popped);
    }
    return NULL;
}

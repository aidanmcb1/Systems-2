#include "bounded_buffer.h"
#include <stdio.h>
#include <stdlib.h>

struct bounded_buffer queue;

void *producer(void *ptr);
void *consumer(void *ptr);

int main() {
    /* initialize the queue */
    const int size = 20;
    struct bounded_buffer* buffer = (struct bounded_buffer*) malloc(sizeof(struct bounded_buffer));
    bounded_buffer_init(buffer, size);
    bounded_buffer_push(buffer, "test");
    bounded_buffer_push(buffer, "test2");
    bounded_buffer_push(buffer, "test3");
    bounded_buffer_push(buffer, "test4");
    bounded_buffer_push(buffer, "test5");
    bounded_buffer_pop(buffer);
    /* create producer and consumer threads */

    return 0;
}

/* this is the function executed by the producer thread. 
   It should generate a number of messages and push them into the queue */
void *producer(void *ptr){
    return NULL;
}

/* this is the function executed by the consumer thread. 
   It should pop messages from the queue and print them */
void *consumer(void *ptr){
    return NULL;
}

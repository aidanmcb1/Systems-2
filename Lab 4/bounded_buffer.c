#include "bounded_buffer.h"
#include <stdio.h>
#include <stdlib.h>

/*Do not use any global variables for implementation*/

void bounded_buffer_init(struct bounded_buffer *buffer, int max_size){
    buffer->head = NULL;
    buffer->tail = NULL;
    buffer->currentsize = 0;
    buffer->max_size = max_size;
    pthread_mutex_init(&buffer->m, NULL);
    pthread_cond_init(&buffer->cfull, NULL);
    pthread_cond_init(&buffer->cempty, NULL);
}

void bounded_buffer_push(struct bounded_buffer *buffer, void *item){
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->item = item;
    new_node->next = NULL;

    pthread_mutex_lock(&buffer->m);
    while (buffer->currentsize == buffer->max_size) {
        pthread_cond_wait(&buffer->cfull, &buffer->m);
    }

    if (buffer->head == NULL) {
        buffer->head = buffer->tail = new_node;
    } else {
        buffer->tail->next = new_node;
        buffer->tail = new_node;
    }
    buffer->currentsize++;

    pthread_cond_signal(&buffer->cempty);
    pthread_mutex_unlock(&buffer->m);
}

void* bounded_buffer_pop(struct bounded_buffer *buffer){
    pthread_mutex_lock(&buffer->m);
    while (buffer->currentsize == 0) {
        pthread_cond_wait(&buffer->cempty, &buffer->m);
    }

    struct node* temp = buffer->head;
    void* item = temp->item;
    buffer->head = buffer->head->next;
    free(temp);
    buffer->currentsize--;

    pthread_cond_signal(&buffer->cfull);
    pthread_mutex_unlock(&buffer->m);

    return item;
}

void bounded_buffer_destroy(struct bounded_buffer *buffer){
    while (buffer->currentsize != 0) {
        void* temp = bounded_buffer_pop(buffer);
        free(temp);
    }
    pthread_cond_destroy(&buffer->cempty);
    pthread_mutex_destroy(&buffer->m);
    pthread_cond_destroy(&buffer->cfull);
}

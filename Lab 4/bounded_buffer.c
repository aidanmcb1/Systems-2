#include "bounded_buffer.h"
#include <stdio.h>
#include <stdlib.h>

/*Do not use any global variables for implementation*/

void bounded_buffer_init(struct bounded_buffer *buffer, int size){
    buffer->head = nullptr;
    buffer->size = 0;
    buffer->max_size = size;
    pthread_mutex_init(&buffer->m, nullptr);
    pthread_cond_init(&buffer->cfull, nullptr);
    pthread_cond_init(&buffer->cempty, nullptr);
}

void bounded_buffer_push(struct bounded_buffer *buffer, void *item){
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->item = item;
    new_node->next = nullptr;

    pthread_mutex_lock(&buffer->m);
    while (buffer->size == buffer->max_size) {
        pthread_cond_wait(&buffer->cfull, &buffer->m);
    }

    if (buffer->head == NULL) {
        buffer->head = new_node;
        buffer->size++;
    } else {
        struct node* temp = buffer->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
        buffer->size++;
    }

    pthread_cond_signal(&buffer->cempty);
    pthread_mutex_unlock(&buffer->m);
}

void* bounded_buffer_pop(struct bounded_buffer *buffer){
    pthread_mutex_lock(&buffer->m);
    while (buffer->size == 0) {
        pthread_cond_wait(&buffer->cempty, &buffer->m);
    }

    struct node* temp = buffer->head;
    void* item = temp->item;
    buffer->head = buffer->head->next;
    free(temp);
    buffer->size--;

    pthread_cond_signal(&buffer->cfull);
    pthread_mutex_unlock(&buffer->m);

    return item;
}

void bounded_buffer_destroy(struct bounded_buffer *buffer){
    while (buffer->size != 0) {
        bounded_buffer_pop(buffer);
    }
    free(buffer);
}

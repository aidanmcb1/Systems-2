#include "bounded_buffer.h"
#include <stdio.h>
#include <stdlib.h>

/*Do not use any global variables for implementation*/

void bounded_buffer_init(struct bounded_buffer *buffer, int size){
    buffer->head = NULL;
    buffer->size = 0;
    buffer->max_size = size;
}

void bounded_buffer_push(struct bounded_buffer *buffer, void *item){
    if (buffer->size == buffer->max_size) {
        printf("buffer is full\n");
        return;
    }
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->item = item;
    new_node->next = NULL;

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
}

void* bounded_buffer_pop(struct bounded_buffer *buffer){
    if (buffer->size == 0) {
        printf("buffer is empty\n");
    }
    struct node* temp = buffer->head;
    void* item = temp->item;
    buffer->head = buffer->head->next;
    free(temp);
    buffer->size--;
    return item;
}

void bounded_buffer_destroy(struct bounded_buffer *buffer){
    while (buffer->size != 0) {
        bounded_buffer_pop(buffer);
    }
    free(buffer);
}

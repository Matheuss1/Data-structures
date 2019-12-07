#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include "lista.h"

typedef struct {
    p_node *list;
    int n, size;
    int begin, end;
} Queue;

typedef Queue* p_queue;

// Creates a new queue of node structure
p_queue newQueue(int size);

// push a node in the queue
void push(p_queue queue, p_node item);

// returns a pointer for the begin of the queue
p_node pop(p_queue queue);

// return if it's true that the queue is empty, or false if it's not empty
int isEmpty(p_queue queue);

// removes the queue and frees the allocated memory for it
void removeQueue(p_queue queue);
 
#endif
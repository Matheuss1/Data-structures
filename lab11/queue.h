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

p_queue newQueue(int size);

void push(p_queue queue, p_node item);

p_node pop(p_queue queue);

int isEmpty(p_queue queue);
 
#endif
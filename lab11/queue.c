#include "queue.h"

p_queue newQueue(int queueSize)
{
    p_queue queue = malloc(sizeof(Queue));
    queue->list = calloc(queueSize, sizeof(Node));
    queue->n = queueSize;
    queue->size = 0;
    queue->begin = 0;
    queue->end = 0;

    return queue;
}


void push(p_queue queue, p_node node)
{
    queue->list[queue->end] = node;
    queue->end = (queue->end + 1) % queue->n;
    queue->size++;
}


p_node pop(p_queue queue)
{
    p_node node = queue->list[queue->begin];
    queue->begin = (queue->begin + 1) %  queue->n;
    queue->size--;
    
    return node;
}


int isEmpty(p_queue queue)
{
    if (queue->size == 0)
        return 1;
    
    return 0;
}


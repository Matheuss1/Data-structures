#ifndef HEAP_H
#define HEAP_H

#include "list.h"

typedef struct {
    p_node *heap;
    int heapSize;
} PQ;
// priority queue pointer
typedef PQ* p_pq;

// Creates a heap of boxes and returns a pointer to it
p_pq newHeap(int size);

// Adds a new box into the heap
void pushToHeap(p_pq pq, p_node box);

// Removes the box in the heap top and returns its pointer
p_node pop(p_pq pq);

// Returns a pointer to the heap top
p_node top(p_pq pq);

// Frees the memory used by the heap allocation
void heapDestruct(p_pq queue);

#endif

#ifndef HEAP_H
#define HEAP_H

#define ID_SIZE 5

typedef struct {
    char id[ID_SIZE];
    int group;
} Box;
// box pointer
typedef Box* p_box;


typedef struct {
    p_box *minHeap, *maxHeap;
    int minSize, maxSize;
} PQ;
// priority queue pointer
typedef PQ* p_pq;

// Creates a heap that stores the boxes ID in a way that
// the median of IDs can be found in linear time
p_pq medianHeap(int size);

// Adds a new box to the median heap
void push(p_pq queue, p_box box);

// Creates a newbox with its group and ID
p_box newBox(char identification[], int group);

// Returns the ID of the median box
void median(p_pq queue);

// Frees the memory used by medianHeap
void heapDestruct(p_pq queue);

#endif

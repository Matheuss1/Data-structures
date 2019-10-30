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
    p_box *boxesBatch;
    int n, queueSize;
} PQ;
// priority queue pointer
typedef PQ* p_pq;

p_pq pqueue(int size);

void push(p_pq queue, p_box box);

p_box newBox(char identification[], int group);

void median(p_pq queue);

void heapDestruct(p_pq queue);

#endif

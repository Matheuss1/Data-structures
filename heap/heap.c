#include "heap.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void bottomUp(p_pq pq, int k, int identifier);
void topDown(p_pq queue, int k, int l);


p_pq newHeap(int size)
{
    p_pq pq = malloc(sizeof(PQ));
    if (pq == NULL)
        exit(1);

    pq->heap = malloc(size  * sizeof(Box*));
    if (pq->heap == NULL)
        exit(1);

    pq->heapSize = 0;
    return pq;
}


void push(p_pq pq, p_box box, int identifier)
{   
    pq->heap[pq->heapSize++] = box; 
    bottomUp(pq, pq->heapSize - 1, identifier);
}


p_box pop(p_pq pq, int identifier)
{
    p_box temp = pq->heap[0];
    pq->heap[0] = pq->heap[pq->heapSize - 1];
    pq->heapSize--;

    topDown(pq, 0, identifier);

    return temp;

}


p_box top(p_pq pq)
{
    if (pq->heap[0] == NULL)
        return NULL;
    
    return pq->heap[0];
}


int getSize(p_pq pq)
{
    return pq->heapSize;
}


// l is used to identify the heap that is being used in following functions, 1 if is the minHeap and 2 if maxHeap

#define FATHER(i) ((i - 1 ) / 2)

// Puts the last add item in the heap in the right position, maintaining the heap properties
void bottomUp(p_pq pq, int k, int identifier)
{
    if (k > 0 && (  (identifier == 1 && (strcmp(pq->heap[FATHER(k)]->id, pq->heap[k]->id) > 0) ) || 
                    (identifier == 2 && (strcmp(pq->heap[FATHER(k)]->id, pq->heap[k]->id) < 0))) ) {
            p_box temp = pq->heap[FATHER(k)];
            pq->heap[FATHER(k)] = pq->heap[k];
            pq->heap[k] = temp;

            bottomUp(pq, FATHER(k), identifier);
    }
}
 

#define L_child(i) (2 * i + 1)

// After an item to be removed from the heap, the last child of the heap is putted in the heap beginning,
// so, is need to traverse down the heap, swapping positions of other children in the tree until the node
// that was placed in the first position to be in the right place
void topDown(p_pq pq, int k, int identifier)
{
    int j;

    while (L_child(k) < pq->heapSize) {
        j = L_child(k);
        if ( (j < pq->heapSize && j + 1 < pq->heapSize) && ( ( identifier == 1 && strcmp(pq->heap[j]->id, pq->heap[j + 1]->id) > 0) ||
                                                             ( identifier == 2 && strcmp(pq->heap[j]->id, pq->heap[j + 1]->id) < 0) ))
            j++;

        if ( (identifier == 1 && strcmp(pq->heap[k]->id, pq->heap[j]->id) < 0) || (identifier == 2 && strcmp(pq->heap[k]->id, pq->heap[j]->id) > 0))
            break;

        // swap the node in the k pos with j pos if the node in k pos has a high priority'
        p_box temp = pq->heap[k];
        pq->heap[k] = pq->heap[j];
        pq->heap[j] = temp;

        k = j;
    }
}


void heapDestruct(p_pq pq)
{
    for (int i = 0; i < pq->heapSize; i++) {
        free(pq->heap[i]);
    }

    free(pq->heap);
    free(pq);
}

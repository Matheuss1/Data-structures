#include "heap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

p_box pop(p_pq pq, int l);
void bottomUp(p_pq queue, int k, int l);
void topDown(p_pq queue, int k, int l);


p_pq medianHeap(int size)
{
    p_pq pq = malloc(sizeof(PQ));
    pq->minHeap = malloc(size  * sizeof(Box*));
    pq->maxHeap = malloc(size * sizeof(Box*) );
    pq->minSize = pq->maxSize = 0;

    return pq;
}


void push(p_pq pq, p_box box)
{   
    // if the minHeap is empty, so we directly insert the new box in it
    if (pq->minSize == 0) {
        pq->minHeap[pq->minSize++] = box;
        return;
    }

    // Compares if the new box has the id higher than the root of minHeap
    // and also verifies if the min and max heaps have the same size, if true
    // the box is add to minHeap, othewise the root of minHeap is extracted and inserted in the maxHeap
    // after that, the new box is add to minHeap
    if (strcmp(box->id, pq->minHeap[0]->id) > 0) {
        if (pq->minSize - pq->maxSize > 0) {
            p_box temp = pop(pq, 1);

            topDown(pq, 0, 1);
            pq->minHeap[pq->minSize++] = box;
            bottomUp(pq, pq->minSize - 1, 1);

            pq->maxHeap[pq->maxSize++] = temp;
            bottomUp(pq, pq->maxSize - 1, 2);

            return;
        }

        pq->minHeap[pq->minSize++] = box;
        bottomUp(pq, pq->minSize - 1, 1);

        return;
    }

    // Adds the box to maxHeap
    pq->maxHeap[pq->maxSize] = box;
    pq->maxSize++;
    bottomUp(pq, pq->maxSize - 1, 2);

    // If the maxHeap has more elements than minHeap, its root is extracted and inserted in the minHeap
    if (pq->maxSize - pq->minSize > 0) {
        p_box temp = pop(pq, 2);
        topDown(pq, 0, 2);

        pq->minHeap[pq->minSize++] = temp;
        bottomUp(pq, pq->minSize - 1, 1);
    }
   
}


// Removes an item from the heap, returning a pointer for the item
p_box pop(p_pq pq, int l)
{
    if (l == 1) {
        p_box temp = pq->minHeap[0];
        pq->minHeap[0] = pq->minHeap[pq->minSize - 1];
        pq->minSize--;

        topDown(pq, 0, 1);

        return temp;
    }

    p_box temp = pq->maxHeap[0];
    pq->maxHeap[0] = pq->maxHeap[pq->maxSize - 1];
    pq->maxSize--;

    topDown(pq, 0, 2);

    return temp;

}


// l is used to identify the heap that is being used in following functions, 1 if is the minHeap and 2 if maxHeap

#define FATHER(i) ((i - 1 ) / 2)

// Puts the last add item in the heap in the right position, maintaining the heap properties
void bottomUp(p_pq queue, int k, int l)
{
    if (l == 1)
        if (k > 0 && (strcmp(queue->minHeap[FATHER(k)]->id, queue->minHeap[k]->id) > 0)) {
            p_box temp = queue->minHeap[FATHER(k)];
            queue->minHeap[FATHER(k)] = queue->minHeap[k];
            queue->minHeap[k] = temp;

            bottomUp(queue, FATHER(k), 1);
        }
    
    if (l == 2)
        if (k > 0 && (strcmp(queue->maxHeap[FATHER(k)]->id, queue->maxHeap[k]->id) < 0)) {
            p_box temp = queue->maxHeap[FATHER(k)];
            queue->maxHeap[FATHER(k)] = queue->maxHeap[k];
            queue->maxHeap[k] = temp;

            bottomUp(queue, FATHER(k), 2);
        }

}

 
#define L_child(i) (2 * i + 1)

// After an item be removed from the heap, the last child of the heap is putted in the heap beginning,
// so, is need to traverse down the heap, swapping positions of other children in the tree until the node
// that was placed in the first position be in the right place
void topDown(p_pq pq, int k, int l)
{
    int j;

    if (l == 1)
        while (L_child(k) < pq->minSize) {
            j = L_child(k);
            if ( (j < pq->minSize && j + 1 < pq->minSize) && strcmp(pq->minHeap[j]->id, pq->minHeap[j + 1]->id) > 0) 
                j++;

            if (strcmp(pq->minHeap[k]->id, pq->minHeap[j]->id) < 0)
                break;

            // swap the node in the k pos with j pos if the node in k pos has a high priority'
            p_box temp = pq->minHeap[k];
            pq->minHeap[k] = pq->minHeap[j];
            pq->minHeap[j] = temp;

            k = j;
        }

    if (l == 2)
        while (L_child(k) < pq->maxSize) {
            j = L_child(k);
            if ( (j < pq->maxSize && j + 1 < pq->maxSize) && strcmp(pq->maxHeap[j]->id, pq->maxHeap[j + 1]->id) < 0) 
                j++;

            if (strcmp(pq->maxHeap[k]->id, pq->maxHeap[j]->id) > 0)
                break;

            // swap the node in the k pos with j pos if the node in k pos has a low priority
            p_box temp = pq->maxHeap[k];
            pq->maxHeap[k] = pq->maxHeap[j];
            pq->maxHeap[j] = temp;

            k = j;
        }
}


void median(p_pq pq)
{
    // if the heap has an even size, so the median are made of two boxes and the ids is printed, one id is the root 
    // of the maxHeap and the other id is the root of minHeap
    if (pq->minSize == pq->maxSize)
        printf("%d %s %s\n", pq->maxHeap[0]->group, pq->maxHeap[0]->id, pq->minHeap[0]->id);
    // otherwise, just print one id, located in the root of minHeap
    else
        printf("%d %s\n", pq->minHeap[0]->group, pq->minHeap[0]->id);
}


p_box newBox(char identification[], int group)
{
    p_box newBox = malloc(sizeof(Box));
    strcpy(newBox->id, identification);
    newBox->group = group;
    return newBox;
}


void heapDestruct(p_pq pq)
{
    for (int i = 0; i < pq->minSize; i++) {
        free(pq->minHeap[i]);
    }

    for (int i = 0; i < pq->maxSize; i++) {
        free(pq->maxHeap[i]);
    }

    free(pq->minHeap);
    free(pq->maxHeap);
    free(pq);
}

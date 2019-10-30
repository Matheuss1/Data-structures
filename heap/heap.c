#include "heap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void bottomUp(p_pq queue, int k);
void topDown(p_pq queue, int k);

p_pq pqueue(int size)
{
    p_pq pq = malloc(sizeof(PQ));
    pq->boxesBatch = malloc(size * sizeof(Box*));
    pq->n = 0;
    pq->queueSize = size;

    return pq;
}


void push(p_pq queue, p_box box)
{
    queue->boxesBatch[queue->n] = box;
    queue->n++;
    bottomUp(queue, queue->n - 1);
}


#define FATHER(i) ((i - 1 ) / 2)

void bottomUp(p_pq queue, int k)
{
    if (k > 0 && (strcmp(queue->boxesBatch[FATHER(k)]->id, queue->boxesBatch[k]->id) > 0)) {
        p_box temp = queue->boxesBatch[FATHER(k)];
        queue->boxesBatch[FATHER(k)] = queue->boxesBatch[k];
        queue->boxesBatch[k] = temp;

        bottomUp(queue, FATHER(k));
    }
}


#define L_child(i) (2 * i + 1)

void topDown(p_pq queue, int k)
{
    int j;

    while (L_child(k) < queue->n) {
        j = L_child(k);
        if ( (j < queue->n && j + 1 < queue->n) && strcmp(queue->boxesBatch[j]->id, queue->boxesBatch[j + 1]->id) > 0) 
            j++;

        if (strcmp(queue->boxesBatch[k]->id, queue->boxesBatch[j]->id) < 0)
            break;

        p_box temp = queue->boxesBatch[k];
        queue->boxesBatch[k] = queue->boxesBatch[j];
        queue->boxesBatch[j] = temp;

        k = j;

    }
}


void popMin(p_pq queue)
{
    p_box temp = queue->boxesBatch[0];

    queue->boxesBatch[0] = queue->boxesBatch[queue->n - 1];
    queue->boxesBatch[queue->n - 1] = temp;
    queue->n--;
    topDown(queue, 0);
}


void median(p_pq queue)
{
    int j, remotions = 0;
    p_box *temp = malloc(queue->n * sizeof(Box*));

    for (j = 0; j < queue->n; j++) {
        temp[j] = queue->boxesBatch[j];
    }

    int k = (queue->n - 1) / 2;

    while (k > 0) {
        popMin(queue);
        remotions++;
        k--;
    }

    if ( (queue->n + remotions) % 2 == 0 && queue->n > 2) {
        p_box box1, box2;
        box1 = queue->boxesBatch[0];
        box2 = queue->boxesBatch[1];

        if (strcmp(queue->boxesBatch[1]->id, queue->boxesBatch[2]->id) > 0)
            box2 = queue->boxesBatch[2];

        printf("%d %s %s\n", box1->group, box1->id, box2->id);
    }
    else
        printf("%d %s\n", queue->boxesBatch[0]->group, queue->boxesBatch[0]->id);

    queue->n += remotions;

    for (j = 0; j < queue->n ; j++) {
        queue->boxesBatch[j] = temp[j];
    }
    free(temp);
}


void heapDestruct(p_pq queue)
{
    for (int i = 0; i < queue->queueSize; i++) {
        free(queue->boxesBatch[i]);
    }
    free(queue->boxesBatch);
    free(queue);
}


p_box newBox(char identification[], int group)
{
    p_box newBox = malloc(sizeof(Box));
    strcpy(newBox->id, identification);
    newBox->group = group;
    return newBox;
}
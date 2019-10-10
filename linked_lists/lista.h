#ifndef LISTA_H
#define LISTA_H

typedef struct Node {
    int index;
    int freeMemory;
    struct Node *next;
    struct Node *prev;
} Node;

typedef Node *n_ptr;  //node pointer

// Creates a new list with the heapsize wanted
n_ptr new_list(int heapSize);

// Allocs a new  memory block in the list node that leftover the minimum unused memory after the allocation
n_ptr memBlockAlloc(n_ptr list, int size);

// Deallocs certain memory block in the heap
// Can dealloc one memory block and realloc in the same or other adress
n_ptr memBlockDealloc(n_ptr list, int adress, int remotionSize);

// Reallocs memory in the heap, trying to maintain the new allocation in the current adress
n_ptr memRealloc(n_ptr list, int adress, int currentBlockSize, int newBlockSize);

// Free the nodes of the list
void removeList(n_ptr list);

// Verifies if the malloc function has allocated valid memory
void validAlloc(n_ptr node);

#endif

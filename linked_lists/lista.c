#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

n_ptr currentReturn(n_ptr list, int adress);
n_ptr originFinder(n_ptr node);


// All variables and expressions used here were wrote trying to explicitly shows the objective of
// each block of code, reducing the number of comments and lines in this file
n_ptr new_list(int heapSize)
{
    n_ptr list;
    list = malloc(sizeof(Node));
    validAlloc(list);
    list->index = 0;
    list->freeMemory = heapSize;
    list->next = NULL;
    list->prev = NULL;
    return list;
}


n_ptr memBlockAlloc(n_ptr list, int size)
{
    n_ptr current, temp;
    current = list;
    temp = list; 
    int aux = 0;

    // looks for the memory block that leftover the minimum memory after to be used
    while(current != NULL) {
        if (current->freeMemory >= size) {
            if (!aux) {
                temp = current;
                aux = 1;
            }
            if ( (current->freeMemory) < (temp->freeMemory) )
                temp = current;
        }
        current = current->next;
    }

    // Verifies if the allocation consumes all memory of the current free memory block
    // if true, the block is deallocated
    if (temp->freeMemory - size == 0) {
        // the two conditions verifies how to free the temp node
        if (temp == list) {
            if (temp->next == NULL) {
                free(temp);
                return NULL;
            }
            current = temp->next;
            current->prev = NULL;
            free(temp);
            return current;
        }
        else {
            temp->prev->next = temp->next;
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
                free(temp);
            }
            else
                free(temp);
        }
    }
    // Resizes the memory block used and set the new index;
    else {
        temp->index += size;
        temp->freeMemory -= size;
    }

    return list;
}


n_ptr memBlockDealloc(n_ptr list, int adress, int remotionSize)
{
    n_ptr new, current;

    // Makes a valid alloc with the condition that list == NULL
    if (list == NULL) {
        new = malloc(sizeof(Node));
        validAlloc(new);
        new->index = adress;
        new->freeMemory = remotionSize;
        new->next = NULL;
        new->prev = NULL;
        return new;
    }

    current = currentReturn(list, adress);

    if ( (current->index) > adress ) {
        // case: when the deallocation makes a new block that can be "linked" with the next node in the list
        if ( (adress + remotionSize) == current->index) {
            current->index = adress;
            current->freeMemory += remotionSize;

            return current;
        }
        
        // Creates a new node in the list with the size of memory that was deallocated
        new = malloc(sizeof(Node));
        validAlloc(new);
        new->index = adress;
        new->freeMemory = remotionSize;
        new->next = current;
        new->prev = NULL;
        current->prev = new;
        return new;
    }

    if ( (current->index) < adress ) {
        // Verifies if the current node can store the freed memory
        if ( (current->index + current->freeMemory) == adress ) {
            current->freeMemory += remotionSize;

            // Avoids to access invalid memory
            if (current->next == NULL) {            
                return originFinder(current);
            }

        // Verifies if the next node can be "linked" to the new freed memory block
            if ( (adress + remotionSize) == current->next->index ) {
                current->freeMemory += current->next->freeMemory;
                
                // Frees the next node takng care to avoid segmentation fault error
                if (current->next->next == NULL) {
                    free(current->next);
                    current->next = NULL;
                }
                else {
                    current->next = current->next->next;
                    free(current->next->prev);
                    current->next->prev = current;
                }

                return originFinder(current);
            }

            return originFinder(current);
        }

        if (current->next != NULL) {
            // Verifies if the next node can be "linked" to the memory freed block
            if ( (adress + remotionSize) == current->next->index) {
                current->next->index = adress;
                current->next->freeMemory += remotionSize;

                return originFinder(current);
            }

            // Allocs the memory freed in a new list link
            new = malloc(sizeof(Node));
            validAlloc(new);
            new->index = adress;
            new->freeMemory = remotionSize;
            new->next = current->next;
            new->next->prev = new;
            new->prev = current;
            current->next = new;

            return originFinder(current);
        }

        // Allocs the memory freed in a new list link
        new = malloc(sizeof(Node));
        validAlloc(new);
        new->index = adress;
        new->freeMemory = remotionSize;
        new->next = NULL;
        new->prev = current;
        current->next = new;

        return originFinder(current);

    }

    return list;
}


n_ptr memRealloc(n_ptr list, int adress, int currentBlockSize, int newBlockSize)
{

    n_ptr current, new;
    current = list;

    // Can only realloc blocks < currentBlockSize
    if (current == NULL) {
        return memBlockDealloc(list, adress + newBlockSize, currentBlockSize - newBlockSize);
    }

    current = currentReturn(list, adress);

    // The program does the operations based in the cases that the current node
    // can be higher, less or equal to adress variable
    // in the last case, 
    if (current->index < adress) {
        // Avoids invalid memory access that leads to segmentation fault
        if (current->next == NULL) {
            if (newBlockSize < currentBlockSize) {
                // Creates a new block in the list
                new = malloc(sizeof(Node));
                validAlloc(new);
                new->index = adress + newBlockSize;
                new->freeMemory = currentBlockSize - newBlockSize;
                new->prev = current;
                new->next = NULL;
                current->next = new;

                return list;
            }
            list = memBlockDealloc(list, adress, currentBlockSize);
            return memBlockAlloc(list, newBlockSize);
        }
        if (current->next != NULL) {
            if (newBlockSize < currentBlockSize) {
                // Resizes current->next memory block and set the new index
                if (adress + currentBlockSize == current->next->index) {
                    current->next->index = adress + newBlockSize;
                    current->next->freeMemory += currentBlockSize - newBlockSize;
                    return list;
                }
                // Allocs a new node in the list with the remnant free memory
                new = malloc(sizeof(Node));
                validAlloc(new);
                new->index = adress + newBlockSize;
                new->freeMemory = currentBlockSize - newBlockSize;
                new->next = current->next;
                new->next->prev = new;
                current->next = new;
                new->prev = current;

                return list;
            }
            // case: the current->next index is free and right in the front of the block that is being reallocated
            // and if the next block memory can be used for the new allocation
            if ((adress + currentBlockSize == current->next->index) && (currentBlockSize + current->next->freeMemory >= newBlockSize)) {
                if (currentBlockSize + current->next->freeMemory > newBlockSize) {
                    current->next->index = adress + newBlockSize;
                    current->next->freeMemory = current->next->freeMemory - (newBlockSize - currentBlockSize);
                    
                    return list;
                }
                // when the memory sum gave in the 'if' above it's equal to newBlocksize
                // proceeds freeing the current->next memory
                new = current->next;
                // Avoids invalid memory access that leads to segmentation fault
                if (new->next == NULL) {
                    current->next = NULL;
                    free(new);

                    return originFinder(current);
                }

                current->next = new->next;
                new->next->prev = current;
                free(new);
                return originFinder(current);
            }
            
        }
    }
    if (current->index > adress) {
        if (newBlockSize < currentBlockSize) {
            // Resizes current memory block and set the new index
            if (adress + currentBlockSize == current->index) {
                current->index = adress + newBlockSize;
                current->freeMemory += currentBlockSize - newBlockSize;
                return list;
            }

            // if the above condition isn't satisfied, alloc a new block with the remnant free memory
            new = malloc(sizeof(Node));
            validAlloc(new);
            new->index = adress + newBlockSize;
            new->next = current;
            new->freeMemory = currentBlockSize - newBlockSize;
            if (current->prev == NULL)
                new->prev = NULL;
            else {
                new->prev = current->prev;
                new->prev->next = new;
            }
            current->prev = new;

            return originFinder(current);
        }
        // case: the current index is free and right in the front of the block that is being reallocated
        // and if the current block memory can be used for the new allocation
        if ((adress + currentBlockSize == current->index) && (currentBlockSize + current->freeMemory >= newBlockSize)) {
            if (currentBlockSize + current->freeMemory > newBlockSize) {
                current->index = adress + newBlockSize;
                current->freeMemory = current->freeMemory - (newBlockSize - currentBlockSize);
                return originFinder(current);
            }

            // Proceeds in this way taking care of possible accesses in invalid memory
            // Only executed when currentBlockSize + current->freeMemory == newBlockSize
            // and deallocs the current block
            if (current->next == NULL) {
                if (current->prev == NULL) {
                    free(current);
                    return NULL;
                }

                current->prev->next = NULL;
                new = current->prev;
                free(current);
                return originFinder(current);
            }

            if (current->prev == NULL) {
                current->next->prev = NULL;
                new = current->next;
                free(current);
                return new;
            }

            current->prev->next = current->next;
            current->next->prev = current->prev;
            new = current->prev;
            free(current);
            return originFinder(new);
        }

    }
    list = memBlockDealloc(list, adress, currentBlockSize);
    return memBlockAlloc(list, newBlockSize);

}

// Destructs list
void removeList(n_ptr list)
{
    if (list == NULL)
        return;

    n_ptr current, temp;

    current = list;
    temp = list;

    // Traverses the list setting free all nodes
    while (temp->next != NULL) {
        current = temp;
        temp = temp->next;
        free(current);
    }
    free(temp);
}

void validAlloc(n_ptr node) 
{
    if (node == NULL) {
        exit(1);
    }
    return;
}


// traverse the list looking for some node with the index < adress
// Used just to reduce the number of lines in the code
n_ptr currentReturn(n_ptr list, int adress) 
{
    n_ptr current = list;

    // Traverses list looking for a node that will be used in function that had called this function
    while (1) {
        if (current->next == NULL) {
            break;
        }
        else if (current->next->index < adress) {
            current = current->next;
        }
        else {
            return current;
        }
    }   

    return current;
}

// Traverses list looking for the first Node, leaving from the node passed in the function
n_ptr originFinder(n_ptr node)
{
    n_ptr current = node;
                        
    while (current->prev != NULL) {
        current = current->prev;
    }

    return current;

}
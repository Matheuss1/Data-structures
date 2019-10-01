#include <stdlib.h>
#include <stdio.h>
#include "lista.h"


n_ptr new_list()
{
    return NULL;
}


n_ptr push(n_ptr list, int index, int freeMemory)
{
    n_ptr new;
    new = malloc(sizeof(Node));
    
    new->freeMemory = freeMemory;
    new->index = index;
    new->next = list;
    new->prev = NULL;

    if (list != NULL)
        list->prev = new;
        
    return new;
}


n_ptr memBlockAlloc(n_ptr list, int size)
{
    n_ptr current, temp;
    temp = list;
    for (current = list; current != NULL; current = current->next) {
        if (current->freeMemory <= size) 
            if (current->freeMemory < temp->freeMemory)
                temp = current;
    }
    
    temp->freeMemory = temp->freeMemory - size;
    
    if (temp->freeMemory == 0) {
        freeMemBlock(temp);
        return list;
    }
    
    temp->index = temp->index + size;

    return list;
}


n_ptr memBlockDealloc(n_ptr list, int adress, int remotionSize)
{
    n_ptr current, new;
    current = list;

    while (1) {
        if (current->next == NULL) {
            break;
        }
        else if (current->next->index < adress) {
            current = current->next;
        }
        else {
            break;
        }
    }

    if (current->next == NULL) {
        if (current->index + current->freeMemory == adress) {
            current->freeMemory += remotionSize;
        }
        else {
            new = malloc(sizeof(Node));
            new->index = adress;
            new->freeMemory = remotionSize;
            new->next = NULL;
            new->prev = current;
            current->next = new;
        }
    }
    else {
        if (current->next->index == remotionSize + adress) {
            current->next->index = adress;
            current->next->freeMemory += remotionSize;
        }
        
        if (current->index + current->freeMemory == adress) {
            current->freeMemory += remotionSize;

            if (current->next->index == current->index + current->freeMemory) {
                current->freeMemory += current->next->freeMemory;
                current->next = current->next->next;
                free(current->next->prev);
                current->next->prev = current;
            }
        }
    }

    while (current->prev != NULL) {
        current = current->prev;
    }

    return current;
}

n_ptr memRealloc(n_ptr list, int currentBlockSize, int newBlockSize)
{
    if (newBlockSize < currentBlockSize) {
        
    }
}



void freeMemBlock(n_ptr node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
}
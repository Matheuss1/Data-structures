#include <stdlib.h>
#include "lista.h"


n_ptr new_list()
{
    return NULL;
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


n_ptr push(n_ptr list, int index, int freeMemory)
{
    n_ptr new;
    new = malloc(sizeof(n_ptr));
    
    new->freeMemory = freeMemory;
    new->index = index;
    new->next = list;
    new->prev = NULL;

    if (list != NULL)
        list->prev = new;
        
    return new;
}


n_ptr memBlockDealloc(n_ptr list, int adress, int remotionSize)
{
    n_ptr current, new;
    int newIndex;

    for (current = list; current->index > current->next->index || current->next != NULL; current = current->next)

    if (current->next == NULL) {
        if (current->index + current->freeMemory == adress) {
            current->freeMemory += remotionSize;
        }
        else {
            new = malloc(sizeof(n_ptr));
            new->index = adress;
            new->freeMemory = remotionSize;
            new->next = NULL;
            new->prev = current;
            current->next = new;
        }
    }
    else {
        
    }
}


void freeMemBlock(n_ptr node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
}
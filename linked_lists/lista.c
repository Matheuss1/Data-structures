#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

n_ptr sortFirstLink(n_ptr list);

n_ptr new_list(int heapSize)
{
    n_ptr list;
    list = malloc(sizeof(Node));
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

    while(current != NULL) {
        if (current->freeMemory >= size) {
            if (!aux) {
                temp = current;
                aux = 1;
            }
            if (current->freeMemory < temp->freeMemory)
                temp = current;
        }
        current = current->next;
    }

    if (temp->freeMemory - size == 0) {
        if (temp->next != NULL)
            temp->next->prev = temp->prev;
        if (temp->prev != NULL)
            temp->prev->next = temp->next;
        
        free(temp);
    }
    else {
        temp->index += size;
        temp->freeMemory -= size;
    }

    return sortFirstLink(list);
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
            if (current->next->index == adress) {
                current->freeMemory += current->next->freeMemory;
                if (current->next->next == NULL) {
                    free(current->next);
                    current->next = NULL;
                }
                else {
                    current->next = current->next->next;
                    free(current->next->prev);
                    current->next->prev = current;
                }
            }
        }
        else {
            new = malloc(sizeof(Node));
            new->index = adress;
            new->freeMemory = remotionSize;
            new->next = current->next;
            new->prev = current;
            current->next = new;
        }
    }

    while (current->prev != NULL) {
        current = current->prev;
    }

    return sortFirstLink(list);
}


//TODO: problemas de realocação que levam a valores errados do heap
n_ptr memRealloc(n_ptr list, int adress, int currentBlockSize, int newBlockSize)
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
    // TODO: existe possibilidade de realocar para um tamanho 0??
    if (current->next == NULL) {
        if (newBlockSize < currentBlockSize) {
            new = malloc(sizeof(Node));
            new->index = adress + newBlockSize;
            new->freeMemory = currentBlockSize - newBlockSize;
            new->next = NULL;
            new->prev = current;
        }
        else {
            if (current->index + current->freeMemory == adress) {
                current->freeMemory += currentBlockSize;
            }
            else {
                new = malloc(sizeof(Node));
                new->index = adress;
                new->freeMemory = currentBlockSize;
                new->next = NULL;
                new->prev = current;
                current->next = new;

                memBlockAlloc(list, newBlockSize);
            }
        }
    }
    else {
        if (newBlockSize < currentBlockSize) {
            if (adress + currentBlockSize == current->next->index) {
                new = current->next;
                new->index = adress + newBlockSize;
                new->freeMemory += currentBlockSize - newBlockSize;
            }
            else {
                new = malloc(sizeof(Node));
                new->index = adress + newBlockSize;
                new->freeMemory += currentBlockSize - newBlockSize;
                new->next = current->next;
                current->next->prev = new;
                current->next = new;
            }
        }
        else {
            new = malloc(sizeof(Node));
            new->index = adress;
            new->freeMemory = currentBlockSize;
            new->next = current->next;
            new->prev = current;
            current->next->prev = new;
            current->next = new;

            memBlockAlloc(list, newBlockSize);
   
        }
    }

    return sortFirstLink(list);

}



void freeMemBlock(n_ptr node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
}


n_ptr sortFirstLink(n_ptr list) {
    if ( (list->next == NULL) || (list->next->index > list->index) )
        return list;
    
    n_ptr current, temp, newList;
    newList = list->next;
    for (current = list; current != NULL; current = current->next) {
        if (current->index < list->index) {
            temp = current;
        }
    }

    if (temp->next == NULL) {
        list->next->prev = NULL;
        list->prev = temp;
        list->next = NULL;
        temp->next = list;
        return newList;
    }


    list->next->prev = NULL;
    list->next = temp->next;
    list->prev = temp;
    temp->next = list;
    list->next->prev = list;
    return newList;
}
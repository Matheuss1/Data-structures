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
            if ( (current->freeMemory) < (temp->freeMemory) )
                temp = current;
        }
        current = current->next;
    }

    if (temp->freeMemory - size == 0) {
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
    else {
        temp->index += size;
        temp->freeMemory -= size;
    }

    return list;
}


n_ptr memBlockDealloc(n_ptr list, int adress, int remotionSize)
{
    n_ptr new, current;

    if (list == NULL) {
        new = malloc(sizeof(Node));
        new->index = adress;
        new->freeMemory = remotionSize;
        new->next = NULL;
        new->prev = NULL;
        return new;
    }

    current = list;
    while(1) {
        if (current->next == NULL)
            break;
        else if (current->next->index < adress)
            current = current->next;
        else
            break;
    }

    if ( (current->index) > adress ) {
        if ( (adress + remotionSize) == current->index) {
            current->index = adress;
            current->freeMemory += remotionSize;

            if (current->prev != NULL) {
                if ( (current->prev->index + current->prev->freeMemory) == adress) {
                    current->prev->freeMemory += current->freeMemory;
                    current->prev->next = current->next;

                    if (current->next != NULL)
                        current->next->prev = current->prev;
                    
                    new = current->prev;
                    free(current);
                    current = new;
                    while (current->prev != NULL) {
                        current = current->prev;
                    }

                    return current;
                }
                else {
                    while (current->prev != NULL)
                    {
                        current = current->prev;
                    }
                    return current;
                }
            }

            return current;

        }
        
        if (current->prev != NULL) {
            if ( (current->prev->index + current->prev->freeMemory) == adress )
                current->prev->freeMemory += remotionSize;
            else {
                new = malloc(sizeof(Node));
                new->index = adress;
                new->next = current;
                new->prev = current->prev;
                new->prev->next = new;
                current->prev = new;
            }

            while (current->prev != NULL) {
                current = current->prev;
            }
            return current;
        }

        new = malloc(sizeof(Node));
        new->index = adress;
        new->freeMemory = remotionSize;
        new->next = current;
        new->prev = NULL;
        current->prev = new;
        return new;
    }

    if ( (current->index) < adress ) {
        if ( (current->index + current->freeMemory) == adress ) {
            current->freeMemory += remotionSize;

            if (current->next == NULL) {            
                while (current->prev != NULL) {
                    current = current->prev;
                }
                return current;
            }

            if ( (adress + remotionSize) == current->next->index ) {
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

                while (current->prev != NULL) {
                    current = current->prev;
                }
                return current;
            }

            while (current->prev != NULL) {
                current = current->prev;
            }
            return current;
        }

        if (current->next != NULL) {
            if ( (adress + remotionSize) == current->next->index) {
                current->next->index = adress;
                current->next->freeMemory += remotionSize;

                while (current->prev != NULL) {
                    current = current->prev;
                }
                return current;
            }

            new = malloc(sizeof(Node));
            new->index = adress;
            new->freeMemory = remotionSize;
            new->next = current->next;
            new->next->prev = new;
            new->prev = current;
            current->next = new;

            while (current->prev != NULL) {
                current = current->prev;
            }
            return current;
        }

        new = malloc(sizeof(Node));
        new->index = adress;
        new->freeMemory = remotionSize;
        new->next = NULL;
        new->prev = current;
        current->next = new;

        while (current->prev != NULL) {
            current = current->prev;
        }
        return current;

    }

    return list;
}


//TODO: problemas de realocação que levam a valores errados do heap
n_ptr memRealloc(n_ptr list, int adress, int currentBlockSize, int newBlockSize)
{

    n_ptr current, new;
    current = list;

    // Can only realloc blocks < currentBlockSize
    if (current == NULL) {
        return memBlockDealloc(list, adress + newBlockSize, currentBlockSize - newBlockSize);
    }

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

    if (current->index < adress) {
        if (current->next == NULL) {
            if (newBlockSize < currentBlockSize) {
                new = malloc(sizeof(Node));
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
                if (adress + currentBlockSize == current->next->index) {
                    current->next->index = adress + newBlockSize;
                    current->next->freeMemory += currentBlockSize - newBlockSize;
                    return list;
                }
                new = malloc(sizeof(Node));
                new->index = adress + newBlockSize;
                new->freeMemory = currentBlockSize - newBlockSize;
                new->next = current->next;
                new->next->prev = new;
                current->next = new;
                new->prev = current;

                return list;
            }
            if ((adress + currentBlockSize == current->next->index) && (currentBlockSize + current->next->freeMemory >= newBlockSize)) {
                if (currentBlockSize + current->next->freeMemory > newBlockSize) {
                    current->next->index = adress + newBlockSize;
                    current->next->freeMemory = current->next->freeMemory - (newBlockSize - currentBlockSize);
                    
                    return list;
                }
                new = current->next;
                if (new->next == NULL) {
                    current->next = NULL;
                    free(new);

                    while (current->prev != NULL)
                    {
                        current = current->prev;
                    }
                    return current;
                }

                current->next = new->next;
                new->next->prev = current;
                free(new);
                while (current->prev != NULL)
                {
                    current = current->prev;
                }
                return current;
            }
            
        }
    }
    if (current->index > adress) {
        if (newBlockSize < currentBlockSize) {
            if (adress + currentBlockSize == current->index) {
                current->index = adress + newBlockSize;
                current->freeMemory += currentBlockSize - newBlockSize;
                return list;
            }

            new = malloc(sizeof(Node));
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

            while (current->prev != NULL)
            {
                current = current->prev;
            }
            return current;
        }
        if ((adress + currentBlockSize == current->index) && (currentBlockSize + current->freeMemory >= newBlockSize)) {
            if (currentBlockSize + current->freeMemory > newBlockSize) {
                current->index = adress + newBlockSize;
                current->freeMemory = current->freeMemory - (newBlockSize - currentBlockSize);
                while (current->prev != NULL)
                {
                    current = current->prev;
                }
                return current;
            }
            if (current->next == NULL) {
                if (current->prev == NULL) {
                    free(current);
                    return NULL;
                }

                current->prev->next = NULL;
                new = current->prev;
                free(current);
                while (new->prev != NULL)
                {
                    new = new->prev;
                }
                return new;
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
            while (new->prev != NULL)
            {
                new = new->prev;
            }
            return new;

        }

    }
    list = memBlockDealloc(list, adress, currentBlockSize);
    return memBlockAlloc(list, newBlockSize);

}


void freeMemBlock(n_ptr node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
}
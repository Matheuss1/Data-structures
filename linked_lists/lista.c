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
                current->freeMemory += remotionSize;
            
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
n_ptr memRealloc(n_ptr list, int adress, int currentBlockSize, int newBlockSize, int heapSize)
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

    if


}


void freeMemBlock(n_ptr node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
}


// n_ptr sortFirstLink(n_ptr list) {
//     if ( (list == NULL) || (list->next == NULL) || (list->next->index > list->index) )
//         return list;
    
//     n_ptr current, temp, newList;
//     newList = list->next;
//     for (current = list; current != NULL; current = current->next) {
//         if (current->index < list->index) {
//             temp = current;
//         }
//     }

//     if (temp->next == NULL) {
//         list->next->prev = NULL;
//         list->prev = temp;
//         list->next = NULL;
//         temp->next = list;
//         return newList;
//     }

//     list->next->prev = NULL;
//     list->next = temp->next;
//     list->prev = temp;
//     temp->next = list;
//     list->next->prev = list;
//     return newList;
// }
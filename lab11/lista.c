#include <stdlib.h>
#include "lista.h"


p_node newList(int size)
{
    return NULL;
}


p_node pushList(p_node list, int pos, char marker, char marker2)
{
    p_node node = malloc(sizeof(Node));
    if (node == NULL)
        exit(1);
    node->value = pos;
    node->next = list;
    node->marker = marker;
    node->marker2 = marker2;

    return node;
}


p_node iterator_(p_node *list, int floor)
{
    return list[floor];
}


p_node nextPos(p_node iterator)
{
    return iterator->next;
}


int getNodeValue(p_node node)
{
    return node->value;
}


int getMarker(p_node node)
{
    return node->marker;
}


int getMarker2(p_node node)
{
    return node->marker2;
}

int isListEmpty(p_node list)
{
    if (list == NULL)
        return 1;
    
    return 0;
}
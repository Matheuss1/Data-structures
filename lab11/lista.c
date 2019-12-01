#include <stdlib.h>
#include "lista.h"


p_node newList(int size)
{
    return NULL;
}


p_node pushList(p_node list, int pos, int marker)
{
    p_node node = malloc(sizeof(Node));
    if (node == NULL)
        exit(1);
    node->visited = 0;
    node->value = pos;
    node->counter = 9999999;
    node->next = list;
    node->marker = marker;

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


int isVisited(p_node node)
{
    if (node->visited == 1)
        return 1;
    
    return 0;
}


void setAsVisited(p_node node)
{
    node->visited = 1;
}


int getNodeValue(p_node node)
{
    return node->value;
}


void setCounter(p_node node, int value)
{
    node->counter = value;
}


int counterValue(p_node node)
{
    return node->counter;
}


int isListEmpty(p_node list)
{
    if (list == NULL)
        return 1;
    
    return 0;
}
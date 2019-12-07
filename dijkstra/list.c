#include <stdlib.h>
#include "list.h"


p_node newList(int size)
{
    return NULL;
}


p_node pushList(p_node list, int pos, int weight)
{
    p_node node = malloc(sizeof(Node));
    if (node == NULL)
        exit(1);

    node->v = pos;
    node->weight = weight;

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


int getWeight(p_node node)
{
    return node->weight;
}


int getVal(p_node node)
{
    return node->v;
}

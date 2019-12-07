#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int v, weight;
    struct Node *next;
} Node;

typedef Node* p_node;

p_node newList(int size);

p_node pushList(p_node list, int pos, int weight);

int getWeight(p_node node);

int getVal(p_node node);

int isEmpty(p_node list);

#endif
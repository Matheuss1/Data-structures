#ifndef LISTA_H
#define LISTA_H

#define TRUE 1
#define FALSE 0

typedef struct Node {
    int value;
    int visited;
    int counter;
    int marker;
    struct Node *next;
} Node;

typedef Node* p_node;

p_node newList(int size);

p_node pushList(p_node list, int pos, int marker);

p_node iterator_(p_node *list, int floor);

p_node nextPos(p_node iterator);

int isVisited(p_node node);

int getNodeValue(p_node node);

void setCounter(p_node node, int value);

void setAsVisited(p_node node);

int counterValue(p_node node);

int isListEmpty(p_node list);

#endif
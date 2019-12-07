#ifndef LISTA_H
#define LISTA_H

typedef struct Node {
    int value;
    char marker;
    char marker2;
    struct Node *next;
} Node;

typedef Node* p_node;

p_node newList();

p_node newNode(int value, int marker, int marker2);

p_node pushList(p_node list, int pos, char marker, char marker2);

p_node iterator_(p_node *list, int floor);

p_node nextPos(p_node iterator);

int getNodeValue(p_node node);

int getMarker(p_node node);

int getMarker2(p_node node);

int isListEmpty(p_node list);

void removeList(p_node list);

#endif
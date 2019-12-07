#ifndef LISTA_H
#define LISTA_H

typedef struct Node {
    int value;
    char marker;
    char marker2;
    struct Node *next;
} Node;

typedef Node* p_node;

// creates a new empty list
p_node newList();

// push a new link in a list gave
p_node pushList(p_node list, int pos, char marker, char marker2);

// returns an iterator for the begin of a linked list
p_node iterator_(p_node *list, int floor);

// advances one link in the iterator gave
p_node nextPos(p_node iterator);

// returns the node value
int getNodeValue(p_node node);

// returns the node marker representing an elevator
int getMarker(p_node node);

// returns the node marker representing if the lift was going down or going up
int getMarker2(p_node node);

// removes the list and free the memory used by the links in the list
void removeList(p_node list);

#endif
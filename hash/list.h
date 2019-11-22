#ifndef LIST_H
#define LIST_H

#define MAX_SIZE 40001

typedef struct {
    char sequence[MAX_SIZE];
    int index;
} Node;

typedef Node* p_node;

#endif
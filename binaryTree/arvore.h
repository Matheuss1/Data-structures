#ifndef ARVORE_H
#define ARVORE_H

typedef struct Node {
    char data;
    struct Node *left, *right;
} Node;

typedef Node* n_ptr;

n_ptr tree(char data, n_ptr left, n_ptr right);



#endif

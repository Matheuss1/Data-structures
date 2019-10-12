#ifndef PILHA_H
#define PILHA_H

// Linked list 
typedef struct Node {
    char num;
    struct Node* prox;
} Node;

typedef Node* n_ptr;    // Node pointer

// Stack implented using linked lists
typedef struct{
    n_ptr top;
} Stack;

typedef Stack* st_ptr;

st_ptr newStack();
void push(st_ptr stack, char number) ;
char pop(st_ptr stack);
char top(st_ptr stack);
int isEmpty(st_ptr stack);

#endif

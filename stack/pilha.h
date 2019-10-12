#ifndef PILHA_H
#define PILHA_H

// Linked list 
typedef struct Node {
    char num;
    struct Node* next;
} Node;

typedef Node* n_ptr;    // Node pointer

// Stack implented using linked lists
typedef struct{
    n_ptr top;
} Stack;

typedef Stack* st_ptr;

// Creates a new stack
st_ptr newStack();

// add item to stack
void push(st_ptr stack, char number) ;

// removes the item in the stack top
char pop(st_ptr stack);

// just shows the stack top
char top(st_ptr stack);

// returns 1 if the stack is empty, otherwise returns 0
int isEmpty(st_ptr stack);

// clear stack without removing it
void clearStack(st_ptr stack);

// totally removes the stack
void removeStack(st_ptr stack);

#endif

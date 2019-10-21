#ifndef ARVORE_H
#define ARVORE_H


// data structure to create an expression tree
// this data accepts both int and char in the data fields
typedef struct Node {
    char data_char;
    int data_int;
    struct Node *left, *right;
} Node;

typedef Node* r_ptr;

// returns a new root with memory already allocated
r_ptr tree();

// converts an infix 
r_ptr expression(int counter);

// does an math operation between two number with a gave operator
int mathOperation(int a, int b, char operator);

// simplifies an expression tree
r_ptr calc(r_ptr expression);

// prints expression tree in order
void inorder(r_ptr eTree);

// deallocs the memory used to construct the tree
void treeDestruct(r_ptr eTree);


#endif

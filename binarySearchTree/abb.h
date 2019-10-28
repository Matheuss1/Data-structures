#ifndef ABB_H
#define ABB_H

#define SIZE 9

typedef struct Node {
    char message[SIZE];
    int id;
    struct Node *left, *right;
} Node;

// Root pointer
typedef Node* r_ptr;

// Creates a new tree pointing to NULL
r_ptr tree();

// Creates a new tree node 
r_ptr newNode(int packageId, char textPackage[]);

// Adds a new node to tree
r_ptr addNode(r_ptr treeRoot, int id, char package[]);

// Prints the the in sorted order
void inOrder(r_ptr treeRoot);

// Frees the allocated memory
void treeDestruct(r_ptr bTree);

#endif

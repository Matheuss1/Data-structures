#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"

r_ptr tree()
{
    return NULL;
}


r_ptr newNode(int packageId, char textPackage[])
{
    r_ptr new = malloc(sizeof(Node));
    if (new == NULL)
        exit(1);

    new->left = NULL;
    new->right = NULL;

    // copies the textPackage to struct char data field
    // and also copies the id to id field
    strcpy(new->message, textPackage);
    new->id = packageId;

    return new;
}


r_ptr addNode(r_ptr treeRoot, int id, char package[])
{
    // if there is no more paths to follow in the tree
    // a node is add as a new leaf
    if (treeRoot == NULL) {
        r_ptr temp;
        temp = newNode(id, package);

        return treeRoot = temp;
    }

    // greater id goes to right side of root,
    // while lower id goes to left
    if (treeRoot->id > id)
        treeRoot->left = addNode(treeRoot->left, id, package);
    
    if (treeRoot->id < id)
        treeRoot->right = addNode(treeRoot->right, id, package);
            
    return treeRoot;
}


void inOrder(r_ptr treeRoot)
{
    if (treeRoot == NULL)
        return;
    
    inOrder(treeRoot->left);

    printf("%s", treeRoot->message);

    inOrder(treeRoot->right);
}


void treeDestruct(r_ptr bTree)
{
    if (bTree == NULL) {
        return;
    }
    
    treeDestruct(bTree->left);
    treeDestruct(bTree->right);

    free(bTree);
}
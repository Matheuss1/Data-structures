#include "arvore.h"

n_ptr tree(char data, n_ptr left, n_ptr right)
{
    n_ptr new = malloc(sizeof(Node));
    new->data = data;
    new->left = left;
    new->right = right;

    return new;
}



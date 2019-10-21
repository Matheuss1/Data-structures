#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

// Creates a root
r_ptr tree()
{
    r_ptr new = malloc(sizeof(Node));
    if (new == NULL)
        exit(1);
    new->data_char = -10;
    new->data_int = 0;
    new->left = NULL;
    new->right = NULL;

    return new;

}


// Converts a math expression like ( a + ( b * ( c / 3 ) ) )
// to a binary tree where each node is an operator or an operand
r_ptr expression(int counter)
{
    // temp array to read the input and starts the tree
    char temp[SIZE];
    r_ptr root = tree();

    scanf(" %s", temp); 
    
    if (temp[0] == '(') {
        root->left = expression(counter + 1);
        
        // this code block is used because the initial recursive call creates
        // an extra node and if this block of code isn't used
        // wrong reads from input occurs
        if (counter == 0) {
            r_ptr tempRoot;
            tempRoot = root->left;
            free(root);
            return tempRoot;
        }
        
        // reads the operator used in root
        scanf(" %s", temp);
        while(temp[0] == ')' && temp[0] != '\n') {
            scanf("%s", temp);
        }

        // adds the operator to root
        root->data_char = temp[0];
        
        scanf(" %s", temp);
        
        // always that a read starts with '(' a new recursive call is made, because
        // this means that a "new expression" was started
        if (temp[0] == '(') {
                root->right = expression(counter + 1);
            return root;
        }

        // verifies the data type of root children, if is an int, so we use
        // the int field in the data structure, otherwise is used the char data field
        if ( (temp[0] >= '0' && temp[0] <= '9') || (temp[0] == '-' && (temp[1] >= '0' && temp[1] <= '9') ) ) {
            r_ptr new = tree();
            new->data_int = atoi(temp);
            root->right = new;

            return root; 
        }
        else {
            r_ptr new = tree();
            new->data_char = temp[0];

            root->right = new;

            return root;
        }
        
    }

    // starts the children nodes with values instead an operator
    r_ptr new_left = tree();
    r_ptr new_right = tree();
    
    // verifies the data type of root children, if is an int, so we use
    // the int field in the data structure, otherwise is used the char data field
    if ( (temp[0] >= '0' && temp[0] <= '9') || (temp[0] == '-' && (temp[1] >= '0' && temp[1] <= '9') ) ) {
        new_left->data_int = atoi(temp);
        root->left = new_left;

        scanf(" %s", temp);
        root->data_char = temp[0];

        scanf(" %s", temp);

        // verifies if this root child calls to another expression ---end of left child 
        if (temp[0] == '(') {
            root->right = expression(counter + 1);
            free(new_right);
            return root;
        }
        else {
            // almost the same operations above
            if ( (temp[0] >= '0' && temp[0] <= '9') || (temp[0] == '-' && (temp[1] >= '0' && temp[1] <= '9') ) ) {
                new_right->data_int =  atoi(temp);
                root->right = new_right;

                return root;
            }
            else {
                new_right->data_char = temp[0];
                root->right = new_right;

                return root;        
            }
        }
    }

    // if left child is unknown, so this block is executed
    new_left->data_char = temp[0];
    root->left = new_left;

    scanf(" %s", temp);
    root->data_char = temp[0];

    scanf(" %s", temp);
    if (temp[0] == '(') {
        root->right = expression(counter + 1);
        free(new_right);
        return root;
    }

    if ( (temp[0] >= '0' && temp[0] <= '9') || (temp[0] == '-' && (temp[1] >= '0' && temp[1] <= '9') ) ) {
        new_right->data_int = atoi(temp);
        root->right = new_right;

        return root;
    }

    new_right->data_char = temp[0];
    root->right = new_right;

    return root;
}


// prints the expression gave from tree in order
void inorder(r_ptr eTree)
{
    if (eTree == NULL)
        return;
    
    if (eTree->data_char == '+' || eTree->data_char == '-' ||
        eTree->data_char == '*' || eTree->data_char == '/')
        printf("( ");

    inorder(eTree->left);

    // verifies if should print an int or an unknow value
    if (eTree->data_char == -10)
        printf("%d ", eTree->data_int);
    else
        printf("%c ", eTree->data_char);

    inorder(eTree->right);

    if (eTree->data_char == '+' || eTree->data_char == '-' ||
        eTree->data_char == '*' || eTree->data_char == '/')
        printf(") ");

}


r_ptr calc(r_ptr expression)
{
    if (expression->data_char != '+' && expression->data_char != '-' &&
        expression->data_char != '*' && expression->data_char != '/')
        return expression;
    
    r_ptr a, b;

    a = calc(expression->left);
    b = calc(expression->right);

    if (a->data_char == -10 && b->data_char == -10) {
        expression->data_int = mathOperation(a->data_int, b->data_int, expression->data_char);
        expression->data_char = -10;
        expression->left = expression->right = NULL;
        free(a);
        free(b);

        return expression;
    }

    return expression;

}


int mathOperation(int a, int b, char operator)
{
    if (operator == '+')
        return a + b;
    if (operator == '-')
        return a - b;
    if (operator == '*')
        return a * b;

    return a / b;
}


void treeDestruct(r_ptr eTree)
{
    if (eTree == NULL) {
        return;
    }
    
    treeDestruct(eTree->left);
    treeDestruct(eTree->right);

    free(eTree);
}
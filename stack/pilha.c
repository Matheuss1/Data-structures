#include <stdlib.h>
#include <stdio.h>

#include "pilha.h"

st_ptr newStack() 
{
    st_ptr stack = malloc(sizeof(Stack));
    if (stack == NULL)
        exit(1);

    stack->top = NULL;
    return stack;
}


void push(st_ptr stack, char number) 
{
    n_ptr new = malloc(sizeof(Node));
    if (stack == NULL)
        exit(1);

    new->num = number;
    new->next = stack->top;
    stack->top = new;
}


char pop(st_ptr stack)
{
    n_ptr top = stack->top;
    
    char number = top->num;
    stack->top = stack->top->next;
    free(top);
    return number;
}


char top(st_ptr stack)
{
    if (stack->top == NULL)
        return -1;
    
    n_ptr top = stack->top;
    return top->num;
}


int isEmpty(st_ptr stack)
{
    if (top(stack) == -1)
        return 1;
    
    return 0;
}


void clearStack(st_ptr stack)
{
    while(!isEmpty(stack))
        pop(stack);
}

void removeStack(st_ptr stack) 
{
    clearStack(stack);
    free(stack);
}


#include <stdlib.h>


#include "pilha.h"

st_ptr newStack() 
{
    st_ptr stack = malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}


void push(st_ptr stack, char number) 
{
    n_ptr new = malloc(sizeof(Node));
    new->num = number;
    new->prox = stack->top;
    stack->top = new;
}


char pop(st_ptr stack)
{
    n_ptr top = stack->top;
    char number = top->num;
    stack->top = stack->top->prox;  // TODO: cuidado para não acessar NULL
    free(top);
    return number;
}


char top(st_ptr stack)
{
    if (stack == NULL)
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

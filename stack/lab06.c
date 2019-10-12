#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha.h"

#define SIZE 1000
void teste(st_ptr stack);
int main()
{
   int m, n;

   scanf("%d", &m);

   int i;
   char digits[SIZE];

   for (i = 0; i < m; i++) {
      st_ptr greatestNumber = newStack();
      scanf("%s %d", digits, &n); // cuidado para a string não ler o \n
      teste(greatestNumber);
      printf("%d", pop(greatestNumber));


   }

   return EXIT_SUCCESS;
}


void removeDigit(char digits[], st_ptr stack)
{
   
   push(stack, 2);
   push(stack, 3);
}
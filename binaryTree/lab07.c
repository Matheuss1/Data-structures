#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

#define SIZE 1000


int main()
{
   int m, i;
   char temp[SIZE];
   scanf("%d", &m);

   for (i = 0; i < m; i++) {
      r_ptr expressionTree;

      expressionTree = expression(0);
      scanf(" %[^\n]", temp);

      expressionTree = calc(expressionTree);

      inorder(expressionTree);
      printf("\n");

      treeDestruct(expressionTree);
   }

   return EXIT_SUCCESS;
}



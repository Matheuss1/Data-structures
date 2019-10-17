#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

#define SIZE 1000

int main()
{
   int m, i;
   char buffer[SIZE];
   n_ptr expression = tree(NULL, NULL, NULL);
   scanf("%d", &m);

   for (i = 0; i < m; i++) {
      scanf("%s", buffer);

   }

   return EXIT_SUCCESS;
}

n_ptr mathExpressionTree(char buffer[])
{
   n_ptr root;
   int counter = 1;

   for (int i = 0; i < strlen(buffer); i++) {

      if (buffer[i] == ' ')
         continue;

      if (buffer[i] == '(' && counter == 1) {
         root->left = mathExpressionTree(buffer[i + 2]);

         for (int j = i; j < strlen(buffer); j++) {
            if (buffer[j] == '(')
               counter += 1;
            
            if (buffer[j] == ')')
               counter -= 1;

            if (counter == 1) {
               root->data = buffer[j + 2];
               root->right = mathExpressionTree(buffer[j + 4]);
               return root;
            }

         }

         return root;
      }


      n_ptr leftNode;
      leftNode = malloc(sizeof(Node));
      leftNode->data = buffer[i];
      leftNode->left = leftNode->right = NULL;
      
      if (buffer[i + 4] != '(') {
         n_ptr rightNode;
         rightNode = malloc(sizeof(Node));
         rightNode->data = buffer[i + 4];
         rightNode->left = NULL;

         if (buffer[i + 4] == ')')
            rightNode->right = NULL;
         else
            rightNode->right = mathExpressionTree(buffer[i + 4]);

         return tree(buffer[i + 2], leftNode, rightNode);
      }

      return tree(buffer[i + 2], leftNode, mathExpressionTree(buffer[i + 3]));

      

      
   }
}

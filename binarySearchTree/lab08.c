#include <stdio.h>
#include <stdlib.h>

#include "abb.h"

int main()
{

   int id;
   char package[SIZE];
   r_ptr message = tree();

   // scanf the entries until read a zero for id
   while(1) {
      scanf("%d%*c", &id);
      if (id == 0)
         break;
         
      scanf("%[^\n]", package);
      
      // constructs the message tree
      message = addNode(message, id, package);
   }

   // prints the message reconstructed
   inOrder(message);
   printf("\n");

   // frees the alocated memory for the message tree
   treeDestruct(message);

   return EXIT_SUCCESS;
}

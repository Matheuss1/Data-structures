#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

int main()
{
   int n;
   char temp[MAX_SIZE];

   scanf("%d", &n);
   p_hash table = newHash(n);

   for (int i = 0; i < n; i++) {
      scanf(" %s", temp);
      push(table, temp, i); 
   }

   return EXIT_SUCCESS;

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

void quicksort(int *array, int l, int r);


int main()
{
   int n, i;

   scanf("%d", &n);

   p_hash table = newHash(n);

   int *sizeOfPatterns = malloc(n * sizeof(int));
   int *ocurrences = calloc(n, sizeof(int));
   char temp[MAX_SIZE];


   for (i = 0; i < n; i++) {
      scanf(" %s", temp);
      push(table, temp, i);

      sizeOfPatterns[i] = strlen(temp);
   }

   scanf(" %s", temp);

   // Sorts the pattern sizes to avoid the following functions to search for the same pattern size
   // more than one time
   quicksort(sizeOfPatterns, 0, n - 1);

   for (i = 0; i < n; i++) {
      if (i == 0) {
         searchPattern(table, ocurrences, sizeOfPatterns[i], temp);
         continue;
      }
      else if (sizeOfPatterns[i - 1] == sizeOfPatterns[i])
         continue;

      searchPattern(table, ocurrences, sizeOfPatterns[i], temp);
   }

   for (i = 0; i < n; i++)
      printf("%d\n", ocurrences[i]);

   for (i = 0; i < table->hashSize; i++) {
      if (table->hashTable[i] != NULL)
         free(table->hashTable[i]);
   }
   free(table->hashTable);
   free(table);
   free(sizeOfPatterns);
   free(ocurrences);
   return EXIT_SUCCESS;

}


int partition(int *array, int l, int r)
{
   int i, pivot = array[l], pos = r + 1;
   
   for (i = r; i >= l; i--) {
      if (array[i] >= pivot) {
         pos--;

         int temp = array[i];
         array[i] = array[pos];
         array[pos] = temp;
      }
   }

   return pos;
}


void quicksort(int *array, int l, int r)
{
   int i;
   
   if (r <= l)
      return;

   i = partition(array, l, r);
   quicksort(array, l, i - 1);
   quicksort(array, i + 1, r);
}
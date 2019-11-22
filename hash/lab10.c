#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

void quicksort(int *array, int l, int r);


int main()
{
   int n, i, j;

   scanf("%d", &n);

   // Creates a new hashTable
   p_hash table = newHash(n);

// ------------------------------------------------------------------------------------
   // This two arrays are used to store the size of patterns used and the number of 
   // ocurrences of each one in the big array with the text to be verified
   int *sizeOfPatterns = malloc(n * sizeof(int));
   if (sizeOfPatterns == NULL) 
      exit(1);

   int *ocurrences = calloc(n, sizeof(int));
   if (ocurrences == NULL) 
      exit(1);
//--------------------------------------------------------------------------------------

   char key[MAX_SIZE];  // Stores each pattern string and the biggest string in the end

   for (i = 0; i < n; i++) {
      scanf(" %s", key);

      push(table, key, i); // Each patter is read and added to the hashTable created

      sizeOfPatterns[i] = strlen(key);
   }

   scanf(" %s", key);

   quicksort(sizeOfPatterns, 0, n - 1);

// ------------------------------ SEARCH FOR OCURRENCES --------------------------------
   int len = strlen(key);
   int size, pos;

   for (i = 0; i < n; i++) {
      // Avoids a pattern size to be searched more than one time, verifying if the next
      // element in array has a different size
      while ((i + 1 != n) && sizeOfPatterns[i] == sizeOfPatterns[i + 1])
            i++;

      size = sizeOfPatterns[i];

      // temp is used to read and store each substring of key
      char *temp = malloc( (size + 1) * sizeof(char));
      if (temp == NULL)
         exit(1);

      for (j = 0; j <= len - size; j++) {
         strncpy(temp, &key[j], size);
         temp[size] = '\0';

         pos = searchPattern(table, temp);

         if (pos != -1)
            ocurrences[pos] += 1;

      }

      free(temp);
   }

   for (i = 0; i < n; i++)
      printf("%d\n", ocurrences[i]);

   removeHash(table);
   free(sizeOfPatterns);
   free(ocurrences);
   return EXIT_SUCCESS;

}

//----------------------------------- SORT FUNCTION ----------------------------------
// The quicksort is used to sort the size of patterns, thus is avoided a size
// of pattern to be searched more than one time
//-------------------------------------------------------------------------------------

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
//--------------------------------------------------------------------------------------

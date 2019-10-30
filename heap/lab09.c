#include <stdlib.h>
#include <stdio.h>

#include "heap.h"

int main()
{
   int n, m;

   scanf("%d", &n);

   for (int i = 0; i < n; ++i) {
      
      scanf("%d", &m);
      
      p_pq pq = pqueue(m);
      p_box box;
      char temp[ID_SIZE];

      for (int j = 0; j < m; j++) {
         scanf(" %s", temp);

         box = newBox(temp, i + 1);
         push(pq, box);

         if ((j + 1) % 5 == 0 && (j + 1 != m)) {
            median(pq);
         }
      }

      median(pq);
      heapDestruct(pq);
   }

   return EXIT_SUCCESS;

}

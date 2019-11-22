#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "heap.h"

void median(p_pq min, p_pq max);

int main()
{
   int n, m;

   scanf("%d", &n);

   for (int i = 0; i < n; ++i) {
      
      scanf("%d", &m);  // m is the size of each batch
      
      p_pq minHeap = newHeap(m);
      p_pq maxHeap = newHeap(m);

      p_box box, tempBox;
      
      char temp[ID_SIZE];

      for (int j = 0; j < m; j++) {
         scanf(" %s", temp);

         // Creating a new box to store the id and the group that it belongs
         box = newBox(temp, i + 1);

         /* This code was implemented in a way that the min heap always has the priority
            to store a box. If the min heap is empty, we directly push the new box to it,
            otherwise is verified if the id of the box in the top of the minHeap is lower than
            the the box waiting to be add in one of the heaps. If true, we pop the minHeap and add
            this item to the maxHeap, after that we push the new box to the minHeap*/
      //------------------------------------------------------------------------------------------------------------------------
         if (getSize(minHeap) == 0) {
            push(minHeap, box, 1);
         }
         else if ( strcmp( getId(box), getId( top(minHeap) ) ) > 0 ) {
            if (getSize(minHeap) - getSize(maxHeap) > 0) {
               tempBox = pop(minHeap, 1);

               push(maxHeap, tempBox, 2);
               push(minHeap, box, 1);
            }
            else
               push(minHeap, box, 1);
         }
         /* If the new box has an id lower than the box in the top of minHeap, we push this to
            maxHeap and if it has more elements than the minHeap, we pop the maxHeap and push the returned
            element in the minHeap */
         else {
            push(maxHeap, box, 2);

            if (getSize(maxHeap) - getSize(minHeap) > 0) {
               tempBox = pop(maxHeap, 2);

               push(minHeap, tempBox, 1);
            }
         }
      //---------------------------------------------------------------------------------------------------------------------
        
         if ((j + 1) % 5 == 0 && (j + 1 != m)) {
            median(minHeap, maxHeap);
         }
      }

      median(minHeap, maxHeap);
      heapDestruct(minHeap);
      heapDestruct(maxHeap);
   }

   return EXIT_SUCCESS;

}


// This print the median items, using the min and max heaps
void median(p_pq min, p_pq max)
{
   // if the min and max heap have the same size, so one of the median boxes is in
   // the maxHeap and another in the minHeap
   if (getSize(min) == getSize(max))
      printf("%d %s %s\n", getBatch( top(max) ), getId( top(max) ), getId( top(min) ));
   else
      printf("%d %s\n", getBatch( top(min) ), getId( top(min) ));
}

#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"
#include "queue.h"

p_node *bfs(p_graph tower, int towerSize);

int main()
{

   int m, n;
   int i, j;
   int x, y, w, z;

   scanf("%d", &m);

   for (i = 0; i < m; i++) {

      scanf("%d", &n);

      p_graph tower = newGraph((n * 2) + 1);
      p_node *parent;

      int currentFloor = n * 2;

      for (j = 0; j < n; j++) {
         scanf("%d%d%d%d", &x, &y, &w, &z);

         // Each vertex is inserted in the beginning of the linked list,
         // but to maintain the list in the sequence entered from input,
         // this vertexs are added from back to front in
         addVertex(tower, currentFloor - 1, currentFloor, 'P', 'P');
         if (y != 0)
            addVertex(tower, currentFloor + y * 2, currentFloor, 'A', 'Y');
         if (x != 0)
            addVertex(tower, currentFloor - x * 2, currentFloor, 'A', 'X');
      
         addVertex(tower, currentFloor, currentFloor * 2 - 1, 'P', 'P');
         if (z != 0)
            addVertex(tower, currentFloor - 1 + z * 2, currentFloor - 1, 'B', 'Z');
         if (w != 0)
            addVertex(tower, currentFloor - 1 - w * 2, currentFloor - 1, 'B', 'W');

         currentFloor -= 2;
      }

      addVertex(tower, -1, 0, 0, 0);
      parent = bfs(tower, n * 2 + 1);
      parent[0]->marker2 = 'i';
   }

   printf("a\n");
   return EXIT_SUCCESS;
}


p_node *bfs(p_graph tower, int towerSize)
{
   int size = towerSize + 1;

   p_node *parent = malloc(size * sizeof(p_node));
   p_queue queue = newQueue(size);

   int *visited = malloc(size * sizeof(int));

   parent[towerSize] = NULL;   // cuidado com o topo
   visited[towerSize] = 1;

   push(queue, pushList(NULL, towerSize, 'P', 'P'));

   while(!isEmpty(queue)) {
      p_node v = pop(queue);
      p_node iterator = getAdjacency(tower, getNodeValue(v));

      while (iterator != NULL) {
         int pos = getNodeValue(iterator);
         if (!visited[pos]) {
            parent[pos] = v;
            visited[pos] = 1;

            push(queue, iterator);

            if (getNodeValue(iterator) == -1)
               return parent;
         }

         iterator = nextPos(iterator);
      }
   }

   return parent;
}


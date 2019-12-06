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
            addVertex(tower, currentFloor + y * 2, currentFloor, 'A', 'Y');
            addVertex(tower, currentFloor - x * 2, currentFloor, 'A', 'X');
      
            addVertex(tower, currentFloor - 1 + z * 2, currentFloor - 1, 'B', 'Z');
            if (currentFloor - 1 - w * 2 < 0)
               addVertex(tower, currentFloor - w * 2, currentFloor - 1, 'B', 'W');
            else
               addVertex(tower, currentFloor - 1 - w * 2, currentFloor - 1, 'B', 'W');
         addVertex(tower, currentFloor, currentFloor - 1, 'P', 'P');

         currentFloor -= 2;
      }

      addVertex(tower, 0, 0, 0, 0);

      for (j = n * 2 ; j >= 0 ; j--) {
         p_node a = tower->adjList[j];

         while (a != NULL) {
            printf(" %d %c %c  |  ", a->value, a->marker, a->marker2);

            a = nextPos(a);
         }
         printf("\n");
      }


      parent = bfs(tower, n * 2 + 1);

      for (j = 0; parent[j] != NULL;) {
         printf("%c %c a\n", parent[j]->marker, parent[j]->marker2);
         j = parent[j]->value;
      }

      printf("\n");

      for (j = 0; j < n * 2 + 1; j++) {
         if (parent[j] == NULL)
            printf("null -- ");
         else
            printf("%c %c -- ", parent[j]->marker, parent[j]->marker2);
      }
      printf("\n");
      
   }

   return EXIT_SUCCESS;
}


p_node *bfs(p_graph tower, int towerSize)
{
   p_node *parent = calloc(towerSize, sizeof(p_node));
   p_queue queue = newQueue(towerSize);

   int *visited = calloc(towerSize, sizeof(int));
   visited[towerSize - 1] = 1;

   push(queue, pushList(NULL, towerSize - 1, 'P', 'P'));

   while(!isEmpty(queue)) {
      p_node v = pop(queue);
      p_node iterator = getAdjacency(tower, getNodeValue(v));

      while (iterator != NULL) {
         int pos = getNodeValue(iterator);

         if (!visited[pos]) {
            if (getMarker(iterator) == 'P') {
               push(queue, iterator);
               iterator = nextPos(iterator);  
               continue;       
            }

            visited[pos] = 1;
            parent[pos] = pushList(NULL, getNodeValue(v), getMarker(iterator), getMarker2(iterator));

            push(queue, iterator);

            if (getNodeValue(iterator) == 0)
               return parent;
         }

         iterator = nextPos(iterator);
      }
   }

   return parent;
}


21
19
15
13
11
7 - 8
8
6
4
2
0


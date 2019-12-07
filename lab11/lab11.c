#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"
#include "queue.h"

p_node *bfs(p_graph tower, int towerSize);

int main()
{
   // number of cases and number of floors in each case
   int m, n;
   // ------ auxiliary variables --------
   int i, j;
   int x, y, w, z;
   // -----------------------------------
   
   scanf("%d", &m);

   for (i = 0; i < m; i++) {

      scanf("%d", &n);

      p_graph tower = newGraph((n * 2) + 1);
      p_node *parent;

      int currentFloor = n * 2;

      for (j = 0; j < n; j++) {
         scanf("%d%d%d%d", &x, &y, &w, &z);

         /* Each vertex is inserted in the beginning of the linked list,
          but to maintain the list in the sequence entered from input,
         this vertexs are added from back to front 
         - vertexs with 'P' markers represents the change between lifts
         - each index of adjacency list in tower graph represents that you are in 
            some floor inside the lift A or B 
         - even indexs represents A, odd represents B*/

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

      // extra position in the adjacency list to represent the ground floor
      addVertex(tower, 0, 0, 0, 0);

      // the bfs returns a parent array with the indexes to be followed for the shortest
      // path until finds the ground floor
      parent = bfs(tower, n * 2 + 1);

      // this list is used to invert the parent array and print path in order
      p_node path = newList();
      p_node temp;

      for (j = 0; parent[j] != NULL;) {
         path = pushList(path, getNodeValue(parent[j]), getMarker(parent[j]), getMarker2(parent[j]));
         j = getNodeValue(parent[j]);
      }

      temp = path;

      // Prints the path for each case
      printf("Cenário #%d\n", i + 1);
      while (path != NULL) {
         if (getMarker(path) != 'P')
            printf("%c %c\n", getMarker(path), getMarker2(path));
         path = nextPos(path);
      }

      // frees all the allocated memory for the graph and parent array
      removeGraph(tower);
      removeList(temp);

      for (j = 0; j < n * 2 + 1; j++) {
         free(parent[j]);
      }
      free(parent);
   }

   return EXIT_SUCCESS;
}


p_node *bfs(p_graph tower, int towerSize)
{
   // parent array is used to store the path for each node
   p_node *parent = calloc(towerSize, sizeof(p_node));
   if (parent == NULL)
      exit(1);
   
   // queue used to exec the BFS
   p_queue queue = newQueue(towerSize);
   if (queue == NULL)
      exit(1);

   // used to avoid infinite loop in queue
   int *visited = calloc(towerSize, sizeof(int));
   if (visited == NULL)
      exit(1);

   //------- Starts BFS pushing the nodes of tower top in the queue ---------------------------
   visited[towerSize - 1] = 1;
   visited[towerSize - 2] = 1;

   p_node topFloorA = pushList(NULL, towerSize - 1, 'P', 'P');
   p_node topFloorB = pushList(NULL, towerSize - 2, 'P', 'P');
   push(queue, topFloorA);
   push(queue, topFloorB);

   //-----------------------------------------------------------------------------------------

   while(!isEmpty(queue)) {
      p_node v = pop(queue);
      p_node iterator = getAdjacency(tower, getNodeValue(v));

      while (iterator != NULL) {
         int pos = getNodeValue(iterator);

         if (!visited[pos]) {
            
            visited[pos] = 1;
            parent[pos] = pushList(NULL, getNodeValue(v), getMarker(iterator), getMarker2(iterator));
            push(queue, iterator);

            if (getNodeValue(iterator) == 0) {
               free(visited);
               removeQueue(queue);

               free(topFloorA);
               free(topFloorB);

               return parent;
            }
         }

         iterator = nextPos(iterator);
      }
   }

   return parent;
}
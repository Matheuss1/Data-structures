#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "grafo.h"
#include "queue.h"

int bfs(p_graph tower, int towerSize);

int main()
{

   int m, n;
   int i, j;
   int x, y, w, z;

   scanf("%d", &m);

   for (i = 0; i < m; i++) {

      scanf("%d", &n);

      p_graph tower = newGraph(n + 1);

      int currentFloor = n;

      for (j = 0; j < n; j++) {
         scanf("%d%d%d%d", &x, &y, &z, &w);

         // Each vertex is inserted in the beginning of the linked list,
         // but to maintain the list in the sequence entered from input,
         // this vertexs are added from back to front in
         addVertex(tower, currentFloor + w, currentFloor, 2);
         addVertex(tower, currentFloor - z, currentFloor, 2);
         addVertex(tower, currentFloor + y, currentFloor, 1);
         addVertex(tower, currentFloor - x, currentFloor, 1);

         currentFloor--;
      }

      addVertex(tower, 0, 0, 0);
      printf("%d\n", bfs(tower, n));
   }

   return EXIT_SUCCESS;
}


int bfs(p_graph tower, int towerSize)
{
   p_queue queue = newQueue(towerSize);

   p_node vertex = getAdjacency(tower, towerSize);

   while (vertex != NULL) {
      setAsVisited(vertex);
      setCounter(vertex, 1);
      push(queue, vertex);

      vertex = getAdjacency(tower, towerSize);
   }

   while(!isEmpty(queue)) {
      vertex = pop(queue);
      p_node tempVertex = vertex;
      
      // setAsVisited(vertex);

      if (getNodeValue(vertex) == 0)
         if (counterValue(vertex) < tower->adjList[0]->counter)
            tower->adjList[0]->counter = counterValue(vertex);



      while(tempVertex != NULL) {
         tempVertex = getAdjacency(tower, getNodeValue(vertex));
         
         if (tempVertex != NULL) {
            if (tempVertex->marker == vertex->marker) {
               if (counterValue(tempVertex) > counterValue(vertex) + 1) {
                  setCounter(tempVertex, counterValue(vertex) + 1);
                  push(queue, tempVertex);
                  // setAsVisited(tempVertex);
               }
            }
            else {
               if (counterValue(tempVertex) > counterValue(vertex) + 2) {
                  setCounter(tempVertex, counterValue(vertex) + 2);
                  push(queue, tempVertex);
                  // setAsVisited(tempVertex);
               }               
            }
         }
         // if (tempVertex != NULL)
      }
   }



   p_node iterator = iterator_(getAdjList(tower), 0);

   int minValue = counterValue(iterator);

   while (iterator != NULL) {
      if (counterValue(iterator) < minValue)
         minValue = counterValue(iterator);
      iterator = nextPos(iterator);
   }

   return minValue;

}
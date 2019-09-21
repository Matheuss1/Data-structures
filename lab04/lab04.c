#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "path_search.h"

int main()
{
   int m, n;

   scanf("%d %d", &m, &n);

   // Maze grid creation
   char** maze = sizeGrid(m, n);
   createGrid(maze, m);

   int j = find_entrance(maze, n);
   
   int** visited = boolGrid(m, n);
   int coords[2];
   sword_finder(maze, visited, coords, m, n, 0, j, 0);
   removeBool(visited, m);

   visited = boolGrid(m, n);
   minotaur_finder(maze, visited, m, n, coords[0], coords[1], 0, 0);
   removeBool(visited, m);
   
   for (int i = 0; i < m; i++) {
      printf("%s\n", maze[i]);
   }


   removeGrid(maze, m);



   return EXIT_SUCCESS;
}

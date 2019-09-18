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
   for (int i = 0; i < m; i++) {
      printf("%s\n", maze[i]);
   }


   removeGrid(maze, m);



   return EXIT_SUCCESS;
}

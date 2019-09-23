#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "path_search.h"

// Moves for each choose (RIGHT - DOWN - LEFT- UP)
int d[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int main()
{
   int m, n;
   scanf("%d %d", &m, &n);

   // Maze grid creation
   char** path1 = sizeGrid(m, n);
   char** path2 = sizeGrid(m, n);
   createGrid(path1, path2, m);

   int j = find_entrance(path1, n);
   
   // Finds the path 
   // first -> Entrance - Sword
   // second -> Sword - minotaur
   int coords[2];
   sword_finder(path1, coords, m, n, 0, j, 0, d);
   minotaur_finder(path2, m, n, coords[0], coords[1], 0, d);

   // Create the solution that will be printed
   create_chart(path1, path2, m, n);
   
   // Print solution
   for (int i = 0; i < m; i++) {
      printf("%s\n", path1[i]);
   }
   
   // Free allocated memory
   removeGrid(path1, m);
   removeGrid(path2, m);

   return EXIT_SUCCESS;
}
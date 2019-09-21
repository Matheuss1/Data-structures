#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "path_search.h"

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
   
   int coords[2];
   sword_finder(path1, coords, m, n, 0, j, 0, d);
   minotaur_finder(path2, m, n, coords[0], coords[1], 0, d);
   
   for (int i = 1; i < m - 1; i++) {
      for (int j = 1; j < n- 1; j++) {
         if (path1[i][j] == ' ' && path2[i][j] == '*') {
            path1[i][j] = path2[i][j];
         }
      }
   }

   for (int i = 0; i < m; i++) {
      printf("%s\n", path1[i]);
   }

   removeGrid(path1, m);
   removeGrid(path2, m);



   return EXIT_SUCCESS;
}
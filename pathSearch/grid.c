#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// the NULL condition is for the case when we can't alloc memory, so the program stops

char** sizeGrid(int m, int n)
{
    char** maze;
    maze = malloc(m * sizeof(char*));
    if (maze == NULL)
        exit(1);

    int i;
    for (i = 0; i < m; i++) {
        maze[i] = malloc( (n + 1) * sizeof(char));
        if (maze[i] == NULL)
            exit(1);
    }
    return maze;
}


void createGrid(char** path1, char** path2, int m)
{
    for (int i = 0; i < m; i++) {
        scanf(" %[^\n]", path1[i]);
        strcpy(path2[i], path1[i]);
    }
}


void create_chart(char** path1, char** path2, int m, int n)
{
    for (int i = 1; i < m - 1; i++) {
      for (int j = 1; j < n- 1; j++) {
         if (path1[i][j] == ' ' && path2[i][j] == '*') {
            path1[i][j] = path2[i][j];
         }
      }
   }
}


void removeGrid(char** maze, int m)
{
    for (int i = 0; i < m; i++) {
        free(maze[i]);
    }
    free(maze);
}
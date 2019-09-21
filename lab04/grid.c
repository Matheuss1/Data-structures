#include <stdio.h>
#include <stdlib.h>

char** sizeGrid(int m, int n)
{
    char** maze;
    maze = malloc(m * sizeof(char*));
    if (maze == NULL)
        exit(1);

    int i;
    for (i = 0; i < m; i++) {
        maze[i] = malloc( (n + 1) * sizeof(char));
    }
    return maze;
}

void createGrid(char** maze, int m)
{
    for (int i = 0; i < m; i++) {
        scanf(" %[^\n]", maze[i]);
    }
}

void removeGrid(char** maze, int m)
{
    for (int i = 0; i < m; i++) {
        free(maze[i]);
    }
    free(maze);
}
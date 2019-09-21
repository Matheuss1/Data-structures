#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void removeGrid(char** maze, int m)
{
    for (int i = 0; i < m; i++) {
        free(maze[i]);
    }
    free(maze);
}
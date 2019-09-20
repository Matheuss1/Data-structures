
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

// TODO: PROBLEMA COM A VARIAVEL DE CONTROLE DE  MOVIMENTOS (move)
int path_finder(char** maze, int coords[], int m, int n, int indexI, int indexJ, int move, char looking_for, int aux, int** visited)
{
    printf("a");
    if (indexJ + 1 > 0 && indexJ + 1 < n - 1 && visited[indexI][indexJ + 1] == 0 && maze[indexI][indexJ + 1] != 'M' && move == 1 && aux != 1 && maze[indexI][indexJ + 1] != '#') {
        visited[indexI][indexJ + 1] = 1;
        
        if (maze[indexI][indexJ + 1] == looking_for) {
            coords[0] = indexI;
            coords[1] = indexJ + 1;
            return 1;
        }   

        maze[indexI][indexJ + 1] = '*';
        aux = path_finder(maze, coords, m, n, indexI, indexJ + 1, 2, looking_for, aux, visited);

        if (aux != 1)
            maze[indexI][indexJ + 1] = ' ';

    }
    if (move == 1)
        move = 2;

    if (indexI  + 1 > 0 && indexI + 1 < m - 1 && visited[indexI + 1][indexJ] == 0 && maze[indexI + 1][indexJ] != 'M' && move == 2 && aux != 1 && maze[indexI + 1][indexJ] != '#') {
        visited[indexI + 1][indexJ] = 1;
        
        if (maze[indexI + 1][indexJ] == looking_for) {
            coords[0] = indexI + 1;
            coords[1] = indexJ;
            return 1;
        }

        maze[indexI + 1][indexJ] = '*';
        aux = path_finder(maze, coords, m, n, indexI + 1, indexJ, 3, looking_for, aux, visited);

        if (aux != 1)
            maze[indexI + 1][indexJ] = ' ';

    }

    if (move == 2)
        move = 3;
    if (indexJ - 1 > 0 && indexJ - 1 < n - 1 && visited[indexI][indexJ - 1] == 0 && maze[indexI][indexJ - 1] != 'M' && move == 3 && aux != 1 && maze[indexI][indexJ - 1] != '#') {
        visited[indexI][indexJ - 1] = 1;  

        if (maze[indexI][indexJ - 1] == looking_for) {
            coords[0] = indexI;
            coords[1] = indexJ - 1;
            return 1;
        }

        maze[indexI][indexJ - 1] = '*';
        aux = path_finder(maze, coords, m, n, indexI, indexJ - 1, 4, looking_for, aux, visited);

        if (aux != 1)
            maze[indexI][indexJ - 1] = ' ';
}

    if (move == 3)
        move = 4;
    if (indexI - 1 > 0 && indexI - 1 < m - 1 && visited[indexI - 1][indexJ] == 0 && maze[indexI - 1][indexJ] != 'M' && move == 4 && aux != 1 && maze[indexI - 1][indexJ] != '#') {
        visited[indexI - 1][indexJ] = 1;

        if (maze[indexI - 1][indexJ] == looking_for) {
            coords[0] = indexI - 1;
            coords[1] = indexJ;
            return 1;
        }

        maze[indexI + 1][indexJ] = '*';
        aux = path_finder(maze, coords, m, n, indexI - 1, indexJ, 1, looking_for, aux, visited);
        
        if (aux != 1)
            maze[indexI - 1][indexJ] = ' ';
}

    return 0;
}   


int find_entrance(char** maze, int n)
{
    for (int i = 1; i < n; i ++) 
        if (maze[0][i] == 'E')
            return i;
    return 1;
}


int** boolGrid(int m, int n)
{
    int** bool;
    bool = malloc(m * sizeof(int*));
    if (bool == NULL)
        exit(1);

    int i;
    for (i = 0; i < m; i++) {
        bool[i] = malloc(n * sizeof(int));
        if (bool[i] == NULL)
            exit(1);
        for (int j = 0; j < n; j++)
            bool[i][j] = 0;
    }
    return bool;
}


void removeBool(int** bool, int m)
{
    for (int i = 0; i < m; i++)
        free(bool[i]);
    free(bool);
}

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "path_search.h"
// TODO: PROBLEMA COM A VARIAVEL DE CONTROLE DE  MOVIMENTOS (move)
int sword_finder(char** maze, int coords[], int m, int n, int indexI, int indexJ, int aux, int d[4][2])
{
    for (int i = 0; i < 4; i++) {
        if (indexI + d[i][0] > 0 && indexI + d[i][0] < m - 1 && indexJ + d[i][1] > 0 && indexJ + d[i][1] < n - 1) {
            if (maze[indexI + d[i][0]][indexJ + d[i][1]] != '#' && maze[indexI + d[i][0]][indexJ + d[i][1]] != 'M' && aux != 1 && maze[indexI + d[i][0]][indexJ + d[i][1]] != '*') {
                if (maze[indexI + d[i][0]][indexJ + d[i][1]] == 'S') {
                    coords[0] = indexI + d[i][0];
                    coords[1] = indexJ + d[i][1];
                    return 1;
                }
                maze[indexI + d[i][0]][indexJ + d[i][1]] = '*';
                aux = sword_finder(maze, coords, m, n, indexI + d[i][0], indexJ + d[i][1], aux, d);
            }
        }
    }
    if (aux)
        return 1;
    maze[indexI][indexJ] = ' ';
    return 0;
}   

int minotaur_finder(char** maze, int m, int n, int indexI, int indexJ, int aux, int d[4][2])
{
    for (int i = 0; i < 4; i++) {
        if (indexI + d[i][0] > 0 && indexI + d[i][0] < m - 1 && indexJ + d[i][1] > 0 && indexJ + d[i][1] < n - 1) {
            if (maze[indexI + d[i][0]][indexJ + d[i][1]] != '#' && maze[indexI + d[i][0]][indexJ + d[i][1]] != 'S' && aux != 1 && maze[indexI + d[i][0]][indexJ + d[i][1]] != '*') {
                if (maze[indexI + d[i][0]][indexJ + d[i][1]] == 'M') {
                    return 1;
                }
                maze[indexI + d[i][0]][indexJ + d[i][1]] = '*';
                aux = minotaur_finder(maze, m, n, indexI + d[i][0], indexJ + d[i][1], aux, d);
            }
        }
    }
    if (aux)
        return 1;
    maze[indexI][indexJ] = ' ';
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
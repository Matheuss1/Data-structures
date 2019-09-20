#ifndef PATH_SEARCH_H
#define PATH_SEARCH_H

int path_finder(char** maze, int coords[], int m, int n, int indexI, int indexJ, int move, char looking_for, int aux, int** visited);
int find_entrance(char** maze, int n);
int** boolGrid(int m, int n);
#endif

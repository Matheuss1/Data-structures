#ifndef PATH_SEARCH_H
#define PATH_SEARCH_H

int sword_finder(char** maze, int** visited, int coords[], int m, int n, int indexI, int indexJ, int aux);
int minotaur_finder(char** maze, int** visited, int m, int n, int indexI, int indexJ, int aux, int binary);
int find_entrance(char** maze, int n);
int** boolGrid(int m, int n);
void removeBool(int** bool, int m);
void fix_visualization(char** maze, int indexI, int indexJ, int move_tracked);
#endif

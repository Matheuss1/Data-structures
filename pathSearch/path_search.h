#ifndef PATH_SEARCH_H
#define PATH_SEARCH_H

/* Find the entrance before starting search*/
int find_entrance(char** maze, int n);

/* Finds the path from the entrance to sword */
int sword_finder(char** maze, int coords[], int m, int n, int indexI, int indexJ, int aux, int d[4][2]);

/* Finds the path from sword to minotaur */
int minotaur_finder(char** maze, int m, int n, int indexI, int indexJ, int aux, int d[4][2]);

#endif
#ifndef GRID_H
#define GRID_H

/* Allocate memory with grid size */
char** sizeGrid(int m, int n);

/* Read the maze from input */
void createGrid(char** path1, char** path2, int m);

/* Create the maze chart solution and paste the path2 path in path1*/
void create_chart(char** path1, char** path2, int m, int n);

/* Deallocate memory from maze grid created */
void removeGrid(char** maze, int m);

#endif

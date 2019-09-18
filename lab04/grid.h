#ifndef GRID_H
#define GRID_H

/* Allocate memory with grid size */
char** sizeGrid(int m, int n);

/* Read the maze from input */
void createGrid(char** maze, int m);

/* Deallocate memory from maze created */
void removeGrid(char** maze, int m);

#endif

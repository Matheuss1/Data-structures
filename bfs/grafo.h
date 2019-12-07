#ifndef GRAFO_H
#define GRAFO_H

#include "lista.h"

typedef struct {
    p_node *adjList;
    int size;
} Graph;

typedef Graph* p_graph;

// Creates a new graph
p_graph newGraph(int size);

// Adds a new vertex in a graph structure gave
void addVertex(p_graph graph, int v, int currentPos, char marker, char marker2);

// returns a pointer for the first item in the adj list in "pos" index
p_node getAdjacency(p_graph graph, int pos);

// removes the graph and free the memory allocated by it
void removeGraph(p_graph graph);

#endif
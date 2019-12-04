#ifndef GRAFO_H
#define GRAFO_H

#include "lista.h"

typedef struct {
    p_node *adjList;
    int size;
} Graph;

typedef Graph* p_graph;

p_graph newGraph(int size);

void addVertex(p_graph graph, int v, int currentPos, char marker, char marker2);

p_node getAdjacency(p_graph graph, int pos);

#endif
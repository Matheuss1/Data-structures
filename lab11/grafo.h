#ifndef GRAFO_H
#define GRAFO_H

#include "lista.h"

typedef struct {
    p_node *adjList;
    int size;
} Graph;

typedef Graph* p_graph;

p_graph newGraph(int size);

void addVertex(p_graph graph, int u, int v, int marker);

p_node getAdjacency(p_graph graph, int pos);

p_node *getAdjList(p_graph graph);

#endif
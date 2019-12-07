#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"

typedef struct {
    p_node *adjList;
    int size;
} Graph;

typedef Graph* p_graph;

p_graph newGraph(int size);

void addVertex(p_graph graph, int u, int v, int weight);

p_node getAdjacency(p_graph graph, int pos);

#endif
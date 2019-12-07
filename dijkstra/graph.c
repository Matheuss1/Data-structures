#include <stdlib.h>

#include "graph.h"


p_graph newGraph(int n)
{
    p_graph graph = malloc(sizeof(Graph));
    if (graph == NULL)    
        exit(1);

    graph->adjList = calloc(n, sizeof(Node));
    if (graph->adjList == NULL)
        exit(1);

    for (int i = 0; i < n; i++)
        graph->adjList[i] = NULL;

    graph->size = n;

    return graph;
}


void addVertex(p_graph graph, int u, int v, int weight)
{
    graph->adjList[u] = pushList(graph->adjList[u], v, weight);
    graph->adjList[v] = pushList(graph->adjList[v], u, weight);
}


p_node getAdjacency(p_graph graph, int pos)
{
    p_node iterator = iterator_(graph->adjList, pos);

    return iterator;
}


#include <stdlib.h>
#include "grafo.h"


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


void addVertex(p_graph graph, int v, int currentPos, char marker, char marker2)
{
    graph->adjList[currentPos] = pushList(graph->adjList[currentPos], v, marker, marker2);
}


p_node getAdjacency(p_graph graph, int pos)
{
    p_node iterator = iterator_(graph->adjList, pos);

    return iterator;
}


void removeGraph(p_graph graph)
{
    for (int i = 0; i < graph->size; i++) {
        removeList(graph->adjList[i]);
    }

    free(graph->adjList);
    free(graph);
}
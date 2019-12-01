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


void addVertex(p_graph graph, int v, int currentPos, int marker)
{
    if (v >= 0 && v < graph->size)
        graph->adjList[currentPos] = pushList(graph->adjList[currentPos], v, marker);
    else
        graph->adjList[currentPos] = pushList(graph->adjList[currentPos], 0, marker);
}


p_node getAdjacency(p_graph graph, int pos)
{
    p_node iterator = iterator_(graph->adjList, pos);

    while (iterator != NULL && (getNodeValue(iterator) == pos || isVisited(iterator)) ) {
        iterator = nextPos(iterator);
    }

    return iterator;
}


p_node *getAdjList(p_graph graph)
{
    return graph->adjList;
}



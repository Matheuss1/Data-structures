#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "heap.h"

int path(p_graph graph, int size, int start, int dest, int parent[]);

int main()
{
    int n, m;
    int a, b, c, d;

    scanf("%d%d", &n, &m);

    p_graph graph = newGraph(n);

    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &c);

        addVertex(graph, a, b, c);
    }

    scanf("%d%d%d%d", &a, &b, &c, &d);

    int *case1 = malloc(sizeof(int) * n);
    int *case2 = malloc(sizeof(int) * n);

    int dist1 = path(graph, n, b, c, case1);
    int dist2 = path(graph, n, b, d, case2);
}


int path(p_graph graph, int size, int start, int dest, int parent[])
{
    int *visited = calloc(size, sizeof(int));
    int *dist = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        dist[i] = __INT_MAX__;
        parent[i] = -1;
    }

    p_pq pq = newHeap(size);

    visited[0] = 1;
    dist[0] = 0;

    pushToHeap(pq, getAdjacency(graph, 0));

    while(!isEmpty(pq)) {
        p_node v = pop(pq);
        int val = getVal(v);
        int weight = getWeight(v);

        if (v == dest - 1)
            break;
        
        p_node iterator = getAdjacency(graph, val);

        while (iterator != NULL) {
            if (dist[getVal(iterator)] > dist[val] + weight) {
                dist[getVal(iterator)] = dist[val] + weight;
                pushToHeap(pq, iterator);
                parent[getVal(iterator)] = val;
            }
        }
    }


    



}


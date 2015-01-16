#define EDGE 100
#define VET 100
#include <iostream>
#include "Graph.h"

int main()
{
    Graph::Graph a(7);
    a.addEdge(1,2,3);
    a.addEdge(2,1,2);
    a.addEdge(2,3,3);
    a.addEdge(3,4,2);
    a.addEdge(4,3,1);
    int color[10]; memset(color, 10, sizeof(color));
    int * p = a.SPFA(1);
}

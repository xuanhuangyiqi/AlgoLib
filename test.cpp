#include <iostream>
#include "Graph.h"

using namespace std;
int n, m, k;

void test1()
{
    Graph::FlowGraph g(4, 5, 0, 3);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(0, 2, 3);
    g.addEdge(2, 3, 4);
    g.addEdge(1, 2, 5);
    assert(g.max_flow() == 4);
}
void test2()
{
    Graph::FlowGraph g(4, 5, 0, 3);
    g.addEdge(0, 1, 1, 1);
    g.addEdge(1, 3, 2, 1);
    g.addEdge(0, 2, 3, 2);
    g.addEdge(2, 3, 4, 2);
    g.addEdge(1, 2, 5, 4);
    int weight = g.max_flow_max_weight().second;
    cout << weight << "!";
    assert(weight == 19);
}
void test3()
{
    Graph::FlowGraph g(4, 5, 0, 3);
    g.addEdge(0, 1, 1, 1);
    g.addEdge(1, 3, 2, 1);
    g.addEdge(0, 2, 3, 2);
    g.addEdge(2, 3, 4, 2);
    g.addEdge(1, 2, 5, 4);
    assert(g.findEdge(2, 3)->c == 4);
}
int main()
{
    test1();
    test2();
    test3();
}

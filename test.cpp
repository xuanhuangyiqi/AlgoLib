#include <iostream>
#include "Graph.h"
#include "others.h"

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
void test4()
{
    Graph::Graph g(7, 7);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(6, 4);
    std::vector<int> colors = g.tarjan();
    assert(colors[0] == colors[1]);
    assert(colors[2] == colors[1]);
    assert(colors[4] == colors[6]);
    assert(colors[5] == colors[6]);
    assert(colors[2] != colors[4]);
}
void test5()
{
    Graph::Graph g(7, 7);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 0, 13);
    g.addEdge(2, 4, 3);
    g.addEdge(4, 5, 5);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 4, 1);
    std::vector<int> dis = g.SPFA(2);
    assert(dis[2] == 0);
    assert(dis[0] == 13);
    assert(dis[1] == 14);
    assert(dis[3] < 0);
    assert(dis[4] == 3);
    assert(dis[5] == 8);
}
void test6()
{
    string s = "abaacbabbadca";
    string p = "bab";
    String::StringProcessor sp;
    assert(sp.KMP(s, p) == 5);
}
int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
}

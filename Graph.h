#include <assert.h>
#include <stack>
#include <queue>

namespace Graph {
    struct Edge { int node, next, dis; };
    class Graph
    {
        private:
        int numOfEdge, numOfVetex, first[VET];
        Edge edge[EDGE];
        int index;

        void strongconnect(int v, int * ind, int * ind_low, std::stack<int>& q, bool * inQ)
        {
            ind[v] = index;
            ind_low[v] = index;
            index++;
            assert(inQ[v] == false);
            inQ[v] = true;
            q.push(v);
            for (int i = first[v]; i != 0; i = edge[i].next)
            {
                int w = edge[i].node;
                if (ind[w] == 0)
                {
                    strongconnect(w, ind, ind_low, q, inQ);
                    ind_low[v] = std::min(ind_low[v], ind_low[w]);
                } 
                else if (inQ[w])
                    ind_low[v] = std::min(ind_low[v], ind[w]);
            }
            if (ind[v] == ind_low[v])
            {
                int w;
                while (!q.empty())
                {
                    w = q.top();
                    q.pop();
                    inQ[w] = false;
                    if (w == v) break;
                }
            }
        }
        public:
        Graph() { init(); }
        Graph(int v) { init(); numOfVetex = v; }
        void init()
        {
            numOfEdge = 0;
            numOfVetex = 0;
            memset(first, 0, sizeof(first));
            memset(edge, 0, sizeof(edge));
            index = 1;
        }

        int getV(){return numOfVetex;}

        int * getEdges(int v)
        {
            int * res = (int *)malloc(sizeof(int)*VET);
            memset(res, 0, sizeof(int)*VET);
            int cnt = 0;
            for (int i = first[v]; i != 0; i = edge[i].next)
                res[cnt++] = edge[i].node;
            return res;
        }

        void addEdge(int s, int t)
        {
            assert(s != 0); assert(t != 0);
            numOfEdge++;
            edge[numOfEdge].node = t;
            edge[numOfEdge].next = first[s];
            first[s] = numOfEdge;
        }

        void addEdge(int s, int t, int d)
        {
            addEdge(s, t);
            edge[numOfEdge].dis = d;
        }
            
        int * SPFA(int v)
        {
            int n = numOfVetex;
            int * res = (int *)malloc(sizeof(int)*VET);
            memset(res, 0xFFF, sizeof(int)*VET);
            res[v] = 0;
            bool inQ[VET]; memset(inQ, false, sizeof(inQ));
            std::queue<int> q;
            q.push(v); inQ[v] = true;
            while (!q.empty())
            {
                int node = q.front(); inQ[node] = false; q.pop();
                for (int i = first[node]; i != 0; i = edge[i].next)
                {
                    if (res[edge[i].node] < 0 || 
                            res[node] + edge[i].dis < res[edge[i].node])
                    {
                        res[edge[i].node] = res[node] + edge[i].dis;
                        if (!inQ[edge[i].node])
                        {
                            inQ[edge[i].node] = true;
                            q.push(edge[i].node);
                        }
                    }
                }
            }
            return res;
        }

        void tarjan(int * color)
        {
            int n = numOfVetex;
            std::stack<int> Q;
            int ind[n+1];       memset(ind,     0, sizeof(ind));
            bool inQ[n+1]; memset(inQ, false, sizeof(inQ));
            for (int i = 1; i <= n; ++i)
               if (ind[i] == 0)
                   strongconnect(i, ind, color, Q, inQ);
        }
        
    };
}

#include <assert.h>
#include <algorithm>
#include <stack>
#include <queue>

#define MAXINT 1000000000

namespace Graph {
    /*
    struct Edge { int node, next, dis; };
    class Graph
    {
        private:
        int _numOf_edges, _numOfVertex, _first[VET];
        _edge _edge[_edge];
        int index;

        void strongconnect(int v, int * ind, int * ind_low, std::stack<int>& q, bool * inQ)
        {
            ind[v] = index;
            ind_low[v] = index;
            index++;
            assert(inQ[v] == false);
            inQ[v] = true;
            q.push(v);
            for (int i = _first[v]; i != 0; i = _edge[i].next)
            {
                int w = _edge[i].node;
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

        void _init(int v, int e)
        {
            _numOf_edges = 0;
            _numOfVertex = 0;
            for (int)
            index = 1;
        }

        public:
        Graph(int v, int e) { _init(); _numOfVertex = v; }
        int getV(){return _numOfVertex;}

        int * get_edges(int v)
        {
            int * res = (int *)malloc(sizeof(int)*VET);
            memset(res, 0, sizeof(int)*VET);
            int cnt = 0;
            for (int i = _first[v]; i != 0; i = _edge[i].next)
                res[cnt++] = _edge[i].node;
            return res;
        }

        void add_edge(int s, int t)
        {
            assert(s != 0); assert(t != 0);
            _numOf_edges++;
            _edge[_numOf_edges].node = t;
            _edge[_numOf_edges].next = _first[s];
            _first[s] = _numOf_edges;
        }

        void add_edge(int s, int t, int d)
        {
            add_edge(s, t);
            _edge[_numOf_edges].dis = d;
        }
            
        int * SPFA(int v)
        {
            int n = _numOfVertex;
            int * res = (int *)malloc(sizeof(int)*VET);
            memset(res, 0xFFF, sizeof(int)*VET);
            res[v] = 0;
            bool inQ[VET]; memset(inQ, false, sizeof(inQ));
            std::queue<int> q;
            q.push(v); inQ[v] = true;
            while (!q.empty())
            {
                int node = q.front(); inQ[node] = false; q.pop();
                for (int i = _first[node]; i != 0; i = _edge[i].next)
                {
                    if (res[_edge[i].node] < 0 || 
                            res[node] + _edge[i].dis < res[_edge[i].node])
                    {
                        res[_edge[i].node] = res[node] + _edge[i].dis;
                        if (!inQ[_edge[i].node])
                        {
                            inQ[_edge[i].node] = true;
                            q.push(_edge[i].node);
                        }
                    }
                }
            }
            return res;
        }

        void tarjan(int * color)
        {
            int n = _numOfVertex;
            std::stack<int> Q;
            int ind[n+1];       
            memset(ind, 0, sizeof(ind));
            bool inQ[n+1]; memset(inQ, false, sizeof(inQ));
            for (int i = 1; i <= n; ++i)
               if (ind[i] == 0)
                   strongconnect(i, ind, color, Q, inQ);
        }
        
    };

*/

    struct FlowEdge
    {
        int from, to, c, f, w, next;
        FlowEdge()
        {
            from = to = -1;
            c = f = w = 0;
            next = 0;
        }
    };

    class FlowGraph
    {
        private:
            int _numOfVetex, _numOfEdges;
            std::vector<FlowEdge> _edge; 
            std::vector<int> _first;
            int _start, _end;

            bool _build_depth_graph(std::vector<int> & dep, std::queue<int> & Q)
            {
                int x, y;
                for (int i = 0; i < _numOfVetex; ++i) dep[i] = -1;
                dep[_start] = 0;
                while (!Q.empty()) Q.pop();
                Q.push(_start);
                while (!Q.empty())
                {
                    x = Q.front(); Q.pop();
                    for (int edge_idx = _first[x]; edge_idx != 0; edge_idx = _edge[edge_idx].next)
                    {
                        y = _edge[edge_idx].to;
                        if(_edge[edge_idx].c > _edge[edge_idx].f && dep[y] == -1)
                        {
                            dep[y] = dep[x] + 1;
                            if(y == _end) return true;
                            Q.push(y);
                        }
                    }
                }
                return false;
            }

            int _find_flow(int s, int inf, std::vector<int> & dep)
            {
                if (s == _end)
                    return inf;
                int flow = 0, t;
                for (int edge_idx = _first[s]; edge_idx != 0; edge_idx = _edge[edge_idx].next)
                {
                    FlowEdge & e = _edge[edge_idx];
                    t = e.to;
                    if (e.c > e.f && dep[t] == dep[s] + 1)
                    {
                        flow = std::min(e.c - e.f, _find_flow(t, std::min(e.c-e.f, inf), dep));
                        if (flow > 0)
                        {
                            e.f += flow;
                            return flow;
                        }
                    }
                }
                return 0;
            }
            int _spfa(std::vector<int> & pre, std::queue<int> & Q, std::vector<int> & dis, std::vector<bool> & inQ)
            {
                inQ.resize(_numOfVetex, false);
                for (int i = 0; i < _numOfVetex; ++i) pre[i] = -1;
                dis.clear();
                dis.resize(_numOfVetex, -1);
                dis[_start] = 0;
                while (!Q.empty()) Q.pop();
                Q.push(_start); inQ[_start] = true;
                while (!Q.empty())
                {
                    int x = Q.front(); Q.pop(); inQ[x] = false;
                    for (int i = _first[x]; i; i = _edge[i].next)
                    {
                        FlowEdge & e = _edge[i];
                        if (e.c > e.f && dis[e.from] + e.w > dis[e.to])
                        {
                            dis[e.to] = dis[e.from] + e.w;
                            pre[e.to] = e.from;
                            if (!inQ[e.to])
                            {
                                Q.push(e.to);
                                inQ[e.to] = true;
                            }
                        }
                    }
                }
                if (pre[_end] == -1)
                    return 0;
                else
                    return dis[_end];
            }

        public:
            // nodes: 0 ~ numOfVetex-1
            FlowGraph(int nV, int nE, int s, int t)
            {
                _numOfVetex = nV;
                _numOfEdges = 0;
                _first.resize(nV);
                for (int i = 0; i < nV; ++i) _first[i] = 0;
                _edge.resize(nE+1);
                _start = s;
                _end = t;
            }

            void addEdge(int s, int t, int _c)
            {
                ++_numOfEdges;
                _edge[_numOfEdges].from = s;
                _edge[_numOfEdges].to = t;
                _edge[_numOfEdges].c = _c;
                _edge[_numOfEdges].next = _first[s];
                _first[s] = _numOfEdges;
            }

            void addEdge(int s, int t, int _c, int _w)
            {
                ++_numOfEdges;
                _edge[_numOfEdges].from = s;
                _edge[_numOfEdges].to = t;
                _edge[_numOfEdges].c = _c;
                _edge[_numOfEdges].w = _w;
                _edge[_numOfEdges].next = _first[s];
                _first[s] = _numOfEdges;
            }

            // recursive implementation of dinic algorithm
            int max_flow()
            {
                std::vector<int> depth(_numOfVetex);
                std::queue<int> Q;

                int flow = 0, cur_flow;
                
                while (_build_depth_graph(depth, Q))
                    while (cur_flow = _find_flow(_start, MAXINT, depth))
                        flow += cur_flow;
                return flow;
            }

            FlowEdge * findEdge(int s, int t)
            {
                for (int i = _first[s]; i != 0; i = _edge[i].next)
                    if (_edge[i].to == t)
                        return &_edge[i];
                return NULL;
            }


            std::pair<int, int> max_flow_max_weight()
            {
                int flow = 0, weight = 0, cur_weight, cur_flow;
                std::vector<int> pre(_numOfVetex);
                std::queue<int> Q;
                std::vector<int> dis;
                std::vector<bool> inQ;
                while (cur_weight=_spfa(pre, Q, dis, inQ))
                {
                    cur_flow = MAXINT;
                    int cur = _end;
                    while (pre[cur] != -1)
                    {
                        FlowEdge * e = findEdge(pre[cur], cur);
                        cur_flow = std::min(cur_flow, e->c - e->f);
                        cur = pre[cur];
                    }
                    cur = _end;
                    while (pre[cur] != -1)
                    {
                        FlowEdge * e = findEdge(pre[cur], cur);
                        e->f += cur_flow;
                        cur = pre[cur];
                    }
                    flow += cur_flow;
                    weight += cur_flow * cur_weight;
                }
                return std::make_pair(flow, weight);
            }
    };
}

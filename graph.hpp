#include <assert.h>
#include <algorithm>
#include <stack>
#include <queue>

#define MAXINT 1000000000

namespace Graph {
    struct Edge { int from, to, next, dis; };
    class Graph
    {
        private:
        int _numOfEdges, _numOfVetex;
        std::vector<int> _first;
        std::vector<Edge> _edge;

        void _strongconnect(int v, int& index, std::vector<int>& ind, std::vector<int>& ind_low, std::stack<int>& S, std::vector<bool>& inS)
        {
            ind[v] = index;
            ind_low[v] = index;
            index++;
            assert(inS[v] == false);
            inS[v] = true;
            S.push(v);

            for (int i = _first[v]; i != 0; i = _edge[i].next)
            {
                Edge & e = _edge[i];
                if (ind[e.to] == -1) // index of w undefined
                {
                    _strongconnect(e.to, index, ind, ind_low, S, inS);
                    ind_low[v] = std::min(ind_low[v], ind_low[e.to]);
                } 
                else if (inS[e.to])
                    ind_low[v] = std::min(ind_low[v], ind[e.to]);
            }
            int w;
            if (ind[v] == ind_low[v])
                while (!S.empty())
                {
                    w = S.top();
                    S.pop();
                    inS[w] = false;
                    if (w == v) break;
                }
        }

        public:
        Graph(int v, int e) : _numOfVetex(v), _numOfEdges(0)
        {
            _edge.resize(e+1);
            _first.resize(v, 0);
        }

        void addEdge(int s, int t)
        {
            //std::cout << "E"; std::cout.flush();
            ++_numOfEdges;
            _edge[_numOfEdges].from = s;
            _edge[_numOfEdges].to = t;
            _edge[_numOfEdges].next = _first[s];
            _first[s] = _numOfEdges;
        }

        void addEdge(int s, int t, int d)
        {
            addEdge(s, t);
            _edge[_numOfEdges].dis = d;
        }
            
        std::vector<int> SPFA(int v)
        {
            std::vector<int> dis(_numOfVetex, -MAXINT);
            dis[v] = 0;
            std::vector<bool> inQ(_numOfVetex, false); 
            std::queue<int> q;
            q.push(v); 
            inQ[v] = true;
            while (!q.empty())
            {
                int from = q.front(); inQ[from] = false; q.pop();
                for (int i = _first[from]; i != 0; i = _edge[i].next)
                {
                    Edge & e = _edge[i];
                    if (dis[e.to] < 0 || dis[from] + e.dis < dis[e.to])
                    {
                        dis[e.to] = dis[e.from] + e.dis;
                        if (!inQ[e.to])
                        {
                            inQ[e.to] = true;
                            q.push(e.to);
                        }
                    }
                }
            }
            return dis;
        }


        // returns colors from 0 and non-continous
        // color[i] == color[j] iff i and j in same SSC
        std::vector<int> tarjan()
        {
            std::vector<int> color(_numOfVetex, -1);
            std::stack<int> S;
            int cur_index = 0;
            std::vector<bool> inS(_numOfVetex, false);
            std::vector<int> ind(_numOfVetex, -1);
            for (int i = 0; i < _numOfVetex; ++i)
               if (ind[i] == -1)    // ind[i] undefined
               {
                   _strongconnect(i, cur_index, ind, color, S, inS);
               }
            return color;
        }
        
    };

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
                    while ((cur_flow = _find_flow(_start, MAXINT, depth)))
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
                while ((cur_weight=_spfa(pre, Q, dis, inQ)))
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

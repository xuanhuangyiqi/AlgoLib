This project includes useful algorhthms for ACM and online algorithm contests.

Already implemented algorithms:
1. graph.h
    * tarjan: finding SCCs(Strong Connected Components) in a directed graph.
    * SPFA: finding the shortest paths from a given node to all other nodes, negative cycles are not forbidden.
    * dinic: computing max-flow of a directed graph. 
    * max flow max weights: each edge is given with a weight, the algorithm can iteratively find augmented paths based on SPFA and returns the max flow with max weights if there are multiple max flows.
2. others.h   
    * KMP: find substring with O(m+n)


#include <iostream>
#include "../include/nautyCaller.h"

int main() {
    const int subgraphSize = 3;
    
    // Adjacency matrix: directed graph
    int subgraph[subgraphSize * subgraphSize] = {
        0, 1, 0,  // Node 0 has edge to node 1
        0, 0, 0,  // Node 1 has no edges
        0, 1, 0   // Node 2 has edges to nodes 0 and 1
    };
    
    // Nauty data structures
    graph nauty_g[MAXN * MAXM];
    graph canon[MAXN * MAXM];
    int lab[MAXN]={0};
    
    // Perform canonicalization
    nautyClassify(subgraph, subgraphSize, lab, nauty_g, canon);
    
    // Print canonical labeling
    std::cout << "Canonical Labeling:" << std::endl;
    for (int i = 0; i < subgraphSize; i++) {
        std::cout << i << " -> " << lab[i] << std::endl;
    }
    
    return 0;
}
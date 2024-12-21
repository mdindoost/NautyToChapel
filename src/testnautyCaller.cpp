#include <iostream>
#include "../include/nautyCaller.h"

int main() {
    const int subgraphSize = 3;
    
    // Adjacency matrix: directed graph
    int subgraph[subgraphSize * subgraphSize] = {
        0, 1, 0,  // Node 0 has edge to node 1
        0, 0, 0,  // Node 1 has no edges
        1, 1, 0   // Node 2 has edges to nodes 0 and 1
    };
    
    // Nauty data structures
    graph nauty_g[MAXN * MAXM];
    graph canon[MAXN * MAXM];
    int lab[MAXN];
    int orbits[MAXN] = {0};  // Initialize to zeros
    int ptn[MAXN] = {0};     // Initialize to zeros
    
    // Prepare partitioning
    for (int i = 0; i < subgraphSize - 1; i++) {
        ptn[i] = 1;  // Set all but the last element to 1
    }
    // Last element naturally remains 0
    
    // Perform canonicalization
    nautyClassify(subgraph, subgraphSize, lab, nauty_g, canon);
    
    // Print canonical labeling
    std::cout << "Canonical Labeling:" << std::endl;
    for (int i = 0; i < subgraphSize; i++) {
        std::cout << i << " -> " << lab[i] << std::endl;
    }
    
    // Print orbits
    std::cout << "\nOrbits:" << std::endl;
    for (int i = 0; i < subgraphSize; i++) {
        std::cout << "Vertex " << i << ": Orbit " << orbits[i] << std::endl;
    }
    
    return 0;
}
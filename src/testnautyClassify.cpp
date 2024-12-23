#include <iostream>
#include "nautyClassify.h"

int main() {
    const int subgraphSize = 3;
    
    // Adjacency matrix: directed graph
    int subgraph[subgraphSize * subgraphSize] = {
        0, 0, 1,  // Node 0 has edge to node 2
        1, 0, 0,  // Node 1 has edge to node 0
        0, 1, 0   // Node 2 has edges to nodes 1
    };
    
    // Allocate results array
    int results[subgraphSize] = {-1};
    
    // Perform canonicalization
    nautyClassify(subgraph, subgraphSize, results);
    
    // Print canonical labeling
    std::cout << "Canonical Labeling:" << std::endl;
    for (int i = 0; i < subgraphSize; i++) {
        std::cout << "Node " << i << " -> " << results[i] << std::endl;
    }


    return 0;
}
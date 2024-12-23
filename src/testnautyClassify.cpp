#include <iostream>
#include "nautyClassify.h"
#include <vector>

// Function to print the canonical labeling
void printCanonicalLabeling(int subgraphSize, int results[]) {
    std::cout << "======== printCanonicalLabeling =======" << std::endl;
    std::cout << "Canonical Labeling:" << std::endl;
    for (int i = 0; i < subgraphSize; i++) {
        std::cout << "Node " << i << " -> " << results[i] << std::endl;
    }
    std::cout << "------------------------" << std::endl;
}

int main() {
    const int subgraphSize = 3;
    
    // Define multiple adjacency matrices as test cases
    std::vector<std::vector<int>> testCases = {
        {0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 1, 0}
    };
    
    // Iterate through each test case
    for (size_t tc = 0; tc < testCases.size(); tc++) {
        std::cout << "Test Case " << tc + 1 << ":" << std::endl;
        
        // Convert the test case to a flat array
        int subgraph[subgraphSize * subgraphSize];
        for (int i = 0; i < subgraphSize * subgraphSize; i++) {
            subgraph[i] = testCases[tc][i];
        }
        
        // Allocate and initialize the results array
        int results[subgraphSize];
        for (int i = 0; i < subgraphSize; i++) {
            results[i] = -1;  // Initialize all elements to -1
        }
        
        int performCheck = 0; // Change to 0 to skip the check

        // Perform canonicalization
        nautyClassify(subgraph, subgraphSize, results, performCheck);
        
        // Print canonical labeling
        printCanonicalLabeling(subgraphSize, results);
    }

    return 0;
}
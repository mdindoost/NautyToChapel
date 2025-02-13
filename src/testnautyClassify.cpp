#include <iostream>
#include "nautyClassify.h"
#include <vector>
#include <string>

// Function from the working code
bool isConnected(int from, int to, int* src, int* dst, int num_edges) {
    for(int i = 0; i < num_edges; i++) {
        if(src[i] == from && dst[i] == to) return true;
    }
    return false;
}

// Implementation from the working code
void workingNauty(int* src, int* dst, int subgraphSize, int num_edges) {
    int M = ((subgraphSize + WORDSIZE - 1) / WORDSIZE);
    
    graph nauty_g[MAXN * MAXM];
    int lab[MAXN], ptn[MAXN], orbits[MAXN];
    static DEFAULTOPTIONS_GRAPH(options);
    statsblk stats;
    setword workspace[160 * MAXM];
    graph canon[MAXN * MAXM];
    
    options.writeautoms = FALSE;
    options.getcanon = TRUE;
    options.defaultptn = TRUE;
    options.digraph = TRUE;
    
    // Initialize lab and ptn
    for (int i = 0; i < subgraphSize; i++) {
        lab[i] = i;
        ptn[i] = 1;
    }
    ptn[subgraphSize-1] = 0;
    
    // Initialize graph
    for (int i = 0; i < subgraphSize; i++) {
        set* gv = GRAPHROW(nauty_g, i, M);
        EMPTYSET(gv, M);
    }
    
    // Add edges
    for (int i = 0; i < num_edges; i++) {
        set* gv = GRAPHROW(nauty_g, src[i], M);
        ADDELEMENT(gv, dst[i]);
    }
    
    nauty(nauty_g, lab, ptn, NULL, orbits, &options, &stats, 
          workspace, 160*MAXM, M, subgraphSize, canon);
    
    std::cout << "\nWORKING CODE RESULTS:" << std::endl;
    std::cout << "lab array (vertex -> position):" << std::endl;
    for(int i = 0; i < subgraphSize; i++) {
        std::cout << "vertex " << i << " -> position " << lab[i] << std::endl;
    }
    
    // Initialize and create inverse mapping
    int inv_lab[MAXN];
    for(int i = 0; i < subgraphSize; i++) {
        inv_lab[i] = -1;
    }
    for(int v = 0; v < subgraphSize; v++) {
        int pos = lab[v];
        inv_lab[pos] = v;
    }
    
    std::cout << "\ninv_lab array (position -> vertex):" << std::endl;
    for(int i = 0; i < subgraphSize; i++) {
        std::cout << "position " << i << " -> vertex " << inv_lab[i] << std::endl;
    }
}

// Helper function to convert adjacency matrix to edge lists
void matrixToEdgeLists(const std::vector<int64_t>& matrix, int size, 
                      std::vector<int>& src, std::vector<int>& dst) {
    src.clear();
    dst.clear();
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(matrix[i * size + j]) {
                src.push_back(i);
                dst.push_back(j);
            }
        }
    }
}

int main() {
    const int size = 3;
    
    // Test cases
    std::vector<std::vector<int64_t>> testCases = {
        // Case 1: vertex 0 points to 1 and 2
        {0, 1, 1,
         0, 0, 0,
         0, 0, 0},
         
        // Case 2: vertex 1 points to 0 and 2
        {0, 0, 0,
         1, 0, 1,
         0, 0, 0},
         
        // Case 3: vertex 2 points to 0 and 1
        {0, 0, 0,
         0, 0, 0,
         1, 1, 0}
    };
    
    for (size_t tc = 0; tc < testCases.size(); tc++) {
        std::cout << "\n=== Test Case " << tc + 1 << " ===" << std::endl;
        
        // Convert matrix to edge lists for working code
        std::vector<int> src, dst;
        matrixToEdgeLists(testCases[tc], size, src, dst);
        
        // Run working code version
        std::cout << "\nRunning original working code:" << std::endl;
        workingNauty(src.data(), dst.data(), size, src.size());
        
        // Run your version
        std::cout << "\nRunning your version:" << std::endl;
        int64_t subgraph[size * size];
        std::copy(testCases[tc].begin(), testCases[tc].end(), subgraph);
        int64_t results[size];
        nautyClassify(subgraph, size, results, 0, 1);
        
        std::cout << "\nComparison of results:" << std::endl;
        std::cout << "Position | Working Code | My Code" << std::endl;
        std::cout << "---------|--------------|----------" << std::endl;
        for(int i = 0; i < size; i++) {
            std::cout << "    " << i << "    |      " << 
                     results[i] << "       |     " << 
                     results[i] << std::endl;
        }
        
        std::cout << "\n----------------------------------------\n";
    }
    
    return 0;
}
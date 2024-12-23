#include "nautyClassify.h"
#include <cstring>
#include <iostream>

void nautyClassify(
    int* subgraph,        // Adjacency matrix as flat array
    int subgraphSize,     // Number of nodes
    int* results,         // Output canonical labeling
    int performCheck      // Flag to perform nauty_check (1 to perform, 0 to skip)
) {

    // Ensure subgraphSize does not exceed MAXN
    if (subgraphSize > MAXN) {
        std::cerr << "Error: subgraphSize exceeds MAXN (" << MAXN << ")" << std::endl;
        return;
    }

    // Calculate number of words needed to represent the graph
    int M = (subgraphSize + WORDSIZE - 1) / WORDSIZE;

    // Allocate memory for Nauty data structures
    graph nauty_g[MAXN * MAXM];
    graph canon[MAXN * MAXM];
    int lab[MAXN];
    int ptn[MAXN];
    int orbits[MAXN];
    setword workspace[160 * MAXM];

    // Initialize lab and ptn
    for (int i = 0; i < subgraphSize; i++) {
        lab[i] = i;
        ptn[i] = 0;
    }

    // Clear Nauty graph representation
    for (int i = 0; i < subgraphSize; i++) {
        set* gv = GRAPHROW(nauty_g, i, M);
        EMPTYSET(gv, M);
        
        for (int j = 0; j < subgraphSize; j++) {
            if (i == j) continue;
            
            // Check if edge exists in the subgraph
            if (subgraph[i * subgraphSize + j]) {
                ADDELEMENT(gv, j);
                std::cout << "Adding edge from " << i << " to " << j << std::endl;
            }
        }
    }

    // Nauty options
    DEFAULTOPTIONS_GRAPH(options);
    options.writeautoms = FALSE;
    options.getcanon = TRUE;
    options.defaultptn = TRUE;
    options.digraph = TRUE; // Set to TRUE for directed graphs; FALSE for undirected

    statsblk(stats);


    // Conditionally perform nauty_check
    if (performCheck == 1) {
        nauty_check(WORDSIZE, M, subgraphSize, NAUTYVERSIONID);
        std::cout << "nauty_check. PASSED!" << std::endl;
    } else {
        std::cout << "Skipping nauty_check as performCheck is not set to 1." << std::endl;
    }

    nauty(nauty_g, lab, ptn, NULL, orbits, &options, &stats, 
          workspace, 160*MAXM, M, subgraphSize, canon);
    
    // Populate the results array with canonical labeling
	std::cout << "results array:" << std::endl;
    for (int i = 0; i < subgraphSize; i++) {
        results[i] = lab[i];
        std::cout << i << " -> " << results[i] << std::endl;
    }

	std::cout << "Partition array:" << std::endl;
	for (int i = 0; i < subgraphSize; i++) {
        std::cout << i << " -> " << ptn[i] << std::endl;
    }

}
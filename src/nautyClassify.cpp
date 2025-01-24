// File: src/nautyClassify.cpp

#include "nautyClassify.h"
#include <cstring>
#include <iostream>

extern "C" {

/**
 * @brief Performs graph canonicalization using Nauty.
 */
int64_t nautyClassify(
    int64_t subgraph[], 
    int64_t subgraphSize, 
    int64_t results[], 
    int64_t performCheck, 
    int64_t verbose
) {
    // Ensure subgraphSize does not exceed MAXN
    if (subgraphSize > MAXN) {
        std::cerr << "Error: subgraphSize exceeds MAXN (" << MAXN << ")" << std::endl;
        return -1; // Error code
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
                if (verbose) {
                    std::cout << "Adding edge from " << i << " to " << j << std::endl;
                }
            }
        }
    }

    // Nauty options
    DEFAULTOPTIONS_GRAPH(options);
    options.writeautoms = FALSE;
    options.getcanon = TRUE;
    options.defaultptn = TRUE;
    options.digraph = TRUE; // Set to TRUE for directed graphs; FALSE for undirected

    statsblk stats;

    // Conditionally perform nauty_check
    if (performCheck == 1) {
        nauty_check(WORDSIZE, M, subgraphSize, NAUTYVERSIONID);
        if (verbose) {
            std::cout << "nauty_check. PASSED!" << std::endl;
        }
    } else {
        if (verbose) {
            std::cout << "Skipping nauty_check as performCheck is not set to 1." << std::endl;
        }
    }

    nauty(nauty_g, lab, ptn, NULL, orbits, &options, &stats, 
          workspace, 160*MAXM, M, subgraphSize, canon);

    if (verbose) {
        // Log the canonical labeling before returning results
        std::cout << "Canonical Labeling (lab array):" << std::endl;
        for (int i = 0; i < subgraphSize; i++) {
            std::cout << "Node " << i << " -> " << lab[i] << std::endl;
        }
    }
    // Populate the results array with canonical labeling
    for (int i = 0; i < subgraphSize; i++) {
        results[i] = lab[i];
    }

    if (verbose) {
        std::cout << "Results array returned to Chapel:" << std::endl;
        for (int i = 0; i < subgraphSize; i++) {
            std::cout << "Node " << i << " -> " << results[i] << std::endl;
        }
    }

    return 0; // Success
}

/**
 * @brief C-compatible wrapper for nautyClassify.
 */
int64_t c_nautyClassify(
    int64_t subgraph[], 
    int64_t subgraphSize, 
    int64_t results[], 
    int64_t performCheck, 
    int64_t verbose
) {
        // Log what is passed to nautyClassify
    std::cout << "Calling nautyClassify with the following parameters:" << std::endl;
    std::cout << "subgraphSize: " << subgraphSize << std::endl;
    std::cout << "performCheck: " << performCheck << ", verbose: " << verbose << std::endl;

    // Log input arrays
    std::cout << "Input subgraph (flattened adjacency matrix):" << std::endl;
    for (int i = 0; i < subgraphSize; i++) {
        for (int j = 0; j < subgraphSize; j++) {
            std::cout << subgraph[i * subgraphSize + j] << " ";
        }
        std::cout << std::endl;
    }

    // Call the main nautyClassify function
    return nautyClassify(subgraph, subgraphSize, results, performCheck, verbose);
}


} // extern "C"

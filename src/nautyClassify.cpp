// File: src/nautyClassify.cpp

#include "nautyClassify.h"
#include <cstring>
#include <iostream>

extern "C" {

int64_t nautyClassify(
    int64_t subgraph[], 
    int64_t subgraphSize, 
    int64_t results[], 
    int64_t performCheck, 
    int64_t verbose
) {
    if (subgraphSize > MAXN) {
        std::cerr << "Error: subgraphSize exceeds MAXN (" << MAXN << ")" << std::endl;
        return -1;
    }

    int M = (subgraphSize + WORDSIZE - 1) / WORDSIZE;

    graph nauty_g[MAXN * MAXM];
    graph canon[MAXN * MAXM];
    int lab[MAXN], ptn[MAXN], orbits[MAXN];
    setword workspace[160 * MAXM];

    // Initialize lab and ptn like the working code
    for (int i = 0; i < subgraphSize; i++) {
        lab[i] = i;
        ptn[i] = 1;  // All vertices in same partition
    }
    ptn[subgraphSize-1] = 0;  // End the partition

    // Initialize graph
    for (int i = 0; i < subgraphSize; i++) {
        set* gv = GRAPHROW(nauty_g, i, M);
        EMPTYSET(gv, M);
    }
    
    // Add edges
    for (int i = 0; i < subgraphSize; i++) {
        for (int j = 0; j < subgraphSize; j++) {
            if (i == j) continue;
            if (subgraph[i * subgraphSize + j]) {
                set* gv = GRAPHROW(nauty_g, i, M);
                ADDELEMENT(gv, j);
                if (verbose) {
                    std::cout << "Adding edge from " << i << " to " << j << std::endl;
                }
            }
        }
    }

    DEFAULTOPTIONS_GRAPH(options);
    options.writeautoms = FALSE;
    options.getcanon = TRUE;
    options.defaultptn = TRUE;  // Use default partitioning like working code
    options.digraph = TRUE;

    statsblk stats;

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
        std::cout << "Canonical Labeling (lab array):" << std::endl;
        for (int i = 0; i < subgraphSize; i++) {
            std::cout << "Node " << i << " -> " << lab[i] << std::endl;
        }
    }

    // Create inverse mapping like the working code
    int inv_lab[MAXN];
    for(int i = 0; i < subgraphSize; i++) {
        inv_lab[i] = -1;  // Initialize to invalid value
    }
    for(int v = 0; v < subgraphSize; v++) {
        int pos = lab[v];
        inv_lab[pos] = v;
    }

    // Copy results using inverse mapping
    for (int i = 0; i < subgraphSize; i++) {
        results[i] = lab[i];
    }

    if (verbose) {
        std::cout << "Results array returned to Chapel:" << std::endl;
        for (int i = 0; i < subgraphSize; i++) {
            std::cout << "Node " << i << " -> " << results[i] << std::endl;
        }
    }

    return 0;
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
    return nautyClassify(subgraph, subgraphSize, results, performCheck, verbose);
}

} // extern "C"
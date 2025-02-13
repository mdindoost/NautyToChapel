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
    if (verbose) {
        std::cout << "\n==== Starting Nauty Classification ====" << std::endl;
        std::cout << "Parameters:" << std::endl;
        std::cout << "subgraphSize: " << subgraphSize << std::endl;
        std::cout << "performCheck: " << performCheck << std::endl;
    }

    if (subgraphSize > MAXN) {
        std::cerr << "Error: subgraphSize exceeds MAXN (" << MAXN << ")" << std::endl;
        return -1;
    }

    if (verbose) {
        std::cout << "\nInput matrix:" << std::endl;
        for(int i = 0; i < subgraphSize; i++) {
            std::cout << "Row " << i << ": ";
            for(int j = 0; j < subgraphSize; j++) {
                std::cout << subgraph[i * subgraphSize + j] << " ";
            }
            std::cout << std::endl;
        }

        // Test 1: Check matrix validity
        std::cout << "\nTest 1 - Matrix Validation:" << std::endl;
        int edgeCount = 0;
        for(int i = 0; i < subgraphSize * subgraphSize; i++) {
            if(subgraph[i] != 0 && subgraph[i] != 1) {
                std::cout << "Warning: Non-binary value found in matrix: " << subgraph[i] << std::endl;
            }
            if(subgraph[i] == 1) edgeCount++;
        }
        std::cout << "Edge count: " << edgeCount << std::endl;
    }

    int M = (subgraphSize + WORDSIZE - 1) / WORDSIZE;

    if (verbose) {
        std::cout << "\nMemory Configuration:" << std::endl;
        std::cout << "M (words needed): " << M << std::endl;
        std::cout << "MAXM: " << MAXM << std::endl;
        std::cout << "MAXN: " << MAXN << std::endl;
        std::cout << "Required space: " << MAXN * MAXM << " words" << std::endl;
    }

    // Test 2: Memory bounds check
    if (M > MAXM) {
        std::cerr << "Error: Required words (" << M << ") exceeds MAXM (" << MAXM << ")" << std::endl;
        return -1;
    }

    graph nauty_g[MAXN * MAXM];
    graph canon[MAXN * MAXM];
    int lab[MAXN];
    int ptn[MAXN];
    int orbits[MAXN];
    setword workspace[160 * MAXM];

    // Initialize lab and ptn
    if (verbose) std::cout << "\nInitializing lab and ptn arrays:" << std::endl;
    for (int i = 0; i < subgraphSize; i++) {
        lab[i] = i;
        //ptn[i] = 1;
        if (verbose) std::cout << "lab[" << i << "] = " << lab[i] << ", ptn[" << i << "] = " << ptn[i] << std::endl;
    }
    ptn[subgraphSize-1] = 0;

    // Create nauty graph
    if (verbose) std::cout << "\nCreating Nauty graph representation:" << std::endl;
    for (int i = 0; i < subgraphSize; i++) {
        set* gv = GRAPHROW(nauty_g, i, M);
        EMPTYSET(gv, M);
        
        for (int j = 0; j < subgraphSize; j++) {
            if (i == j) continue;
            if (subgraph[i * subgraphSize + j]) {
                ADDELEMENT(gv, j);
                if (verbose) std::cout << "Added edge: " << i << " -> " << j << std::endl;
            }
        }
    }

    // Nauty options
    DEFAULTOPTIONS_GRAPH(options);
    options.writeautoms = FALSE;
    options.getcanon = TRUE;
    options.defaultptn = TRUE;
    options.digraph = TRUE;

    statsblk stats;

    if (verbose) {
        std::cout << "\nPre-Nauty state:" << std::endl;
        std::cout << "lab array: ";
        for(int i = 0; i < subgraphSize; i++) {
            std::cout << lab[i] << " ";
        }
        std::cout << std::endl;
    }

    // Call nauty
    if (verbose) std::cout << "\nCalling nauty..." << std::endl;
    nauty(nauty_g, lab, ptn, NULL, orbits, &options, &stats, 
          workspace, 160*MAXM, M, subgraphSize, canon);

    if (verbose) {
        std::cout << "Nauty call completed" << std::endl;
        std::cout << "\nPost-Nauty state:" << std::endl;
        std::cout << "lab array: ";
        for(int i = 0; i < subgraphSize; i++) {
            std::cout << lab[i] << " ";
        }
        std::cout << std::endl;
    }

    // Validate results
    if (verbose) std::cout << "\nValidating Nauty results:" << std::endl;
    bool used[MAXN] = {false};
    for(int i = 0; i < subgraphSize; i++) {
        if(lab[i] < 0 || lab[i] >= subgraphSize) {
            std::cerr << "Error: Invalid label at position " << i << ": " << lab[i] << std::endl;
            return -1;
        }
        if(used[lab[i]]) {
            std::cerr << "Error: Duplicate label found: " << lab[i] << std::endl;
            return -1;
        }
        used[lab[i]] = true;
        if (verbose) std::cout << "Position " << i << " -> label " << lab[i] << " (valid)" << std::endl;
    }

    // Copy results
    if (verbose) std::cout << "\nCopying final results:" << std::endl;
    for (int i = 0; i < subgraphSize; i++) {
        results[i] = lab[i];
        if (verbose) std::cout << "results[" << i << "] = " << results[i] << std::endl;
    }

    if (verbose) std::cout << "\n==== Nauty Classification Complete ====\n" << std::endl;
    return 0;
}

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


// File: include/nautyClassify.h

#ifndef NAUTY_CLASSIFY_H
#define NAUTY_CLASSIFY_H

#include "nauty.h"
#include <stdint.h> // For fixed-width integer types

// Define constants
#define MAXN 1000   // Maximum number of vertices in motif
#define MAXM 100    // Maximum number of words to represent graph

// Type definitions similar to Kavosh
typedef int vertex;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Performs graph canonicalization using Nauty.
 *
 * @param subgraph       Adjacency matrix as a flat array.
 * @param subgraphSize   Number of nodes in the graph.
 * @param results        Array to store the canonical labeling.
 * @param performCheck   Flag to perform nauty_check (1 to perform, 0 to skip).
 * @param verbose        Flag to control verbosity (1 to enable, 0 to disable).
 * @return int           Status code (0 for success, -1 for error).
 */
int64_t nautyClassify(
    int64_t subgraph[],        // Adjacency matrix as flat array
    int64_t subgraphSize,     // Number of nodes
    int64_t results[],         // Output canonical labeling
    int64_t performCheck,     // Flag to perform nauty_check (1 to perform, 0 to skip)
    int64_t verbose           // Flag to control verbosity (1 to enable, 0 to disable)
);

int64_t c_nautyClassify(
    int64_t subgraph[], 
    int64_t subgraphSize, 
    int64_t results[], 
    int64_t performCheck, 
    int64_t verbose
);

#ifdef __cplusplus
}
#endif

#endif // NAUTY_CLASSIFY_H

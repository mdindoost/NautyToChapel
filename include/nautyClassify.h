#ifndef NAUTY_CLASSIFY_H
#define NAUTY_CLASSIFY_H

extern "C" {
    #include <nauty.h>
}

#define MAXN 1000   // Maximum number of vertices in motif
#define MAXM 100    // Maximum number of words to represent graph

// Type definitions similar to Kavosh
typedef int vertex;

// Function declaration for nauty classification
// Takes subgraph, its size, results array, and performCheck
void nautyClassify(
    int* subgraph,        // Adjacency matrix as flat array
    int subgraphSize,     // Number of nodes
    int* results,         // Output canonical labeling
    int performCheck      // Flag to perform nauty_check (1 to perform, 0 to skip)
);

#endif // NAUTY_CLASSIFY_H
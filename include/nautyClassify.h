#ifndef NAUTY_CLASSIFY_H
#define NAUTY_CLASSIFY_H

extern "C" {
    #include <nauty.h>
}

#define MAXN 1000   // Maximum number of vertices
#define MAXM 100    // Maximum number of words to represent graph

// Type definitions similar to Kavosh
typedef int vertex;

// Function declaration for nauty classification
// Now only takes subgraph, its size, and results array
void nautyClassify(
    int* subgraph,        // Adjacency matrix as flat array
    int subgraphSize,     // Number of nodes
    int* results          // Output canonical labeling
);

#endif // NAUTY_CLASSIFY_H
#ifndef NAUTY_CALLER_H
#define NAUTY_CALLER_H

extern "C" {
    #include <nauty.h>
}

#define MAXN 1000   // Maximum number of vertices
#define MAXM 100    // Maximum number of words to represent graph

// Type definitions similar to Kavosh
typedef int vertex;

// Function declaration for nauty classification
void nautyClassify(
    int* subgraph,        // Adjacency matrix as flat array
    int subgraphSize,     // Number of nodes
    int* lab,             // Output canonical labeling
    graph* nauty_g,       // Nauty graph representation
    graph* canon          // Output canonical graph
);

#endif // NAUTY_CALLER_H
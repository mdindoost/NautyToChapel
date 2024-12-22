#include "../include/nautyCaller.h"
#include <cstring>
#include <iostream>

void nautyClassify(
    int* subgraph,        // Adjacency matrix as flat array
    int subgraphSize,     // Number of nodes
    int* lab,             // Output canonical labeling
    graph* nauty_g,       // Nauty graph representation
    graph* canon          // Output canonical graph
) {
    // Calculate number of words needed to represent the graph
    int M = (subgraphSize + WORDSIZE - 1) / WORDSIZE;
    
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
    
    // Prepare partitioning and labeling
    int ptn[MAXN] = {0};
    int orbits[MAXN];
    
    for (int i = 0; i < subgraphSize; i++) {
        lab[i] = i;
        ptn[i] = 0;
    }
    //ptn[subgraphSize - 1] = 0;
    
    // Nauty options
    static DEFAULTOPTIONS_GRAPH(options);
    options.writeautoms = FALSE;
    options.getcanon = TRUE;
    options.defaultptn = TRUE;
	options.digraph = TRUE;

    statsblk(stats);
    setword workspace[160*MAXM];

    // Perform canonicalization
    nauty_check(WORDSIZE, M, subgraphSize, NAUTYVERSIONID);

    std::cout << "nauty_check. PASSED!" << std::endl;
    
    nauty(nauty_g, lab, ptn, NULL, orbits, &options, &stats, 
          workspace, 160*MAXM, M, subgraphSize, canon);

	std::cout << "Partition array:" << std::endl;
    
	for (int i = 0; i < subgraphSize; i++) {
        std::cout << i << " -> " << ptn[i] << std::endl;
    }
    //  delete [] lab;
    //  delete [] ptn	;
    //  delete [] orbits;
	//  delete [] nauty_g;
}
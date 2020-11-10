// Compile this assignment with: gcc main.c -o main

//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"
#include "myqueue.h"
#include "tests.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

// ====================================================
// ================== Program Entry ===================
// ====================================================

void tests() {
    testCreate();

    graph_t* testGraph = create_graph();
    testEmpty(testGraph);
    testAdd();
    testContains();
    testAddEdge();
    testGets();
    testContainEdge();
    testNumNeigh();
    testNeighArr();
    testRemoveEdge(); 
    testRemoveNode();
    testQ();
    testPrintGraph();
    testReachable();
    testCycle();
    free_graph(testGraph);    

}


int main(){
    tests();
    return 0;
}

















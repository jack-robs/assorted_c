// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_bst.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

// ====================================================
// ================== Program Entry ===================
// ====================================================

int testers() {
    printf("in testers\n");
    bst_t* tester = create_bst();
    testCreate(tester);
    testEmpty(tester);
    testAdd(tester);
    testPrint(tester);
    testSum(tester);
    testFind(tester);
    free_bst(tester);


}


int main(){
    bst_t * testBST = create_bst();
    testers();
    free_bst(testBST);    
    return 0;
}

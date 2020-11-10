// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "mystack.h"
// Note that we are locating this file
// within the same directory, so we use quotations 
// and provide the path to this file which is within
// our current directory.


// A sample test of your program
// You need to add sufficient testing.
void unitTest0(){
    printf("\n********\nunitTest0\n********\n");
	stack_t* test1 = create_stack(MAX_DEPTH);
	printf("Attempting to push %d\n",1);
	stack_enqueue(test1,1);	
	printf("Removing: %d\n",stack_dequeue(test1));	

	free_stack(test1);
}

void unitTest1() {
    printf("\n********\nunitTest1 Create\n********\n");
    stack_t* test0 = create_stack(4);
    test0->count = 2;
    printf("Expected capacity 4, actual: %d\n", test0->capacity);
    printf("Expected count 2, actual: %d\n", test0->count);
    printf("Node linkage, pointer expected: %p\n", test0->head); 

    free(test0);
}

void unitTest2() {
    printf("\n********\nunitTest2 Empty?\n********\n");
    stack_t* test0 = create_stack(3);
    // empty
    test0->count = 0;
    int tval0 = stack_empty(test0);
    printf("Expected return 1, actual %d\n", tval0);

    // 1 element
    test0->count = 1;
    int tval1 = stack_empty(test0);
    printf("Expected return 0, actual %d\n", tval1);
    
    free(test0);
} 


void unitTest3() {
    printf("\n********\nunitTest3 full\n********\n");
    stack_t* test0 = create_stack(3);
    test0->count = 3;
    int tval0 = stack_full(test0);
    
    // full
    printf("Full, expected 1, actual: %d\n", tval0);

    test0->count = 2;
    // not full
    printf("Not Full, expected 0, actual: %d\n", tval0);
}

void unitTest4() {
    printf("\n********\nunitTest4 Size\n********\n");
    stack_t* test0 = create_stack(3);
    test0->count = 2;
    printf("test count, %d\n", test0->count); 
    int tval0 = stack_size(test0);
    printf("Expected size, 2, actual: %d\n", tval0); 
    test0->count = 0; 
    int tval1 = stack_size(test0);
    printf("Expected size, 0, actual: %d\n", tval1);  
}
// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){

	// List of Unit Tests to test your data structure	
	unitTest1();
    unitTest2();
    unitTest3();
    unitTest4();
	return 0;
}




























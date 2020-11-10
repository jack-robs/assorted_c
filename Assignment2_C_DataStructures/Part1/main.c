;// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "myqueue.h"
// Note that we are locating this file
// within the same directory, so we use quotations 
// and provide the path to this file which is within
// our current directory.

// test create_queue(usigned int _capacity)
void unitTest0Create() {
    
    printf("**********\nUNIT TEST 0: CREATE Q\n*************\n");    
    // create 2-cap queue
    queue_t* test0 = create_queue(2);
    // print values created
    test0->back = 1;
    test0->front = 2;
    test0->size = 3;
    printf("Back test. Exp 1, Act: %d\n", test0->back); 
    printf("front test. Exp 2, Act:  %d\n", test0->front);
    printf("size test. Exp 3, Act:  %d\n", test0->size);
    printf("capacity test: Exp 2, Act:  %d\n", test0->capacity);
    printf("Data array test (pointer) %p\n", test0->data);  
    
    free_queue(test0);
    
}


// test queue_empty(queue_t* q)
void unitTest1Empty() {
    printf("**********\nUNIT TEST 1: EMPTY\n*************\n");    
    // return 1
    queue_t* test0 = create_queue(0);
    int tval = queue_empty(test0);
    printf("Empty Return 1, Actual:%d\n", tval);

    // return 0
    queue_t* test1 = create_queue(1);
    test1 ->size = 1;
    int tval1 = queue_empty(test1);
    printf(">0 Expected Return 0, Actual %d\n", tval1);

//    // TODO fix, current seg fault
//    // return -1
//    queue_t* test3 = NULL;
//    int tval3 = queue_empty(test3);
//    printf("NULL, Expected Return NULL, Actual %d\n", tval3);
    
    free_queue(test0);
    free_queue(test1);

}

// test queue_full(queue_t* q)
void unitTest2Full() {
    printf("**********\nUNIT TEST 2: FULL QUEUE\n*************\n");    
    // return 1 full queue
    // capacity 2 queue
    queue_t* test0 = create_queue(2);
    test0->size = 2;
    int tval0 = queue_full(test0);  
    printf("Full queue, Exp 1, Actual: %d\n", tval0);

    // return 0 not full queue
    queue_t* test1 = create_queue(3);
    test1->size = 2;
    int tval1 = queue_full(test1);  
    printf("Full queue, Exp 0, Actual: %d\n", tval1);
          
    // return -1 queue NULL
    // SEG FAULT

    free_queue(test0);
    free_queue(test1);

}

void unitTest3EnQu() {
    // FIFO
    
    printf("**********\nUNIT TEST 3: ENQUE\n*************\n");    
 
    //return 0 if no add, cap=size
    queue_t* test0 = create_queue(3);
    test0->size = 3;
    int item0 = 0;
    int tval0 = queue_enqueue(test0, item0);
    printf("Full Queue, Exp 0, Actual: %d\n", tval0);

    // return 1 if success add, cap>size
    queue_t* test1 = create_queue(3);
    test1->size = 1;
    test1->front = 1;
    test1->data[test1->front] = 20;
    test1->back = 2;
    int item1 = 10; 
    int tval1 = queue_enqueue(test1, item1);
    printf("Space-a, Front ind, expect 1, act %d\n", test1->front);
    printf("Space-a, Front val, expect 20, act %d\n", test1->data[test1->front]);
    printf("Space-a, back ind, expect 3, act %d\n", test1->back);
    printf("Space-a, Front val, expect 10, act %d\n", test1->data[test1->back]);
    printf("Queue with space, Exp 1, Actual: %d\n", tval1);

    // empty queue
    queue_t* test3 = create_queue(4);
    test3->size = 0;
    int item3 = 30;
    int tval3 = queue_enqueue(test3, item3);
    printf("Empty q-enq, Front value, expect 0, act %d\n", test3->front);
    printf("Value at data[0], expected 30, act %d\n", test3->data[test3->front]);

    // return -1 if null return
    // fix segfault

    // frees
    free_queue(test0);
    free_queue(test1);
    free_queue(test3);
}


void unitTest4DeQu() {
    // FIFO
    
    printf("**********\nUNIT TEST 4: DEQ\n*************\n");    
    // empty queue
    queue_t* test0 = create_queue(4); 
    test0->size = 0;
    int tval0 = queue_dequeue(test0);
    printf("Empty Q, Deq, Exp r0, act:%d\n", tval0);

    //reg queue
    queue_t* test1 = create_queue(4);
    test1->size = 3;
    test1->front = 3;
    test1->data[test1->front] = 11;
    int newFront = (test1->front + 1) % test1->capacity;
    test1->data[newFront] = 10;
    printf("Initial front before queue: %d\n", test1->front);
    printf("Init Front value[], exp: 11, actual: %d\n", test1->data[test1->front]);
    printf("Anticipated new front and []. %d and [%d]\n", newFront, test1->data[newFront]);
    int tval1 = queue_dequeue(test1);
    printf("After: return-  expected 0, act: %d\n", tval1);
    printf("After: new front, expected 0, act: %d\n", test1->front);
    printf("After: new front[], expected 10, act: %d\n", test1->data[test1->front]);

    //free queues
    free(test0);
    free(test1);
}

void unitTest5Size() {
    printf("**********\nUNIT TEST 5: Size\n*************\n");    
    //empty q
    queue_t* test0 = create_queue(0);
    test0->size = 0;
    int tval0 = queue_size(test0);
    printf("Current size, expected 0, act: %d\n", tval0);

    //populated q
    queue_t* test1 = create_queue(2);
    test1->size = 2;
    int tval1 = queue_size(test1);
    printf("Current size, expected 2, act: %d\n", tval1);
   
    free(test0);
    free(test1); 

}




// A sample test of your program
// You need to add sufficient testing.
void unitTest10(){

    printf("**********\nUNIT TEST 10: EXAMPLE\n*************\n");    
	queue_t* test10 = create_queue(1);
	printf("Attempting to add %d\n",1);
	queue_enqueue(test10,1);	
	printf("Removing: %d\n",queue_dequeue(test10));	

	free_queue(test10);
}


// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){

	// List of Unit Tests to test your data structure	
    unitTest0Create();
	unitTest1Empty();
    unitTest2Full();
    unitTest3EnQu();
    unitTest4DeQu();
    unitTest5Size();
    unitTest10();
	return 0;
}

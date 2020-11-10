// =================== Support Code =================
// Queue
//
//
//
// - Implement each of the functions to create a working circular queue.
// - Do not change any of the function declarations
//   - (i.e. queue_t* create_queue(unsigned int _capacity) should not have additional arguments)
// - You should not have any 'printf' statements in your queue functions. 
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// ==================================================



// ifndef allows for conditional compilation
// preprocessor determines if provided macros does not exist, before including the subsequent code in the comp process
//https://www.techonthenet.com/c_language/directives/ifndef.php
// MYQUEUE is a macro...
#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <stdlib.h>

// The main data structure for the queue

// struct is a custom data type, for 'composite data'
struct queue{
    // struct fields, can be filled with queue.field
    
	int back;	    // The next free position in the queue	
			                  // (i.e. the end or tail of the line)

	int front;	    // Current 'head' of the queue
				                  // (i.e. the front or head of the line)

	int size;	    // How many total elements we currently have enqueued.

	int capacity;  // Maximum number of items the queue can hold

	int* data; 		          // The 'integer' data our queue holds	
};

// Creates a global definition of 'queue_t' so we 
// do not have to retype 'struct queue' everywhere.
typedef struct queue queue_t;

// Create a queue
// Returns a pointer to a newly created queue.
// The queue should be initialized with data on
// the heap.
// If you weren't able to allocate memory, return NULL.
queue_t* create_queue(int _capacity){    
 
    // malloc myQueue
    queue_t* myQueue;
    myQueue = (queue_t*)malloc(sizeof(queue_t));
    if (myQueue) {

        // create a queue: 
        myQueue->back = 0;
        myQueue->front = 0;
        myQueue->size = 0;
        myQueue->capacity = _capacity;
        printf("capacity %d %d\n", myQueue->capacity, _capacity);
            
        // malloc returns memory address accessible by an array
        myQueue->data = (int*)malloc(sizeof(int) * _capacity); 
        
     
        // if malloc array fails, return a NULL
        // assert(myQueue != NULL);
        // returns pointer
        return myQueue;}
    else {
        return 0;}
}

// Queue Empty
// Check if the queue is empty
// Returns 1 if true (The queue is completely empty)
// Returns 0 if false (the queue has at least one element enqueued)
// Returns -1 if the queue is NULL
int queue_empty(queue_t* q){
    
    if (q->size == 0) {
        return 1;
    } else if (q->size > 0) {
        return 0;
    } else if (!q) {
        return -1; 
    }
}

// Queue Full
// Check if the queue is Full
// Returns 1 if true (The queue is completely full)
// Returns 0 if false (the queue has more space available to enqueue items)
// Returns -1 if the queue is NULL.
int queue_full(queue_t* q){
    
    if (q->size == q->capacity) {
        return 1; 
    } else if (q->size < q->capacity) {
        return 0;
    } else if (!q) {
        return -1;
    }
}

// Enqueue a new item
// i.e. push a new item into our data structure
// Returns a 0 if the operation fails 
// Returns a 1 if the operation suceeds
// Returns -1 if the queue is NULL.
// (i.e. if the queue is full that is an error).
int queue_enqueue(queue_t* q, int item){
        printf("********in eq\n");
        
        if (!q) {
            return -1;
        }

        printf("********in eq\n");
        if (q->size == q->capacity) {
    
            return 0;
        }

        printf("********in eq\n");
        q->data[q->back] = item;
        q->back = (q->back + 1) % q->capacity;
        q->size ++;
        return 1;
}

// Dequeue an item
// Returns the item at the front of the queue and
// removes an item from the queue.
// Removing from an empty gueue should return 0 // assume all entries are going to be > 0.
// Returns -1 if the queue is NULL. Assumption there is not going to be negative numbers in the queue
int queue_dequeue(queue_t *q){
        //check empty queue
        if (q->size == 0) {
            return 0;
        } else if (q->size > 0){
            // increment front val
            int data = q->data[q->front];
            int newFront = (q->front+1) % q->capacity;
            q->front = newFront;
            return data; 
        }
        else {
		    return -1; 
        }
}

// Queue Size
// Queries the current size of a queue
// Returns -1 if the queue is NULL.
unsigned int queue_size(queue_t* q){
    int currentSize = q->size;
    return currentSize;
    
    //else return -1    

}


// Free queue
// Removes a queue and all of its elements from memory.
// This should be called before the proram terminates.
void free_queue(queue_t* q){
//    int i = 0;
//    g_node* swingNode = q->front;
//    while (i < q->size) {
//        g_node* prevNode = swingNode;
//        swingNode = swingNode->next;
//        free(prevNode);
//    }
//    free(swingNode);
//    free(q);

    free(q);
}


#endif

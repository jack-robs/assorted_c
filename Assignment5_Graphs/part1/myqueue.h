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
#include <stdio.h>
#include <stdlib.h>


typedef struct queue{
	int size;		
	struct q_node* head;	 
    struct q_node* tail;
}queue_t;

typedef struct q_node{
	int data;
	struct q_node* next;
    struct q_node* prev;
}q_node;

// Creates a global definition of 'queue_t' so we 
// do not have to retype 'struct queue' everywhere.

// Create a queue
// Returns a pointer to a newly created queue.
// The queue should be initialized with data on
// the heap.
// If you weren't able to allocate memory, return NULL.
queue_t* create_queue(){    
 
    // malloc myQueue
    queue_t* myQueue;
    myQueue = (queue_t*)malloc(sizeof(queue_t));
    if (myQueue) {

        // create a queue: 
        myQueue->head = NULL;
        myQueue->tail = NULL;
        myQueue->size = 0;

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

// Enqueue a new item
// i.e. push a new item into our data structure
// Returns a 0 if the operation fails 
// Returns a 1 if the operation suceeds
// Returns -1 if the queue is NULL.
// (i.e. if the queue is full that is an error).
int queue_enqueue(queue_t* q, int item){
        // check size vs. capacity
        // full queue

        q_node* newQ = (q_node*)malloc(sizeof(q_node));
        newQ->data = item;
        newQ->prev = NULL;
        newQ->next == NULL;

        if (q->size == 0) {
            q->head = newQ;
            q->tail = newQ;
            q->size ++;
            return 0;
        } else {
            q_node* oldTail = q->tail;
            oldTail->next = newQ;
            q->tail = newQ;
            newQ->prev = oldTail;
            q->size ++;
            return 0;
        }
		return 1; // Note: you should have two return statements in this function.
}

void printQueue(queue_t* q) {

    printf("\nQueue:\n");
    printf("front>");
    q_node* swingQ =  q->head;

    for (int i = 0; swingQ->next != NULL; i++) {
       printf("[%d]", swingQ->data);
       swingQ = swingQ->next;
    }
    printf("[%d]", swingQ->data);
    printf("<back\n\n");
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

            q_node* newFront = q->head->next;
            q_node* kill = q->head;
            int value = q->head->data;
            free(kill);
            q->head = newFront;

            q->size --;
            return value; 
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
    q_node* freeq = q->head;

    while (freeq) {
        q_node* tempq = freeq;
        freeq = tempq->next;
        free(tempq);
    }
    free(q);
}



#endif

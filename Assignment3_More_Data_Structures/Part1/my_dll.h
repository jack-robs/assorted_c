// =================== Support Code =================
// Doubly Linked List ( DLL ).
//
//
//
// - Implement each of the functions to create a working DLL.
// - Do not change any of the function declarations
//   - (i.e. dll_t* create_dll() should not have additional arguments)
// - You should not have any 'printf' statements in your DLL functions. 
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// ==================================================
#ifndef MYDLL_H
#define MYDLL_H
#include <stdlib.h>
#include <stdio.h>

// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node{
	int data;
	struct node* next;
  	struct node* previous;
}node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL{
	int count;		// count keeps track of how many items are in the DLL.
	node_t* head;		// head points to the first node in our DLL.
    node_t * tail;          //tail points to the last node in our DLL.
}dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
dll_t* create_dll(){
	// Modify the body of this function as needed.
	dll_t* myDLL= NULL;	
    myDLL = (dll_t*)malloc(sizeof(dll_t*));

    // confirm no NULL, instantiate head/tail NULL nodes and count
    if (myDLL) {
        myDLL->count = 0;    
        myDLL->head = (node_t*)malloc(sizeof(node_t*));
        myDLL->tail = (node_t*)malloc(sizeof(node_t*)); 
        return myDLL;
    } else {
    return 0;
    }
}

void testCreate() {
    dll_t* test_dll = create_dll();
    printf("\n**** testCreate() ****\n");
    printf("Test Count, E: 0, A: %d\n", test_dll->count);
    printf("Test Count, E: p*, A: %p\n", test_dll->head);
    printf("Test Count, E: p*, A: %p\n", test_dll->tail);

}

// DLL Empty
// Check if the DLL is empty
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t* l){
    if (l->count == 0) {
        return 1;
    } else {
	return 0;
    }
}

void testEmpty() {
    dll_t* emptyL = create_dll();
    int tval0 = dll_empty(emptyL);
    printf("\n*** testEmpty() ***\n");
    printf("Test Count, E: 0, A:%d\n", tval0);

    emptyL->count == 1;
    int tval1 = dll_empty(emptyL);
    printf("Test Count, E1:, A:%d\n",tval1);

    free(emptyL);
}

// push a new item to the front of the DLL ( before the first node in the list).
// Returns a -1 if the operation fails ( and if the DLL is NULL), otherwise returns 1 on success.
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t* l, int item){
    if (l) {
        // check empty list
        if (l->count == 0) {
            // add data to existing null node
            l->head->data = item;

            //iterate count, dll is no longer empty
            l->count ++;
            return 1;  

        } else {
            // stage and build new node//
            // create node
            node_t* newNode = (node_t*)malloc(sizeof(node_t*));  
            // add item to node 
            newNode->data = item;
            newNode->previous = NULL;
            // linkage process //
            // point newNode's next at current head: newNode->next->dll->head;
            newNode->next = l->head;
            // point current head's previous at newNode: dll->head->previous->newNode
            l->head->previous = newNode;
            // point dll head at new node: dll->head->newNode
            l->head = newNode; 
            l->count ++;
            return 1;
        }

    } else {
		return -1;
    }
}

void testPushFront() {
    dll_t* testPush = create_dll();
    printf("\n*** test empty list pushfront ***\n");
    printf("Before push 0, count E:0 A:%d, head E:p, A:%p\n", testPush->count, testPush->head);
    int tval0 = dll_push_front(testPush, 88);
    printf("expected tval0 1, actual %d\n,", tval0);
    printf("After push to empty, count E:1, A:%d, head E: same as prev., A:%p, Data in head E:88, A:%d\n", testPush->count, testPush->head, testPush->head->data);
    
    printf("\n*** test occupied list pushfront ***\n");
    printf("Before push 1, count E:1 A:%d, head E:p, A:%p\n", testPush->count, testPush->head);
    int tval1 = dll_push_front(testPush, 77);
    printf("expected tval1 1, actual %d\n,", tval1);
    printf("After push to empty, count E:1, A:%d, head E: same as prev., A:%p, Data in head E:88, A:%d\n", testPush->count, testPush->head, testPush->head->data);
    printf("After push to 1count, count E:2, A:%d, head E: new,  A:%p, Data in head E:77, A:%d\n", testPush->count, testPush->head, testPush->head->data);
    printf("Before push 2, count E:2 A:%d, head E:p, A:%p\n", testPush->count, testPush->head);
    int tval2 = dll_push_front(testPush, 66);
    printf("expected tval2 1, actual %d\n,", tval2);
    printf("After push to empty, count E:1, A:%d, head E: same as prev., A:%p, Data in head E:88, A:%d\n", testPush->count, testPush->head, testPush->head->data);
    printf("After push 2 to 2count, count E:3, A:%d, head E: new,  A:%p, Data in head E:66, A:%d\n", testPush->count, testPush->head, testPush->head->data);

    free(testPush);
}

// push a new item to the end of the DLL (after the last node in the list).
// Returns a -1 if the operation failsm (and if the DLL is NULL), otherwise returns 1 on success.
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* l, int item){
        if (l) {
            if (l->count == 0) {
            // add data to existing null node
            l->head->data = item;

            //iterate count, dll is no longer empty
            l->count ++;
            return 1;  

        } else {
            // stage and build new node//
            // create node
            node_t* newNode = (node_t*)malloc(sizeof(node_t*));  
            // add item to node 
            newNode->data = item;

            // linkage process //
            
            // point current tails's next at newNode (currently tail->next= NULL)
            l->tail->next = newNode;

            // point newNode's next at current tail: 
            newNode->previous = l->tail;

            // point dll tail at new node:
            l->tail = newNode;

            l->count ++;
                 
            return 1;
            }
        } else {
		return -1; 
        }
}

void testPushBack() {
    dll_t* testPush = create_dll();
    printf("\n*** test empty list pushback ***\n");
    printf("Before push 0, count E:0 A:%d, tail E:p, A:%p\n", testPush->count, testPush->tail);
    int tval0 = dll_push_back(testPush, 88);
    printf("expected tval0 1, actual %d\n,", tval0);
    printf("After push to empty, count E:1, A:%d, tail E: same as prev., A:%p, Data in tail E:88, A:%d\n", testPush->count, testPush->tail, testPush->head->data);
    
    printf("\n*** test occupied list pushback ***\n");
    printf("\n");
    printf("Before push 1, count E:1 A:%d, tail E:p, A:%p\n", testPush->count, testPush->tail);
    int tval1 = dll_push_back(testPush, 77);
    printf("expected tval1 1, actual %d\n,", tval1);
    printf("After push to 1count, count E:2, A:%d, tail E: new,  A:%p, Data in tail E:77, A:%d\n", testPush->count, testPush->tail, testPush->tail->data);
    printf("\n");
    printf("Before push 2, count E:2 A:%d, tail E:same as previous, A:%p\n", testPush->count, testPush->tail);
    int tval2 = dll_push_back(testPush, 66);
    printf("expected tval2 1, actual %d\n,", tval2);
    printf("After push 2 to 2count, count E:3, A:%d, tail E: new,  A:%p, Data in tail E:66, A:%d\n", testPush->count, testPush->tail, testPush->tail->data);

    free(testPush);
}

// Returns the first item in the DLL and also removes it from the list.
// Returns a -1 if the operation fails (and if the DLL is NULL). Assume no negative numbers in the list.
int dll_pop_front(dll_t* t){
    if (t) { 
        // get first item//
        int firstItem = t->head->data;
        
        // point t->head at current head->head->next
        t->head = t->head->next;

        return firstItem; 
    } else {
        return -1;}
}

void testPopFront() {
    dll_t* testPop = create_dll();
    printf("\n*** test popFront() ***\n");
    printf("\n"); 
    dll_push_front(testPop, 44);
    int tval0 = dll_pop_front(testPop);
    printf("test get first item, E 44, A %d\n", tval0);
    free(testPop);

}

// Returns the last item in the DLL, and also removes it from the list.
// Returns a -1 if the operation fails (and if the DLL is NULL). Assume no negative numbers in the list.
int dll_pop_back(dll_t* t){
    if (t) {
        // empty list
        if (t->count == 0) {
            return -1;}
        
        if (t->count == 1) {
            return t->head->data;
        }
        // get last item
        int lastItem = t->tail->data;
        
        //set list tail to tail->previous
        t->tail = t->tail->previous;

        return lastItem;
    } else {
    return -1; 
    }
}

void testPopBack() {
    dll_t* testPop = create_dll();
    printf("\n*** test popBack() ***\n");
    printf("\n"); 
    dll_push_back(testPop, 2222);
    int tval0 = dll_pop_back(testPop);
    printf("test get popped item, E 2222, A %d\n", tval0);
    dll_push_back(testPop, 3333);
    int tval1 = dll_pop_back(testPop);
    printf("test get popped item, E 3333, A %d\n", tval1);
    free(testPop); 
}

// Inserts a new node before the node at the specified position.
// Returns a -1 if the operation fails (and if the DLL is NULL), otherwise returns 1 on success.
// (i.e. the memory allocation for a new node failed or trying to insert at a negative position or at 
//  a position past the size of the DLL ). Think testcases here.
int dll_insert(dll_t* l, int pos, int item){ 

    if (pos > l->count || pos < 0) {
        return -1;

    }

    if (pos == 0) {
        l->count ++;
        return dll_push_front(l, item);
        


    } else if (pos == l->count) {
        l->count ++;
        return dll_push_back(l, item);
        
        
    } else {
            
        int i;
        node_t* swingNode;

        swingNode = l->head;

        for (i=0; i < pos; i++) {
           swingNode = swingNode->next;
         } 
    
          //make new node
          node_t* newNode = (node_t*)malloc(sizeof(node_t*));

        // set new node's prev to swingNode prev
        newNode->previous = swingNode->previous;

        //set prev node's nex to newnode
        swingNode->previous->next = newNode;
        newNode->next = swingNode->next;
        

        return 1;
    }
    
}

void testInsert() {
    dll_t* testIns = create_dll();
    dll_insert(testIns, 10, 11);    
}

// Returns the item at position pos starting at 0 ( 0 being the first item )
// Returns a -1 if the operation fails (and if the DLL is NULL). Assume no negative numbers are in the list.
// (i.e. trying to get at a negative position or at a position past the size of the DLL ). 
// Think testcases here.
int dll_get(dll_t* l, int pos){

    int i;
    node_t* swingNode;
    
    // if want to move beyond count, negative pos, or null node, kill
    if (pos > l->count || pos <0 || !l) {
        return -1;
    } else {
        // set initial swingNode

        swingNode = l->head;

        for (i=0; i<pos; i++) {
            swingNode = swingNode->next;
        }
        return swingNode->data;

    }

}

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Returns a -1 if the operation fails (and if the DLL is NULL). 
// (i.e. trying to remove at a negative position or at a position past the size of the DLL ). 
// Think testcases here.
int dll_remove(dll_t* l, int pos){
	
    if (pos > l->count || pos < 0) {
        return -1;

    }

    if (pos == 0) {
        l->count --;
        return dll_pop_front(l);
        


    } else if (pos == l->count) {
        l->count --;
        return dll_pop_back(l);
        
        
    } else {
            
        int i;
        node_t* swingNode;

        swingNode = l->head;

        for (i=0; i < pos; i++) {
           swingNode = swingNode->next;
         } 
            
        //swing node is holding address to kill
            // swingNode has a next
            // swingNode has a prev
        node_t* theNextNode = swingNode->next;
        node_t* thePrevNode = swingNode->previous;
        
        theNextNode->previous = thePrevNode;
        thePrevNode->next = theNextNode;

        free(swingNode);

        return 1;
    }
  	return -1; // Note: you should have two return statements in this function.
}

// DLL Size
// Queries the current size of a DLL
// A DLL that has not been previously created will crash the program.
// Returns -1 if the DLL is NULL.
unsigned int dll_size(dll_t* t){
    if (t) {
        return t->count; 
    } else
	return -1;
}

// Free DLL
// Removes a DLL and ALL of its elements from memory.
// This should be called before the proram terminates.
void free_dll(dll_t* t){
    node_t* temp = t->head;
    int finish = t->count;
    int i;
    
    for (i=0; i<finish; i++) {
        temp = t->head;
        t->head = t->head->next;
        free(temp);
    }
    free(t);
}



#endif

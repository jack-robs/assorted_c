// JACK ROBERTSON
// =================== Support Code =================
// Binary Search Tree ( BST ).
//
//
//
// - Implement each of the functions to create a working BST.
// - Do not change any of the function declarations
//   - (i.e. bst_t* create_bst() should not have additional arguments)
// - You should not have any 'printf' statements in your BST functions. 
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// ==================================================
#ifndef MYBST_H
#define MYBST_H
#include <stdlib.h>
#include <stdio.h>

// Create a node data structure to store data within
// our BST. In our case, we will stores 'integers'
typedef struct node{
	int data;
	struct node* rightChild;
  	struct node* leftChild;
}node_t;

// Create a BST data structure
// Our BST holds a pointer to the root node in our BST called root.
typedef struct BST{
	int count;		// count keeps track of how many items are in the BST.
	node_t* root;		// root points to the root node in our BST.
}bst_t;

// Creates a BST
// Returns a pointer to a newly created BST.
// The BST should be initialized with data on the heap.
// The BST fields should also be initialized to default values.
bst_t* create_bst(){
	// Modify the body of this function as needed.
	bst_t* myBST = (bst_t*)malloc(sizeof(bst_t*));
    myBST->count = 0;
    myBST->root = NULL;

	return myBST;
}


// BST Empty
// Check if the BST is empty
// Returns 1 if true (The BST is completely empty)
// Returns 0 if false (the BST has at least one element enqueued)
int bst_empty(bst_t* t){
    if (t->count == 0) {
        return 1;
    } else {
	    return 0;
    }
}

node_t* addHelp(node_t* n, int item){
    if (n == NULL) {
        node_t* p = (node_t*)malloc(sizeof(node_t*));
        p->data = item;
        p->leftChild = NULL;
        p->rightChild = NULL;
        n = p;
    } else if (item > n->data) {
        n->leftChild = addHelp(n->leftChild, item);
    } else {
        n->rightChild = addHelp(n->rightChild, item);
    }
    return n;
}


// Adds a new node containng item in the correct place of the BST.
// If the data is less then the current node we go right, otherwise we go left.
// Same as described in the README.md file. 
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. the memory allocation for a new node failed).
// It should run in O(log(n)) time.
int bst_add(bst_t* t, int item){


    // no instantaite node
    if (t == NULL) {
        return -1;
    }  
    // add to NULL root
    if (t->root == NULL) {
        node_t* root = (node_t*)malloc(sizeof(node_t*));
        t->root = root;
        t->root->data = item;
        t->root->leftChild = NULL;
        t->root->rightChild = NULL;
        t->count ++;
        return 0;
    }
    t->root = addHelp(t->root, item); 
    t->count ++;
    return 0;
}

void printHelp(node_t* node, int order) {
    // base case: null node, stop traversing
    if (node == NULL) {
        return;
    }
    if (order == 0) {
        printHelp(node->rightChild, order);
        printf("%d ", node->data);
        printHelp(node->leftChild, order);
    } else {
        printHelp(node->leftChild, order);
        printf("%d ", node->data);
        printHelp(node->rightChild, order);
    }
}

// Prints the tree in ascending order if order = 0, otherwise prints in descending order.
// For NULL tree it should print nothing. 
// It should run in O(n) time.
void bst_print(bst_t*t, int order){

    // print nothing null tree
    if (t == NULL) {
        char* tree = "EMPTY PRINT for t== null";
        printf("%s", tree);
    }
   else {
        node_t* node = t->root;
        // call helper function with node
        printHelp(node, order);
        } 
}

int sumHelp(node_t* node) {
    if (node == NULL) {
        return 0;
    }
    int left = sumHelp(node->leftChild);
    int right = sumHelp(node->rightChild); 
    int sum = node->data + left + right;
    return sum;
}

// Returns the sum of all the nodes in the tree. 
// exits the program for a NULL tree. 
// It should run in O(n) time.
int sum(bst_t *t){
    if (!t) {
        return 0;
    } 
    else {
        // pull node
        node_t* node = t->root;
        int sum = sumHelp(node);
        return sum;
    }
}

int findHelp(node_t* node, int value) { 

    if (node->data == value) {
        return 1;
    }
 
    if (node == NULL) {
        return 0;
   } else if (value < node->data) {
        if (node->rightChild == NULL) {
            return 0;
        } else {
            return findHelp(node->rightChild, value);
        }
    } else if (value > node->data) {
        if (node->leftChild == NULL) {
            return 0;
        } else {
            return findHelp(node->leftChild, value);
        }

    }
} 
       // print from tree: 
    //          99
    //         /  \
    //       10    101
    //              /
    //             100
    
// Returns 1 if value is found in the tree, 0 otherwise. 
// For NULL tree it exists the program. 
// It should run in O(log(n)) time.
int find(bst_t * t, int value){
    if (!t) {
        return 0;
    }
    else {
        node_t* node = t->root;
        int result = findHelp(node, value);
        return result;
      }
    }


// BST Size
// Queries the current size of the BST
// A BST that has not been previously created will crash the program.
// (i.e. A NULL BST cannot return the size)
unsigned int bst_size(bst_t* t){
	return 0;
}

void freeHelper(node_t* n) {
    // base case, if n is a leaf    
    if (n == NULL) {
        return;
    }
    freeHelper(n->rightChild);
    freeHelper(n->leftChild);
    free(n);
}

// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the proram terminates.
void free_bst(bst_t* t){
    freeHelper(t->root);
    free(t);

}

//TESTS TESTS TESTS

void testCreate(bst_t* t0) { 
    printf("\n****testCreate()****\n");
    // confirm root == NULL
    printf("\ncreate root... \nE: null, A:%p\n", t0->root); 
    // confirm count = 0
    printf("Count = 0, \nE:0, A:%d\n", t0->count);
    printf("\n#########\n");
}

void testAdd(bst_t* t0) {

    printf("\n***testAdd()***\n");

    //root nodes nill
    printf("Condition: ROOT NIL add to ROOT\n");
        //test add to root
        printf("\tPre-add, *root:\n\tE:nil, A:%p\n", t0->root);
        int tval = bst_add(t0, 99);
        printf("\n\tAdded, return:\n\tE:0, A:%d\n",tval);
        printf("\tt0->root, E:p, A:%p\n", t0->root);
        printf("\tt0->root data E:99, A:%d\n",t0->root->data);
        printf("\tCount, E:1, A:%d\n", t0->count); 
        printf("\tlc, rc, E: nil/nil, A:%p, %p\n", t0->root->leftChild, t0->root->rightChild);

    // root node exists, add 10 to right child 
    printf("\n\nCondition: Root has data:99, add 10 rightChild"); 
        printf("\n\tPre-add, *root:\tE:p, A:%p", t0->root);
        printf("\n\tPre-add, root->data, E:99, A:%d", t0->root->data);
        int tval2 = bst_add(t0, 10);
        printf("\n\tAdded, return:\tE:0, A:%d\n",tval2);
        printf("\tt0->root, E:p, A:%p\n", t0->root);
        printf("\tt0->root data E:99, A:%d\n",t0->root->data);
        printf("\tCount, E:2, A:%d\n", t0->count); 
        printf("\tlc, rc, E: nil/p, A:%p/%p\n", t0->root->leftChild, t0->root->rightChild);
        printf("\t expected rc, data 10, a: %d\n", t0->root->rightChild->data);


    // root node exist, rC has 10, add lC 101
    printf("\n\nCondition: Root 99, rc10, add lc 101"); 
        printf("\n\tPre-add, *root:\tE:p, A:%p", t0->root);
        printf("\n\tPre-add, root->data, E:99, A:%d", t0->root->data);
        printf("\tCount, E:2, A:%d\n", t0->count); 
        printf("\tlc, rc, E: nil/p, A:%p/%p\n", t0->root->leftChild, t0->root->rightChild);
        printf("\t expected rc, data 10, a: %d\n", t0->root->rightChild->data);
        printf("\tadding to lc, 101\n");
        int tval3 = bst_add(t0, 101);
        printf("\tAdded, return:\tE:0, A:%d\n",tval3);
        printf("\tlc, rc, E: p/p, A:%p/%p\n", t0->root->leftChild, t0->root->leftChild);
        printf("\t expected lc, data 101, a: %d\n", t0->root->leftChild->data);


    // root node exist, rC has 10, lc has 101, add 100 (expected lC->rC reach)
    printf("\n\nCondition: Root 99, rc10, lc101, add 100, expected lC->rC to work"); 
        printf("\n\tPre-add, *root: E:p, A:%p", t0->root);
        printf("\n\tPre-ade, root->data, E:99, A:%d\n", t0->root->data);
        printf("\tCount, E:3, A:%d\n", t0->count); 
        printf("\tlc, rc, E: p/p, A:%p/%p\n", t0->root->leftChild, t0->root->rightChild);
        printf("\trc/lc data, E:10,101, a: %d,%d\n", t0->root->rightChild->data, t0->root->leftChild->data);
        printf("\tadding 100\n");
        int tval4 = bst_add(t0, 100);
        printf("\tAdded, return:\tE:0, A:%d\n",tval4);
        printf("\tlc, rc, E: p/p, A:%p/%p\n", t0->root->leftChild, t0->root->leftChild);
        printf("\t lC->rC, E:p, A%p\n", t0->root->leftChild->rightChild);
        printf("\t expected lC->rC data 100, a: %d\n", t0->root->leftChild->rightChild->data);

        printf("\n#########\n");

}


void testEmpty(bst_t* t0) {
    printf("\n***testEmpty()***\n");
    int tval = bst_empty(t0);
    printf("\nbst_empty return pre-add:\nE: 1, A:%d\n", tval);
    printf("Confirm count pre:\nE:0, A:%d\n",t0->count);
    t0->count ++;
    int tval1=  bst_empty(t0);
    printf("Confirm count change:\nE:1, A:%d\n",t0->count);
    printf("Added, return value:\n E:0, A:%d\n", tval1);
    printf("\n#########\n");
    t0->count --;
}


void testPrint(bst_t*t) {
     // print from tree: 
    //          99
    //         /  \
    //       10    101
    //              /
    //             100
    
    printf("\n***testPrint()***\n");
    // print null tree
    bst_print(t, 0);
    printf("\n");
    bst_print(t, 2);
    printf("\n\n##########\n");
}


void testSum(bst_t* t) {
    printf("\n***testSum()***\n");
    int testSum = sum(t);
    printf("test sum, expected 310, a: %d\n", testSum);
    printf("\n#############\n");
}



void testFind(bst_t* t0) {
    printf("\n****testFind()****\n");
    bst_print(t0, 0);
    printf("\n");

    // Find 99, expected 1
    printf("find(99), E: 1, A: %d\n", find(t0, 99));

    // Find 100, two layers in 
    printf("find(100), E: 1, A: %d\n", find(t0, 100));

    // Find 0, expected 0
   printf("find(1), E: 0, A: %d\n", find(t0, 1));
    
    // Find -100, expected 0
   printf("find(-100), E: 0, A: %d\n", find(t0, -100));
     
    // Find 10.0, expected 0
    // NOTE: weird result, returns 10.0
    //printf("find(10.0), E: 0, A: %d\n", find(t0, 10.0));
    

    
    printf("\n#########\n");
}

#endif

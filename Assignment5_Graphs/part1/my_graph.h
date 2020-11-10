// =/================== Support Code =================
// Graph.
//
//
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions. 
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// ==================================================
#ifndef MYGRAPH_H
#define MYGRAPH_H
#include <stdio.h>
#include "myqueue.h"

// Create a graph data structure
// Our graph keeps track of the number of nodes, the number of edges and an array
// of all the nodes in the graph, and the maximum number of nodes we store in our graph.
// Create a node data structure to store data within
// our graph. In our case, we will stores 'integers'
// as our data in the nodes
typedef struct g_node{
	int data;
	struct g_node* next;
    struct g_node* prev;
    //SLL of neighbor nodes
	struct n_node* neighbor;
    int searched;
    int cycle;
}g_node;


typedef struct graph_t{
	int numNodes;		
    int numEdges;
	struct g_node* head;	 
    struct g_node* tail;
}graph_t;


// Create a neighbor data structure to server as the neighbor's list.
// In our case, we will stores 'integers' as our neighbors that 
// corresponding to the data that the actual nodes store.
typedef struct n_node{
    //hit data, locate by g_node->data;
	struct g_node* data; 
	struct n_node* next;
}n_node;

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
graph_t* create_graph(){

    // malloc it 
    graph_t* myGraph = (graph_t*)malloc(sizeof(graph_t*));
    myGraph->numNodes = 0;
    myGraph->numEdges = 0;
    myGraph->head = NULL;
    myGraph->tail = NULL;

    // return it
	return myGraph;
}


// Graph Empty
// Check if the graph is empty
// Returns >=0 if true (The graph is completely empty, i.e. numNodes == 0 )
// Returns -1 if false (the graph has at least one node)
int graph_empty(graph_t* g){
    
    if (g) {
        if (g->numNodes == 0) {
            return 0;
        } else if (g->numNodes > 0) {
            return -1;
        } else {
            //error code
            return 99999;
        } 
    }
    else {
        // error code
        return 99999;
    }
}

//Returns >=0 if the node with value is in the graph, otherwise returns -1;
int contains_node( graph_t* g, int value){
    if (g->numNodes == 0) {
        return -1;
    } else {

    g_node* swingNode = g->head;
    
    for (int i = 0; i < (g->numNodes); i++) {
        if (swingNode->data == value) {
            // returns index
            return i;
        } else {
        swingNode = swingNode->next;
        }
    }
    // not in
   	return -1;
    }
}


// Adds a new node withe the correspoding item in the graph.
// Returns a -1 if the operation fails or has duplicate node. (otherwise returns >=0 on success) 
// (i.e. the memory allocation for a new node failed).
int graph_add_node(graph_t* g, int item){

    if (!g) {
        return -1;
    }
    
    int test = contains_node(g, item);
    if (test != -1) {
        return -1;
    } 
 
    if (g->numNodes == 0) {
        
        // malloc new node
        g_node* newNode = (g_node*)malloc(sizeof(g_node));

        // link head and tail
        g->head = newNode;
        g->tail = newNode;
   
        // add data
        g->head->data = item;
        g->head->searched = 0;
        g->head->cycle = 0;

        // gnode null next, prev and neighbor
        newNode->next = NULL;
        newNode->prev = NULL;
        newNode->neighbor = NULL;
        
        // update numNodes
        g->numNodes ++;

        return 0;

        } else {
            // occupied add //
            g_node* newNode2 = (g_node*)malloc(sizeof(g_node));

            // tail changes
            g_node* tempTail = g->tail;
            g->tail->next = newNode2;
            g->tail = newNode2;
            g->tail->prev = tempTail; 

            // set data
            g->tail->data = item;
 
            // null next and neighbor
            g->tail->next = NULL;
            g->tail->neighbor = NULL;
            g->tail->searched = 0;
            g->tail->cycle = 0;

            g->numNodes ++;
            
            return 0;
    }   
}

//Adds an edge from source to destination. 
//If source or desination is not found, or the edge already exists in the graph returns -1.
//Otherwise it returns >= 0
int graph_add_edge(graph_t * g, int source, int destination){

    // empty graph, no nnodes
    if (g->numNodes == 0) {  
        return -1; 
    }
    // !src || !dest 
    else if (contains_node(g, source) == -1 || contains_node(g, destination) == -1) {
        return -1;
    } 

    // src exists, dest exists, add an edge, including dup check
    else {
        // loop through gnode list until gnode->data = src
        g_node* sourceNode = g->head;

        for (int i = 0; i < g->numNodes; i++) {
            if (sourceNode->data == source) {
                break;
            } else {
            sourceNode = sourceNode->next;
            }
        }
        
        g_node* destNode = g->head;
        for (int j = 0; j< g->numNodes; j++) {
            if (destNode->data == destination) {
                break;
            } else {
            destNode = destNode->next;
            }
        }
       // printf("Dest pointer value: %p\n", destNode);
       // printf("Check from next->next chain: %p\n", g->head->next->next); 
       // printf("Dest pointer data value: %d\n", destNode->data);

        //CREATE FIRST NEIGHBOR NODE 
        if (sourceNode->neighbor == NULL) {
            // add n_node and return 0;
            n_node* newNeighbor = (n_node*)malloc(sizeof(n_node));
            sourceNode->neighbor = newNeighbor;
            // write gnode pointer to dest
            newNeighbor->data = destNode;
            //printf("Check newNeighbor data dest: E:dest addr, A:%p\n", newNeighbor->data);
            //printf("Check newNeighbor data dest: E:5, A:%d\n", newNeighbor->data->data);
            // set nnode next to null
            newNeighbor->next = NULL;
            //printf("check newNeighbor next null E:nil, A:%p\n", newNeighbor->next);
            // increment grahp num edges
            g->numEdges ++;
            // return 0
            return 0;

        
        } else {
            //printf("\nin else, first source->neighbor p %p and val %d\n", sourceNode->neighbor, sourceNode->neighbor->data->data);
            // swing through to NULL and create node
            // check for duplicates in here

            n_node* adjNode = sourceNode->neighbor;

            while (adjNode->next) {
                adjNode = adjNode->next;
                if (adjNode->data->data == destNode->data) {
                    //printf("duplicate hit\n");
                    return -1;
                }
            }

            //printf("\n\nFinal adj node, E:nil, A:%p\n", adjNode->next);

            n_node* newNeighbor = (n_node*)malloc(sizeof(n_node));
            adjNode->next = newNeighbor;
            // write gnode pointer to dest
            newNeighbor->data = destNode;
            //printf("Check newNeighbor data dest: E:dest addr, A:%p\n", newNeighbor->data);
            //printf("Check newNeighbor data dest: E:7, A:%d\n", newNeighbor->data->data);
            // set nnode next to null
            newNeighbor->next = NULL;
            //printf("check newNeighbor next null E:nil, A:%p\n", newNeighbor->next);
            // increment grahp num edges
            g->numEdges ++;
            // return 0
            return 0;
        }
        // error exit
	    return 9999;
    }
}


void free_list(n_node* iterator) {
    while(iterator !=NULL) {
        // set hold, hold next address
        n_node* keeper = iterator->next;
        
        //free current iterator
        free(iterator);

        //set iterator to keeper
        iterator = keeper; 
    }    

    //free final
    free(iterator);
}

//Returns >=0 if an edge from source to destination exists, -1 otherwise.
int contains_edge( graph_t * g, int source, int destination){

    if (!g || contains_node(g, source) == -1 || contains_node(g, destination) == -1) {
        return -1;
    }

    g_node* sNode = g->head;
    
    int flag = 0;
    
    // loop through nodes to source
    while (flag != 1) {

        // exit
        if (sNode->data == source) {
            flag ++;
        } else if (sNode->next == NULL) {
            flag ++;
        } else {
            sNode = sNode->next;
        }
    }

    //loop sNode's neighbor
    int flag2 = 0;
    n_node* nNode = sNode->neighbor;

    while (flag != 1) {
        if (nNode->data->data == destination) {
            flag ++;
        } else if (nNode->next == NULL) {
            return -1;
        }  else {
            nNode = nNode->next;
        }
    }

	return 0;
}

//Removes an edge from source to destination. 
//If source or desination is not found in the graph returns -1.
//If no such edge exists also returns -1.
//Otherwise it returns >=0
//TODO: finish
int graph_remove_edge(graph_t * g, int source, int destination){
    if (contains_node(g, source) == -1 || contains_node(g, destination) == -1) {
        return -1;
    }
    if (!g || contains_edge(g, source, destination) == -1) {
        return -1;
    }

    g_node* sNode = g->head;
    
    int flag = 0;
    while (flag != 1) {
        if (sNode->data == source) {
            flag ++;
        } else if (sNode->next == NULL) {
            flag ++;
        } else {
            sNode = sNode->next;
        }
    }

    n_node* nNode = sNode->neighbor;

    // sourceNode: sNode
    // first neighbor node: nNode    

    if (nNode == NULL) {
        return -1;
    } 

    int condition = 0;
    for (int i = 0; nNode != NULL; i++) {
        // check first node
        if (nNode->data->data == destination) {
            condition = 1;
            break;
        }

        // next node null check
        else if (nNode->next == NULL) {
            return -1;
        }

        else if (nNode->next->data->data == destination) {
            condition = 2; 
            break;
        }
        nNode = nNode->next;
    }
    if (condition == 1) {
        n_node* kill = sNode->neighbor;
        sNode->neighbor = sNode->neighbor->next;
        free(kill);
        g->numEdges --;
        return 0;
    } else {
        n_node* temp = nNode->next->next;
        n_node* kill = nNode->next;
        nNode->next = temp;
        free(kill);
        g->numEdges --;
        return 0;
    }

}


// Removes the node from the graph and the corresponding edges connected 
// to the node.
// Returns a -1 if the operation fails (otherwise returns >=0 on success).
// (the node to be removed doesn't exist in the graph).
int graph_remove_node(graph_t* g, int item){
    if (contains_node(g, item) == -1) {
        return -1;        
    }

    g_node* swingNode = g->head;

    // node at begnning
    if (swingNode->data == item) {
        //TODO
        // free neighbors of head node
        n_node* swingNeighbor = swingNode->neighbor;

        free_list(swingNeighbor);
        
        // make new head node, link to old 2nd node
        g_node* newHead = g->head->next;
        
        // free old head node
        free(g->head);
        g->head = newHead;

        // iterate along graph, free edge(src = current node, dest = remove node)
        while (swingNode != g->tail) {
            swingNode = swingNode->next; 
        }

        g->numNodes --;

        return 0;
    } 
    
    // node at end
    else if (g->tail->data == item) {
        //TODO
        // while swingNode != tailNode
            // free edge (src = currentNode, dest = remove node) 
        while (swingNode != g->tail) {
        //    graph_remove_edge(g, swingNode->data, item);
            swingNode = swingNode->next;
        }
        
        // then: remove neighbors of tail node
        free_list(swingNode->neighbor);

        // make new tail node, delete old tail
        g_node* newTail = swingNode->prev;
        g->tail = newTail;
        free(swingNode);

        g->numNodes --;


        return 0;
    } 

    // node in middle
    else {
       g_node* targetNode = g->head;
       for (int i = 0; i < g->numNodes; i++) {
         //    graph_remove_edge(g, swingNode->data, item);
             if (swingNode->data == item) {
                 targetNode = swingNode;
             }
             swingNode = swingNode->next; 
        }

        // relink prev/next
        free_list(targetNode->neighbor);

        g_node* oldNext = targetNode->next;
        g_node* oldPrev = targetNode->prev;

        oldPrev->next = oldNext;
        oldNext->prev = oldPrev;
        free(targetNode);

        g->numNodes --;

    	return 0; 
    }
}



//Returns an int array of all the neighbors of the node with data=value.
int * getNeighbors( graph_t * g, int value){

    g_node* sNode = g->head;
    
    int flag = 0;
    while (flag != 1) {
        if (sNode->data == value) {
            flag ++;
        } else if (sNode->next == NULL) {
            flag ++;
        } else {
            sNode = sNode->next;
        }
    }

    //loop sNode's neighbor
    int flag2 = 0;
    int nn = 0;
    
    if (sNode->neighbor == NULL) {
        return 0;
    }
    n_node* nNode = sNode->neighbor;

    while (flag2 != 1) {
        if (nNode->next == NULL) {
            nn ++;
            flag2 ++;
        }  else {
            nNode = nNode->next;
            nn ++;
        }
    }

	int * arr = malloc(nn);

    int flag3 = 0;
    int nx = 0;
    
    n_node* nNode2 = sNode->neighbor;
    while (flag3 != 1) {
        if (nNode2->next == NULL) {
            arr[nx] = nNode2->data->data;
            flag3 ++;
        }  else {
            arr[nx] = nNode2->data->data;
            nNode2 = nNode2->next;
            nx ++;
        }
    }
	return arr;
}


// Returns the number of neighbors for value.
int numNeighbors( graph_t * g, int value ){

    if (!g || contains_node(g, value) == -1) {
        return -1;
    }

    g_node* sNode = g->head;
    
    int flag = 0;
    while (flag != 1) {
        if (sNode->data == value) {
            flag ++;
        } else if (sNode->next == NULL) {
            flag ++;
        } else {
            sNode = sNode->next;
        }
    }

    //loop sNode's neighbor
    int flag2 = 0;
    int nn = 0;
    
    if (sNode->neighbor == NULL) {
        return 0;
    }
    n_node* nNode = sNode->neighbor;
    if (nNode == NULL) {
        return 0;
    }

    while (flag2 != 1) {
        if (nNode->next == NULL) {
            nn ++;
            flag2 ++;
        }  else {
            nNode = nNode->next;
            nn ++;
        }
    }

	return nn;
}

// Graph Size
// Returns the number of nodes in the graph
// Returns -1 on failure.
int graph_num_nodes(graph_t* g){
    if (g) {
        return g->numNodes;
    } else {
	    return -1;
    }
}

// Graph Size
// Returns the number of edges in the graph, 
// Returns -1 on failure. 
int graph_num_edges(graph_t* g){
    if (g) {
        return g->numEdges;
    } else {
	    return -1;
    } 
}

// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the proram terminates.
void free_graph(graph_t* g){
    g_node* freeg = g->head;

    // loop up to tail
    while (freeg) {

        n_node* freen = freeg->neighbor;
        while (freen) {

            n_node* tempn = freen;
            freen = tempn->next;
            free(tempn);
        }
        g_node* tempg = freeg;
        freeg = tempg->next;
        free(tempg);
        }
    free(g);
}



//returns 0 if I can reach the destination from source, -1 otherwise ( using BFS)
void printArray(int * arr, graph_t* tg, int node) {
    int t2 = numNeighbors(tg, node);
    for (int i = 0; i < t2; i++) {
        int val = arr[i];
        printf("(%d)->", val);
    }
    printf("(*)\n");
}

//TODO
// HOW TO DECLARE AN ARRAY IN THE METHOD SOUCH THAT
int is_reachable(graph_t* g, int source, int dest) {
    if (contains_node(g, source) == -1 || contains_node(g, dest) == -1) {
        return -1;
    }

    // create queue
    queue_t* bfs_q =  create_queue();


    //###INITIAL SOURCE NEIGHBORS CHECK###
    //get number of neighbors for source
    int numNeigh = numNeighbors(g, source);
    if (numNeigh == 0) {
        return -1;
    }
    int* narray = getNeighbors(g, source);

    //search immediate neighbors of source
    // this might be redunant
    for (int k = 0; k < numNeigh; k++) {
        if (narray[k] == dest) {
            return 0;
        }
    }

    //enque all the neighbors of source
    for (int i = 0; i < numNeigh; i++) {
        queue_enqueue(bfs_q, narray[i]);
    }

    //create searched array
    int index = 0;
    int* searched = malloc(g->numNodes);

    // set fail condiiton, if queue is empty, will break loop
    int t = queue_empty(bfs_q);
    // while queue is not empty
    while (t != -1) {
        //dequeue neighbor (item 0 in queueu)
        int search = queue_dequeue(bfs_q); 
        if (search == dest) {
            free_queue(bfs_q);
            return 0;
        }
        
        //get array of neighbors from FIFO dequeue
        int searchNeighbors = numNeighbors(g, search);
        if (searchNeighbors == 0) {
            searched[index] = search;
            index ++;
            if (queue_empty(bfs_q)) {
                break;
            }
            t = queue_empty(bfs_q);
            continue;
        }
        int* searchArray = getNeighbors(g, search);

        //add dq'd to searched array
        searched[index] = search;

        // for each dq'd, see if neighbor list matches item
        for (int l = 0; l < searchNeighbors; l++) {
            if (searchArray[l] == dest) {
                //TODO: causes segfualt here
                free_queue(bfs_q);
                return 0;
            } else {
                //get array of neighbors from FIFO dequeue
                int moreNeigh = numNeighbors(g, searchArray[l]);
                int* moreArray = getNeighbors(g, searchArray[l]);
                // loop through array: if new vals are searched, skiped
                // for each value in new array
                for (int z = 0; z < moreNeigh; z++) {
                    //for each value in searched array
                    int noAdd = 0;
                    for (int a = 0; a < g->numNodes; a++) {
                        if (moreArray[z] == searched[a]) {
                            noAdd = 1;
                        }
                    }
                    if (noAdd == 0) {
                        queue_enqueue(bfs_q, moreArray[z]);
                    }
                }
                free(moreArray);
            }
        }
        free(searchArray);
        index ++;
        t = queue_empty(bfs_q);
    }
    free(searched);
    free_queue(bfs_q);
    return -1;
}
// Prints the the graph using BFS
// For NULL or empty graph it should print nothing. 
void graph_print(graph_t * g){
    //null check
    if (g == NULL || g->numNodes == 0) {
        printf("\n");
    } else {
        g_node* swingNode = g->head;

        printf("\nGraph:\n");
        for (int i = 0; swingNode != g->tail; i++) {
            printf("[%d]->", swingNode->data);            
            int* neighs = getNeighbors(g, swingNode->data);
            int nums = numNeighbors(g, swingNode->data);
            printArray(neighs, g, swingNode->data);
            printf(" |\n");
            swingNode = swingNode->next;
        }
        // handle tail
        printf("[%d]->", swingNode->data);
        int* neighs = getNeighbors(g, swingNode->data);
        int nums = numNeighbors(g, swingNode->data);
        printArray(neighs, g, swingNode->data);
        printf("\n");
        free(neighs);
    }

	
}


//* `has_cycle(graph_t * g)` returns 0 if there is a cycle in the graph, -1 otherwise (using BFS or DFS)
//Do is reachable for each node? but if source shows up agian, it has a cycle
int has_cycle(graph_t* g) {

    if (!g || g->numNodes == 0) {
        return -1;
    }

    g_node* swingNode = g->head;

    for (int i = 0; swingNode != g->tail; i++) {
        int source = swingNode->data;
        int cycle = is_reachable(g, source, source);
        if (cycle == 0) {
            return 0;
        }
        swingNode = swingNode->next;
    }
    int source = swingNode->data;
    int cycle = is_reachable(g, source, source);
    if (cycle == 0) {
        return 0;
    }
    return -1;
}

//* `print_path(graph_t * g, int source, int dest)` prints any path from source to destination if there exists one (Choose either BFS or DFS, typically DFS is much simpler)

void print_path(graph_t* g, int source, int dest) {
    
}


#endif

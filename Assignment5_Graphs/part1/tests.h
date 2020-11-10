//Test file for Assignment5, graphs

#include <stdio.h>
#include <stdlib.h>

void testName(char* str) {
    printf("\n******%s*****\n", str);
}


//testCreate()
void testCreate() {
    testName("testCreate");
    graph_t* tg = create_graph();
    printf("Expected 0x.., A: %p\n", tg);
    free_graph(tg);

}

//testEmpty
void testEmpty(graph_t* tg) {
    // test empty case
    testName("testEmpty");
   
    printf("Test empty node\n");
    printf("E: 0, A:%d\n", graph_empty(tg));

    // test node added 
    //TODO
    printf("Test node added\n");
    graph_add_node(tg, 55);
    printf("E: -1, A:%d\n", graph_empty(tg));

    free_graph(tg);
}

//testAdd
void testAdd() {
    
    graph_t* tg = create_graph();
    
    testName("testAdd");

    //#######FIRST ADD#########
    printf("Add item: int 5:\n");
    int tval0 = graph_add_node(tg, 5);

    //PASS Add node: check numNodes 1
    printf("numNodes, E:1, A:%d\n", tg->numNodes);
    
    //PASS Add node: code 0
    printf("return, E:0, A:%d\n", tval0);

    //FAILL Add node: graph_dll->head = 0xAA; 
    printf("g->head, E:0xAA, A:%p\n", tg->head);

    //FAIL node: graph_dll->tail = 0xAA; 
    printf("g->tail, E:0xAA, A:%p\n", tg->tail);
  
    // Add node: g_node->data = 5
    printf("g->head(g_node)->data, E:5, A:%d\n", tg->head->data);

    // Add node: g_node->next = null
    printf("g_node->next, E:null, A:%p\n", tg->head->next);
    
    // Add node: g_node->prev = null
    printf("g_node->prev, E:null, A:%p\n", tg->head->prev);

    // Add node: g_node->neighbor = null
    printf("g_node->neighbor, E:null, A:%p\n", tg->head->neighbor);

    //TODO Add node: check for duplicates
    printf("\nAdd DUPLICATE item: int 5:\n");
    int tval9 = graph_add_node(tg, 5);

    //PASS Add node: check numNodes 1
    printf("numNodes, E:1, A:%d\n", tg->numNodes);
    
    //PASS Add node: code 0
    printf("return, E:-1, A:%d\n", tval9);

    //FAILL Add node: graph_dll->head = 0xAA; 
    printf("g->head, E:0xAA, A:%p\n", tg->head);

    //FAIL node: graph_dll->tail = 0xAA; 
    printf("g->tail, E:0xAA, A:%p\n", tg->tail);
  
    // Add node: g_node->data = 5
    printf("g->head(g_node)->data, E:5, A:%d\n", tg->head->data);

    // Add node: g_node->next = null
    printf("g_node->next, E:null, A:%p\n", tg->head->next);
    
    // Add node: g_node->prev = null
    printf("g_node->prev, E:null, A:%p\n", tg->head->prev);

    // Add node: g_node->neighbor = null
    printf("g_node->neighbor, E:null, A:%p\n", tg->head->neighbor);


    //Add node: check numNudes 2

    //#######SECOND ADD#########
    printf("\nAdd SECOND item: int 6:\n");
    int tval1 = graph_add_node(tg, 9);

    //Add node: check numNodes 2
    printf("numNodes, E:2, A:%d\n", tg->numNodes);
   
    //Add node: code 0
    printf("return, E:0, A:%d\n", tval1);

    //Add node: graph_dll->head = 0xAA; 
    printf("Same as prior graph_dll->head, E:0xAA, A:%p\n", tg->head);

    //Add node: graph_dll->tail = 0xBB; 
    printf("New graph_dll->tail, E:0xBB, A:%p\n", tg->tail);
    
    // Add node, existing head still there: g_node->data = 5
    printf("Original node still there, E:5, A:%d\n", tg->head->data);

    // Add node: (5) g_node->next =  0xBB
    printf("(5)'s next g_node->next, E:0xBB, A:%p\n", tg->head->next);

    // ADD node: (9) exists
    printf("(9) exists,  g_node->next->data; E:9, A:%d\n", tg->head->next->data);
    
    // Add node: (9) linked to (5) by previous 
    printf("(9) g_node->prev, E:0xAA, A:%p\n", tg->tail->prev);

    // Add node: (9) next is null
    printf("(9)-> next E:null, A:%p\n", tg->tail->next);

    // Add node: (9) neighbor is null
    printf("(9) neighbor, E: null, A:%p\n", tg->tail->neighbor);

    free_graph(tg);

}

void testContains() {
    testName("testContains");
    graph_t* tg = create_graph();

    // Return -1, not in graph
    int tval0 = contains_node(tg, 1);
    printf("!contains, E:-1, A:%d\n", tval0);

    // contains, added graph
    graph_add_node(tg, 5); 
    int tval1 = contains_node(tg, 5);
    printf("Contains, r E:0, A:%d\n", tval1);
    
    // contains, 2x added graph
    graph_add_node(tg, 10);
    int tval2 = contains_node(tg, 10);
    printf("Contains, r E:1, A:%d\n", tval2);


    // conatins, 3x, added graph, early index
    graph_add_node(tg, 11);
    graph_add_node(tg, 12);
    int tval3 = contains_node(tg, 11);
    printf("Contains, early index, r E:2, A:%d\n", tval3);

    // !contains, added graph
    int tval4 = contains_node(tg, 77);
    printf("!contains, filled graph, r E:-1, A:%d\n", tval4);

    free_graph(tg);
}


void testAddEdge() {
    
    graph_t* tg = create_graph();
    testName("testAddEdge");

    // Case0: empty graph, no nodes
    int tval0 = graph_add_edge(tg, 4, 2);
    printf("Empty graph, g->numNodes 0, r E:-1, A:%d\n", tval0);  

    // Case 1: src not exist
    graph_add_node(tg, 2);
    int tval1 = graph_add_edge(tg, 5, 2);
    printf("!src, E: -1, A:%d\n", tval1);
    
    int tval1a = graph_add_edge(tg, 7, 2);
    printf("!src, E: -1, A:%d\n", tval1a);

    // Case 2: destination not exist
    int tval2 = graph_add_edge(tg, 2, 5);
    printf("!dest, E:-1, A:%d\n", tval2); 

    // Case 3: !src, !dest
    int tval3 = graph_add_edge(tg, 77, 99);
    printf("!src && !dest E:-1 A:%d\n", tval3);

    // Case4: no edges exist yet
    graph_add_node(tg, 5);
    printf("State: (2), (5), add edge (2)->(5), DAG\n");
    int tval4 = graph_add_edge(tg, 2, 5);
    printf("(2), (5) add edge (2)->(5), r E:0, A:%d\n", tval4);  

    // Case5: nodes and edges exist, add new edge
    graph_add_node(tg, 7);
    // State: (2)->(5), 7, add edge (5)->(7);
    printf("State: (2)->(5), 7, add edge (2)->(7)\n");
    int tval5 = graph_add_edge(tg, 2, 7);

    // Case5: nodes and edges xist, new edge is duplicate 
    printf("\n*** dupe test***\n");
    printf("state, (2)->(5)->(7), add edge (2)->(7), expect dupe\n");
    int tval6 = graph_add_edge(tg, 2, 7);
    printf("E: -1, A: %d\n", tval6);





    free_graph(tg);
}


void testGets() {

    testName("testGetNum/Edge");
    graph_t* tg = create_graph();

    graph_add_node(tg, 2);
    graph_add_node(tg, 3);
    graph_add_edge(tg, 2, 3);

    printf("numNodes E:2, A:%d\n", graph_num_nodes(tg));
    printf("numEdge E:1, A:%d\n", graph_num_edges(tg));


    free_graph(tg);
}


void testContainEdge() {

    testName("testContainsEdge");
    graph_t* tg = create_graph();

    graph_add_node(tg, 4);
    graph_add_node(tg, 2);
    graph_add_node(tg, 3);
    graph_add_node(tg, 7);
    graph_add_edge(tg, 3, 2);
    graph_add_edge(tg, 4, 7);

    int tval0 = contains_edge(tg, 3, 2);
    int tval0a = contains_edge(tg, 4, 7);
    printf("r1 E:0, A:%d, r2 E:0, A:%d\n", tval0, tval0a);

    // bad src or dest
    int tval1 = contains_edge(tg, 4, 1);
    int tval2 = contains_edge(tg, 1, 8);
    int tval3 = contains_edge(tg, 1, 3);
    printf("!src or !dest, E:-1, A:%d, A:%d, A:%d\n", tval1, tval2, tval3);

    free_graph(tg);

}

void testNumNeigh() {
    testName("testNumNeigh");

    graph_t* tg = create_graph();

    int t0 = numNeighbors(tg, 1);
    printf("Empty, E:-1, A:%d\n", t0);

    graph_add_node(tg, 2);
    graph_add_node(tg, 0);
    graph_add_node(tg, 4);
    graph_add_node(tg, 5);
    graph_add_node(tg, 9);
    graph_add_edge(tg, 2, 4);
    graph_add_edge(tg, 2, 5);
    graph_add_edge(tg, 2, 9);

    int t1 = numNeighbors(tg, 2);
    printf("t1 numNeigh E:3, A:%d\n", t1);

    int t2 = numNeighbors(tg, 0);
    printf("t2 numNeigh E:0, A:%d\n", t2);

    free_graph(tg);
}

void printNeighArray(int * arr, graph_t* tg, int node) {
    int t2 = numNeighbors(tg, node);
    printf("Array Size %d\n", t2);
    printf("Neighbor Array for %d: ", node);
    for (int i = 0; i < t2; i++) {
        int val = arr[i];
        printf("[%d]", val);
    }
    printf("\n");
}
void testNeighArr() {
    graph_t* tg = create_graph();

    graph_add_node(tg, 2);
    graph_add_node(tg, 4);
    graph_add_node(tg, 8);
    graph_add_node(tg, 9);
    graph_add_edge(tg, 2, 4);
    graph_add_edge(tg, 2, 8);
    graph_add_edge(tg, 2, 9);
    int* t = getNeighbors(tg, 2);
    printf("getNeigh %p\n", t);
    printf("Array print helper fxn:\n");
    printNeighArray(t, tg, 2);

}

void testRemoveEdge() {
    testName("testRemoveEdge");
    graph_t* tg = create_graph();

    graph_add_node(tg, 2);
    graph_add_node(tg, 4);
    graph_add_node(tg, 5);
    graph_add_node(tg, 8);
    graph_add_node(tg, 9);
    graph_add_edge(tg, 2, 4);
    graph_add_edge(tg, 2, 8);
    graph_add_edge(tg, 2, 9);

    //case one: head remove
    // (2--4--8--9)(5) to (2--8--9)(5)
    // e 0
    printf("killing (4) in (2--4--8--9)(5)\n");
    int* t = getNeighbors(tg, 2);
    printNeighArray(t, tg, 2);
    int t0 = graph_remove_edge(tg, 2, 4);
    printf("numNeigh E: 2, A:%d\n", numNeighbors(tg, 2));
    printf("in-graph neighbor reach, n1 E:8 A:%d, E:9 A:%d\n", tg->head->neighbor->data->data, tg->head->neighbor->next->data->data);

    //e: -1
    int t1 = contains_edge(tg, 2, 4);
    printf("Contains Edge post 4 remove, E:-1, A:%d\n", t1);

    int* t2 = getNeighbors(tg, 2);
    printNeighArray(t2, tg, 2);

    //case two: tail remove
    // (2--8--9)(5) to (2--8)(5)
    //case three: middle remove
    printf("2--8--9)(5) to (2--8)(5)");
    graph_remove_edge(tg, 2, 9);
    int* t3 = getNeighbors(tg, 2);    
    printNeighArray(t3, tg, 2);

    //case three: middle remove
    // (2--8--11--10)(5) to (2--8--10)(5)
    graph_add_node(tg, 11);
    graph_add_node(tg, 10);
    graph_add_edge(tg, 2, 11);
    graph_add_edge(tg, 2, 10);
    int* t4 = getNeighbors(tg, 2); 
    printNeighArray(t4, tg, 2);
    graph_remove_edge(tg, 2, 11);
    int* t5 = getNeighbors(tg, 2);
    printNeighArray(t5, tg, 2);

    free_graph(tg);
}

void testRemoveNode() {
    


    testName("testRemoveNode");
    graph_t* tg = create_graph();
    
    // no node in graph r -1
    printf("\n#### empty graph###\n");
    printf("Empty graph E:-1 A:%d\n", graph_remove_node(tg, 5));


    // Node beginning: remove (2)
    graph_add_node(tg, 2);
    graph_add_node(tg, 5);
    graph_add_node(tg, 7);
    graph_add_edge(tg, 5, 2);


    printf("\n#### remove head ###\n");

     // succes t0 tg->head = (2)
    printf("t0 g->head->data E:2, A:%d\n", tg->head->data);
    int* t0 = getNeighbors(tg, 5);
    printNeighArray(t0, tg, 5);

   // (2)-(5--2)-(7) to (5)-(7)
    int tval0 = graph_remove_node(tg, 2);
    // success r 0
    printf("(2)(5--2)(7) to (5)(7), r E:0 A:%d\n", tval0);

    // success tg->numEdges --;
    printf("g->numNodes --, E:2, A:%d\n", tg->numNodes);

    // success t1 tg->head = (5)
    printf("t0 g->head->data E:5, A:%d\n", tg->head->data);
    int* t = getNeighbors(tg, 5);
    printNeighArray(t, tg, 5);
    // success t1 tg->head->next = (7)
    printf("t0 g->head->next->data E:7, A:%d\n", tg->head->next->data);
    printf("t0 g->tail->data E:7, A:%d\n", tg->tail->data);

  
    printf("\n#### remove tail ###\n");
    // Node end: remove (11)
    // (5--11)-(7)-(11) to (5)-(7)
    graph_add_node(tg, 11);
    graph_add_edge(tg, 5, 11);

    // success r 0
    int tval3 = graph_remove_node(tg, 11);

    printf("remove tail (5--11)-(7)-(11) to (5)-(7) r, E:0, A:%d\n", tval3);

    // success tg->numEdges --;
    printf("g->numNodes E:2, A:%d\n", tg->numNodes);

    // succes t1 tg->head = (5)
    printf("g->head->data E:5, A:%d\n",tg->head->data);

    // success t1 tg->tail = (7)
    printf("g->tail->data E:7, A:%d\n", tg->tail->data);

    // success t1 tg->head->next = (7)
    printf("g->head->next->data E:7, A:%d\n", tg->head->next->data);


    printf("\n#### remove middle ###\n");
    // Node middle: remove (7) 
    // (5)-(7)-(8--7) to (5)-(8)
    graph_add_node(tg, 8);
    graph_add_edge(tg, 8, 7);

    // success r 0
    int tval1 = graph_remove_node(tg, 7);

    // success r 0
    printf("(5)(7)(8) to (5)(8), r E:0 A:%d\n", tval1);

    // success tg->numEdges --;
    printf("g->numNodes --, E:2, A:%d\n", tg->numNodes);

    // succes t1 tg->head = (5)
    printf("t1 g->head->data E:5, A:%d\n", tg->head->data);

    // success t1 tg->tail = (8)
    printf("t1 g->tail->data E:8 A:%d\n", tg->tail->data);

    // success t1 tg->head->next = (8)
    printf("t1 g->head->->next->data E:8 A:%d\n", tg->head->next->data);

    free_graph(tg);

}



void testReachable() {
    testName("testReachable");
    graph_t* tg = create_graph();
    //  (2--5---22)(5---4)(4---3---9)(3)(9)(10)(22);
    graph_add_node(tg, 2);
    graph_add_node(tg, 5);
    graph_add_node(tg, 22);
    graph_add_node(tg, 4);
    graph_add_node(tg, 3);
    graph_add_node(tg, 9);
    graph_add_node(tg, 10);
    graph_add_edge(tg, 2, 5);
    graph_add_edge(tg, 2, 22);
    graph_add_edge(tg, 5, 4);
    graph_add_edge(tg, 4, 3);
    graph_add_edge(tg, 4, 9);

    //test path from: 2->9
    //E: 0
    int t = is_reachable(tg, 2, 9);
    printf("SUCCESS test path from: 2->9 E:0, A:%d\n", t);
    printf("\n");
    // test path from: 2->10
    //E: -1
    int t0 = is_reachable(tg, 2, 10);
    printf("FAIL test path from: 2->10 E:-1, A:%d\n", t0);


    free_graph(tg);

}

void testQ() {
    testName("testQ");

    //create queue with 10 capacity
    queue_t* bfs_q = create_queue();
    printf("\n## Q after creation ##\n");
    int a = queue_size(bfs_q);
    printf("Size after creation %d\n", a);

    printf("**Adding to Queue: 10**\n");
    queue_enqueue(bfs_q, 10);
    printf("Size after 1st add %d\n", queue_size(bfs_q));
    printf("Head after 1st add %d\n", bfs_q->head->data);
    printQueue(bfs_q);
 
    printf("**Adding to Queue: 20, 30, 40, 50 **\n");
    printf("E: 10, 20, 30, 40, 50\n");
    int t = queue_size(bfs_q);
    printf("Size E: 5, A:%d\n", t);
    queue_enqueue(bfs_q, 20);
    queue_enqueue(bfs_q, 30);
    queue_enqueue(bfs_q, 40);
    queue_enqueue(bfs_q, 50);
    printf("Head, next %d %d", bfs_q->head->data, bfs_q->head->next->data);
    printQueue(bfs_q);

    printf("Removing fom Q x3\n");
    printf("E: 40, 50\n");
    queue_dequeue(bfs_q);
    queue_dequeue(bfs_q);
    queue_dequeue(bfs_q);
    int t0 = queue_size(bfs_q);
    printf("Queue Size: E:2, A:%d\n", t0);
    printf("Head, next %d %d", bfs_q->head->data, bfs_q->head->next->data);
    printQueue(bfs_q);

    printf("ring add\n");
    queue_enqueue(bfs_q, 50);
    queue_enqueue(bfs_q, 50);
    queue_enqueue(bfs_q, 50);
    queue_enqueue(bfs_q, 50);
    queue_enqueue(bfs_q, 50);
    queue_enqueue(bfs_q, 50);
    queue_enqueue(bfs_q, 50);
    queue_enqueue(bfs_q, 50);
    printQueue(bfs_q);
    queue_enqueue(bfs_q, 50);
    queue_enqueue(bfs_q, 50);
    queue_enqueue(bfs_q, 50);
    queue_enqueue(bfs_q, 20);
    queue_enqueue(bfs_q, 20);
    queue_enqueue(bfs_q, 20);
    queue_enqueue(bfs_q, 20);
    queue_enqueue(bfs_q, 20);
    printQueue(bfs_q);
    free_queue(bfs_q);
}

void testPrintGraph() {
    testName("testPrintGraph");
    graph_t* tg = create_graph();

    //empty print
    printf("Empty, E:"", A:");
    graph_print(tg);
    //  (2--5---22)(5---4)(4---3---9--2)(3)(9)(10)(22)
    graph_add_node(tg, 2);
    graph_add_node(tg, 5);
    graph_add_node(tg, 22);
    graph_add_node(tg, 4);
    graph_add_node(tg, 3);
    graph_add_node(tg, 9);
    graph_add_node(tg, 10);
    graph_add_edge(tg, 2, 5);
    graph_add_edge(tg, 4, 2);
    graph_add_edge(tg, 2, 22);
    graph_add_edge(tg, 5, 4);
    graph_add_edge(tg, 4, 3);
    graph_add_edge(tg, 4, 9);

    printf("E:(2--5---22)(5---4)(22)(4---3---9--2)(3)(9)(10)\n");
    graph_print(tg);
    graph_remove_edge(tg, 4, 3);
    printf("Remove Edge 4->3, E:(2--5---22)(5---4)(22)(4--9--2)(3)(9)(10)\n");
    printf("Num Neighs, 4, E: 2, A:%d\n", numNeighbors(tg, 4));
    graph_print(tg);

    graph_add_edge(tg, 4, 3);
    printf("Add Edge 4->3, E:(2--5---22)(5---4)(22)(4--3--9--2)(3)(9)(10)\n");
    printf("Num Neighs, 4, E: 3, A:%d\n", numNeighbors(tg, 4));
    graph_print(tg);
    free_graph(tg);

}

void testCycle() {
    testName("testCycle");
    graph_t* tg = create_graph();

    //empty graph
    int t0 = has_cycle(tg);
    printf("Empty graph cycle E:-1 A:%d\n",t0);

    //  (2--5---22)(5---4)(4---3---9--2)(3)(9)(10)(22)
    graph_add_node(tg, 2);
    graph_add_node(tg, 5);
    graph_add_node(tg, 22);
    graph_add_node(tg, 4);
    graph_add_node(tg, 3);
    graph_add_node(tg, 9);
    graph_add_node(tg, 10);
    graph_add_edge(tg, 4, 2);
    graph_add_edge(tg, 2, 5);
    graph_add_edge(tg, 2, 4);
    graph_add_edge(tg, 2, 22);
    graph_add_edge(tg, 5, 4);
    graph_add_edge(tg, 4, 3);
    graph_add_edge(tg, 4, 9);

    graph_print(tg);
    printf("Graph with cycles:\n");
    printf("E: 0, A:%d\n", has_cycle(tg));
    free_graph(tg);

    graph_t* ty = create_graph();

    //empty graph

    printf("Graph with no cycles:\n");
    graph_add_node(ty, 2);
    graph_add_node(ty, 5);
    graph_add_node(ty, 22);
    graph_add_node(ty, 4);
    graph_add_node(ty, 3);
    graph_add_node(ty, 9);
    graph_add_node(ty, 10);

    printf("E: -1, A:%d\n", has_cycle(ty));

    free_graph(ty);

}



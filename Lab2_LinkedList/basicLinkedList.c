// lab 2 example of basic linked list with iterator

#include <stdio.h>

// build node struct
typedef struct node {
    int myData;
    struct node* next;
} node_t;

// use struct
int main() {

    // create nodes
    node_t node1;
    node1.myData = 100;

    node_t node2;
    node2.myData = 200;


    // link nodes
    node1.next = &node2;
    node2.next = NULL;

    // create iterator node
    node_t* iterator;
    iterator = &node1; 

    // use nodes
    while (iterator!= NULL) {
        printf("%d\n", iterator -> myData);
        iterator = iterator -> next;
    }

    return 0;
}
















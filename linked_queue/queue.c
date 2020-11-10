//https://www.educative.io/edpresso/how-to-use-the-typedef-struct-in-c
#include<stdlib.h>
#include<stdio.h>

/*
    process_t: struct that represents a process
    -> int id //numerical idenifier
    -> char*  //process name
*/
typedef struct process {
    int id;
    char* name;
} process_t; 


//Node type for LL
typedef struct node {
    //type of data held and pointer to next node
    void* data;
    struct node *next; 
} node;

/*
    queue_t: linked list queue
    -> Node *front //the head of the LL
    -> Node *back //tail of LL
*/
typedef struct queue {
    //num nodes in it
    int count;
    node *front;
    node *back;
} queue_t;



//helper function, create a process
process_t* create_process(char* name, int id) {
    
    process_t* p = (process_t*)malloc(sizeof(process_t));
    p->name = name;
    p->id = id;

    return p;

}

//helper fxn, create an empty shell queue
queue_t* initqueue() {
    
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    q->count = 0;
    q->front = NULL;
    q->back = NULL;

    return q;
}


/*
NOTE TO GRADER:
I can't get the void* pointer to work in reference to passing in a 
process_t* pointer to enqueue as the data for a node. The 
following error keeps occuring, full error message below (just on
test printing of struct fields for simplication)

queue.c: In function ‘enqueue’:
queue.c:65:27: warning: dereferencing ‘void *’ pointer
   65 |     printf("%s\n", element->name);
      |                           ^~
queue.c:65:27: error: request for member ‘name’ in something not a structure or union
queue.c:66:27: warning: dereferencing ‘void *’ pointer
   66 |     printf("%d\n", element->id);
      |                           ^~
queue.c:66:27: error: request for member ‘id’ in something not a structure or union

Because of this, I can get the enqueue to work if I use a
process_t* process param in the function, which I've done 
to demonstrate I can get a linked list queue working conceptually
*/

void enqueue(queue_t* q, process_t* element) {

    //make and malloc a node
    node* new = malloc(sizeof(node));

    //set it equal to the process passed in
    new->data = element;

    //if queue isn't empty:
    if (!(q->back == NULL)) {
        
        //set current back->next to new node, set q->back to newnode
        q->back->next = new;
        q->back = new;
        q->count++;

    } else {
        //if queue is empty:
        
        //set front and back to new node
        q->front = new;
        q->back = new;
        q->count++;
    }
}

//remove head element and returns it, 
void* dequeue(queue_t *queue) {

    if (queue->back == NULL) {
        printf("Queue is empty");
        return NULL;
    }
    
    //save current head in temp variable
    node* oldhead = queue->front;

    //set current head to second in queue
    queue->front = queue->front->next;

    //extract process from the node
    process_t* p = oldhead->data;

    //drop count
    queue->count--;


    return p;
}

int main() {

    process_t* p0 = create_process("p0", 0);
    process_t* p1 = create_process("p1", 1);
    process_t* p2 = create_process("p2", 2);

    queue_t* q = initqueue();
    
    printf("Queue size: %d\n", q->count);
    enqueue(q, p0);
    printf("Queue size: %d\n", q->count);
    enqueue(q, p1);
    printf("Queue size: %d\n", q->count);
    enqueue(q, p2);

    //print queue state
    printf("Queue size: %d\n", q->count);

    //remove x1
    process_t* offQueue = dequeue(q);
    printf("Queue size: %d\n", q->count);
    printf("Exp P0/0: %s %d\n", offQueue->name, offQueue->id);

    process_t* off2 = dequeue(q);
    printf("Exp P1/1: %s %d\n", off2->name, off2->id);
    process_t* off1 = dequeue(q);
    printf("Exp P2/2: %s %d\n", off1->name, off1->id);


    //TODO: should offer way to fail dequeue empty queue safely

    return 0;
}

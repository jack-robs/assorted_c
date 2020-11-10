// Jack Robertson, Lab 2, CS5006, 20JAN20
// compile with: gcc linkedlist.c -o linkedlist

#include <stdio.h>
#include <stdlib.h> // contains the functions free/malloc

// Create your node_t type here
typedef struct node{
    int year;
    int wins; 
    struct node* next;
} nodeSox;

// Write your functions here
// There should be 1.) create_list 2.) print_list 3.) free_list

nodeSox* create_list() {

    // create nodes, data and links
    // head
    nodeSox* sox2018 = malloc(sizeof(nodeSox));
    sox2018->year = 2018;
    sox2018->wins = 108;

    nodeSox* sox2017 = malloc(sizeof(nodeSox));
    sox2017->year = 2017;
    sox2017->wins = 93;

    nodeSox* sox2016 = malloc(sizeof(nodeSox));
    sox2016->year = 2016;
    sox2016->wins = 93;

    nodeSox* sox2015 = malloc(sizeof(nodeSox));
    sox2015->year = 2015;
    sox2015->wins = 78;

    // tail
    nodeSox* sox2014 = malloc(sizeof(nodeSox));
    sox2014->year = 2014;
    sox2014->wins = 71;

    sox2018->next = sox2017;
    sox2017->next = sox2016;
    sox2016->next = sox2015;
    sox2015->next = sox2014;
    sox2014->next = NULL;

    return sox2018;

}

// print list
void print_list(nodeSox* iterator) {
    
    while(iterator != NULL) {
        printf("wins in %d are %d\n", iterator->year, iterator->wins);
        iterator = iterator-> next;
    }

}


// free list
void free_list(nodeSox* iterator) {
    while(iterator !=NULL) {
        // set hold, hold next address
        nodeSox* keeper = iterator->next;
        
        //free current iterator
        free(iterator);

        //set iterator to keeper
        iterator = keeper; 
    }    

    //free final
    free(iterator);
}


int main(){
  
    nodeSox* redsox;
    
    redsox = create_list();

    nodeSox* iterator = redsox;
    // print function
    print_list(iterator);

    // free function
    free_list(iterator);    
 
    return 0;
}

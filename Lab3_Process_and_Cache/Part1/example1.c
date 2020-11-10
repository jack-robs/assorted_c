//Predicated result: 2?
//Actual:
//$ ./example1
//parent: x = 0
//chid: x = 2



// Type in and try example1.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

    //data type from sys/types.h
    pid_t pid;
    int x = 1;

    pid = fork();

    if (pid == 0) {
        printf("chid: x = %d\n", ++x);
        return 0;
    }

    //Parent
    printf("parent: x = %d\n", --x);

    return 0;
    


}

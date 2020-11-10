// Type in and try example3.c
// child runs forver

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    
    pid_t pid;
    int x = 1;

    pid = fork();

    if (pid == 0) {
        printf("RUnning child forver now pid = %d\n", getpid());
        while(1) {}
    } else {
        // run the parent
        printf("terminating parent pid %d\n", getpid());
        exit(0);
    }
    return 0;
}


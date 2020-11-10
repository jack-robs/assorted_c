// Take a look at some of the previous examples to create your own program!
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    char* myargv[16];
    myargv[0] = "/bin/mkdir";
    myargv[1] = "TESTDIR";
    myargv[2] = NULL;

    char* myargv2[16];
    myargv2[0] = "/bin/ls";
    myargv2[1] = "-F";
    myargv2[2] = NULL;

    char* myargv3[16];
    myargv3[0] = "/bin/rm";
    myargv3[1] = "-rf";
    myargv3[2] = "TESTDIR";
    myargv3[3] = NULL;

    char* myargv4[16];
    myargv4[0] = "/bin/ls";
    myargv4[1] = "-F";
    myargv4[2] = NULL;



    if (fork() == 0) {
        execve(myargv[0], myargv, NULL);
        printf("fork() 0\n");
        exit(1);
    } else {
        wait(NULL);
        printf("Left mkdir\n");
    }

     if (fork() == 0) {
        execve(myargv2[0], myargv2, NULL);
        printf("fork() 0\n");
        exit(1);
    } else {
        wait(NULL);
        printf("left ls\n");
    }

 
     if (fork() == 0) {
        execve(myargv3[0], myargv3, NULL);
        printf("fork() 0\n");
        exit(1);
    } else {
        wait(NULL);
        printf("left rm -rf dr\n");
    }
 
     if (fork() == 0) {
        execve(myargv4[0], myargv4, NULL);
        printf("fork() 0");
        exit(1);
    } else {
        wait(NULL);
        printf("Always prints last\n");
    }

  
    return 0;




}

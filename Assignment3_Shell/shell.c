// Modify this file for your assignment

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


//signal handler

void sighan(int sig) {
    write(1,"Terminating through signal handler\n",35);
    exit(0);
}

//getIndex()
//params: the input from the myshell terminal, and the mapping array of 
//myshell row[0], related bash command row[1]
//returns: index of relevant myshell-bash mapping

int getIndex(char * shellIn, char* cmdMap[2][5]){
    
    int index = -1;
    int check = -1;

    //remove newline
    if (shellIn[strlen(shellIn) -1] == '\n'){
        shellIn[strlen(shellIn) -1] = '\0' ;
    }

    //look through row
    int i = 0;
    for (int j = 0; j < 5; j++) {
        check = strncmp(shellIn, cmdMap[i][j], 80); 
        if (check == 0) {
            index = j;
            break;
        }
    }
    return index;
}


char* getBash(int index, char* cmdMap[2][5]) {
    
    int row = 1;
    int col = index;


    char* bsh = cmdMap[row][col];
    
    return bsh;

}


int buildExecv(char* myargv[], char* bash, int inputLen, char* store[]) {

    myargv[0] = bash;
    myargv[inputLen] = NULL;

    store[inputLen - 1] = strtok(store[inputLen - 1], "\n");

    for (int i = 1; i < inputLen; i++) {
        myargv[i] = store[i];
    }

    return 0;

}

void game() {
    printf("play game!\n");
    printf("Loading.\n");
    sleep(1);
    printf("Loading...\n");
    sleep(1);
    printf("Loading....\n");
    sleep(1);
    printf("Loading.....\n");
    sleep(1);

    printf("A random number will be generated in the background each round.\nYou have 4 methods to guess correctly, each worth different points.\n-Divisible by 2: 1 point.\n-Divisible by 3: 3 points.\n-Divisible by 7: 10 points.\n-Divislbe by 11: 22 points.\nYou will lose the same amount of points if you guess wrong. All players start with 23 points.\n");
    printf("Enter a single number for your guess, example: `Guess> 7` will guess divisible by 7\n");
    printf("Game ends at less than 0, or WINS at 40\n");
    printf("Example of game play:\nPoints: 23. (Background random number: 199232121). \nGuess> 2.\nResult: wrong, -1 pts,\nPoints:22.\n");
    int pts = 23;

    printf("\n\nenter> q to quit\n\n");
    while (1) {
        
        srand(time(NULL));
        int rng = rand();

        char input[20];
        printf("Current Points: %d\n", pts);
        printf("Guess> ");
        scanf("%s", input);
        
 
        int cmp1= strncmp(input, "q", 1);
        if (cmp1== 0) {
            break;
        }

        
        int cmp2= strncmp(input, "2", 1);
        if (cmp2== 0) {
            if (rng % 2 == 0) {
                pts ++;
            } else {
                pts --;
            }
        }

        int cmp3= strncmp(input, "3", 1);
        if (cmp3== 0) {
            if (rng % 3 == 0) {
                pts += 3;
            } else {
                pts -= 3;
            }
        }

        int cmp4 = strncmp(input, "7", 1);
        if (cmp4 == 0) {
            if (rng % 7 == 0) {
                pts += 10;
            } else {
                pts -= 10;
            }
            }

        int cmp5 = strncmp(input, "11", 2);
        if (cmp5 == 0) {
            if (rng % 11 == 0) {
                pts += 22;
                continue;
            } else {
                pts -= 22;
            }
        }
        
        //check win/loss
        if (pts <= 0) {
            break;
        } else if (pts >= 40) {
            break;
        }
        
    }

    if (pts >= 40) {
        printf("win!\n");
    } else {
        printf("lose!\n");
    }


}


int main(){

    //instal signal handler
    signal(SIGINT, sighan);
    //help statement
    char* quitHelp = "Terminate by pressing CTRL-C\n";

    char* commands = "\nSupported commands:\n* showme - list contents of directory\n* killme <file> - delete file\n* myuse - disk mem use\n* makeme <file> - make a file\n* showproc - show running processes\n* game - a FUN FUN GAME\n* help - display help \n* cd <directory> please - MUST ADD PLEASE TO END. \n\tchange up: cd .. please\n\tchange down: cd <Name if in current dir> please\n* exit -leaves shell";


    int session = 0;
    char shellIn[80];
    char * rawIn;
    char * cmdMap[2][5];

    //map of myshell to bash
    cmdMap[0][0] = "showme";
    cmdMap[1][0] = "/bin/ls";
    
    cmdMap[0][1] = "killme";
    cmdMap[1][1] = "/bin/rm";

    cmdMap[0][2] = "showproc";
    cmdMap[1][2] = "/bin/ps";

    cmdMap[0][3] = "myuse";
    cmdMap[1][3] = "/bin/df";

    cmdMap[0][4] = "makeme";
    cmdMap[1][4] = "/bin/touch";

    printf("%s\n", quitHelp);

    printf("%s\n", commands);
    
    printf("\nRunning myShell\n");
    while(session == 0) {

        printf("\n\n");

        char pwd[256];
        if (getcwd(pwd, sizeof(pwd)) == NULL) {
            printf("Error fetching cur dir\n");
        } else {
            printf("Cur Dir: %s\n", pwd);
        }


        //build child proc array, +1 len for NULL
        char* storeInput[80];

        //take input
        printf("mini-shell> ");
        fgets(shellIn, 80, stdin);

        //special cases: game, help, exit, cd
        int cmp = strncmp(shellIn, "game", 4);
        if (cmp == 0) {
            game();
            continue;
        }

        int cmp1 = strncmp(shellIn, "help", 4);
        if (cmp1 == 0) {
            printf("%s\n", commands);
            continue;
        }

        int cmp2 = strncmp(shellIn, "exit", 4);
        if (cmp2 == 0) {
            exit(1);
        }

        //handle change directory
        char delim[] = " ";

        char *lex = strtok(shellIn, delim);

        int lenInput = 0;
        while(lex != NULL) {
            storeInput[lenInput] = lex;
            lenInput ++;
            lex = strtok(NULL, delim);
        }


        int cmp3 = strncmp(storeInput[0], "cd", 2);
        if (cmp3 == 0) {
            int cdDir = strncmp(storeInput[1], "..", 2);
            if (cdDir == 0) {
                chdir("..");
                continue;
            } else {
                chdir(storeInput[1]);
                continue;
            }
        }

        //get int index of equiv bash command
        int index = getIndex(shellIn, cmdMap);

        if (index == -1) {
            printf("unknown commmand\n");
            continue;
        }
  
        char* bsh = getBash(index, cmdMap);

        char* myargv[lenInput + 1];

        //build execve array
        int buildCmd = buildExecv(myargv, bsh, lenInput, storeInput); 

        //uncomment for tracking myargv contents
        //printf("\n\n\nmyargv has:\n");
        //for (int i = 0; i < lenInput + 1; i++) {
        //    printf("%s\n", myargv[i]);
        //}

        if (fork() == 0) {
            execve(myargv[0], myargv, NULL);
            exit(1);
        } else {
            wait(NULL);
        }

        
    

    }


    return 0;
}


































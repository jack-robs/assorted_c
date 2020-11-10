//task3 
// gcc vfork.c -o vfork
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


void paint(int artist) {
	printf("Arist %d is painting\n", artist);

}


int main(int argc, char** argv) {

	int* integers = malloc(sizeof(int)*8000);

	int numberOfArtists = 8;

	pid_t pid;
	
	for(int i = 0; i < numberOfArtists; i++) {
		pid = fork();

		if(pid == 0) {
			int workId = getpid();
			paint(workId);
			exit(0);
		} else {
			wait(NULL);
		}
	
	}
	
	printf("parent is exiting\n");


	free(integers);
	return 0;
}

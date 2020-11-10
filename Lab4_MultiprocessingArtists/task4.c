//task4
//
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
		}// else {
		 //       wait(NULL);
		//}//
	
	}
	pid_t wpid;
	int status = 0;
	while ((wpid = wait(&status)) > 0);
	
	printf("parent is exiting\n");


	free(integers);
	return 0;
}

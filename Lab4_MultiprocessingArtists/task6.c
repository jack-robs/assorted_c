//task4
//
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int colors[64][64*3];

void paint(int artist) {
	printf("Arist %d is painting\n", artist);
	
	for (int i = 0; i < 64*3; i++) {
		colors[artist][i] = artist;
	}
	

}


int main(int argc, char** argv) {


	int numberOfArtists = 64;

	pid_t pid;
	
	for(int i = 0; i < numberOfArtists; i++) {
		pid = vfork();

		if(pid == 0) {
			paint(i);
			exit(0);
		}

		printf("Child: %d\n", pid);

	}
	
	printf("PPM TIME\n");

	FILE *fp;
	fp = fopen("vfork.ppm", "w+");
	fputs("P3\n", fp);
	fputs("64 64\n", fp);
	fputs("255\n", fp);
	for(int i = 0; i < 64; i++) {
		for(int j = 0; j < 64 *3; j++) {
			fprintf(fp, "%d", colors[i][j]);
			fputs(" ",fp);
		}
		fputs("\n",fp);
	}
	fclose(fp);

	return 0;
}






























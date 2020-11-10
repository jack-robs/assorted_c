// Implement a working parser in this file that splits text into individual tokens.

#include <stdio.h>
#include <string.h>

//take CL input
int main(int argc, char*argv[]) {
	
	if (argc == 1) {
		printf("Usage: ./parse \"<commands>\"\n");
	
	}

	char delim[] = " ";

	char *lex = strtok(argv[1], delim);

	while(lex != NULL) {
		printf("%s\n", lex);
		lex = strtok(NULL, delim);
	}

	return 0;
	
}


	
	
	

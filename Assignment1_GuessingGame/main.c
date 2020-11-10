#include <stdio.h>


void prompt(){
	int d = 0;

	for (d; d < 20; d++){
		printf("=");
	}

	printf("\nGuess a number between 1-10\n");
	
	for (d=0; d < 20; d++){
		printf("=");
	}
	printf("\n");
}



int game_play(){
		
	int comp_guess = rand() % 10;	
	int u_input = -1;	
	int num_guess = 0;
	
	while (u_input != comp_guess){		
	
		// take user input	
		printf("Enter Guess: ");
		scanf("%d", &u_input);

		//if else for user high/low hint	

		if (u_input < comp_guess){
			printf("Guess higher!\n");	

		} else if (u_input > comp_guess) {
			printf("Guess lower!\n");
		}
	
		num_guess ++;
	}

	printf("Success! It took you %d guesses to guess %d\n", num_guess, comp_guess);	
	return num_guess;
}


int main(){

	int i = 0;
	int game_array[5];

	// gameplay for 5 rounds
	while (i < 6){
		prompt();
		int result = game_play();
		// store in guess_array	
		game_array[i] = result;

		// start next game, iterate	
		i ++;

	}
	
	// report results
	for (i=0; i<6; i++){
		printf("Game %d Guesses: %d\n", i, game_array[i]);
	}
} 


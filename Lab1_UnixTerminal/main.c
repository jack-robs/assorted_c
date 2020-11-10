// Add your program here!

#include <stdio.h>

// function signature
double power(double base, double n){
    // declare fxn vars
    int i, p;
   
    // set p = 1, initial power
    p = 1;
    for (i = 1; i <=n; ++i){
        p = p * base; 
    } 
    return p;
}    

int main() {
    // declare & assign variables
    double base = 2;
    double n = 1;

    while (n < 11){
        printf("\n");

               
        printf("2 to the %.0fth:\n", n);
        // function call function
        printf("%.0f\n", power(base,n)); 
         
        n ++;
    }
} 

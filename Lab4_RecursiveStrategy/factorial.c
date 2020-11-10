// gcc factorial.c -o factorial
// ./factorial

#include <stdio.h>

int factorial(int n){
    int i;
    int j = 1;

    for (i = 1; i<n; i++) {
        j = j * i; 
    }

    return j;
};

int factorial_rec(int n){
    // base case
    if (n == 1) {
        return 1;
    }
    
    int j = n * factorial_rec(n-1);

    return j;
}

int main(){

    printf("factorial(10) = %d\n",factorial(10));
    printf("factorial_rec(10) = %d\n",factorial_rec(10));


    return 0;
}

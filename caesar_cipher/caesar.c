//CS5600 SYS Proj 0, Part3: caesar.c
//Jack Robertson, robertson.jo@northeastern.edu
//https://flaviocopes.com/c-return-string/
//https://github.com/Rainier-Cyber/C-cheatsheet
//https://overiq.com/c-programming-101/array-of-pointers-to-strings-in-c/
//https://www.geeksforgeeks.org/c-program-to-find-the-length-of-a-string/
//https://www.educative.io/edpresso/what-is-the-toupper-function-in-c
//ascii math: http://www.asciitable.com/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//signature: encode(const char* plaintext, int key)
char* encode(const char* plaintext, int key) {

   //find length of plaintext
    int len = 0;
    for (int i = 0; plaintext[i] != '\0'; ++i) {
        len++;
    }

    //create copy of PT into working copy of ciphertext, char array
    char ciphertext[len]; 
    strcpy(ciphertext, plaintext);

    //convert to upper case here vs. latter
    int i = 0;
    while (ciphertext[i]) {
        char ch = ciphertext[i];
        ciphertext[i] = toupper(ch);
        i++;
    }

    //do encoding
    for (int i = 0; ciphertext[i] != '\0'; ++i) {

        //grab indiv char, char will be mutated per caesar rules
        char cipher = ciphertext[i];

        cipher = cipher + key;
        
        //handle translations of final ciphers > 'Z', i.e. 
        //rounding the horn to Z->C for shift of 3;
        if (cipher > 'Z') {
            //similar to mod operation if using 0->25 alphabet, not ASCII
            cipher = cipher - 'Z' + 'A' - 1;
            ciphertext[i] = cipher;
            continue;
        }

        ciphertext[i] = cipher;
    }

    
    //create and malloc char* that gets returned
    char* finalCipher;
    int size = len + 1;
    finalCipher = (char*)malloc(sizeof(char)*size);

    //fill char* finalCipher character by character
    for (int i = 0; i <= len; ++i) {
        char c = ciphertext[i];
        *(finalCipher + i) = c;
    }

    return finalCipher;
    

}

char* decode(const char* ciphertext, int key) {

   //find length of ciphertext
    int len = 0;
    for (int i = 0; ciphertext[i] != '\0'; ++i) {
        len++;
    }

    //create copy of CT into working copy of plaintexttext, char array
    char plaintext[len]; 
    strcpy(plaintext, ciphertext);

    //convert to upper case here vs. latter
    int i = 0;
    while (plaintext[i]) {
        char ch = plaintext[i];
        plaintext[i] = toupper(ch);
        i++;
    }

    //do encoding
    for (int i = 0; plaintext[i] != '\0'; ++i) {

        //grab indiv char, char will be mutated per caesar rules
        char plain = plaintext[i];

        plain = plain - key;
        
        //similar idea as rounding the horn for chars past z, but 
        //in this case, dipped below 'A' in ASCII
        if (plain < 'A') {
            
            //reverse of rounding the horn math from encode
            plain = plain + 'Z' - 'A' + 1;
            plaintext[i] = plain;
            continue;
        }

        plaintext[i] = plain;
    }

    
    //create and malloc char* that gets returned
    char* finalPlain;
    int size = len + 1;
    finalPlain = (char*)malloc(sizeof(char)*size);

    //fill char* finalCipher character by character
    for (int i = 0; i <= len; ++i) {
        char c = plaintext[i];
        *(finalPlain + i) = c;
    }

    return finalPlain;
}
    

//main fxn for caesar.c
//'const' is a keyword in C that applies to variables. It prohibits from changing its value after its declaration (quora)
//possible TODOs: take input, deal w/ punctuation

int main() {
    
    /*
    Encrypt
    */
    //expected output: 'GRJ', shift of 3
    char* plaintext = "Dog";
    int key = 3;
 
    printf("\nPlaintext in: %s\n", plaintext);
    char* ct = encode(plaintext, key);
    printf("Cipher text out: %s\n", ct);
    
    //expected out: CRR
    char* test2 = "Zoo";
    printf("\nPlaintext in: %s\n", test2);
    printf("Ciphertext out: %s\n", encode(test2, key));

    /*
    Decrypt
    */

    //expected out: dog
    char* cipher = "GRJ";
    char* plain = decode(cipher, key);
    printf("\nCiphertext in: %s\n", cipher);
    printf("Plaintext out: %s\n", plain);
    
    printf("\nCiphertext in: CRR\nPlaintext out: %s\n", decode("CRR", key));


    return 0;
}

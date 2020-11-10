// Task: Implement the 'sortIntegers' function below

// =================== Libraries ==================
#include <stdio.h> // Include file for standart input/output
    
// =============== Helper Functions ===============

// Returns the minimum integer from a range in an array
// Input: array - An array of integers
//        start - Where to start looking in an array
//        stop - End of where to search. Typically the 'size' of the array.
// Output: The index in an array of the minimum value between a range [start,stop]


int findMinimum(int* array, int start, int stop){
    // set min index to starting indexe
    int minVal = array[start];
    int minIndex = start;
    int i;

    // for loop through array
    for (i = start; i < stop; i++) {
        if (array[i] < minVal) {
            minVal = array[i];
            minIndex = i;
        }
    }

    return minIndex; 
}

void testFindMinimum() {

    int testMinArr[] = {100,201,52,3223,24,55,623,75,8523,-9,150};
    
    printf("\n***running testFindMinimum()***\n");

    printf("start 1, stop 4, expected index 4, %d\n", findMinimum(testMinArr, 1, 4));
    printf("start 0, stop 11, expected index 9, %d\n", findMinimum(testMinArr, 0, 11));
    printf("start 0, stop 0, expected index 0, %d\n", findMinimum(testMinArr, 0, 0));

}


// Swaps two numbers in an array
// Input: The 'address of' an index into an array for positions in an array.
//K&R page 88
void swap(int* a, int* b){
    int temp;

    temp = *a;
    *a = *b;
    *b = temp; 
}

void testSwap() {
    int a = 5;
    int b = 6;

    printf("\n***running testSwap()***\n");

    printf("%d, %d\n", a, b);
    swap(&a, &b);   
    printf("%d, %d\n", a, b);
}

// Provided below is a sort function. I have also
// provided a template for how to document functions
// to help organize your code.
// Name: sort
// Input(s):
//          (1) 'array' is a pointer to an integer address. 
//              This is the start of some 'contiguous block of memory' that we will sort.
//          (2) 'size' tells us how big the array of data is we are sorting.
// Output: No value is returned, but 'array' should be modified to store a sorted array of numbers.
void sortIntegers(int* array, unsigned int size){
    
    int i;

    // iterate through list
    for (i=0; i < size; i++) {
        int j = findMinimum(array, i, size);
        swap(&array[i], &array[j]);
    }

}


// Input: A pointer to an array (i.e. the array itself points to the first index)
//        The size of the array (Because we do not know how big the array is automatically)
void printIntArray(int* array, unsigned int size){
  unsigned int i; // Note: 'unsigned int' is a datatype for storing positive integers.
  for(i = 0; i < size; i=i+1){
    printf("%d ",array[i]);
  }
  printf("\n");
}

int main(){
    
    // test swap 
    testSwap();

    // test findMinimum
    testFindMinimum();


    // Some test data sets.
    int dataset1[] = {0,1,2,3,4,5,6,7,8,9,10};
    int dataset2[] = {10,9,8,7,6,5,4,3,2,1,0};
    int dataset3[] = {0,3,2,1,4,7,6,5,8,9,10};
    int dataset4[] = {2,1,1,1,1,1,1,1,1,1,1};
    int dataset5[] = {100,201,52,3223,24,55,623,75,8523,-9,150};
    int dataset6[] = {-1,1,2,-3,4,5,-6,7,8,-9,10};


    printf("\n*** running  printIntArray() BEFORE sort***\n");
    // Print out an array
    printIntArray(dataset1, 11);
    printIntArray(dataset2, 11);
    printIntArray(dataset3, 11);
    printIntArray(dataset4, 11);
    printIntArray(dataset5, 11);
    printIntArray(dataset6, 11);


    // Sort our integer array
    printf("\n*** calling sortIntegers() ***\n");
    sortIntegers(dataset1, 11);
    sortIntegers(dataset2, 11);
    sortIntegers(dataset3, 11);
    sortIntegers(dataset4, 11);
    sortIntegers(dataset5, 11);
    sortIntegers(dataset6, 11);


    printf("\n*** running  printIntArray() AFTER sort***\n");
    // Print out an array
    printIntArray(dataset1, 11);
    printIntArray(dataset2, 11);
    printIntArray(dataset3, 11);
    printIntArray(dataset4, 11);
    printIntArray(dataset5, 11);
    printIntArray(dataset6, 11);

    return 0;
}

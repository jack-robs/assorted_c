// Task: Implement the 'sortIntegers' function below

// =================== Libraries ==================
#include <stdio.h> // Include file for standart input/output

// =============== Helper Functions ===============

void printIntArray(int* array, unsigned int size){
  unsigned int i; // Note: 'unsigned int' is a datatype for storing positive integers.
  for(i = 0; i < size; i=i+1){
    printf("%d ",array[i]);
  }
}

// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(int arr[], int l, int m, int r) {
    // temp arrays
    int left[m - l + 1];
    int right[r - m];

    // build arrays
    int i, j, k;
    for (i=0; i < (m - l + 1); i ++) {
        left[i] = arr[l + i];
    }
    for (j = 0; j < (r- m); j++) {
        right[j] = arr[m+ j + 1];
    }

    // merge temps 
    // initial i, j k
    i = 0;
    j = 0;
    k = l;
    while (i < (m - l + 1) && j < (r - m)) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i ++;
        } else {
            arr[k] = right[j];
            j ++;
        }
        k++;
    }
   
   // final copy
   while (i < (m - l + 1)) {
        arr[k] = left[i];
        i++;
        k++;
   }

   while (j < (r-m)) {
        arr[k] = right[j];
        j++;
        k++;
   }
}

void mergeSort(int* array, int l, int r) {


    if (l == r) {
        return;
    }


    if ( l < r) {
        int m = l + (r - l) / 2;
    
        // left side
        mergeSort(array, l, m);

        // right side
        mergeSort(array, m +1, r);

        merge(array, l, m, r);
    }
}

// Provided below is a sort function. We have also
// provided a template for how to document functions
// to help organize your code.
// Name: sortIntegers
// Input(s):
//          (1) 'array' is a pointer to an integer address. 
//              This is the start of some 'contiguous block of memory' that we will sort.
//          (2) 'size' tells us how big the array of data is we are sorting.
// Output: No value is returned, but 'array' should be modified to store a sorted array of numbers.
void sortIntegers(int* array, unsigned int size){
    // define left
    int initL = 0;
    // define right
    int initR = size - 1;

    mergeSort(array, initL, initR);
}

int main(){
  
  // Some test data sets.
  int dataset1[] = {0,1,2,3,4,5,6,7,8,9,10};
  int dataset2[] = {10,9,8,7,6,5,4,3,2,1,0};
  int dataset3[] = {0,3,2,1,4,7,6,5,8,9,10};
  int dataset4[] = {2,1,1,1,1,1,1,1,1,1,1};
  int dataset5[] = {100,201,52,3223,24,55,623,75,8523,-9,150};
  int dataset6[] = {-1,1,2,-3,4,5,-6,7,8,-9,10};
 
  printf("\n*****pre sort *****\n"); 
  // Print out an array
  printIntArray(dataset1, 11);
  printIntArray(dataset2, 11);
  printIntArray(dataset3, 11);
  printIntArray(dataset4, 11);
  printIntArray(dataset5, 11);
  printIntArray(dataset6, 11);
  
  // Sort our integer array
  sortIntegers(dataset1, 11);
  sortIntegers(dataset2, 11);
  sortIntegers(dataset3, 11);
  sortIntegers(dataset4, 11);
  sortIntegers(dataset5, 11);
  sortIntegers(dataset6, 11);
  
  printf("\n*****post sort *****\n"); 
  // Print out an array
  printIntArray(dataset1, 11);
  printIntArray(dataset2, 11);
  printIntArray(dataset3, 11);
  printIntArray(dataset4, 11);
  printIntArray(dataset5, 11);
  printIntArray(dataset6, 11);
  
  return 0;
}

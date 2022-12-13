#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { 
  SIZE_N = 6
};

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); \
                               } while (0)

int * getResizedArray(int *arr, int oldSize) {
  int *newArr = (int *) malloc(2 * oldSize * sizeof(int));
  if(newArr == NULL){
    errExit("malloc");
  }
  for (size_t i = 0; i < oldSize; i++) {
    newArr[i] = arr[i]; 
  }
  free(arr);
  arr = NULL;
  return newArr;
}

int main() {
  int size = 10;
  int *arr = NULL;
  arr = malloc(size * sizeof(int));
  if(arr == NULL){
    errExit("malloc");
  }
  for (size_t i = 0; i < 10000; i++) {
     if(i*2 >= size) {
       arr = getResizedArray(arr, size);
       size = 2*size;
       printf("size %li\n", size);
     }
     arr[i] = 1;
  }
  free(arr);
}

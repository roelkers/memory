#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void * mem_area;

int main() {
  mem_area = calloc(255, 1);
  char * string = (char *) mem_area;
  for (size_t i = 0; i < 255; i++) {
     printf("%c", string[i]); 
  }
  memset(mem_area, '0', 255);

  for (size_t i = 0; i < 255; i++) {
     printf("%c", string[i]); 
  }
}

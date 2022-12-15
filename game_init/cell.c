#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "cell.h"
#include "constants.h"


void allocCells(Cell ** fields, int length, int width) {
  for (size_t i = 0; i < length; i++) {
     fields[i] = malloc(width* sizeof(Cell)); 
     for (size_t j = 0; j < width; j++) {
        allocCell(&fields[i][j]); 
     }
   } 
}

void allocCell(Cell * cell) {
  cell->color = (char* ) malloc(MAX_STR_LENGTH);
}

void createCell(Cell* cell, char* color) {
  strcpy(cell->color, color);
}

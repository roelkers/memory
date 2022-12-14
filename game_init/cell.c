#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "cell.h"
#include "constants.h"

void createCell(Cell* cell, char* color) {
  cell->color = (char* ) malloc(MAX_STR_LENGTH);
  strcpy(cell->color, color);
}

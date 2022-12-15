#include <stdio.h>
#include <stdlib.h>

#ifndef GRID
#define GRID

#include "cell.h"

typedef struct Grid {
  int width;
  int height;
  Cell **fields;
} Grid;

void createGrid(Grid * grid, Cell** fields, int width, int height);

#endif // !Grid

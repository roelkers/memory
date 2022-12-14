#ifndef GRID
#define GRID

#include "cell.h"

typedef struct Grid {
  int width;
  int height;
  Cell **fields;
} Grid;

Grid * createGrid(int width, int height);

#endif // !Grid

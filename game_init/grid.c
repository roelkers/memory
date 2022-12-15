#include "grid.h"

void createGrid(Grid * grid, Cell** fields, int width, int height) {
  grid = (Grid *) malloc(sizeof(Grid));
  allocCells(grid->fields, grid->width, grid->height);
  for (size_t i = 0; i < width; i++) {
     for (size_t j = 0; j < height; j++) {
       createCell(&fields[i][j], "red");
     }
   } 
}

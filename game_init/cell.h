#ifndef CELL
#define CELL

typedef struct Cell {
  char * color;
} Cell;

void allocCells(Cell ** cell, int length, int width);

void allocCell(Cell * cell);

void createCell(Cell * cell, char* color);

#endif 

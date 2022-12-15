#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "enemy.h"
#include "cell.h"
#include "grid.h"

enum { 
  width = 10,
  height = 10
};

int main() {
  Cell **fields; 

  Grid * grid;
  createGrid(grid, fields, width, height);

}

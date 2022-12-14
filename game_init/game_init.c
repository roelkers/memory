#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "enemy.h"
#include "cell.h"
#include "grid.h"

enum { 
  width = 10,
  length = 10
};

int main() {
  Cell **fields = malloc(length * sizeof(Cell*)); 

  for (size_t i = 0; i < length; i++) {
     fields[i] = malloc(width* sizeof(Cell)); 
     for (size_t j = 0; j < width; j++) {
        createCell(&fields[i][j], "color"); 
     }
   } 

}

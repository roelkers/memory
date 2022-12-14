#ifndef GAME
#define GAME

#include "grid.h"
#include "cell.h"
#include "enemy.h"

typedef struct Game {
  Grid * grid; 
  Enemy * enemies;
} Game;

Game * createGame(Grid* grid, Enemy * enemies);

#endif

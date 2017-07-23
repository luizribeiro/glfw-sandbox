#ifndef __TETRIS_H
#define __TETRIS_H

#include "Game.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

class Tetris : public Game {
  public:
    void init();
    void render();
    void step();
  private:
    int board[BOARD_WIDTH][BOARD_HEIGHT];
};

#endif

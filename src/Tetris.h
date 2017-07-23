#ifndef __TETRIS_H
#define __TETRIS_H

#include "Game.h"

class Tetris : public Game {
  public:
    void init();
    void render();
    void step();
};

#endif

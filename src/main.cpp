#include "Engine.h"
#include "Tetris.h"

int main() {
  Engine engine;
  Game *game = new Tetris();

  if (!engine.init(960, 540, game)) {
    return -1;
  }

  engine.run();

  return 0;
}

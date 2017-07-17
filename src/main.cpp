#include "Engine.h"

int main() {
  Engine engine;

  if (!engine.init(960, 540)) {
    return -1;
  }

  engine.run();

  return 0;
}

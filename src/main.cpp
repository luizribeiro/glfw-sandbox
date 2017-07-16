#include "Engine.h"

int main() {
  Engine engine;

  if (!engine.init(640, 480)) {
    return -1;
  }

  engine.run();

  return 0;
}

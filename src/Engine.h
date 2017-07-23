#ifndef __ENGINE_H
#define __ENGINE_H

#include "Input.h"

class GLFWwindow;
class Game;

class Engine {
  public:
    bool init(int width, int height, Game *game);
    void run();
    Input getInput();
  private:
    GLFWwindow* window;
    Input input;
    Game* game;
};

#endif

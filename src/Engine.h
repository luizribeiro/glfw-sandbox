#ifndef __ENGINE_H
#define __ENGINE_H

#include "Input.h"

#include <GLFW/glfw3.h>

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

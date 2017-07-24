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
    double getTime();
    int getScreenWidth();
    int getScreenHeight();
  private:
    GLFWwindow* window;
    Input input;
    Game* game;
    int screenWidth;
    int screenHeight;
};

#endif

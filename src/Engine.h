#ifndef __ENGINE_H
#define __ENGINE_H

#include "Input.h"

#include <GLFW/glfw3.h>

class Engine {
  public:
    bool init(int width, int height);
    void run();
  private:
    GLFWwindow* window;
    Input input;

    void draw();
};

#endif

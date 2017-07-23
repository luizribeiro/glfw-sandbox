#ifndef __ENGINE_H
#define __ENGINE_H

#include <GLFW/glfw3.h>

class Engine {
  public:
    bool init(int width, int height);
    void run();
  private:
    GLFWwindow* window;

    void draw();
};

#endif

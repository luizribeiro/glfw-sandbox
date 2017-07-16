#include "Engine.h"

bool Engine::init(int width, int height) {
  if (!glfwInit()) {
    return false;
  }

  this->window = glfwCreateWindow(
    width,
    height,
    "grotto",
    NULL,
    NULL
  );
  if (!this->window) {
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(this->window);
  return true;
}

void Engine::run() {
  while (!glfwWindowShouldClose(this->window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    this->draw();
    glfwSwapBuffers(this->window);
    glfwPollEvents();
  }

  glfwTerminate();
}

void Engine::draw() {
  glBegin(GL_TRIANGLES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0, 0, 0);
  glVertex3f(0.5, 0, 0);
  glVertex3f(0, 0.5, 0);
  glEnd();
}

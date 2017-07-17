#include "Engine.h"

static void handle_keyboard(
  GLFWwindow* window,
  int key,
  int scancode,
  int action,
  int mods
) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

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
  glfwSetKeyCallback(this->window, handle_keyboard);
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

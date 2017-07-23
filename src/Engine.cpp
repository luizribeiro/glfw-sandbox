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

  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, height, 0, 0, 1);

  return true;
}

void Engine::run() {
  while (!glfwWindowShouldClose(this->window)) {
    this->draw();
    glfwSwapBuffers(this->window);
    glfwPollEvents();
  }

  glfwTerminate();
}

void Engine::draw() {
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  int axesCount;
  const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

  glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f((1 + axes[0]) * 480 - 50, (1 + axes[1]) * 270 - 50);
    glVertex2f((1 + axes[0]) * 480 + 50, (1 + axes[1]) * 270 - 50);
    glVertex2f((1 + axes[0]) * 480 + 50, (1 + axes[1]) * 270 + 50);
    glVertex2f((1 + axes[0]) * 480 - 50, (1 + axes[1]) * 270 + 50);
  glEnd();
}

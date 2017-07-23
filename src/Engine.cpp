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

  this->input.init(GLFW_JOYSTICK_1);

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
    this->input.poll();
  }

  glfwTerminate();
}

void Engine::draw() {
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  Vec2f stick = this->input.getStick(STK_LEFT);
  glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f((1 + stick.x) * 480 - 50, (1 + stick.y) * 270 - 50);
    glVertex2f((1 + stick.x) * 480 + 50, (1 + stick.y) * 270 - 50);
    glVertex2f((1 + stick.x) * 480 + 50, (1 + stick.y) * 270 + 50);
    glVertex2f((1 + stick.x) * 480 - 50, (1 + stick.y) * 270 + 50);
  glEnd();
}

#include "Engine.h"
#include "Game.h"

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

bool Engine::init(int width, int height, Game *game) {
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
  this->game = game;
  this->game->setEngine(this);
  this->game->init();

  glViewport(0, 0, (GLsizei)width, (GLsizei)height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, height, 0, 0, 1);

  return true;
}

void Engine::run() {
  while (!glfwWindowShouldClose(this->window)) {
    this->game->render();
    glfwSwapBuffers(this->window);
    glfwPollEvents();
    this->input.read();
    this->game->step();
  }

  glfwTerminate();
}

Input Engine::getInput() {
  return this->input;
}

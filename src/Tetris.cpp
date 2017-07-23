#include "Engine.h"
#include "Input.h"
#include "OpenGL.h"
#include "Tetris.h"

void Tetris::init() {
  glClearColor(.26, .42f, .69f, 1.0f);
}

void Tetris::render() {
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  Vec2f stick = this->engine->getInput().getStick(STK_LEFT);
  glBegin(GL_QUADS);
    glColor3f(.9f, .53f, .58f);
    glVertex2f((1 + stick.x) * 480 - 50, (1 + stick.y) * 270 - 50);
    glVertex2f((1 + stick.x) * 480 + 50, (1 + stick.y) * 270 - 50);
    glVertex2f((1 + stick.x) * 480 + 50, (1 + stick.y) * 270 + 50);
    glVertex2f((1 + stick.x) * 480 - 50, (1 + stick.y) * 270 + 50);
  glEnd();
}

void Tetris::step() {
}

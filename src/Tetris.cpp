#include "Engine.h"
#include "Input.h"
#include "OpenGL.h"
#include "Tetris.h"

enum BoardCell {
  BOARD_NONE,
  BOARD_RED,
  BOARD_ORANGE,
  BOARD_YELLOW,
  BOARD_GREEN,
  BOARD_CYAN,
  BOARD_BLUE,
  BOARD_PURPLE
};

#define CELL_WIDTH 20
#define BORDER_WIDTH 2

void Tetris::init() {
  glClearColor(.26, .42f, .69f, 1.0f);

  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      board[i][j] = BOARD_NONE;
    }
  }
}

void setColor(int cell) {
  switch (cell) {
    case BOARD_NONE:
      glColor3f(.18f, .40f, .67f);
      return;
    case BOARD_RED:
      glColor3f(.9f, .53f, .58f);
      return;
    case BOARD_PURPLE:
      glColor3f(.54f, .63f, .83f);
      return;
    case BOARD_YELLOW:
      glColor3f(.98f, .79f, .35f);
      return;
    case BOARD_GREEN:
      glColor3f(.67f, .80f, .42f);
      return;
    case BOARD_ORANGE:
      glColor3f(.93f, .66f, .42f);
      return;
    case BOARD_BLUE:
      glColor3f(.18f, .73f, .91f);
      return;
    case BOARD_CYAN:
      glColor3f(.09f, .72f, .75f);
      return;
  }
}

void Tetris::render() {
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      glBegin(GL_QUADS);
        setColor(board[i][j]);
        glVertex2f(
            i * (CELL_WIDTH + BORDER_WIDTH),
            j * (CELL_WIDTH + BORDER_WIDTH)
        );
        glVertex2f(
            i * (CELL_WIDTH + BORDER_WIDTH) + CELL_WIDTH,
            j * (CELL_WIDTH + BORDER_WIDTH)
        );
        glVertex2f(
            i * (CELL_WIDTH + BORDER_WIDTH) + CELL_WIDTH,
            j * (CELL_WIDTH + BORDER_WIDTH) + CELL_WIDTH
        );
        glVertex2f(
            i * (CELL_WIDTH + BORDER_WIDTH),
            j * (CELL_WIDTH + BORDER_WIDTH) + CELL_WIDTH
        );
      glEnd();
    }
  }
}

void Tetris::step() {
}

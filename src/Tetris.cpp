#include "Engine.h"
#include "Input.h"
#include "OpenGL.h"
#include "Tetris.h"

#include <cstdlib>
#include <vector>

#define CELL_WIDTH 20
#define BORDER_WIDTH 2
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

static int board[BOARD_WIDTH][BOARD_HEIGHT];
static std::vector<std::vector<int>> currentPiece;
static int pieceX, pieceY;
static bool isGameOver;

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

static std::vector<std::vector<std::vector<int>>> pieces = {
  {
    {1, 1, 0},
    {0, 1, 1}
  },
  {
    {2, 2, 2},
    {2, 0, 0}
  },
  {
    {3, 3},
    {3, 3}
  },
  {
    {0, 4, 4},
    {4, 4, 0}
  },
  {
    {5, 5, 5, 5}
  },
  {
    {6, 6, 6},
    {0, 0, 6}
  },
  {
    {7, 7, 7},
    {0, 7, 0}
  }
};

static void setCurrentPiece() {
  int type = rand() % 7;
  pieceX = 4;
  pieceY = 0;

  currentPiece.clear();
  for (int i = 0; i < pieces[type].size(); i++) {
    currentPiece.push_back(std::vector<int>());
    for (int j = 0; j < pieces[type][i].size(); j++) {
      currentPiece[i].push_back(pieces[type][i][j]);
    }
  }
}

void Tetris::init() {
  glClearColor(.26, .42f, .69f, 1.0f);

  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      board[i][j] = BOARD_NONE;
    }
  }

  setCurrentPiece();
  isGameOver = false;
}

static void setColor(int cell) {
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

static int getCell(int x, int y) {
  int pieceH = currentPiece[0].size();
  int pieceW = currentPiece.size();
  if (pieceX <= x && x < pieceX + pieceW &&
      pieceY <= y && y < pieceY + pieceH && !isGameOver) {
    int currentPieceCell = currentPiece[x - pieceX][y - pieceY];
    if (currentPieceCell != BOARD_NONE) {
      return currentPieceCell;
    }
  }
  return board[x][y];
}

void Tetris::render() {
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      int cell = getCell(i, j);
      glBegin(GL_QUADS);
        setColor(cell);
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

static int lastTick = 0;

static bool collides() {
  int pieceW = currentPiece.size();
  int pieceH = currentPiece[0].size();
  if (pieceX < 0 || pieceX + pieceW > BOARD_WIDTH ||
      pieceY < 0 || pieceY + pieceH > BOARD_HEIGHT) {
    return true;
  }
  for (int i = 0; i < pieceW; i++) {
    for (int j = 0; j < pieceH; j++) {
      if (currentPiece[i][j] != BOARD_NONE &&
          board[pieceX + i][pieceY + j] != BOARD_NONE) {
        return true;
      }
    }
  }
  return false;
}

static void transfer() {
  int pieceW = currentPiece.size();
  int pieceH = currentPiece[0].size();
  for (int i = 0; i < pieceW; i++) {
    for (int j = 0; j < pieceH; j++) {
      if (currentPiece[i][j] == BOARD_NONE) {
        continue;
      }
      board[pieceX + i][pieceY + j] = currentPiece[i][j];
    }
  }
}

void Tetris::step() {
  if (isGameOver) {
    return;
  }


  int mTime = (int)(this->engine->getTime() * 1000);
  int dX = 0, dY = 0;
  bool isTicking = false;
  if (mTime >= lastTick + 800) {
    lastTick = mTime;
    dY = +1;
    isTicking = true;
  } else {
    Input input = this->engine->getInput();
    if (input.isPressing(BTN_RIGHT)) dX = +1;
    else if (input.isPressing(BTN_LEFT)) dX = -1;
    if (input.isPressing(BTN_DOWN)) dY = +1;
  }
  pieceX += dX;
  pieceY += dY;

  if (!collides()) {
    return;
  }

  pieceX -= dX;
  pieceY -= dY;

  if (!isTicking) {
    return;
  }

  transfer();
  setCurrentPiece();
  if (collides()) {
    isGameOver = true;
  }
}

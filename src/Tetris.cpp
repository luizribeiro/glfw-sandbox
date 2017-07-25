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

#define BTN_REPEAT_MS 250

enum class BoardCell {
  NONE,
  RED,
  ORANGE,
  YELLOW,
  GREEN,
  CYAN,
  BLUE,
  PURPLE
};

static std::vector<std::vector<BoardCell>> board;
static std::vector<std::vector<BoardCell>> currentPiece;
static int pieceX, pieceY;
static bool isGameOver;

static std::vector<std::vector<std::vector<BoardCell>>> pieces = {
  {
    {BoardCell::RED,  BoardCell::RED, BoardCell::NONE},
    {BoardCell::NONE, BoardCell::RED, BoardCell::RED }
  },
  {
    {BoardCell::ORANGE, BoardCell::ORANGE, BoardCell::ORANGE},
    {BoardCell::ORANGE, BoardCell::NONE,   BoardCell::NONE  }
  },
  {
    {BoardCell::YELLOW, BoardCell::YELLOW},
    {BoardCell::YELLOW, BoardCell::YELLOW}
  },
  {
    {BoardCell::NONE,  BoardCell::GREEN, BoardCell::GREEN},
    {BoardCell::GREEN, BoardCell::GREEN, BoardCell::NONE }
  },
  {
    {BoardCell::CYAN, BoardCell::CYAN, BoardCell::CYAN, BoardCell::CYAN}
  },
  {
    {BoardCell::BLUE, BoardCell::BLUE, BoardCell::BLUE},
    {BoardCell::NONE, BoardCell::NONE, BoardCell::BLUE}
  },
  {
    {BoardCell::PURPLE, BoardCell::PURPLE, BoardCell::PURPLE},
    {BoardCell::NONE,   BoardCell::PURPLE, BoardCell::NONE}
  }
};

static void setCurrentPiece() {
  int type = rand() % 7;
  pieceX = 4;
  pieceY = 0;
  currentPiece = pieces[type];
}

static void rotate() {
  std::vector<std::vector<BoardCell>> newPiece;
  int pieceH = currentPiece[0].size();
  int pieceW = currentPiece.size();
  for (int i = 0; i < pieceH; i++) {
    newPiece.push_back(std::vector<BoardCell>());
    for (int j = 0; j < pieceW; j++) {
      newPiece[i].push_back(currentPiece[pieceW-j-1][i]);
    }
  }
  currentPiece = newPiece;
  pieceX -= (pieceH - pieceW) / 2;
  pieceY += (pieceH - pieceW) / 2;
}

void Tetris::init() {
  glClearColor(.26, .42f, .69f, 1.0f);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  board = std::vector<std::vector<BoardCell>>(
    BOARD_HEIGHT,
    std::vector<BoardCell>(BOARD_WIDTH, BoardCell::NONE)
  );

  srand(this->engine->getTime());
  setCurrentPiece();
  isGameOver = false;
}

static void setColor(BoardCell cell) {
  switch (cell) {
    case BoardCell::NONE:
      glColor3f(.18f, .40f, .67f);
      return;
    case BoardCell::RED:
      glColor3f(.9f, .53f, .58f);
      return;
    case BoardCell::PURPLE:
      glColor3f(.54f, .63f, .83f);
      return;
    case BoardCell::YELLOW:
      glColor3f(.98f, .79f, .35f);
      return;
    case BoardCell::GREEN:
      glColor3f(.67f, .80f, .42f);
      return;
    case BoardCell::ORANGE:
      glColor3f(.93f, .66f, .42f);
      return;
    case BoardCell::BLUE:
      glColor3f(.18f, .73f, .91f);
      return;
    case BoardCell::CYAN:
      glColor3f(.09f, .72f, .75f);
      return;
  }
}

static BoardCell getCell(int x, int y) {
  int pieceH = currentPiece[0].size();
  int pieceW = currentPiece.size();
  if (pieceX <= x && x < pieceX + pieceW &&
      pieceY <= y && y < pieceY + pieceH && !isGameOver) {
    BoardCell currentPieceCell = currentPiece[x - pieceX][y - pieceY];
    if (currentPieceCell != BoardCell::NONE) {
      return currentPieceCell;
    }
  }
  return board[y][x];
}

void Tetris::render() {
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(
    (this->engine->getScreenWidth() -
      (CELL_WIDTH + BORDER_WIDTH) * BOARD_WIDTH - BORDER_WIDTH) / 2.0f,
    (this->engine->getScreenHeight() -
      (CELL_WIDTH + BORDER_WIDTH) * BOARD_HEIGHT - BORDER_WIDTH) / 2.0f,
    .0f
  );

  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      BoardCell cell = getCell(i, j);
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

  if (isGameOver) {
    glLoadIdentity();
    glBegin(GL_QUADS);
      glColor4f(.0f, .0f, .0f, .5f);
      glVertex2f(.0f, .0f);
      glVertex2f(this->engine->getScreenWidth(), .0f);
      glVertex2f(
        this->engine->getScreenWidth(),
        this->engine->getScreenHeight()
      );
      glVertex2f(.0f, this->engine->getScreenHeight());
    glEnd();
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
      if (currentPiece[i][j] != BoardCell::NONE &&
          board[pieceY + j][pieceX + i] != BoardCell::NONE) {
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
      if (currentPiece[i][j] == BoardCell::NONE) {
        continue;
      }
      board[pieceY + j][pieceX + i] = currentPiece[i][j];
    }
  }

  currentPiece.clear();
}

static int pressedAt[(int)InputButton::NUM_BUTTONS];
static bool isPressed(Input input, int mTime, InputButton btn) {
  if (!input.isPressing(btn)) {
    pressedAt[(int)btn] = 0;
    return false;
  }

  if (pressedAt[(int)btn] == 0) {
    pressedAt[(int)btn] = mTime;
    return true;
  }

  return pressedAt[(int)btn] + BTN_REPEAT_MS <= mTime;
}

static bool cleanRows() {
  bool didClean = false;

  for (int i = 0; i < BOARD_HEIGHT; i++) {
    bool isFull = true;
    for (int j = 0; j < BOARD_WIDTH; j++) {
      if (board[i][j] == BoardCell::NONE) {
        isFull = false;
        continue;
      }
    }

    if (isFull) {
      didClean = true;
      board.erase(board.begin() + i);
      board.insert(board.begin(), std::vector<BoardCell>(BOARD_WIDTH));
    }
  }
  return false;
}

void Tetris::step() {
  Input input = this->engine->getInput();
  int mTime = (int)(this->engine->getTime() * 1000);

  if (isGameOver) {
    if (isPressed(input, mTime, InputButton::TRI)) {
      this->init();
    }
    return;
  }

  int dX = 0, dY = 0, dR = 0;
  if (mTime >= lastTick + 500) {
    lastTick = mTime;
    if (cleanRows()) {
    } else if (currentPiece.empty()) {
      setCurrentPiece();
      if (collides()) {
        isGameOver = true;
      }
      return;
    } else {
      dY = +1;
    }
  } else {
    if (isPressed(input, mTime, InputButton::X)) dR = +1;
    else if (isPressed(input, mTime, InputButton::DOWN)) dY = +1;
    else if (isPressed(input, mTime, InputButton::RIGHT)) dX = +1;
    else if (isPressed(input, mTime, InputButton::LEFT)) dX = -1;
  }

  pieceX += dX;
  pieceY += dY;
  if (dR == 1) {
    rotate();
    int pX = pieceX;
    for (int i = 0; i <= 2; i++) {
      pieceX = pX + i;
      if (!collides()) break;
      pieceX = pX - i;
      if (!collides()) break;
    }
  }

  if (!collides()) {
    return;
  }

  pieceX -= dX;
  pieceY -= dY;
  if (dR == 1) {
    // undo rotation... poorly
    for (int i = 0; i < 3; i++) rotate();
  }

  if (dY == +1) {
    transfer();
  }
}

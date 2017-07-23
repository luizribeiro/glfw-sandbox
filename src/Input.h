#ifndef __INPUT_H
#define __INPUT_H

#include "Common.h"

enum InputButton {
  BTN_UP,
  BTN_RIGHT,
  BTN_DOWN,
  BTN_LEFT,
  BTN_X,
  BTN_O,
  BTN_SQR,
  BTN_TRI,
  NUM_BUTTONS
};

enum InputStick {
  STK_LEFT,
  STK_RIGHT,
  NUM_STICKS
};

class Input {
  public:
    void init(int joystick);
    void poll();
    bool isPressing(InputButton button);
    Vec2f getStick(InputStick stick);

  private:
    int joystick;
    bool buttons[NUM_BUTTONS];
    Vec2f sticks[NUM_STICKS];
};

#endif

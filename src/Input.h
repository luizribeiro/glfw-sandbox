#ifndef __INPUT_H
#define __INPUT_H

#include "Common.h"

enum class InputButton {
  UP,
  RIGHT,
  DOWN,
  LEFT,
  X,
  O,
  SQR,
  TRI,
  NUM_BUTTONS
};

enum class InputStick {
  LEFT,
  RIGHT,
  NUM_STICKS
};

class Input {
  public:
    void init(int joystick);
    void read();
    bool isPressing(InputButton button);
    Vec2f getStick(InputStick stick);

  private:
    int joystick;
    bool buttons[(int)InputButton::NUM_BUTTONS];
    Vec2f sticks[(int)InputStick::NUM_STICKS];
};

#endif

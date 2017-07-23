#ifndef __INPUT_H
#define __INPUT_H

#include <utility>

enum InputButton {
  BTN_UP,
  BTN_RIGHT,
  BTN_DOWN,
  BTN_LEFT,
  NUM_BUTTONS
};

enum InputStick {
  STK_LEFT,
  STK_RIGHT,
  NUM_STICKS
};

using InputAxis = std::pair<float, float>;

class Input {
  public:
    void init(int joystick);
    void poll();
    bool isPressing(InputButton button);
    InputAxis getStick(InputStick stick);

  private:
    int joystick;
    bool buttons[NUM_BUTTONS];
    InputAxis sticks[NUM_STICKS];
};

#endif

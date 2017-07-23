#include "Input.h"

#include <map>

#include <GLFW/glfw3.h>

int inputButtonToGlfwButton[NUM_BUTTONS] = {
  12, // BTN_UP
  15, // BTN_RIGHT
  13, // BTN_DOWN
  14 // BTN_LEFT
};

void Input::init(int joystick) {
  this->joystick = joystick;

  for (int i = 0; i < NUM_BUTTONS; i++) {
    this->buttons[i] = false;
  }
}

void Input::poll() {
  int numButtons;
  const unsigned char *buttons = glfwGetJoystickButtons(
    this->joystick,
    &numButtons
  );

  for (int i = 0; i < NUM_BUTTONS; i++) {
    this->buttons[i] = !!buttons[inputButtonToGlfwButton[i]];
  }

  int axesCount;
  const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
  this->sticks[STK_LEFT] = std::make_pair(axes[0], axes[1]);
  this->sticks[STK_RIGHT] = std::make_pair(axes[2], axes[3]);
}

bool Input::isPressing(InputButton button) {
  return this->buttons[button];
}

InputAxis Input::getStick(InputStick stick) {
  return this->sticks[stick];
}

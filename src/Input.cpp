#include "Input.h"

#include <map>

#include <GLFW/glfw3.h>

int inputButtonToGlfwButton[NUM_BUTTONS] = {
  /*BTN_UP   */ 14,
  /*BTN_RIGHT*/ 15,
  /*BTN_DOWN */ 16,
  /*BTN_LEFT */ 17,
  /*BTN_X    */ 1,
  /*BTN_O    */ 2,
  /*BTN_SQR  */ 0,
  /*BTN_TRI  */ 3
};

void Input::init(int joystick) {
  this->joystick = joystick;

  for (int i = 0; i < NUM_BUTTONS; i++) {
    this->buttons[i] = false;
  }
}

void Input::read() {
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
  this->sticks[STK_LEFT] = Vec2f(axes[0], axes[1]);
  this->sticks[STK_RIGHT] = Vec2f(axes[2], axes[3]);
}

bool Input::isPressing(InputButton button) {
  return this->buttons[button];
}

Vec2f Input::getStick(InputStick stick) {
  return this->sticks[stick];
}

#include "Input.h"

#include <map>

#include <GLFW/glfw3.h>

int inputButtonToGlfwButton[(int)InputButton::NUM_BUTTONS] = {
  /*UP   */ 14,
  /*RIGHT*/ 15,
  /*DOWN */ 16,
  /*LEFT */ 17,
  /*X    */ 1,
  /*O    */ 2,
  /*SQR  */ 0,
  /*TRI  */ 3
};

void Input::init(int joystick) {
  this->joystick = joystick;

  for (int i = 0; i < (int)InputButton::NUM_BUTTONS; i++) {
    this->buttons[i] = false;
  }
}

void Input::read() {
  int numButtons;
  const unsigned char *buttons = glfwGetJoystickButtons(
    this->joystick,
    &numButtons
  );

  for (int i = 0; i < (int)InputButton::NUM_BUTTONS; i++) {
    this->buttons[i] = !!buttons[inputButtonToGlfwButton[i]];
  }

  int axesCount;
  const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
  this->sticks[(int)InputStick::LEFT] = Vec2f(axes[0], axes[1]);
  this->sticks[(int)InputStick::RIGHT] = Vec2f(axes[2], axes[3]);
}

bool Input::isPressing(InputButton button) {
  return this->buttons[(int)button];
}

Vec2f Input::getStick(InputStick stick) {
  return this->sticks[(int)stick];
}

#ifndef INPUTREGISTRY_H
#define INPUTREGISTRY_H
#include <Arduino.h>

enum InputID
{
  F_IN,
  B_IN,
  L_IN,
  R_IN,
  M_IN,
  DEL_IN,
  MENU_IN,

  INPUT_COUNT
};

struct inputState
{
  int pin;
  bool pressed;
  bool wasPressed;
  bool isHeld;
  bool lastState;
  unsigned long startPressTime;
};

const unsigned long HOLD_TIME = 500;

inputState inputs[INPUT_COUNT] = //array of structs, each button gets a struct created
{
  {3},   // F
  {4},   // B
  {5},   // L
  {6},   // R
  {7},   // M
  {12},  // DEL
  {2}    // MENU
};

void setupInputs()
{
  for(int i = 0; i < INPUT_COUNT; i++)
    pinMode(inputs[i].pin, INPUT_PULLUP);
}

void updateInputs()
{
  for(int i = 0; i < INPUT_COUNT; i++)
  {
    bool currentState = digitalRead(inputs[i].pin);

    inputs[i].wasPressed = false;
    inputs[i].isHeld = false;

    if(inputs[i].lastState == HIGH && currentState == LOW)
    {
      inputs[i].wasPressed = true;
      inputs[i].startPressTime = millis();
    }

    if(currentState == LOW)
    {
      inputs[i].pressed = true;
      if(millis() - inputs[i].startPressTime >= HOLD_TIME)
        inputs[i].isHeld = true;
    }
    else
      inputs[i].pressed = false;

    inputs[i].lastState = currentState;
  }
}
#endif
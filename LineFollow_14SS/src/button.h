#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

const int c_i_PIN_BUTTONS[3] = { 38, 37, 36 };

void InitButton();
bool GetButton(int rb_i_keyNum);

#endif

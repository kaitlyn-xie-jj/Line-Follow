#ifndef _FREYSCALSENSOR_h
#define _FREYSCALSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <EEPROM.h>

const int c_i_PIN_GREYSCALE[14] = { 1, 2, 3, 4, 5, 6, 20, 19, 18, 17, 16, 15, 14, 13 };

const int c_i_SENSORCAL_GOTIME = 350;
const int c_i_SENSORCAL_GOSPD = 160;

const int c_i_ANALOGREAD_RESOLUTION = 6;
const int c_i_EEPROM_SIZE = 28;

void InitGreyscale();
int GetGreyscaleraw(int ggr_i_channle);
int GetGreyscalevalue(int ggv_i_channle);
void GreycaleCalibration();

#endif

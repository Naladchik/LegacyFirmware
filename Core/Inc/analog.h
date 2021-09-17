
#ifndef __ANALOG_H
#define __ANALOG_H

#include "stm32f1xx_hal.h"
#include "basic.h"
#include "config.h"

typedef struct VoltStruct{
	float PressLeft;
  float PressRight;
  float PSUVolt;
  float BatVolt;
	//uint8_t LEDvalueL;
	//uint8_t LEDvalueR;
	uint8_t new_data;
} TypeVolt;

void measure_volt(TypeVolt* Volt);
#endif

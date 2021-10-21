
#ifndef __LOGIC_H
#define __LOGIC_H

#include "stm32f1xx_hal.h"
#include "basic.h"
#include "config.h"
#include "analog.h"

//Alarms
typedef struct AlarmStruct{
  uint8_t LineMin:1;
  uint8_t LineMax:1;
  uint8_t ConcentratorNOT_OK:1;
  uint8_t ConcentratorMax:1;
  uint8_t CylindersEmpty:1;
  uint8_t PowerOff:1;
  uint8_t BatteryOut:1;
	uint8_t EmergState:1; //system is in emergency state
} TypeAlarm;

void make_action(const TypeVolt* Volt);
#endif

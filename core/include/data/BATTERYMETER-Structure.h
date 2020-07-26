#ifndef _ESP_BATTERYMETER_Structure_h
#define _ESP_BATTERYMETER_Structure_h

#include <Configuration.h>
#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER

#include "arduino.h"

struct BATTERY_DATA {
  double voltage;
  float percentage;
};

struct BATTERY_VOLTAGE {
  double max;
  double min;
};

struct BATTERYMETER {
  uint8_t adcInput;
  uint32_t interval;
  BATTERY_VOLTAGE voltage;
};

#endif // ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
#endif // _ESP_BATTERYMETER_Structure_h

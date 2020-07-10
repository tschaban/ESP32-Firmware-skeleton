#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY

#ifndef _ESP_SENSOR_BINARY_Structure_h
#define _ESP_SENSOR_BINARY_Structure_h

#include "arduino.h"

struct BINARY_SENSOR {
  uint8_t gpio;
  uint16_t bouncing;
  uint16_t interval;
};

#endif // _ESP_SENSOR_BINARY_Structure_h
#endif // ESP_CONFIG_HARDWARE_SENSOR_BINARY
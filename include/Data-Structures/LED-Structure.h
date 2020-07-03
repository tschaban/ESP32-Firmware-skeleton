#ifndef _ESP_LED_Structure_h
#define _ESP_LED_Structure_h

#include <Configuration.h>
#ifdef ESP_CONFIG_HARDWARE_LED

#include "arduino.h"

struct LED {
  uint8_t gpio = 2;
  boolean reverseState = false;
};

#endif // ESP_CONFIG_HARDWARE_LED
#endif // _ESP_LED_Structure_h
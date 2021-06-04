/* AFE Firmware for smart home devices, Website: https://afe.smartnydom.pl/ */

#ifndef _ESP_SWITCH_Structure_h
#define _ESP_SWITCH_Structure_h

#include <Configuration.h>
#ifdef ESP_CONFIG_HARDWARE_SWITCH

#include "arduino.h"

struct SWITCH {
  uint8_t gpio;
  uint8_t type;
  uint16_t bouncing;
  uint8_t functionality;
  uint8_t pinMode;
  boolean reverseState = false;
};

#endif // ESP_CONFIG_HARDWARE_SWITCH
#endif // _ESP_SWITCH_Structure_h

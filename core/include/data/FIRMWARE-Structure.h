/* AFE Firmware for smart home devices, Website: https://afe.smartnydom.pl/ */

#ifndef _ESP_FIRMWARE_Structure_h
#define _ESP_FIRMWARE_Structure_h

#include "arduino.h"

struct FIRMWARE {
  char version[10];
  uint8_t type;
  uint8_t api;
  uint8_t autoUpgrade;
  char upgradeURL[120];
};

#endif

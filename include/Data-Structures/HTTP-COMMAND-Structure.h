/* AFE Firmware for smart home devices, Website: https://afe.smartnydom.pl/ */

#ifndef _ESP_HTTP_COMMAND_Structure_h
#define _ESP_HTTP_COMMAND_Structure_h

#include "arduino.h"

struct HTTPCOMMAND {
  char device[16];
  char name[16];
  char command[32];
  char source[9];
};

#endif

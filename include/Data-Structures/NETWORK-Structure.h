#ifndef _ESP_NETWORK_Structure_h
#define _ESP_NETWORK_Structure_h

#include "arduino.h"

struct NETWORK {
  char ssid[33];
  char password[33];
  boolean isDHCP;
  char ip[16];
  char gateway[16];
  char subnet[16];
  uint8_t noConnectionAttempts;
  uint8_t waitTimeConnections;
  uint8_t waitTimeSeries;
};

#endif

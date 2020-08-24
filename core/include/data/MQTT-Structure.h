/* ESP Firmware for smart home devices, Website: https://ESP.smartnydom.pl/ */

#ifndef _ESP_MQTT_Structure_h
#define _ESP_MQTT_Structure_h

#include <Configuration.h>

#ifdef ESP_CONFIG_API_MQTT

#include "arduino.h"

struct MQTT_MESSAGE {
  char *topic;
  byte *content;
  uint16_t length;
};


struct MQTT_BASIC_CONFIG {
  char topic[65];
};


struct MQTT_BROKER {
  char host[65];
  char ip[16];
  uint16_t port;
  char user[65];
  char password[65];
  MQTT_BASIC_CONFIG lwt;
  uint16_t timeout;
  uint8_t qos;
  boolean retain;
};

#endif // ESP_CONFIG_API_MQTT

#endif // _ESP_MQTT_Structure_h
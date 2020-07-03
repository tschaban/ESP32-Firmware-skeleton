#ifndef _ESP_WiFi_h
#define _ESP_WiFi_h

#include "arduino.h"

#include <Configuration.h>

#include <ESP-Data-Access.h>
#include <ESP-Device.h>

#ifdef ESP_CONFIG_HARDWARE_LED
#include <ESP-LED.h>
#endif

#include <Data-Structures.h>
#include <WiFi.h>

#ifdef DEBUG
#include <Streaming.h>
#endif

class ESPWiFi {

private:
  ESPDevice *Device;
  ESPDataAccess *Data;
  NETWORK configuration;
  unsigned long delayStartTime = 0;
  uint8_t WiFiMode;
// HTTPClient http;

#ifdef ESP_CONFIG_HARDWARE_LED
  unsigned long ledStartTime = 0;
#endif

  uint8_t connections = 0;
  unsigned long sleepStartTime = 0;
  boolean sleepMode = false; // It's set to true after defined in configuration
                             // X number of connection failures
#ifdef ESP_CONFIG_HARDWARE_LED
  ESPLED *Led;
#endif

  boolean eventConnectionEstablished = false;
  boolean disconnected = false;

  void initialize(ESPDevice *, ESPDataAccess *, uint8_t mode);

public:
  /* Constructor: no actions */
  ESPWiFi();

/* Sets connection parameters and host name. Must be invoked before connect
 * method */
#ifdef ESP_CONFIG_HARDWARE_LED
  void begin(ESPDevice *, ESPDataAccess *, ESPLED *, uint8_t mode);
#else
  void begin(ESPDevice *, ESPDataAccess *, uint8_t mode);
#endif

  /* Return TRUE if device is connected to WiFi Acces Point */
  boolean connected();

  /* Returns true if device just connected to the network. It's set to true each
   * time it connected. */
  boolean eventConnected();

  /* Method checks if device is connected to WiFi - if it's not then it connects
   * to it */
  void listener();

  // uint16_t getJSON(const String& url, String& response);
};

#endif

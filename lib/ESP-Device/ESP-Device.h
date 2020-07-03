/* AFE Firmware for smart home devices, Website: https://afe.smartnydom.pl/ */

#ifndef _ESP_Device_h
#define _ESP_Device_h

#include "arduino.h"

//#include <AFE-Defaults.h>
#include <ESP-Data-Access.h>
//include <FS.h>

#include <Configuration.h>
#include <Data-Structures.h>

#ifdef DEBUG
#include <Streaming.h>
#endif

class ESPDevice {

private:
  ESPDataAccess *Data;
  uint8_t deviceMode;

public:
  DEVICE configuration;

  ESPDevice();

  /* Method reads device configuration data. It used in config panel */
  void begin(ESPDataAccess *);

  /* Method reboots device to specyfic mode  define by MODE_.. */
  void reboot(uint8_t mode = ESP_MODE_NORMAL);

  /* Method returns current device mode */
  uint8_t getMode();

  /* Method saves current device mode to EEPROM */
  void saveMode(uint8_t mode);
};

#endif
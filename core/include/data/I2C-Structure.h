/* AFE Firmware for smart home devices, Website: https://afe.smartnydom.pl/ */

#ifndef _ESP_I2C_Structure_h
#define _ESP_I2C_Structure_h

#include "arduino.h"

#include <Configuration.h>
#ifdef ESP_CONFIG_HARDWARE_I2C


struct I2CBUS {
  uint8_t SDA;
  uint8_t SCL;
  uint32_t frequency;
};

#endif // ESP_CONFIG_HARDWARE_I2C
#endif // _ESP_I2C_Structure_h

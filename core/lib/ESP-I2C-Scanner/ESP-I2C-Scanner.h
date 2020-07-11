#ifndef _ESP_I2C_Scanner_h
#define _ESP_I2C_Scanner_h

#include "arduino.h"

#include <Configuration.h>
#ifdef ESP_CONFIG_HARDWARE_I2C

#include <Wire.h>

#ifdef DEBUG
#include <Streaming.h>
#endif

class ESPI2CScanner {

private:
  TwoWire *WirePort;

public:
  ESPI2CScanner();

  void begin(TwoWire *);

#ifdef DEBUG
  /* Method only call in the debug mode. It scans all adesses */
  void scanAll();
#endif

  /* Method scans for device presence for inpute address. Return true if a
   * device is found  */
  boolean scan(byte address);

  /* Method returns potential name of the device based. Based on default known
   * devices addresses */
  const char *getName(byte deviceAddress);
};

#endif // ESP_CONFIG_HARDWARE_I2C
#endif // _ESP_I2C_Scanner_h

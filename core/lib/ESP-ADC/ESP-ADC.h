#ifndef _ESP_ADC_h
#define _ESP_ADC_h

#include <Configuration.h>

#ifdef ESP_CONFIG_HARDWARE_ADC

#include "arduino.h"
#include <ESP-Data-Access.h>

#ifdef DEBUG
#include <Streaming.h>
#endif

#ifdef ESP_CONFIG_HARDWARE_ADS1115
#include <Adafruit_ADS1115.h>
#include <Wire.h>
#endif

class ESPADC {

private:
  boolean ready = false;
  unsigned long startTime = 0;
  boolean _initialized = false;
  uint8_t counterOfSamplings = 0;
  uint16_t temporaryAnalogData = 0;

  ESPDataAccess *Data;

#ifdef ESP_CONFIG_HARDWARE_ADS1115
  TwoWire *WirePort0;
  TwoWire *WirePort1;
  TwoWire *WirePort;
  Adafruit_ADS1115 ADS1115Input;
  boolean readFromGPIO = true;
  void begin(ESPDataAccess *_Data, uint8_t id);
#endif

public:
  ADC configuration;
  ADC_DATA data;

  /* Constructor */
  ESPADC();

/* Initialized analog input using configuration parameters */

#ifdef ESP_CONFIG_HARDWARE_ADS1115
  void begin(ESPDataAccess *_Data, TwoWire *_WirePort0, TwoWire *_WirePort1,
             uint8_t id);
#else
  void begin(ESPDataAccess *_Data, uint8_t id);
#endif
  /* Returns values from Analog Input */
  ADC_DATA get();

  /* Main method that takes care for analog reads based on config parameters.
   * Returns true if there is a new value available from analog input  */
  boolean listener();
};

#endif // ESP_CONFIG_HARDWARE_ADC
#endif // _ESP_ADC_h

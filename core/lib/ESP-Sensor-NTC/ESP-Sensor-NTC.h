#ifndef _ESP_Sensor_NTC_h
#define _ESP_Sensor_NTC_h

#include <Configuration.h>
#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC

#include <ESP-ADC.h>
#include <ESP-Data-Access.h>
#include <arduino.h>

#ifdef DEBUG
#include <Streaming.h>
#endif

class ESPNTCSensor {

private:
  ESPDataAccess *Data;
  ESPADC ADCInput;

  boolean ready = false;
  boolean _initialized = false;

#ifdef ESP_CONFIG_HARDWARE_ADS1115
  void begin(ESPDataAccess *_Data, uint8_t id);
#endif

public:
  /* Constructor: entry parameter is GPIO number where Sensor is connected to */
  ESPNTCSensor();

  NTC_SENSOR configuration;
  double temperature = 0;

#ifdef ESP_CONFIG_HARDWARE_ADS1115
  void begin(ESPDataAccess *_Data, TwoWire *_WirePort0, TwoWire *_WirePort1,
             uint8_t id);
#else
  void begin(ESPDataAccess *_Data, uint8_t id);
#endif

  boolean listener();
};

#endif // ESP_CONFIG_HARDWARE_SENSOR_NTC
#endif // _ESP_Sensor_NTC_h
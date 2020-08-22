#ifndef _ESP_Sensor_ACS758_h
#define _ESP_Sensor_ACS758_h

#include <Configuration.h>
#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758

#include <ESP-ADC.h>
#include <ESP-Data-Access.h>
#include <arduino.h>

#ifdef DEBUG
#include <Streaming.h>
#endif

class ESPACS758Sensor {

private:
  ESPDataAccess *Data;
  ESPADC ADCInput;

  boolean ready = false;
  boolean _initialized = false;

  uint8_t temperatureOffset = ESP_CONFIG_HARDWARE_SENSOR_ACS758_TEMP_25_OFFSET;

#ifdef ESP_CONFIG_HARDWARE_ADS1115
  void begin(ESPDataAccess *_Data, uint8_t id);
#endif

  const float VCC = 5;

  float cutOffLimit = 1; // reading cutt off current. 1.00 is 1 Amper

  float sensitivity[3][8] = {
      {0.041,  0.061, 0.0205,  0.041,  0.0135, 0.0274, 0.01013, 0.0203},
      {0.04,   0.06,  0.02,    0.04,   0.0133, 0.0266, 0.01,    0.02},
      {0.0394, 0.059, 0.01975, 0.0395, 0.0131, 0.0266, 0.00988, 0.0197}};
  
  float voltageOffset[8] = {0.5, 0.12, 0.5, 0.12, 0.5, 0.12, 0.5, 0.12};

  float QOV;
  float voltage;
  float cutOff;

public:
  /* Constructor: entry parameter is GPIO number where Sensor is connected to */
  ESPACS758Sensor();

  ACS758_SENSOR configuration;
  double current = 0;

#ifdef ESP_CONFIG_HARDWARE_ADS1115
  void begin(ESPDataAccess *_Data, TwoWire *_WirePort0, TwoWire *_WirePort1,
             uint8_t id);
#else
  void begin(ESPDataAccess *_Data, uint8_t id);
#endif

  boolean listener();
  void setTemperatureOffset(uint8_t);
};

#endif // ESP_CONFIG_HARDWARE_SENSOR_ACS758
#endif // _ESP_Sensor_ACS758_h
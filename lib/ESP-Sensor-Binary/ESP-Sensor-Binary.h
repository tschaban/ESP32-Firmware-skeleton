
#ifndef _ESP_Sensor_Binary_h
#define _ESP_Sensor_Binary_h

#include <Configuration.h>
#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY

#include "arduino.h"

#include <ESP-Data-Access.h>

#ifdef DEBUG
#include <Streaming.h>
#endif

class ESPSensorBinary {

public:
  BINARY_SENSOR configuration;

  /* Constructors */
  ESPSensorBinary();

  /* Init switch */
  void begin(uint8_t id);

  void get(uint32_t &noOfImpulses, uint32_t &duration);
  boolean listener(void);


private:
  uint8_t _id;
  uint32_t counterStarted = 0;

  uint32_t _previousDuration = 0; // Used in case of time rollout
  
};

#endif // _ESP_Sensor_Binary_h
#endif // ESP_CONFIG_HARDWARE_SENSOR_BINARY
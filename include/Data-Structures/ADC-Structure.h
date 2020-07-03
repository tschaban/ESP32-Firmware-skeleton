#ifndef _ESP_ADC_INPUT_Structure_h
#define _ESP_ADC_INPUT_Structure_h

#include <Configuration.h>
#ifdef ESP_CONFIG_HARDWARE_ADC

#include "arduino.h"

struct ADC_DATA {
  int32_t raw;
  float percent;
  double voltage;
  double voltageCalculated;
};

struct ADC_VOLTAGE_DIVIDER {
  uint32_t Ra;
  uint32_t Rb;
};

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
struct ADC_BATTERY_METER {
  float maxVoltage;
  float minVoltage;
};
#endif // ESP_CONFIG_FUNCTIONALITY_BATTERYMETER

#ifdef ESP_CONFIG_HARDWARE_ADS1115
struct ADC_I2C {
  uint8_t id;
  uint8_t inputId;
  uint8_t address;
};
#endif // ESP_CONFIG_HARDWARE_I2C

struct ADC {
  uint8_t gpio;
#ifdef ESP_CONFIG_HARDWARE_ADS1115
  ADC_I2C i2c;
#endif // ESP_CONFIG_HARDWARE_I2C
  uint32_t interval;
  uint16_t numberOfSamples;
  double maxVCC;
  uint16_t resolution;
  ADC_VOLTAGE_DIVIDER divider;
#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
  ADC_BATTERY_METER battery;
#endif // ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
};

#endif // ESP_CONFIG_HARDWARE_ADC
#endif // _ESP_ADC_INPUT_Structure_h

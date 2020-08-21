#ifndef _ESP_NTC_Structure_h
#define _ESP_NTC_Structure_h

#include <Configuration.h>
#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC

struct NTC_SENSOR_COEFFICIENTS_UNIT {
 float value;
 uint8_t precision;
};

struct NTC_SENSOR_COEFFICIENTS
{
  NTC_SENSOR_COEFFICIENTS_UNIT A;
  NTC_SENSOR_COEFFICIENTS_UNIT B;
  NTC_SENSOR_COEFFICIENTS_UNIT C;
};


struct NTC_SENSOR {
  uint8_t adcInput;
  uint32_t interval;
  uint8_t unit;
  NTC_SENSOR_COEFFICIENTS coefficients;
  uint32_t resistor;
  double correction;
  double vcc;
};

#endif // ESP_CONFIG_HARDWARE_SENSOR_NTC
#endif //_ESP_NTC_Structure_h

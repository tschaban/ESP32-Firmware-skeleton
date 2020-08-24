#ifndef _ESP_ACS758_Structure_h
#define _ESP_ACS758_Structure_h

#include <Configuration.h>
#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758

struct ACS758_SENSOR {
  uint8_t adcInput;
  uint32_t interval;
  uint8_t type;
  float vcc;
  float currentCutOff;
};

#endif // ESP_CONFIG_HARDWARE_SENSOR_ACS758
#endif //_ESP_ACS758_Structure_h

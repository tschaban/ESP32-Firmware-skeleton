#ifndef _ESP_DS18B20_Structure_h
#define _ESP_DS18B20_Structure_h

#include <Configuration.h>
#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20

#include <DallasTemperature.h>

typedef DeviceAddress DS18B20Addresses[ESP_CONFIG_HARDWARE_SENSOR_DS18B20_MAX_NUMBER];

struct DS18B20_SENSOR {
  uint8_t gpio;
  DeviceAddress address;
  float correction;
  uint32_t interval;
  uint8_t unit;

};

#endif // ESP_CONFIG_HARDWARE_SENSOR_DS18B20
#endif //_ESP_DS18B20_Structure_h

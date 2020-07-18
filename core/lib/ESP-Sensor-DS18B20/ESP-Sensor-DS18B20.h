/* ESP Firmware for smart home devices, Website: https://ESP.smartnydom.pl/ */

#ifndef _ESP_Sensor_DS18B20_h
#define _ESP_Sensor_DS18B20_h

#include <Configuration.h>
#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20

#include <DallasTemperature.h>
#include <ESP-Data-Access.h>
#include <OneWire.h>
#include <arduino.h>

#ifdef DEBUG
#include <Streaming.h>
#endif

class ESPDS18B20Sensor {

private:
  ESPDataAccess *Data;
  OneWire WireBUS;
  DallasTemperature Sensor;
  boolean ready = false;
  boolean _initialized = false;
  unsigned long startTime = 0;

  float currentTemperature = -127;

public:
  /* Constructor: entry parameter is GPIO number where Sensor is connected to */
  ESPDS18B20Sensor();

  DS18B20_SENSOR configuration;

  void begin(ESPDataAccess *_Data, uint8_t id);

  uint8_t numberOfDevicesOnBus = 0;
  uint8_t scan(uint8_t gpio, DS18B20Addresses &addresses);

  float getTemperature();

  float getLatestTemperature();

  boolean isReady();

  /* Method has to be added to the loop in order to listen for sensor value
   * changes */
  void listener();

  void addressToChar(DeviceAddress &address, char *addressString);
  void addressToInt(char *addressString, DeviceAddress &address);
  void addressNULL(DeviceAddress &address);
};

#endif // ESP_CONFIG_HARDWARE_SENSOR_DS18B20
#endif // _ESP_Sensor_DS18B20_h
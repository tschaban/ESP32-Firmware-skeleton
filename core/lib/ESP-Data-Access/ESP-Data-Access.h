#ifndef _ESP_Data_Access_h
#define _ESP_Data_Access_h

#include "arduino.h"

#include <ArduinoJson.h>
#include <Configuration.h>
#include <Data-Structures.h>
#include <LITTLEFS.h>

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
#include <NXB-Configuration.h>
#endif /* End Generic verson */

#ifdef DEBUG
#include <Streaming.h>
#endif

class ESPDataAccess {
private:
  IPAddress IPfromString(const char *address);
  boolean _initialized = false;

public:
  ESPDataAccess(void);

  boolean begin(void);

  /* It formats SPIFFS */
  boolean formatFileSystem(void);

  void createDefaultConfiguration(void);

  /* Returns true if a file exists */
  boolean fileExist(const char *);

  void get(DEVICE &data);
  void save(DEVICE *data);
  void createDeviceConfigurationFile();

  uint8_t getDeviceMode(void);
  void saveDeviceMode(uint8_t mode);

  void get(NETWORK &data);
  void save(NETWORK *data);
  void createNetworkConfigurationFile();

#ifdef ESP_CONFIG_HARDWARE_I2C
  void get(uint8_t, I2CBUS &data);
  void save(uint8_t, I2CBUS *data);
  void createI2CConfigurationFile();
#endif

#ifdef ESP_CONFIG_HARDWARE_UART
  void get(uint8_t, UARTBUS &data);
  void save(uint8_t, UARTBUS *data);
  void createUARTConfigurationFile();
#endif

#ifdef ESP_CONFIG_HARDWARE_LED
  void get(uint8_t, LED &data);
  void save(uint8_t, LED *data);
  void createLEDConfigurationFile();
  uint8_t getSystemLEDId(void);
  void saveSystemLEDId(uint8_t);
#endif

#ifdef ESP_CONFIG_HARDWARE_SWITCH
  void get(uint8_t, SWITCH &data);
  void save(uint8_t, SWITCH *data);
  void createSwitchConfigurationFile();
#endif

#ifdef ESP_CONFIG_HARDWARE_ADC
  void get(uint8_t, ADC &data);
  void save(uint8_t, ADC *data);
  void createADCConfigurationFile();
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
  void get(uint8_t, BINARY_SENSOR &data);
  void save(uint8_t, BINARY_SENSOR *data);
  void createBinarySensorConfigurationFile();
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
  void get(uint8_t, DS18B20_SENSOR &data);
  void save(uint8_t, DS18B20_SENSOR *data);
  void createDS18B20SensorConfigurationFile();
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
  void get(uint8_t, NTC_SENSOR &data);
  void save(uint8_t, NTC_SENSOR *data);
  void createNTCSensorConfigurationFile();
#endif

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
  void get(uint8_t, BATTERYMETER &data);
  void save(uint8_t, BATTERYMETER *data);
  void createBatterymeterConfigurationFile();
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
  void get(uint8_t, ACS758_SENSOR &data);
  void save(uint8_t, ACS758_SENSOR *data);
  void createACS758SensorConfigurationFile();
#endif

#ifdef ESP_CONFIG_API_MQTT
  void get(uint8_t, MQTT_BROKER &data);
  void save(uint8_t, MQTT_BROKER *data);
  void createMQTTBrokerConfigurationFile();
#endif

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */

  void NXBGet(SpeedometerDataType &data, boolean archive = false);
  void NXBSave(SpeedometerDataType *data, boolean archive = false);
  void NXBCreateSPEEDOMETERConfigurationFile(boolean archive = false);

  void NXBGetScreen(LCDScreenCurrentConfigurationType &data);
  void NXBSaveSceen(LCDScreenCurrentConfigurationType *data);
  void NXBCreateScreenConfigurationFile();

#endif /* End Generic verson */
};
#endif

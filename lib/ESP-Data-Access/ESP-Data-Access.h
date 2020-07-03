#ifndef _ESP_Data_Access_h
#define _ESP_Data_Access_h

#include "arduino.h"

#include <Configuration.h>
#include <Data-Structures.h>
//#include <ESP8266WiFi.h>
//#include <IPAddress.h>
#include <ArduinoJson.h>
#include <LITTLEFS.h>


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
  void save(DEVICE *);
  void createDeviceConfigurationFile();

  uint8_t getDeviceMode(void);
  void saveDeviceMode(uint8_t mode);

  void get(NETWORK &data);
  void save(NETWORK *);
  void createNetworkConfigurationFile();

#ifdef ESP_CONFIG_HARDWARE_I2C
  void get(uint8_t, I2CBUS &data);
  void save(uint8_t, I2CBUS *);
  void createI2CConfigurationFile();
#endif

#ifdef ESP_CONFIG_HARDWARE_UART
  void get(uint8_t, UARTBUS &data);
  void save(uint8_t, UARTBUS *);
  void createUARTConfigurationFile();
#endif


#ifdef ESP_CONFIG_HARDWARE_LED
  void get(uint8_t, LED &data);
  void save(uint8_t, LED *);
  void createLEDConfigurationFile();
  uint8_t getSystemLEDId(void);
  void saveSystemLEDId(uint8_t);
#endif

#ifdef ESP_CONFIG_HARDWARE_SWITCH
  void get(uint8_t, SWITCH &data);
  void save(uint8_t, SWITCH *);
  void createSwitchConfigurationFile();
#endif

#ifdef ESP_CONFIG_HARDWARE_ADC
  void get(uint8_t, ADC &data);
  void save(uint8_t, ADC *);
  void createADCConfigurationFile();
#endif

};
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20

#include <ESP-Sensor-DS18B20.h>
ESPDS18B20Sensor DS18B20Sensor[ESP_CONFIG_HARDWARE_SENSOR_DS18B20_MAX_NUMBER];
void initializeDS18B20Sensor(void);
void eventsListnerDS18B20Sensor(void);

#ifdef DEBUG
void scanGPIOForDS18B20Sensors(void);
#endif

/***** Body ******/

void initializeDS18B20Sensor(void) {
#ifdef DEBUG
  scanGPIOForDS18B20Sensors();
#endif

  for (uint8_t i = 0; i < Device.configuration.noOfDS18B20s; i++) {

#ifdef DEBUG
    Serial << endl << "INFO: DS18B20(" << i + 1 << ") initialized";
#endif
  }
};

void eventsListnerDS18B20Sensor(void) {

  /* Listens for switch events */
  for (uint8_t i = 0; i < Device.configuration.noOfDS18B20s; i++) {
    DS18B20Sensor[i].listener();
    if (DS18B20Sensor[i].isReady()) {

#ifdef DEBUG
      Serial << endl
             << "INFO: Data from DS18B20(" << i + 1
             << "): in buffer. Ready for processing.";
      ;
#endif

      // HERE CODE FOR DS18B20
    }
  }
}

#ifdef DEBUG

void scanGPIOForDS18B20Sensors(void) {
  DS18B20_SENSOR configuration;
  configuration.gpio = 14;
  DS18B20Addresses addresses;
  DS18B20Sensor[0].scan(configuration.gpio, addresses);
  /*
  for (uint8_t i = 0; i < Device.configuration.noOfDS18B20s; i++) {
    // Data.get(i, configuration);

    if (configuration.gpio != ESP_HARDWARE_ITEM_NOT_EXIST) {
      DS18B20Sensor[0].scan(configuration.gpio);
    }
  }*/
}

#endif

#endif // ESP_CONFIG_HARDWARE_SENSOR_DS18B20

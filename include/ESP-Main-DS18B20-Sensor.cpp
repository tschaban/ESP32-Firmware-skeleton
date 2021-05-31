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
  if (Device.configuration.noOfDS18B20s > 0) {
    scanGPIOForDS18B20Sensors();
  }
#endif

  for (uint8_t i = 0; i < Device.configuration.noOfDS18B20s; i++) {
    DS18B20Sensor[i].begin(&Data, i);
#ifdef DEBUG
    Serial << endl << "INFO: DS18B20(" << i + 1 << ") initialized";
#endif
  }
};

void eventsListnerDS18B20Sensor(void) {
  char _number[10];
  /* Listens for switch events */
  for (uint8_t i = 0; i < Device.configuration.noOfDS18B20s; i++) {
    if (DS18B20Sensor[i].listener()) {
      sprintf(_number, "%-.3f", DS18B20Sensor[i].getTemperature());
      if (i == 0) {
        p0_t3.setText(_number);
      } else if (i == 1) {
        p0_t4.setText(_number);
      }

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

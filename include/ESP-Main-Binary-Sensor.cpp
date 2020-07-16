#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY

#include <ESP-Sensor-Binary.h>
ESPSensorBinary BinarySensor[ESP_CONFIG_HARDWARE_SENSOR_BINARY_MAX_NUMBER];
void initializeBinarySensor(void);
void eventsListnerBinarySensor(void);

/***** Body ******/

void initializeBinarySensor(void) {
  for (uint8_t i = 0; i < Device.configuration.noOfBinarySensors; i++) {
    BinarySensor[i].begin(&Data,i);
#ifdef DEBUG
    Serial << endl << "INFO: Binary Sesnor(" << i + 1 << ") initialized";
#endif
  }
};

void eventsListnerBinarySensor(void) {

  /* Listens for switch events */
  for (uint8_t i = 0; i < Device.configuration.noOfBinarySensors; i++) {
    if (BinarySensor[i].listener()) {
      uint32_t impulses, duration;
      BinarySensor[i].get(impulses, duration);

      char _number[10];
      sprintf(_number, "%d", impulses);
      p0_t2.setText(_number);

      // HERE CODE FOR BINARY SESNOR
    }
  }
}

#endif // ESP_CONFIG_HARDWARE_SENSOR_BINARY

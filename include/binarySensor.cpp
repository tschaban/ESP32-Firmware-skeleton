#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY

#include <ESP-Sensor-Binary.h>
ESPSensorBinary BinarySensor[ESP_CONFIG_HARDWARE_SENSOR_BINARY_MAX_NUMBER];
void initializeSensorBinary(void);
void eventsListnerSensorBinary(void);

/***** Body ******/

void initializeSensorBinary(void) {
  for (uint8_t i = 0; i < Device.configuration.noOfBinarySensors; i++) {
    BinarySensor[i].begin(i);
#ifdef DEBUG
    Serial << endl << "INFO: Binary Sesnor(" << i + 1 << ") initialized";
#endif
  }
};

void eventsListnerSensorBinary(void) {

  /* Listens for switch events */
  for (uint8_t i = 0; i < Device.configuration.noOfBinarySensors; i++) {
    if (BinarySensor[i].listener()) {
      uint32_t impulses, duration;
      BinarySensor[i].get(impulses, duration);

      char _number[10];
      sprintf(_number, "%d", impulses);
      p0_t0.setText(_number);

      // HERE CODE FOR BINARY SESNOR
    }
  }
}

#endif // ESP_CONFIG_HARDWARE_SENSOR_BINARY

#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758

#include <ESP-Sensor-ACS758.h>
ESPACS758Sensor ACS758Sensor[ESP_CONFIG_HARDWARE_SENSOR_ACS758_MAX_NUMBER];
void initializeACS758Sensor(void);
void eventsListnerACS758Sensor(void);

/***** Body ******/

void initializeACS758Sensor(void) {
  for (uint8_t i = 0; i < Device.configuration.noOfACS758s; i++) {

#ifdef ESP_CONFIG_HARDWARE_ADS1115
    ACS758Sensor[i].begin(&Data, &WirePort0, &WirePort1, i);
#else
    ACS758Sensor[i].begin(&Data, i);
#endif
  }
};

void eventsListnerACS758Sensor(void) {
  char _number[20];
  /* Listens for switch events */
  for (uint8_t i = 0; i < Device.configuration.noOfACS758s; i++) {
    if (ACS758Sensor[i].listener()) {
      sprintf(_number, "C:%-.2fA", ACS758Sensor[i].current);
      p0_t4.setText(_number);

      // HERE CODE FOR ACS758
    }
  }
}

#endif // ESP_CONFIG_HARDWARE_SENSOR_ACS758

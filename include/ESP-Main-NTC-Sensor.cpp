#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC

#include <ESP-Sensor-NTC.h>
ESPNTCSensor NTCSensor[ESP_CONFIG_HARDWARE_SENSOR_NTC_MAX_NUMBER];
void initializeNTCSensor(void);
void eventsListnerNTCSensor(void);

/***** Body ******/

void initializeNTCSensor(void) {
  for (uint8_t i = 0; i < Device.configuration.noOfNTCs; i++) {

#ifdef ESP_CONFIG_HARDWARE_ADS1115
    NTCSensor[i].begin(&Data, &WirePort0, &WirePort1, i);
#else
    NTCSensor[i].begin(&Data, i);
#endif

#ifdef DEBUG
    Serial << endl << "INFO: NTC(" << i + 1 << ") initialized";
#endif
  }
};

void eventsListnerNTCSensor(void) {
  char _number[10];
  /* Listens for switch events */
  for (uint8_t i = 0; i < Device.configuration.noOfNTCs; i++) {
    if (NTCSensor[i].listener()) {
      sprintf(_number, "%-.3f", NTCSensor[i].temperature);
      p0_t5.setText(_number);

      // HERE CODE FOR NTC
    }
  }
}

#endif // ESP_CONFIG_HARDWARE_SENSOR_NTC

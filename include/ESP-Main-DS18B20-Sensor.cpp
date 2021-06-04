#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20

#include <ESP-Sensor-DS18B20.h>
ESPDS18B20Sensor DS18B20Sensor[ESP_CONFIG_HARDWARE_SENSOR_DS18B20_MAX_NUMBER];

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */

float tempOutside = 0;
float tempInFrame = 0;
uint16_t _tempOutside = 0;
uint16_t _tempInFrame = 0;
uint16_t lastTempOutside = 0;
uint16_t lastTempInFrame = 0;

#else  /* Generic verson */
#endif /* End Generic verson */

void initializeDS18B20Sensor(void);
void eventsListnerDS18B20Sensor(void);

/***** Body ******/

void initializeDS18B20Sensor(void) {
  for (uint8_t i = 0; i < Device.configuration.noOfDS18B20s; i++) {
    DS18B20Sensor[i].begin(&Data, i);
#ifdef DEBUG
    Serial << endl << "INFO: DS18B20(" << i + 1 << ") initialized";
#endif
  }

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
Screen.setTemperatureInFrame(lastTempInFrame);
Screen.setTemperatureOutside(lastTempOutside);
#endif

};

void eventsListnerDS18B20Sensor(void) {
  /* Listens for switch events */
  for (uint8_t i = 0; i < Device.configuration.noOfDS18B20s; i++) {

    if (DS18B20Sensor[i].listener()) {

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
      switch (i) {
      case 0:
        _tempInFrame = (uint16_t)(
            round(DS18B20Sensor[i].getTemperature() *
                  (DS18B20Sensor[i].getTemperature() < 0 ? -100 : 100)));
        if (lastTempInFrame != _tempInFrame) {
          lastTempInFrame = _tempInFrame;
          Screen.setTemperatureInFrame(lastTempInFrame);
        }
        break;
      case 1:
        _tempOutside = (uint16_t)(
            round(DS18B20Sensor[i].getTemperature() *
                  (DS18B20Sensor[i].getTemperature() < 0 ? -100 : 100)));
        if (lastTempOutside != _tempOutside) {
          lastTempOutside = _tempOutside;
          Screen.setTemperatureOutside(lastTempOutside);
        }
        break;
      }

#else /* Generic verson */

// HERE CODE FOR DS18B20

#endif /* End Generic verson */
    }
  }
}

#endif // ESP_CONFIG_HARDWARE_SENSOR_DS18B20

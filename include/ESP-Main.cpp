#ifndef NXTBIKECOMPUTER /* NxtBike Computer */

void run(void);


void run(void) {
  if (Device.getMode() == ESP_MODE_NORMAL ||
      Device.getMode() == ESP_MODE_CONFIGURATION) {
    if (Network.connected()) {
      if (Device.getMode() == ESP_MODE_NORMAL) {

        /* Code only for: Normal mode, and connected to WiFi */

        HTTPServer.listener();

#ifdef ESP_CONFIG_HARDWARE_ADC
        eventsListnerADC();
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
        eventsListnerBinarySensor();
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
        eventsListnerDS18B20Sensor();
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
        eventsListnerNTCSensor();
#endif
#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
        eventsListnerBatterymeter();
#endif
#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
        eventsListnerACS758Sensor();
#endif

#ifdef ESP_CONFIG_HARDWARE_NEXTION
        eventsListnerNextion();
#endif

      } else { /* Device runs in configuration mode over WiFi */
#ifdef ESP_CONFIG_HARDWARE_LED
        if (!Led.isBlinking()) {
          Led.blinkingOn(100);
        }
#endif
        HTTPServer.listener();
      }
    }

#ifdef ESP_CONFIG_HARDWARE_LED
    else {
      if (Device.getMode() == ESP_MODE_CONFIGURATION && !Led.isBlinking()) {
        Led.blinkingOn(100);
      }
    }
#endif
    yield();
    Network.listener();

    /** Here: Code that will be run no matter if connected or disconnected
     * from Network
     * Works for device in Normal or Configuration mode: (excluding: HotSpot
     * mode) */
  } else { /* Deviced runs in Access Point mode */
    HTTPServer.listener();
  }

/* Switch listener */
#ifdef ESP_CONFIG_HARDWARE_SWITCH
  eventsListnerSwitch();
#endif

#ifdef ESP_CONFIG_HARDWARE_LED
  Led.loop();
#endif
}
#endif
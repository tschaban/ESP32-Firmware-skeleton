#ifdef ESP_CONFIG_HARDWARE_LED

#include <ESP-LED.h>
ESPLED Led;
void initializeLED(void);

/***** Body ******/

void initializeLED(void) {
  uint8_t id = Data.getSystemLEDId();
#ifdef DEBUG
  boolean initialized = false;
#endif
  if (id != ESP_HARDWARE_ITEM_NOT_EXIST) {
    if (Device.configuration.noOfLEDs - 1 >= id) {
      if (Led.begin(&Data, id)) {
        Led.on();
#ifdef DEBUG
        initialized = true;
#endif
      }
    }
#ifdef DEBUG
    if (initialized) {
      Serial << endl << F("INFO: System LED initialized");
    } else {
      Serial << endl << F("WARN: System LED NOT initialized");
    }
#endif // DEBUG
  }
};
#endif // ESP_CONFIG_HARDWARE_LED

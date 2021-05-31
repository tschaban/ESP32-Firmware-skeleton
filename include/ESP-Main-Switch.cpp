#ifdef ESP_CONFIG_HARDWARE_SWITCH

#include <ESP-Switch.h>
ESPSwitch Switch[ESP_CONFIG_HARDWARE_SWITCH_MAX_NUMBER];
void initializeSwitch(void);
void eventsListnerSwitch(void);

/***** Body ******/

void initializeSwitch(void) {
  for (uint8_t i = 0; i < Device.configuration.noOfSwitches; i++) {
#ifdef ESP_CONFIG_HARDWARE_LED
    Switch[i].begin(i, &Data, &Led);
#else
    Switch[i].begin(i, &Data);
#endif // ESP_CONFIG_HARDWARE_LED
  }
};

void eventsListnerSwitch(void) {

  /* Listens for switch events */
  for (uint8_t i = 0; i < Device.configuration.noOfSwitches; i++) {
    Switch[i].listener();

    if (Switch[i].isPressed(true)) {

      unsigned long pressDuration = Switch[i].pressEvent();
#ifdef DEBUG
      Serial << endl << "INFO: Switched pressed for: " << pressDuration;
#endif

      if (pressDuration > 0 && pressDuration <= 5000) {
#ifdef DEBUG
        Serial << endl << "INFO: Processing switch 0-5sec";
#endif

      } else if (pressDuration > 5000 && pressDuration <= 10000) {
#ifdef DEBUG
        Serial << endl << "INFO: Processing switch 5-10sec";
#endif

        if (Switch[i].configuration.functionality ==
            ESP_CONFIG_HARDWARE_SWITCH_FUNCTIONALITY_MULTI) {
          Device.getMode() == ESP_MODE_NORMAL
              ? Device.reboot(ESP_MODE_CONFIGURATION)
              : Device.reboot(ESP_MODE_NORMAL);
        }
      } else if (pressDuration > 10000 && pressDuration <= 15000) {
#ifdef DEBUG
        Serial << endl << "INFO: Processing switch 10-15sec";
#endif
        if (Switch[i].configuration.functionality ==
            ESP_CONFIG_HARDWARE_SWITCH_FUNCTIONALITY_MULTI) {
          Device.getMode() == ESP_MODE_NORMAL
              ? Device.reboot(ESP_MODE_ACCESS_POINT)
              : Device.reboot(ESP_MODE_NORMAL);
        }
      } else if (pressDuration > 15000 && pressDuration <= 20000) {
#ifdef DEBUG
        Serial << endl << "INFO: Processing switch 30-35sec";
#endif
        if (Switch[i].configuration.functionality ==
            ESP_CONFIG_HARDWARE_SWITCH_FUNCTIONALITY_MULTI) {
          Data.createDefaultConfiguration();
          Device.reboot(ESP_MODE_ACCESS_POINT);
        }
      }
    }
  }
}

#endif // ESP_CONFIG_HARDWARE_SWITCH
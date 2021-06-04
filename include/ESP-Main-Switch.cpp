#ifdef ESP_CONFIG_HARDWARE_SWITCH

#include <ESP-Switch.h>
ESPSwitch Switch[ESP_CONFIG_HARDWARE_SWITCH_MAX_NUMBER];

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
unsigned long _durationButtonPressed = 0;
unsigned long _whenButtonPressed = 0;
uint8_t _progressBar = SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL;
uint8_t _lastScreen = 0;
#else  /* Generic verson */
#endif /* End Generic verson */

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

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */

void eventsListnerSwitch(void) {

  /* Listens for switch events */
  for (uint8_t i = 0; i < Device.configuration.noOfSwitches; i++) {

    Switch[i].listener();

    if (Switch[i].configuration.functionality ==
        ESP_CONFIG_HARDWARE_SWITCH_FUNCTIONALITY_MULTI) {

      if (Switch[i].isPressed(true)) {
        // Screen.set(SCREEN_SPLASH);
        unsigned long pressDuration = Switch[i].pressEvent();

        if (pressDuration == 0) {
          Screen.set(SCREEN_SPLASH);
          Screen.setTextAtSplashScreen("System button pressed...");
        } else if (pressDuration > 0 &&
                   pressDuration <=
                       ESP_CONFIG_HARDWARE_SWITCH_PRESS_FUNCTIONS_INTERVAL) {
          if (Device.getMode() != ESP_MODE_NORMAL) {
            Device.reboot(ESP_MODE_NORMAL);
          } else {
            Device.reboot(ESP_MODE_CONFIGURATION);
          }
        } else if (
            pressDuration >
                ESP_CONFIG_HARDWARE_SWITCH_PRESS_FUNCTIONS_INTERVAL &&
            pressDuration <=
                2 * ESP_CONFIG_HARDWARE_SWITCH_PRESS_FUNCTIONS_INTERVAL) {
          if (Device.getMode() != ESP_MODE_NORMAL) {
            Device.reboot(ESP_MODE_NORMAL);
          } else {
            Device.reboot(ESP_MODE_ACCESS_POINT);
          }
        } else if (pressDuration >
                   2 * ESP_CONFIG_HARDWARE_SWITCH_PRESS_FUNCTIONS_INTERVAL) {

          Device.reboot(ESP_MODE_NORMAL);
        }
      }
    } else { /* Non System button */

      _whenButtonPressed = Switch[i].whenButtonPressed();
      if (_whenButtonPressed > 0) {
        _durationButtonPressed = millis() - _whenButtonPressed;

        if (_durationButtonPressed > SCREEN_BUTTON_MENU_SHOW_TIME &&
            _durationButtonPressed <= SCREEN_BUTTON_MENU_SHOW_TIME +
                                          SCREEN_BUTTON_MENU_ITEM_DURATION) {
          if (Screen.getActiveScreenID() != SCREEN_BUTTON_CHANGE_THEME) {
            _lastScreen = Screen.getActiveScreenID();
            Screen.setMenuPregressBarSpeed(
                SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL);
            Screen.set(SCREEN_BUTTON_CHANGE_THEME);
          }
          _progressBar = (uint8_t)(
              SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL +
              round(
                  (_durationButtonPressed - SCREEN_BUTTON_MENU_ITEM_DURATION) /
                  (SCREEN_BUTTON_MENU_ITEM_DURATION /
                   (100 - 2 * SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL))));

        } else if (_durationButtonPressed >
                       SCREEN_BUTTON_MENU_SHOW_TIME +
                           SCREEN_BUTTON_MENU_ITEM_DURATION &&
                   _durationButtonPressed <=
                       SCREEN_BUTTON_MENU_SHOW_TIME +
                           2 * SCREEN_BUTTON_MENU_ITEM_DURATION) {
          if (Screen.getActiveScreenID() != SCREEN_BUTTON_RESET_METER) {
            Screen.setMenuPregressBarSpeed(
                SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL);
            Screen.set(SCREEN_BUTTON_RESET_METER);
          }

          _progressBar = (uint8_t)(
              SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL +
              round((_durationButtonPressed -
                     2 * SCREEN_BUTTON_MENU_ITEM_DURATION) /
                    (SCREEN_BUTTON_MENU_ITEM_DURATION /
                     (100 - 2 * SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL))));
        } else if (_durationButtonPressed >
                       SCREEN_BUTTON_MENU_SHOW_TIME +
                           2 * SCREEN_BUTTON_MENU_ITEM_DURATION &&
                   _durationButtonPressed <=
                       SCREEN_BUTTON_MENU_SHOW_TIME +
                           3 * SCREEN_BUTTON_MENU_ITEM_DURATION) {
          if (Screen.getActiveScreenID() != SCREEN_BUTTON_CONNECT_TO_WIFI) {
            Screen.setMenuPregressBarSpeed(
                SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL);
            Screen.set(SCREEN_BUTTON_CONNECT_TO_WIFI);
          }
          _progressBar = (uint8_t)(
              SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL +
              round((_durationButtonPressed -
                     3 * SCREEN_BUTTON_MENU_ITEM_DURATION) /
                    (SCREEN_BUTTON_MENU_ITEM_DURATION /
                     (100 - 2 * SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL))));
        } else if (_durationButtonPressed >
                       SCREEN_BUTTON_MENU_SHOW_TIME +
                           3 * SCREEN_BUTTON_MENU_ITEM_DURATION &&
                   _durationButtonPressed <=
                       SCREEN_BUTTON_MENU_SHOW_TIME +
                           4 * SCREEN_BUTTON_MENU_ITEM_DURATION) {
          if (Screen.getActiveScreenID() != SCREEN_BUTTON_ACCESS_POINT) {
            Screen.setMenuPregressBarSpeed(
                SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL);
            Screen.set(SCREEN_BUTTON_ACCESS_POINT);
          }
          _progressBar = (uint8_t)(
              SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL +
              round((_durationButtonPressed -
                     4 * SCREEN_BUTTON_MENU_ITEM_DURATION) /
                    (SCREEN_BUTTON_MENU_ITEM_DURATION /
                     (100 - 2 * SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL))));
        } else if (_durationButtonPressed >
                       SCREEN_BUTTON_MENU_SHOW_TIME +
                           4 * SCREEN_BUTTON_MENU_ITEM_DURATION &&
                   _durationButtonPressed <=
                       SCREEN_BUTTON_MENU_SHOW_TIME +
                           5 * SCREEN_BUTTON_MENU_ITEM_DURATION) {
          if (Screen.getActiveScreenID() != SCREEN_BUTTON_CANCEL) {
            Screen.setMenuPregressBarSpeed(
                SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL);
            Screen.set(SCREEN_BUTTON_CANCEL);
          }
          _progressBar = (uint8_t)(
              SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL +
              round((_durationButtonPressed -
                     5 * SCREEN_BUTTON_MENU_ITEM_DURATION) /
                    (SCREEN_BUTTON_MENU_ITEM_DURATION /
                     (100 - 2 * SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL))));
        } else if (_durationButtonPressed >
                   SCREEN_BUTTON_MENU_SHOW_TIME +
                       5 * SCREEN_BUTTON_MENU_ITEM_DURATION) {
          Switch[i].resetButtonPressedTimer(millis() -
                                            SCREEN_BUTTON_MENU_SHOW_TIME);
        }

        Screen.setMenuPregressBarSpeed(_progressBar);
      }

      if (Switch[i].isPressed(true)) {

        unsigned long pressDuration = Switch[i].pressEvent();
#ifdef DEBUG
        Serial << endl << "INFO: Switched pressed for: " << pressDuration;
#endif

        if (pressDuration > 0 &&
            pressDuration <= SCREEN_BUTTON_MENU_SHOW_TIME) { /* Screen change */
          Screen.change();

          switch (Screen.getActiveScreenID()) {
          case SCREEN_SPEEDOMETER:
            Screen.setCurrentSpeed(lastCurrentSpeed);
            Screen.setAvgSpeed(lastAvgSpeed);
            Screen.setMaxSpeed(lastMaxSpeed);
            Screen.setPregressBarSpeed(lastProgressBarSpeed);
            Screen.setTotalDistance(lastTotalDistance);
            Screen.setTripDistance(lastTripDistance);
            Screen.setRideTime(lastTimeRide);
            break;
          case SCREEN_ELECTRICITY:
            Screen.setCurrentSpeed(lastCurrentSpeed);
            Screen.setAvgSpeed(lastAvgSpeed);
            Screen.setMaxSpeed(lastMaxSpeed);
            Screen.setPregressBarSpeed(lastProgressBarSpeed);
            Screen.setRideTime(lastTimeRide);
            Screen.setBatteryPercent(lastBatteryPercent);
            Screen.setBatteryVoltage(lastBatteryVoltage);
            break;
          case SCREEN_SPEED:
            Screen.setCurrentSpeed(lastCurrentSpeed);
            break;
          case SCREEN_TEMPERATURE:
            Screen.setCurrentSpeed(lastCurrentSpeed);
            Screen.setAvgSpeed(lastAvgSpeed);
            Screen.setMaxSpeed(lastMaxSpeed);
            Screen.setPregressBarSpeed(lastProgressBarSpeed);
            Screen.setRideTime(lastTimeRide);
            Screen.setTemperatureInFrame(lastTempInFrame);
            Screen.setTemperatureOutside(lastTempOutside);
            break;
          }

        } else if (pressDuration > SCREEN_BUTTON_MENU_SHOW_TIME &&
                   pressDuration <=
                       SCREEN_BUTTON_MENU_SHOW_TIME +
                           SCREEN_BUTTON_MENU_ITEM_DURATION) { /* Theme change
                                                                  */

          Screen.changeTheme();
          Screen.set(_lastScreen);

        } else if (pressDuration > SCREEN_BUTTON_MENU_SHOW_TIME +
                                       SCREEN_BUTTON_MENU_ITEM_DURATION &&
                   pressDuration <=
                       SCREEN_BUTTON_MENU_SHOW_TIME +
                           2 * SCREEN_BUTTON_MENU_ITEM_DURATION) { /* Reset
                                                                      Meter */
          Speedometer.reset();
          Screen.set(_lastScreen);

        } else if (pressDuration > SCREEN_BUTTON_MENU_SHOW_TIME +
                                       2 * SCREEN_BUTTON_MENU_ITEM_DURATION &&
                   pressDuration <=
                       SCREEN_BUTTON_MENU_SHOW_TIME +
                           3 * SCREEN_BUTTON_MENU_ITEM_DURATION) { /* Connet
                                                                      to
                                                                      WiFi */
          Device.reboot(ESP_MODE_CONFIGURATION);
        } else if (pressDuration > SCREEN_BUTTON_MENU_SHOW_TIME +
                                       3 * SCREEN_BUTTON_MENU_ITEM_DURATION &&
                   pressDuration <=
                       SCREEN_BUTTON_MENU_SHOW_TIME +
                           4 * SCREEN_BUTTON_MENU_ITEM_DURATION) { /* Access
                                                                      point */
          Device.reboot(ESP_MODE_ACCESS_POINT);
        } else if (pressDuration > SCREEN_BUTTON_MENU_SHOW_TIME +
                                       4 * SCREEN_BUTTON_MENU_ITEM_DURATION &&
                   pressDuration <=
                       SCREEN_BUTTON_MENU_SHOW_TIME +
                           5 * SCREEN_BUTTON_MENU_ITEM_DURATION) { /* Cancel
                                                                      */
          if (Device.getMode() != ESP_MODE_NORMAL) {
            Device.reboot(ESP_MODE_NORMAL);
          } else {
            Screen.set(_lastScreen);
          }
        }
      }
    }
  }
}

#else /* Generic verson */

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

#endif /* End Generic verson */

#endif // ESP_CONFIG_HARDWARE_SWITCH
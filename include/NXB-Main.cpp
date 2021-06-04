#ifdef NXTBIKECOMPUTER /* NxtBike Computer */

unsigned long _timeFromLastSave = millis();
unsigned long _timeFromLastArchiveSave = millis();

void run(void);

/* Body */

void run(void) {

  if (Device.getMode() == ESP_MODE_NORMAL) {

/*
if (Device.getMode() == ESP_MODE_NORMAL) {
  Device.saveMode(ESP_MODE_CONFIGURATION);
}
*/

#ifdef ESP_CONFIG_HARDWARE_ADC
    eventsListnerADC();
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
    eventsListnerBinarySensor();
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
    eventsListnerDS18B20Sensor();
#endif

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
    eventsListnerBatterymeter();
#endif

#ifdef ESP_CONFIG_HARDWARE_NEXTION
    eventsListnerNextion();
#endif

    /* Achiving data */

    if (millis() - _timeFromLastSave > SPEEDOMETER_DATA_ARCHIVE_TIME) {
      if (Speedometer.data.speed.current <
          SPEEDOMETER_DATA_ARCHIVE_SAFE_SPEED) {
        if (Speedometer.data.distance.total >
            SPEEDOMETER_DEFAULT_TOTAL_DISTANCE) {
          BinarySensor.detachInterrupts(0);
          Data.NXBSave(&Speedometer.data);
          BinarySensor.attachInterrupts(0);
          Screen.showSyncStatus();
        }
        _timeFromLastSave = millis();
#ifdef DEBUG
        Serial << endl << "INFO: Speedometer: saving data";
#endif
      } else {
        if (Screen.getSyncStatus() != SYNC_WAITING_TO_SYNC) {
          Screen.showSyncStatus(SYNC_WAITING_TO_SYNC);
        }
      }
    }

    /* Backup of the speedometer data */

    if (millis() - _timeFromLastSave > SPEEDOMETER_DATA_ARCHIVE_TIME_BACKUP) {
      if (Speedometer.data.speed.current <
          SPEEDOMETER_DATA_ARCHIVE_SAFE_SPEED) {
        if (Speedometer.data.distance.total >
            SPEEDOMETER_DEFAULT_TOTAL_DISTANCE) {
#ifdef DEBUG
          Serial << endl << "INFO: Speedometer: saving backup file";
#endif
          BinarySensor.detachInterrupts(0);
          Data.NXBSave(&Speedometer.data, true);
          BinarySensor.attachInterrupts(0);
        }
      }
    }

  } /* End of operating mode */

  /* Network connected */
  else {

    if (Screen.getActiveScreenID() != SCREEN_SPLASH) {
      Screen.set(SCREEN_SPLASH);
      Screen.setTextAtSplashScreen("Configuration mode");
    }

    if (Device.getMode() == ESP_MODE_CONFIGURATION) {
      if (Network.connected()) {
        HTTPServer.listener();
      } else {
        // Screen.setTextAtSplashScreen("Connecting to WiFi...");
      }
    } else {
      HTTPServer.listener();
    }

#ifdef ESP_CONFIG_HARDWARE_LED
    if (!Led.isBlinking()) {
      Led.blinkingOn(100);
    }
#endif
  }
/* End of Connected to WiFi Mode */

/* Code for all modes */

/* Switch listener */
#ifdef ESP_CONFIG_HARDWARE_SWITCH
  eventsListnerSwitch();
#endif

#ifdef ESP_CONFIG_HARDWARE_LED
  Led.loop();
#endif
}
#endif /* End NxtBike Computer */
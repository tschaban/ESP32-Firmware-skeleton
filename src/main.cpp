#include <main.h>

void setup() {

#ifdef DEBUG
  Serial.begin(ESP_CONFIG_SERIAL_SPEED);
  delay(10);
#endif

#ifdef DEBUG
  Serial << endl
         << endl
         << F("################################ BOOTING "
              "################################")
         << endl
         << F("INFO: All classes and global variables initialized") << endl
         << F("INFO: Initializing device");
#endif

#ifdef DEBUG
  Serial << endl << F("INFO: Initializing File System");
#endif
  if (!Data.begin()) {
#ifdef DEBUG
    Serial << endl << F("ERROR: File System NOT initialized");
#endif
  }

  Device.begin(&Data);

#ifdef DEBUG
  Serial << endl << "INFO: Checking if first time launch ... ";
#endif

  if (Device.getMode() == ESP_MODE_FIRST_TIME_LAUNCH) {
#ifdef DEBUG
    Serial << "YES";
#endif
    Data.formatFileSystem();
    Data.createDefaultConfiguration();
    Device.begin(&Data);
  }
#ifdef DEBUG
  else {
    Serial << "NO";
  }
#endif

/* Initializing: System LED */
#ifdef ESP_CONFIG_HARDWARE_LED
  initializeLED();
#endif // ESP_CONFIG_HARDWARE_LED

/* Initializing: Network */
#ifdef ESP_CONFIG_HARDWARE_LED
  Network.begin(&Device, &Data, &Led, Device.getMode());
#else
  Network.begin(&Device, &Data, Device.getMode());
#endif

  Network.listener();
#ifdef DEBUG
  Serial << endl << F("INFO: Network initialized");
#endif

/* Initializing I2C BUS */
#ifdef ESP_CONFIG_HARDWARE_I2C
  initializeI2CBUS();
#endif // ESP_CONFIG_HARDWARE_I2C

  /* Initializing HTTP HTTPServer */
  initializeHTTPServer();

/* Initializing Switches */
#ifdef ESP_CONFIG_HARDWARE_SWITCH
  initializeSwitch();
#endif

  /* Initialization components required for Normal mode */
  if (Device.getMode() == ESP_MODE_NORMAL) {

/* Initializing ADC */
#ifdef ESP_CONFIG_HARDWARE_ADC
    initializeADC();
#endif
  }

#ifdef DEBUG
  Serial << endl
         << F("################################################################"
              "########")
         << endl
         << F("#                           BOOTING COMPLETED                   "
              "       #")
         << endl
         << F("#                            STARTING DEVICE                    "
              "       #");
  if (Device.getMode() != ESP_MODE_NORMAL) {
    Serial << endl
           << F("#                           CONFIGURATION MODE                "
                "         #");
  }

  Serial << endl
         << F("################################################################"
              "########");
#endif
}

void loop() {

  if (Device.getMode() == ESP_MODE_NORMAL ||
      Device.getMode() == ESP_MODE_CONFIGURATION) {
    if (Network.connected()) {
      if (Device.getMode() == ESP_MODE_NORMAL) {

/* Code only for: Normal mode, and connected to WiFi */

#ifdef ESP_CONFIG_HARDWARE_ADC
        eventsListnerADC();
#endif
      }
      /* Code only for: Normal and Configuration mode, and connected to WiFi */

      HTTPServer.listener();
    }
    /* Code only for: Normal and Configuration mode, and connected/disconnected
     * to WiFi */
    Network.listener();
  } else {
    /* Code only for: Configuration mode in HotSpote mode */
    HTTPServer.listener();
  }

/* Code run in each modes when device is connected or disconnected from WiFi */

/* Led listener */
#ifdef ESP_CONFIG_HARDWARE_LED
  if (Device.getMode() == ESP_MODE_NORMAL && Led.isBlinking()) {
    Led.blinkingOff();
  } else if (Device.getMode() != ESP_MODE_NORMAL && !Led.isBlinking()) {
    Led.blinkingOn(100);
  }
  Led.loop();
#endif

/* Switch listener */
#ifdef ESP_CONFIG_HARDWARE_SWITCH
  eventsListnerSwitch();
#endif
}

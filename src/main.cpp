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

/* Initializing ADC
#ifdef ESP_CONFIG_HARDWARE_ADC
   initializeADC();
#endif  */

/* Nextion */
#ifdef ESP_CONFIG_HARDWARE_NEXTION
    initializeNextion();
#endif

/* Sensor: Binary Input */
#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
    initializeBinarySensor();
#endif

/* Sensor: DS18B20 */
#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
    initializeDS18B20Sensor();
#endif

/* Sensor: NTC */
#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
    initializeNTCSensor();
#endif

/* Batterymeter */
#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
    initializeBatterymeter();
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

/* #ifdef ESP_CONFIG_HARDWARE_ADC
      eventsListnerADC();
#endif */

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

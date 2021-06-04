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
         << F("INFO: Initializing device") << endl;

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

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
  if (Device.getMode() != ESP_MODE_NORMAL) {
#ifdef ESP_CONFIG_HARDWARE_LED
    Network.begin(&Device, &Data, &Led, Device.getMode());
#else
    Network.begin(&Device, &Data, Device.getMode());
#endif

    Network.listener();
#ifdef DEBUG
    Serial << endl << F("INFO: Network initialized");
#endif
  }

#else /* Generic verson */

#ifdef ESP_CONFIG_HARDWARE_LED
  Network.begin(&Device, &Data, &Led, Device.getMode());
#else
  Network.begin(&Device, &Data, Device.getMode());
#endif

  Network.listener();
#ifdef DEBUG
  Serial << endl << F("INFO: Network initialized");
#endif

#endif /* End Generic verson */

/* Initializing I2C BUS */
#ifdef ESP_CONFIG_HARDWARE_I2C
  initializeI2CBUS();
#endif // ESP_CONFIG_HARDWARE_I2C

/* Initializing HTTP HTTPServer */
#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
  if (Device.getMode() != ESP_MODE_NORMAL) {
    initializeHTTPServer();
  }
#else  /* Generic verson */
  initializeHTTPServer();
#endif /* End Generic verson */

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

/* Sensor: _ACS758 */
#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
    initializeACS758Sensor();
#endif
  }

#ifdef ESP_CONFIG_HARDWARE_LED
  Led.off();
  /* If device in configuration mode then it starts LED blinking */
  if (Device.getMode() == ESP_MODE_ACCESS_POINT ||
      Device.getMode() == ESP_MODE_NETWORK_NOT_SET) {
    Led.blinkingOn(100);
  }
#endif

/* Nextion */
#ifdef ESP_CONFIG_HARDWARE_NEXTION
  initializeNextion();
#endif

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

void loop() { run(); }

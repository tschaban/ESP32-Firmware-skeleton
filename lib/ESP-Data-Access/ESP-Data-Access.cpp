#include "ESP-Data-Access.h"

ESPDataAccess::ESPDataAccess() {}

boolean ESPDataAccess::begin(void) {
  _initialized = LITTLEFS.begin(true);
#ifdef DEBUG
  Serial << endl
         << F("INFO: File system: ")
         << (_initialized ? F("mounted") : F("not mounted"));
#endif
  return _initialized;
}

boolean ESPDataAccess::formatFileSystem() {
#ifdef DEBUG
  Serial << endl << "INFO: Formatig File System";
#endif
  return LITTLEFS.format();
}

void ESPDataAccess::createDefaultConfiguration(void) {
#ifdef DEBUG
  Serial << endl << "INFO: Creating default configuration";
  Serial << endl << "INFO: Creating device configuration";
#endif
  createDeviceConfigurationFile();
#ifdef DEBUG
  Serial << endl << "INFO: Creating network configuration";
#endif
  createNetworkConfigurationFile();

#ifdef DEBUG
  Serial << endl << "INFO: Saving device mode";
#endif
  saveDeviceMode(ESP_MODE_NETWORK_NOT_SET);

#ifdef ESP_CONFIG_HARDWARE_I2C
#ifdef DEBUG
  Serial << endl << "INFO: Creating I2C configuration";
#endif
  createI2CConfigurationFile();
#endif // ESP_CONFIG_HARDWARE_I2C

#ifdef ESP_CONFIG_HARDWARE_UART
#ifdef DEBUG
  Serial << endl << "INFO: Creating UART configuration";
#endif
  createUARTConfigurationFile();
#endif // ESP_CONFIG_HARDWARE_UART

#ifdef ESP_CONFIG_HARDWARE_LED
#ifdef DEBUG
  Serial << endl << "INFO: Creating LEDs configuration";
#endif
  createLEDConfigurationFile();
#ifdef DEBUG
  Serial << endl << "INFO: Creating System LED configuration";
#endif
  saveSystemLEDId(0);
#endif // ESP_CONFIG_HARDWARE_LED

#ifdef ESP_CONFIG_HARDWARE_SWITCH
#ifdef DEBUG
  Serial << endl << "INFO: Creating Switches configuration";
#endif
  createSwitchConfigurationFile();
#endif // ESP_CONFIG_HARDWARE_SWITCH

#ifdef ESP_CONFIG_HARDWARE_ADC
#ifdef DEBUG
  Serial << endl << "INFO: Creating ADC configuration";
#endif
  createADCConfigurationFile();
#endif // ESP_CONFIG_HARDWARE_ADC
}

boolean ESPDataAccess::fileExist(const char *path) {
  return LITTLEFS.exists(path);
}

void ESPDataAccess::get(DEVICE &data) {

#ifdef DEBUG
  Serial << endl
         << endl
         << "INFO: Opening file: " << ESP_FILE_DEVICE_CONFIGURATION << " ... ";
#endif

  File configFile = LITTLEFS.open(ESP_FILE_DEVICE_CONFIGURATION, "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: JSON: ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<ESP_CONFIG_FILE_BUFFER_DEVICE> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif
      sprintf(data.name, root["name"]);

#ifdef ESP_CONFIG_HARDWARE_LED
      data.noOfLEDs = root["noOfLEDs"] | ESP_CONFIG_HARDWARE_LED_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_SWITCH
      data.noOfSwitches =
          root["noOfSwitches"] | ESP_CONFIG_HARDWARE_SWITCH_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_ADC
      data.noOfADCs = root["noOfADCs"] | ESP_CONFIG_HARDWARE_ADC_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_I2C
      data.noOfI2Cs = root["noOfI2Cs"] | ESP_CONFIG_HARDWARE_I2C_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_UART
      data.noOfUARTs =
          root["noOfUARTs"] | ESP_CONFIG_HARDWARE_UART_DEFAULT_NUMBER;
#endif

#ifdef DEBUG
      Serial << endl
             << "INFO: JSON: Buffer size: " << ESP_CONFIG_FILE_BUFFER_DEVICE
             << ", actual JSON size: " << jsonBuffer.size();
      if (ESP_CONFIG_FILE_BUFFER_DEVICE < jsonBuffer.size() + 10) {
        Serial << endl << "WARN: Too small buffer size";
      }
#endif
    }
#ifdef DEBUG
    else {
      Serial << "ERROR: JSON not pharsed";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << endl
           << "ERROR: Configuration file: " << ESP_FILE_DEVICE_CONFIGURATION
           << " not opened";
  }
#endif
}
void ESPDataAccess::save(DEVICE *data) {

#ifdef DEBUG
  Serial << endl
         << endl
         << "INFO: Opening file: " << ESP_FILE_DEVICE_CONFIGURATION << " ... ";
#endif

  File configFile = LITTLEFS.open(ESP_FILE_DEVICE_CONFIGURATION, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: Writing JSON: ";
#endif

    StaticJsonBuffer<ESP_CONFIG_FILE_BUFFER_DEVICE> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["name"] = data->name;
#ifdef ESP_CONFIG_HARDWARE_LED
    root["noOfLEDs"] = data->noOfLEDs;
#endif
#ifdef ESP_CONFIG_HARDWARE_SWITCH
    root["noOfSwitches"] = data->noOfSwitches;
#endif
#ifdef ESP_CONFIG_HARDWARE_ADC
    root["noOfADCs"] = data->noOfADCs;
#endif
#ifdef ESP_CONFIG_HARDWARE_I2C
    root["noOfI2Cs"] = data->noOfI2Cs;
#endif
#ifdef ESP_CONFIG_HARDWARE_UART
    root["noOfUARTs"] = data->noOfUARTs;
#endif

    root.printTo(configFile);

#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "INFO: Data saved" << endl
           << "INFO: JSON: Buffer size: " << ESP_CONFIG_FILE_BUFFER_DEVICE
           << ", actual JSON size: " << jsonBuffer.size();
    if (ESP_CONFIG_FILE_BUFFER_DEVICE < jsonBuffer.size() + 10) {
      Serial << endl << "WARN: Too small buffer size";
    }
#endif
  }
#ifdef DEBUG
  else {
    Serial << endl
           << "ERROR: failed to open file: " << ESP_FILE_DEVICE_CONFIGURATION;
  }
#endif
}

void ESPDataAccess::createDeviceConfigurationFile() {
#ifdef DEBUG
  Serial << endl << "INFO: Creating file: " << ESP_FILE_DEVICE_CONFIGURATION;
#endif
  DEVICE data;
  sprintf(data.name, ESP_HOSTNAME);
#ifdef ESP_CONFIG_HARDWARE_LED
  data.noOfLEDs = ESP_CONFIG_HARDWARE_LED_DEFAULT_NUMBER;
#endif
#ifdef ESP_CONFIG_HARDWARE_SWITCH
  data.noOfSwitches = ESP_CONFIG_HARDWARE_SWITCH_DEFAULT_NUMBER;
#endif
#ifdef ESP_CONFIG_HARDWARE_ADC
  data.noOfADCs = ESP_CONFIG_HARDWARE_ADC_DEFAULT_NUMBER;
#endif
#ifdef ESP_CONFIG_HARDWARE_I2C
  data.noOfI2Cs = ESP_CONFIG_HARDWARE_I2C_DEFAULT_NUMBER;
#endif
#ifdef ESP_CONFIG_HARDWARE_UART
  data.noOfUARTs = ESP_CONFIG_HARDWARE_UART_DEFAULT_NUMBER;
#endif

  save(&data);
}

uint8_t ESPDataAccess::getDeviceMode() {
  uint8_t mode = ESP_MODE_FIRST_TIME_LAUNCH;
#ifdef DEBUG
  Serial << endl
         << endl
         << "INFO: Opening file: " << ESP_FILE_DEVICE_MODE << " ... ";
#endif

  File configFile = LITTLEFS.open(ESP_FILE_DEVICE_MODE, "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: JSON: ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<ESP_CONFIG_FILE_BUFFER_DEVICE_MODE> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif
      mode = root["mode"];
#ifdef DEBUG
      Serial << endl
             << "INFO: JSON: Buffer size: "
             << ESP_CONFIG_FILE_BUFFER_DEVICE_MODE
             << ", actual JSON size: " << jsonBuffer.size();
      if (ESP_CONFIG_FILE_BUFFER_DEVICE_MODE < jsonBuffer.size() + 10) {
        Serial << endl << "WARN: Too small buffer size";
      }
#endif
    }
#ifdef DEBUG
    else {
      Serial << "ERROR: JSON not pharsed";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << endl
           << "ERROR: Configuration file: " << ESP_FILE_DEVICE_MODE
           << " not opened";
  }
#endif
  return mode;
}

void ESPDataAccess::saveDeviceMode(uint8_t mode) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "INFO: Opening file: " << ESP_FILE_DEVICE_MODE << " ... ";
#endif

  File configFile = LITTLEFS.open(ESP_FILE_DEVICE_MODE, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: Writing JSON: ";
#endif

    StaticJsonBuffer<ESP_CONFIG_FILE_BUFFER_DEVICE_MODE> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["mode"] = mode;
    root.printTo(configFile);

#ifdef DEBUG
    Serial << endl
           << "INFO: Data saved" << endl
           << "INFO: JSON: Buffer size: " << ESP_CONFIG_FILE_BUFFER_DEVICE_MODE
           << ", actual JSON size: " << jsonBuffer.size();
    if (ESP_CONFIG_FILE_BUFFER_DEVICE_MODE < jsonBuffer.size() + 10) {
      Serial << endl << "WARN: Too small buffer size";
    }
#endif
  }
#ifdef DEBUG
  else {
    Serial << endl << "ERROR: failed to open file: " << ESP_FILE_DEVICE_MODE;
  }
#endif
}

IPAddress ESPDataAccess::IPfromString(const char *address) {
  IPAddress ip;
  if (!ip.fromString(address)) {
#ifdef DEBUG
    Serial << endl
           << "ERROR: converting from IP String (" << address
           << ") to IP address";
#endif
  };
  return ip;
}

void ESPDataAccess::get(NETWORK &data) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "INFO: Opening file: " << ESP_FILE_NETWORK_CONFIGURATION << " ... ";
#endif

  File configFile = LITTLEFS.open(ESP_FILE_NETWORK_CONFIGURATION, "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: JSON: ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<ESP_CONFIG_FILE_BUFFER_NETWORK> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      sprintf(data.ssid, root["ssid"]);
      sprintf(data.password, root["password"]);

      data.isDHCP = root["isDHCP"];

      sprintf(data.ip, root["ip"]);
      sprintf(data.gateway, root["gateway"]);
      sprintf(data.subnet, root["subnet"]);

      data.noConnectionAttempts = root["noConnectionAttempts"];
      data.waitTimeConnections = root["waitTimeConnections"];
      data.waitTimeSeries = root["waitTimeSeries"];

#ifdef DEBUG
      Serial << endl
             << "INFO: JSON: Buffer size: " << ESP_CONFIG_FILE_BUFFER_NETWORK
             << ", actual JSON size: " << jsonBuffer.size();
      if (ESP_CONFIG_FILE_BUFFER_NETWORK < jsonBuffer.size() + 10) {
        Serial << endl << "WARN: Too small buffer size";
      }
#endif
    }
#ifdef DEBUG
    else {
      Serial << "ERROR: JSON not pharsed";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << endl
           << "ERROR: Configuration file: " << ESP_FILE_NETWORK_CONFIGURATION
           << " not opened";
  }
#endif
}

void ESPDataAccess::save(NETWORK *data) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "INFO: Opening file: " << ESP_FILE_NETWORK_CONFIGURATION << " ... ";
#endif

  File configFile = LITTLEFS.open(ESP_FILE_NETWORK_CONFIGURATION, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: Writing JSON: ";
#endif

    StaticJsonBuffer<ESP_CONFIG_FILE_BUFFER_NETWORK> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["ssid"] = data->ssid;
    root["password"] = data->password;
    root["isDHCP"] = data->isDHCP;
    root["ip"] = data->ip;
    root["gateway"] = data->gateway;
    root["subnet"] = data->subnet;

    root["noConnectionAttempts"] = data->noConnectionAttempts;
    root["waitTimeConnections"] = data->waitTimeConnections;
    root["waitTimeSeries"] = data->waitTimeSeries;

    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "INFO: Data saved" << endl
           << "INFO: JSON: Buffer size: " << ESP_CONFIG_FILE_BUFFER_NETWORK
           << ", actual JSON size: " << jsonBuffer.size();
    if (ESP_CONFIG_FILE_BUFFER_NETWORK < jsonBuffer.size() + 10) {
      Serial << endl << "WARN: Too small buffer size";
    }
#endif
  }
#ifdef DEBUG
  else {
    Serial << endl
           << "ERROR: failed to open file: " << ESP_FILE_NETWORK_CONFIGURATION;
  }
#endif
}
void ESPDataAccess::createNetworkConfigurationFile() {
#ifdef DEBUG
  Serial << endl << "INFO: Creating file: " << ESP_FILE_NETWORK_CONFIGURATION;
#endif

  NETWORK data;
  data.ssid[0] = ESP_EMPTY_STRING;
  data.password[0] = ESP_EMPTY_STRING;
  data.isDHCP = ESP_CONFIG_NETWORK_DCHP;
  data.ip[0] = ESP_EMPTY_STRING;
  data.gateway[0] = ESP_EMPTY_STRING;
  data.subnet[0] = ESP_EMPTY_STRING;
  data.noConnectionAttempts = ESP_CONFIG_NETWORK_CONNECTION_ATTEMPTS;
  data.waitTimeConnections =
      ESP_CONFIG_NETWORK_TIME_BETWEEN_CONNECTION_ATTEMPTS;
  data.waitTimeSeries =
      ESP_CONFIG_NETWORK_SLEEP_TIME_BETWEEN_FAILED_CONNECTION_ATTEMPTS;
  save(&data);
}

/******** I2C *************************/
#ifdef ESP_CONFIG_HARDWARE_I2C
void ESPDataAccess::get(uint8_t id, I2CBUS &data) {
  char fileName[16];
  sprintf(fileName, ESP_CONFIG_HARDWARE_I2C_FILE_NAME, id);

#ifdef DEBUG
  Serial << endl << endl << "INFO: Opening file: " << fileName << " ... ";
#endif

  File configFile = LITTLEFS.open(fileName, "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: JSON: ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<ESP_CONFIG_HARDWARE_I2C_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      data.SCL = root["SCL"];
      data.SDA = root["SDA"];
      data.frequency = root["frequency"];

#ifdef DEBUG
      Serial << endl
             << "INFO: JSON: Buffer size: "
             << ESP_CONFIG_HARDWARE_I2C_FILE_BUFFER
             << ", actual JSON size: " << jsonBuffer.size();
      if (ESP_CONFIG_HARDWARE_I2C_FILE_BUFFER < jsonBuffer.size() + 10) {
        Serial << endl << "WARN: Too small buffer size";
      }
#endif
    }
#ifdef DEBUG
    else {
      Serial << "ERROR: JSON not pharsed";
    }
#endif
    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << endl
           << "ERROR: Configuration file: " << fileName << " not opened";
  }
#endif
}

void ESPDataAccess::save(uint8_t id, I2CBUS *data) {
  char fileName[16];
  sprintf(fileName, ESP_CONFIG_HARDWARE_I2C_FILE_NAME, id);

#ifdef DEBUG
  Serial << endl << endl << "INFO: Opening file: " << fileName << " ... ";
#endif

  File configFile = LITTLEFS.open(fileName, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: Writing JSON: ";
#endif

    StaticJsonBuffer<ESP_CONFIG_HARDWARE_I2C_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["SDA"] = data->SDA;
    root["SCL"] = data->SCL;
    root["frequency"] = data->frequency;

    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "INFO: Data saved" << endl
           << "INFO: JSON: Buffer size: " << ESP_CONFIG_HARDWARE_I2C_FILE_BUFFER
           << ", actual JSON size: " << jsonBuffer.size();
    if (ESP_CONFIG_HARDWARE_I2C_FILE_BUFFER < jsonBuffer.size() + 10) {
      Serial << endl << "WARN: Too small buffer size";
    }
#endif
  }
#ifdef DEBUG
  else {
    Serial << endl << F("ERROR: failed to open file: ") << fileName;
  }
#endif
}

void ESPDataAccess::createI2CConfigurationFile() {
#ifdef DEBUG
  Serial << endl << F("INFO: Creating I2C configuration files");
#endif
  I2CBUS data;
  data.frequency = ESP_CONFIG_HARDWARE_I2C_DEFAULT_FREQUENCY;
  data.SDA = ESP_CONFIG_HARDWARE_I2C_1_DEFAULT_SDA;
  data.SCL = ESP_CONFIG_HARDWARE_I2C_1_DEFAULT_SCL;
  save(0, &data);
  data.SDA = ESP_CONFIG_HARDWARE_I2C_2_DEFAULT_SDA;
  data.SCL = ESP_CONFIG_HARDWARE_I2C_2_DEFAULT_SCL;
  save(1, &data);
}
#endif // ESP_CONFIG_HARDWARE_I2C

/******** UART *************************/
#ifdef ESP_CONFIG_HARDWARE_UART
void ESPDataAccess::get(uint8_t id, UARTBUS &data) {
  char fileName[16];
  sprintf(fileName, ESP_CONFIG_HARDWARE_UART_FILE_NAME, id);

#ifdef DEBUG
  Serial << endl << endl << "INFO: Opening file: " << fileName << " ... ";
#endif

  File configFile = LITTLEFS.open(fileName, "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: JSON: ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<ESP_CONFIG_HARDWARE_UART_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif
      data.RXD = root["RXD"];
      data.TXD = root["TXD"];
#ifdef DEBUG
      Serial << endl
             << "INFO: JSON: Buffer size: "
             << ESP_CONFIG_HARDWARE_UART_FILE_BUFFER
             << ", actual JSON size: " << jsonBuffer.size();
      if (ESP_CONFIG_HARDWARE_UART_FILE_BUFFER < jsonBuffer.size() + 10) {
        Serial << endl << "WARN: Too small buffer size";
      }
#endif
    }
#ifdef DEBUG
    else {
      Serial << "ERROR: JSON not pharsed";
    }
#endif
    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << endl
           << "ERROR: Configuration file: " << fileName << " not opened";
  }
#endif
}

void ESPDataAccess::save(uint8_t id, UARTBUS *data) {
  char fileName[17];
  sprintf(fileName, ESP_CONFIG_HARDWARE_UART_FILE_NAME, id);

#ifdef DEBUG
  Serial << endl << endl << "INFO: Opening file: " << fileName << " ... ";
#endif

  File configFile = LITTLEFS.open(fileName, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: Writing JSON: ";
#endif

    StaticJsonBuffer<ESP_CONFIG_HARDWARE_UART_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["RXD"] = data->RXD;
    root["TXD"] = data->TXD;
    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "INFO: Data saved" << endl
           << "INFO: JSON: Buffer size: "
           << ESP_CONFIG_HARDWARE_UART_FILE_BUFFER
           << ", actual JSON size: " << jsonBuffer.size();
    if (ESP_CONFIG_HARDWARE_UART_FILE_BUFFER < jsonBuffer.size() + 10) {
      Serial << endl << "WARN: Too small buffer size";
    }
#endif
  }
#ifdef DEBUG
  else {
    Serial << endl << F("ERROR: failed to open file: ") << fileName;
  }
#endif
}

void ESPDataAccess::createUARTConfigurationFile() {
#ifdef DEBUG
  Serial << endl << F("INFO: Creating UART configuration files");
#endif
  UARTBUS data;
  data.RXD = ESP_CONFIG_HARDWARE_UART_1_RXD;
  data.TXD = ESP_CONFIG_HARDWARE_UART_1_TXD;
  save(0, &data);
  data.RXD = ESP_CONFIG_HARDWARE_UART_2_RXD;
  data.TXD = ESP_CONFIG_HARDWARE_UART_2_TXD;
  save(1, &data);
  data.RXD = ESP_CONFIG_HARDWARE_UART_3_RXD;
  data.TXD = ESP_CONFIG_HARDWARE_UART_3_TXD;
  save(2, &data);
}
#endif // ESP_CONFIG_HARDWARE_UART

/******** LED *************************/
#ifdef ESP_CONFIG_HARDWARE_LED
void ESPDataAccess::get(uint8_t id, LED &data) {
  char fileName[16];
  sprintf(fileName, ESP_CONFIG_HARDWARE_LED_FILE_NAME, id);

#ifdef DEBUG
  Serial << endl << endl << "INFO: Opening file: " << fileName << " ... ";
#endif

  File configFile = LITTLEFS.open(fileName, "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: JSON: ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<ESP_CONFIG_HARDWARE_LED_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      data.gpio = root["gpio"];
      data.reverseState = root["reverseState"];

#ifdef DEBUG
      Serial << endl
             << "INFO: JSON: Buffer size: "
             << ESP_CONFIG_HARDWARE_LED_FILE_BUFFER
             << ", actual JSON size: " << jsonBuffer.size();
      if (ESP_CONFIG_HARDWARE_LED_FILE_BUFFER < jsonBuffer.size() + 10) {
        Serial << endl << "WARN: Too small buffer size";
      }
#endif
    }
#ifdef DEBUG
    else {
      Serial << "ERROR: JSON not pharsed";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << endl
           << "ERROR: Configuration file: " << fileName << " not opened";
  }
#endif
}

void ESPDataAccess::save(uint8_t id, LED *data) {
  char fileName[16];
  sprintf(fileName, ESP_CONFIG_HARDWARE_LED_FILE_NAME, id);

#ifdef DEBUG
  Serial << endl << endl << "INFO: Opening file: " << fileName << " ... ";
#endif

  File configFile = LITTLEFS.open(fileName, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: Writing JSON: ";
#endif

    StaticJsonBuffer<ESP_CONFIG_HARDWARE_LED_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["gpio"] = data->gpio;
    root["reverseState"] = data->reverseState;

    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "INFO: Data saved" << endl
           << "INFO: JSON: Buffer size: " << ESP_CONFIG_HARDWARE_LED_FILE_BUFFER
           << ", actual JSON size: " << jsonBuffer.size();
    if (ESP_CONFIG_HARDWARE_LED_FILE_BUFFER < jsonBuffer.size() + 10) {
      Serial << endl << "WARN: Too small buffer size";
    }
#endif
  }
#ifdef DEBUG
  else {
    Serial << endl << F("ERROR: failed to open file: ") << fileName;
  }
#endif
}

void ESPDataAccess::createLEDConfigurationFile() {
#ifdef DEBUG
  Serial << endl << F("INFO: Creating LEDs configuration files");
#endif

  LED data;
  data.gpio = ESP_CONFIG_HARDWARE_LED_DEFAULT_GPIO;
  data.reverseState = ESP_CONFIG_HARDWARE_LED_DEFAULT_REVERSE;
  save(0, &data);
  data.gpio = ESP_HARDWARE_ITEM_NOT_EXIST;
  for (uint8_t i = 1; i < ESP_CONFIG_HARDWARE_LED_MAX_NUMBER; i++) {
    save(i, &data);
  }
}

uint8_t ESPDataAccess::getSystemLEDId(void) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "INFO: Opening file: " << ESP_CONFIG_HARDWARE_SYSTEM_LED_FILE_NAME
         << " ... ";
#endif

  uint8_t _ret = ESP_HARDWARE_ITEM_NOT_EXIST;

  File configFile =
      LITTLEFS.open(ESP_CONFIG_HARDWARE_SYSTEM_LED_FILE_NAME, "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: JSON: ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<ESP_CONFIG_HARDWARE_SYSTEM_LED_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      _ret = root["id"];

#ifdef DEBUG
      Serial << endl
             << "INFO: JSON: Buffer size: "
             << ESP_CONFIG_HARDWARE_SYSTEM_LED_FILE_BUFFER
             << ", actual JSON size: " << jsonBuffer.size();
      if (ESP_CONFIG_HARDWARE_SYSTEM_LED_FILE_BUFFER < jsonBuffer.size() + 10) {
        Serial << endl << "WARN: Too small buffer size";
      }
#endif
    }
#ifdef DEBUG
    else {
      Serial << "ERROR: JSON not pharsed";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << endl
           << "ERROR: Configuration file: "
           << ESP_CONFIG_HARDWARE_SYSTEM_LED_FILE_NAME << " not opened";
  }
#endif
  return _ret;
}

void ESPDataAccess::saveSystemLEDId(uint8_t id) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "INFO: Opening file: " << ESP_CONFIG_HARDWARE_SYSTEM_LED_FILE_NAME
         << " ... ";
#endif

  File configFile =
      LITTLEFS.open(ESP_CONFIG_HARDWARE_SYSTEM_LED_FILE_NAME, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: Writing JSON: ";
#endif

    StaticJsonBuffer<ESP_CONFIG_HARDWARE_SYSTEM_LED_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["id"] = id;
    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "INFO: Data saved" << endl
           << "INFO: JSON: Buffer size: "
           << ESP_CONFIG_HARDWARE_SYSTEM_LED_FILE_BUFFER
           << ", actual JSON size: " << jsonBuffer.size();
    if (ESP_CONFIG_HARDWARE_SYSTEM_LED_FILE_BUFFER < jsonBuffer.size() + 10) {
      Serial << endl << "WARN: Too small buffer size";
    }
#endif
  }
#ifdef DEBUG
  else {
    Serial << endl
           << F("ERROR: failed to open file: ")
           << ESP_CONFIG_HARDWARE_SYSTEM_LED_FILE_NAME;
  }
#endif
}
#endif // ESP_CONFIG_HARDWARE_LED

/******** SWITCH *************************/
#ifdef ESP_CONFIG_HARDWARE_SWITCH
void ESPDataAccess::get(uint8_t id, SWITCH &data) {
  char fileName[19];
  sprintf(fileName, ESP_CONFIG_HARDWARE_SWITCH_FILE_NAME, id);

#ifdef DEBUG
  Serial << endl << endl << "INFO: Opening file: " << fileName << " ... ";
#endif

  File configFile = LITTLEFS.open(fileName, "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: JSON: ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<ESP_CONFIG_HARDWARE_SWITCH_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      data.gpio = root["gpio"];
      data.bouncing = root["bouncing"];
      data.functionality = root["functionality"];
      data.type = root["type"];
      data.pinMode = root["pinMode"];

#ifdef DEBUG
      Serial << endl
             << "INFO: JSON: Buffer size: "
             << ESP_CONFIG_HARDWARE_SWITCH_FILE_BUFFER
             << ", actual JSON size: " << jsonBuffer.size();
      if (ESP_CONFIG_HARDWARE_SWITCH_FILE_BUFFER < jsonBuffer.size() + 10) {
        Serial << endl << "WARN: Too small buffer size";
      }
#endif
    }
#ifdef DEBUG
    else {
      Serial << "ERROR: JSON not pharsed";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << endl
           << "ERROR: Configuration file: " << fileName << " not opened";
  }
#endif
}

void ESPDataAccess::save(uint8_t id, SWITCH *data) {
  char fileName[19];
  sprintf(fileName, ESP_CONFIG_HARDWARE_SWITCH_FILE_NAME, id);

#ifdef DEBUG
  Serial << endl << endl << "INFO: Opening file: " << fileName << " ... ";
#endif

  File configFile = LITTLEFS.open(fileName, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: Writing JSON: ";
#endif

    StaticJsonBuffer<ESP_CONFIG_HARDWARE_SWITCH_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["gpio"] = data->gpio;
    root["bouncing"] = data->bouncing;
    root["type"] = data->type;
    root["functionality"] = data->functionality;
    root["pinMode"] = data->pinMode;

    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "INFO: Data saved" << endl
           << "INFO: JSON: Buffer size: "
           << ESP_CONFIG_HARDWARE_SWITCH_FILE_BUFFER
           << ", actual JSON size: " << jsonBuffer.size();
    if (ESP_CONFIG_HARDWARE_SWITCH_FILE_BUFFER < jsonBuffer.size() + 10) {
      Serial << endl << "WARN: Too small buffer size";
    }
#endif
  }
#ifdef DEBUG
  else {
    Serial << endl << F("ERROR: failed to open file: ") << fileName;
  }
#endif
}

void ESPDataAccess::createSwitchConfigurationFile() {
#ifdef DEBUG
  Serial << endl << F("INFO: Creating Switches configuration files");
#endif

  SWITCH data;
  data.gpio = ESP_CONFIG_HARDWARE_SWITCH_DEFAULT_GPIO;
  data.bouncing = ESP_CONFIG_HARDWARE_SWITCH_DEFAULT_BOUNCING;
  data.type = ESP_CONFIG_HARDWARE_SWITCH_DEFAULT_TYPE;
  data.functionality = ESP_CONFIG_HARDWARE_SWITCH_DEFAULT_FUNCTIONALITY;
  data.pinMode = ESP_CONFIG_HARDWARE_SWITCH_DEFAULT_PIN_MODE;
  save(0, &data);
  data.gpio = ESP_HARDWARE_ITEM_NOT_EXIST;
  for (uint8_t i = 1; i < ESP_CONFIG_HARDWARE_SWITCH_MAX_NUMBER; i++) {
    save(i, &data);
  }
}
#endif // ESP_CONFIG_HARDWARE_SWITCH

/******** ADC *************************/
#ifdef ESP_CONFIG_HARDWARE_ADC
void ESPDataAccess::get(uint8_t id, ADC &data) {
  char fileName[16];
  sprintf(fileName, ESP_CONFIG_HARDWARE_ADC_FILE_NAME, id);

#ifdef DEBUG
  Serial << endl << endl << "INFO: Opening file: " << fileName << " ... ";
#endif

  File configFile = LITTLEFS.open(fileName, "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: JSON: ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<ESP_CONFIG_HARDWARE_ADC_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      data.gpio = root["gpio"];
      data.interval = root["interval"];
      data.maxVCC = root["maxVCC"];
      data.numberOfSamples = root["numberOfSamples"];
      data.resolution = root["resolution"];
      data.divider.Ra = root["divider"]["Ra"];
      data.divider.Rb = root["divider"]["Rb"];
#ifdef ESP_CONFIG_HARDWARE_ADS1115
      data.i2c.id = root["i2c"]["id"];
      data.i2c.inputId = root["i2c"]["inputId"];
      data.i2c.address = root["i2c"]["address"];
      data.i2c.gain = root["i2c"]["gain"];
      data.i2c.samplesPerSecond = root["i2c"]["samplesPerSecond"];
#endif
#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
      data.battery.minVoltage = root["battery"]["minVoltage"];
      data.battery.maxVoltage = root["battery"]["maxVoltage"];
#endif

#ifdef DEBUG
      Serial << endl
             << "INFO: JSON: Buffer size: "
             << ESP_CONFIG_HARDWARE_ADC_FILE_BUFFER
             << ", actual JSON size: " << jsonBuffer.size();
      if (ESP_CONFIG_HARDWARE_ADC_FILE_BUFFER < jsonBuffer.size() + 10) {
        Serial << endl << "WARN: Too small buffer size";
      }
#endif
    }
#ifdef DEBUG
    else {
      Serial << "ERROR: JSON not pharsed";
    }
#endif
    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << endl
           << "ERROR: Configuration file: " << fileName << " not opened";
  }
#endif
}

void ESPDataAccess::save(uint8_t id, ADC *data) {
  char fileName[16];
  sprintf(fileName, ESP_CONFIG_HARDWARE_ADC_FILE_NAME, id);

#ifdef DEBUG
  Serial << endl << endl << "INFO: Opening file: " << fileName << " ... ";
#endif

  File configFile = LITTLEFS.open(fileName, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: Writing JSON: ";
#endif

    StaticJsonBuffer<ESP_CONFIG_HARDWARE_ADC_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    JsonObject &divider = root.createNestedObject("divider");
#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
    JsonObject &battery = root.createNestedObject("battery");
#endif
#ifdef ESP_CONFIG_HARDWARE_ADS1115
    JsonObject &i2c = root.createNestedObject("i2c");
#endif
    root["gpio"] = data->gpio;
    root["interval"] = data->interval;
    root["maxVCC"] = data->maxVCC;
    root["numberOfSamples"] = data->numberOfSamples;
    root["resolution"] = data->resolution;
    divider["Ra"] = data->divider.Ra;
    divider["Rb"] = data->divider.Rb;
#ifdef ESP_CONFIG_HARDWARE_ADS1115
    i2c["id"] = data->i2c.id;
    i2c["inputId"] = data->i2c.inputId;
    i2c["address"] = data->i2c.address;
    i2c["gain"] = data->i2c.gain;
    i2c["samplesPerSecond"] = data->i2c.samplesPerSecond;
#endif
#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
    battery["minVoltage"] = data->battery.minVoltage;
    battery["maxVoltage"] = data->battery.maxVoltage;
#endif

    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "INFO: Data saved" << endl
           << "INFO: JSON: Buffer size: " << ESP_CONFIG_HARDWARE_ADC_FILE_BUFFER
           << ", actual JSON size: " << jsonBuffer.size();
    if (ESP_CONFIG_HARDWARE_ADC_FILE_BUFFER < jsonBuffer.size() + 10) {
      Serial << endl << "WARN: Too small buffer size";
    }
#endif
  }
#ifdef DEBUG
  else {
    Serial << endl << F("ERROR: failed to open file: ") << fileName;
  }
#endif
}

void ESPDataAccess::createADCConfigurationFile() {
#ifdef DEBUG
  Serial << endl << F("INFO: Creating ADC configuration files");
#endif
  ADC data;
  data.gpio = ESP_HARDWARE_ITEM_NOT_EXIST;
#ifdef ESP_CONFIG_HARDWARE_ADS1115
  data.i2c.id = ESP_HARDWARE_ITEM_NOT_EXIST;
  data.i2c.inputId = ESP_HARDWARE_ITEM_NOT_EXIST;
  data.i2c.address = ESP_HARDWARE_ITEM_NOT_EXIST;
  data.i2c.gain = ESP_CONFIG_HARDWARE_ADS1115_DEFAULT_GAIN;
  data.i2c.samplesPerSecond = ESP_CONFIG_HARDWARE_ADS1115_DEFAULT_SAMPLES;
#endif
  data.interval = ESP_CONFIG_HARDWARE_ADC_DEFAULT_INTERVAL;
  data.maxVCC = ESP_CONFIG_HARDWARE_ADC_DEFAULT_MAX_VCC;
  data.numberOfSamples = ESP_CONFIG_HARDWARE_ADC_DEFAULT_SAMPLES;
  data.resolution = ESP_CONFIG_HARDWARE_ADC_DEFAULT_RESOLUTION;
  data.divider.Ra = ESP_CONFIG_HARDWARE_ADC_DEFAULT_DIVIDER_RESISTOR;
  data.divider.Rb = ESP_CONFIG_HARDWARE_ADC_DEFAULT_DIVIDER_RESISTOR;
#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
  data.battery.maxVoltage = ESP_CONFIG_HARDWARE_ADC_DEFAULT_BATTERY_MAX_VOLTAGE;
  data.battery.minVoltage = ESP_CONFIG_HARDWARE_ADC_DEFAULT_BATTERY_MIN_VOLTAGE;
#endif
  for (uint8_t i = 0; i < ESP_CONFIG_HARDWARE_ADC_MAX_NUMBER; i++) {
    save(i, &data);
  }
}
#endif // ESP_CONFIG_HARDWARE_ADC

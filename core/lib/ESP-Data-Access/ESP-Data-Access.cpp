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

#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
#ifdef DEBUG
  Serial << endl << "INFO: Creating Binary sensor configuration";
#endif
  createBinarySensorConfigurationFile();
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
#ifdef DEBUG
  Serial << endl << "INFO: Creating DS18B20 sensor configuration";
#endif
  createDS18B20SensorConfigurationFile();
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
#ifdef DEBUG
  Serial << endl << "INFO: Creating NTC termistor configuration";
#endif
  createNTCSensorConfigurationFile();
#endif

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
#ifdef DEBUG
  Serial << endl << "INFO: Creating Batterymeter configuration";
#endif
  createBatterymeterConfigurationFile();
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
#ifdef DEBUG
  Serial << endl << "INFO: Creating ACS758 configuration";
#endif
  createACS758SensorConfigurationFile();
#endif

#ifdef ESP_CONFIG_API_MQTT
#ifdef DEBUG
  Serial << endl << "INFO: Creating MQTT Broker configuration";
#endif
  createMQTTBrokerConfigurationFile();
#endif
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

#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
      data.noOfBinarySensors = root["noOfBinarySensors"] |
                               ESP_CONFIG_HARDWARE_SENSOR_BINARY_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
      data.noOfDS18B20s = root["noOfDS18B20s"] |
                          ESP_CONFIG_HARDWARE_SENSOR_DS18B20_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
      data.noOfNTCs =
          root["noOfNTCs"] | ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
      data.noOfBatterymeters = root["noOfBatterymeters"] |
                               ESP_CONFIG_HARDWARE_BATTERYMETER_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
      data.noOfACS758s = root["noOfACS758s"] |
                         ESP_CONFIG_HARDWARE_SENSOR_ACS758_DEFAULT_NUMBER;
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
#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
    root["noOfBinarySensors"] = data->noOfBinarySensors;
#endif
#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
    root["noOfDS18B20s"] = data->noOfDS18B20s;
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
    root["noOfNTCs"] = data->noOfNTCs;
#endif

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
    root["noOfBatterymeters"] = data->noOfBatterymeters;
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
    root["noOfACS758s"] = data->noOfACS758s;
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
#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
  data.noOfBinarySensors = ESP_CONFIG_HARDWARE_SENSOR_BINARY_DEFAULT_NUMBER;
#endif
#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
  data.noOfDS18B20s = ESP_CONFIG_HARDWARE_SENSOR_DS18B20_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
  data.noOfNTCs = ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
  data.noOfBatterymeters = ESP_CONFIG_HARDWARE_BATTERYMETER_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
  data.noOfACS758s = ESP_CONFIG_HARDWARE_SENSOR_ACS758_DEFAULT_NUMBER;
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
      sprintf(data.ssidBackup, root["ssidBackup"]);
      sprintf(data.password, root["password"]);
      sprintf(data.passwordBackup, root["passwordBackup"]);

      data.isDHCP = root["isDHCP"];

      sprintf(data.ip, root["ip"]);
      sprintf(data.gateway, root["gateway"]);
      sprintf(data.subnet, root["subnet"]);

      data.noConnectionAttempts = root["noConnectionAttempts"];
      data.waitTimeConnections = root["waitTimeConnections"];
      data.waitTimeSeries = root["waitTimeSeries"];
      data.noFailuresToSwitchNetwork = root["noFailuresToSwitchNetwork"];

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
    root["ssidBackup"] = data->ssidBackup;
    root["password"] = data->password;
    root["passwordBackup"] = data->passwordBackup;
    root["isDHCP"] = data->isDHCP;
    root["ip"] = data->ip;
    root["gateway"] = data->gateway;
    root["subnet"] = data->subnet;
    root["noConnectionAttempts"] = data->noConnectionAttempts;
    root["waitTimeConnections"] = data->waitTimeConnections;
    root["waitTimeSeries"] = data->waitTimeSeries;
    root["noFailuresToSwitchNetwork"] = data->noFailuresToSwitchNetwork;

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
  sprintf(data.ssid, "%s", ESP_CONFIG_NETWORK_DEFAULT_NONE_SSID);
  sprintf(data.ssidBackup, "%s", ESP_CONFIG_NETWORK_DEFAULT_NONE_SSID);
  data.password[0] = ESP_EMPTY_STRING;
  data.passwordBackup[0] = ESP_EMPTY_STRING;
  data.isDHCP = ESP_CONFIG_NETWORK_DCHP;
  data.ip[0] = ESP_EMPTY_STRING;
  data.gateway[0] = ESP_EMPTY_STRING;
  data.subnet[0] = ESP_EMPTY_STRING;
  data.noConnectionAttempts = ESP_CONFIG_NETWORK_CONNECTION_ATTEMPTS;
  data.waitTimeConnections =
      ESP_CONFIG_NETWORK_TIME_BETWEEN_CONNECTION_ATTEMPTS;
  data.waitTimeSeries =
      ESP_CONFIG_NETWORK_SLEEP_TIME_BETWEEN_FAILED_CONNECTION_ATTEMPTS;
  data.noFailuresToSwitchNetwork =
      ESP_CONFIG_NETWORK_DEFAULT_SWITCH_NETWORK_AFTER;
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
  for (uint8_t i = 0; i < ESP_CONFIG_HARDWARE_ADC_MAX_NUMBER; i++) {
    save(i, &data);
  }
}
#endif // ESP_CONFIG_HARDWARE_ADC

/******** Binary Sensor *************************/
#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
void ESPDataAccess::get(uint8_t id, BINARY_SENSOR &data) {
  char fileName[26];
  sprintf(fileName, ESP_CONFIG_HARDWARE_SENSOR_BINARY_FILE_NAME, id);

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
    StaticJsonBuffer<ESP_CONFIG_HARDWARE_SENSOR_BINARY_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      data.gpio = root["gpio"];
      data.interval = root["interval"];
      data.bouncing = root["bouncing"];

#ifdef DEBUG
      Serial << endl
             << "INFO: JSON: Buffer size: "
             << ESP_CONFIG_HARDWARE_SENSOR_BINARY_FILE_BUFFER
             << ", actual JSON size: " << jsonBuffer.size();
      if (ESP_CONFIG_HARDWARE_SENSOR_BINARY_FILE_BUFFER <
          jsonBuffer.size() + 10) {
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

void ESPDataAccess::save(uint8_t id, BINARY_SENSOR *data) {
  char fileName[26];
  sprintf(fileName, ESP_CONFIG_HARDWARE_SENSOR_BINARY_FILE_NAME, id);

#ifdef DEBUG
  Serial << endl << endl << "INFO: Opening file: " << fileName << " ... ";
#endif

  File configFile = LITTLEFS.open(fileName, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: Writing JSON: ";
#endif

    StaticJsonBuffer<ESP_CONFIG_HARDWARE_SENSOR_BINARY_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["gpio"] = data->gpio;
    root["interval"] = data->interval;
    root["bouncing"] = data->bouncing;
    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "INFO: Data saved" << endl
           << "INFO: JSON: Buffer size: "
           << ESP_CONFIG_HARDWARE_SENSOR_BINARY_FILE_BUFFER
           << ", actual JSON size: " << jsonBuffer.size();
    if (ESP_CONFIG_HARDWARE_SENSOR_BINARY_FILE_BUFFER <
        jsonBuffer.size() + 10) {
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

void ESPDataAccess::createBinarySensorConfigurationFile() {
#ifdef DEBUG
  Serial << endl << F("INFO: Creating Binary sensor configuration files");
#endif
  BINARY_SENSOR data;
  data.gpio = ESP_HARDWARE_ITEM_NOT_EXIST;
  data.bouncing = ESP_CONFIG_HARDWARE_SENSOR_BINARY_DEFAULT_BOUNCING;
  data.interval = ESP_CONFIG_HARDWARE_SENSOR_BINARY_DEFAULT_INTERVAL;
  for (uint8_t i = 0; i < ESP_CONFIG_HARDWARE_SENSOR_BINARY_MAX_NUMBER; i++) {
    save(i, &data);
  }
}
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
void ESPDataAccess::get(uint8_t id, DS18B20_SENSOR &data) {
  char fileName[27];
  sprintf(fileName, ESP_CONFIG_HARDWARE_SENSOR_DS18B20_FILE_NAME, id);

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
    StaticJsonBuffer<ESP_CONFIG_HARDWARE_SENSOR_DS18B20_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      data.gpio = root["gpio"];
      data.interval = root["interval"];
      data.correction = root["correction"];
      data.unit = root["unit"];
      data.resolution = root["resolution"];

      for (uint8_t i = 0; i < ESP_CONFIG_HARDWARE_SENSOR_DS18B20_ADDRESS_LENGTH;
           i++) {
        data.address[i] = root["address"][i].as<int>();
      }

#ifdef DEBUG
      Serial << endl
             << "INFO: JSON: Buffer size: "
             << ESP_CONFIG_HARDWARE_SENSOR_DS18B20_FILE_BUFFER
             << ", actual JSON size: " << jsonBuffer.size();
      if (ESP_CONFIG_HARDWARE_SENSOR_DS18B20_FILE_BUFFER <
          jsonBuffer.size() + 10) {
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

void ESPDataAccess::save(uint8_t id, DS18B20_SENSOR *data) {
  char fileName[27];
  sprintf(fileName, ESP_CONFIG_HARDWARE_SENSOR_DS18B20_FILE_NAME, id);

#ifdef DEBUG
  Serial << endl << endl << "INFO: Opening file: " << fileName << " ... ";
#endif

  File configFile = LITTLEFS.open(fileName, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: Writing JSON: ";
#endif

    StaticJsonBuffer<ESP_CONFIG_HARDWARE_SENSOR_DS18B20_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    JsonArray &address = jsonBuffer.createArray();
    root["gpio"] = data->gpio;
    root["interval"] = data->interval;
    root["correction"] = data->correction;
    root["unit"] = data->unit;
    root["resolution"] = data->resolution;
    address.copyFrom(data->address);
    root["address"] = address;
    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "INFO: Data saved" << endl
           << "INFO: JSON: Buffer size: "
           << ESP_CONFIG_HARDWARE_SENSOR_DS18B20_FILE_BUFFER
           << ", actual JSON size: " << jsonBuffer.size();
    if (ESP_CONFIG_HARDWARE_SENSOR_DS18B20_FILE_BUFFER <
        jsonBuffer.size() + 10) {
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

void ESPDataAccess::createDS18B20SensorConfigurationFile() {
#ifdef DEBUG
  Serial << endl << F("INFO: Creating DS18B20 sensor configuration files");
#endif
  DS18B20_SENSOR data;
  data.gpio = ESP_HARDWARE_ITEM_NOT_EXIST;
  data.interval = ESP_CONFIG_HARDWARE_SENSOR_DS18B20_DEFAULT_INTERVAL;
  DeviceAddress _address = {0, 0, 0, 0, 0, 0, 0, 0};
  memcpy(&data.address[0], _address, sizeof(_address[0]) * 8);
  data.correction = ESP_CONFIG_HARDWARE_SENSOR_DS18B20_DEFAULT_CORRECTION;
  data.unit = ESP_CONFIG_HARDWARE_SENSOR_DS18B20_DEFAULT_UNIT;
  data.resolution = ESP_CONFIG_FUNCTIONALITY_TEMPERATURE_UNIT_CELSIUS;
  for (uint8_t i = 0; i < ESP_CONFIG_HARDWARE_SENSOR_DS18B20_MAX_NUMBER; i++) {
    save(i, &data);
  }
}
#endif // ESP_CONFIG_HARDWARE_SENSOR_DS18B20

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
void ESPDataAccess::get(uint8_t id, NTC_SENSOR &data) {
  char fileName[23];
  sprintf(fileName, ESP_CONFIG_HARDWARE_SENSOR_NTC_FILE_NAME, id);

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
    StaticJsonBuffer<ESP_CONFIG_HARDWARE_SENSOR_NTC_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      data.coefficients.A.value = root["coefficients"]["A"]["value"];

      Serial << endl
             << "data.coefficients.A.value = " << data.coefficients.A.value;

      data.coefficients.B.value = root["coefficients"]["B"]["value"];
      data.coefficients.C.value = root["coefficients"]["C"]["value"];
      data.coefficients.A.precision = root["coefficients"]["A"]["precision"];
      data.coefficients.B.precision = root["coefficients"]["B"]["precision"];
      data.coefficients.C.precision = root["coefficients"]["C"]["precision"];
      data.interval = root["interval"];
      data.correction = root["correction"];
      data.unit = root["unit"];
      data.resistor = root["resistor"];
      data.vcc = root["vcc"];
      data.adcInput = root["adcInput"];

#ifdef DEBUG
      Serial << endl
             << "INFO: JSON: Buffer size: "
             << ESP_CONFIG_HARDWARE_SENSOR_NTC_FILE_BUFFER
             << ", actual JSON size: " << jsonBuffer.size();
      if (ESP_CONFIG_HARDWARE_SENSOR_NTC_FILE_BUFFER < jsonBuffer.size() + 10) {
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

void ESPDataAccess::save(uint8_t id, NTC_SENSOR *data) {
  char fileName[23];
  sprintf(fileName, ESP_CONFIG_HARDWARE_SENSOR_NTC_FILE_NAME, id);

#ifdef DEBUG
  Serial << endl << endl << "INFO: Opening file: " << fileName << " ... ";
#endif

  File configFile = LITTLEFS.open(fileName, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: Writing JSON: ";
#endif

    StaticJsonBuffer<ESP_CONFIG_HARDWARE_SENSOR_NTC_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    JsonObject &coefficient = root.createNestedObject("coefficients");
    JsonObject &coefficientA = coefficient.createNestedObject("A");
    JsonObject &coefficientB = coefficient.createNestedObject("B");
    JsonObject &coefficientC = coefficient.createNestedObject("C");
    root["resistor"] = data->resistor;
    root["interval"] = data->interval;
    root["correction"] = data->correction;
    root["unit"] = data->unit;
    root["vcc"] = data->vcc;
    root["adcInput"] = data->adcInput;
    coefficientA["value"] = data->coefficients.A.value;
    coefficientA["precision"] = data->coefficients.A.precision;
    coefficientB["value"] = data->coefficients.B.value;
    coefficientB["precision"] = data->coefficients.B.precision;
    coefficientC["value"] = data->coefficients.C.value;
    coefficientC["precision"] = data->coefficients.C.precision;
    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "INFO: Data saved" << endl
           << "INFO: JSON: Buffer size: "
           << ESP_CONFIG_HARDWARE_SENSOR_NTC_FILE_BUFFER
           << ", actual JSON size: " << jsonBuffer.size();
    if (ESP_CONFIG_HARDWARE_SENSOR_NTC_FILE_BUFFER < jsonBuffer.size() + 10) {
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

void ESPDataAccess::createNTCSensorConfigurationFile() {
#ifdef DEBUG
  Serial << endl << F("INFO: Creating NTC sensor configuration files");
#endif
  NTC_SENSOR data;
  data.adcInput = ESP_HARDWARE_ITEM_NOT_EXIST;
  data.resistor = ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_RESISTOR;
  data.interval = ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_INTERVAL;
  data.correction = ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_CORRECTION;
  data.unit = ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_UNIT;
  data.vcc = ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_VCC;
  data.coefficients.A.value = ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_A;
  data.coefficients.A.precision = 0;
  data.coefficients.B.value = ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_B;
  data.coefficients.B.precision = 0;
  data.coefficients.C.value = ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_C;
  data.coefficients.C.precision = 0;
  for (uint8_t i = 0; i < ESP_CONFIG_HARDWARE_SENSOR_NTC_MAX_NUMBER; i++) {
    save(i, &data);
  }
}
#endif // ESP_CONFIG_HARDWARE_SENSOR_NTC

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
void ESPDataAccess::get(uint8_t id, BATTERYMETER &data) {
  char fileName[25];
  sprintf(fileName, ESP_CONFIG_HARDWARE_BATTERYMETER_FILE_NAME, id);

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
    StaticJsonBuffer<ESP_CONFIG_HARDWARE_BATTERYMETER_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      data.voltage.min = root["voltage"]["min"];
      data.voltage.max = root["voltage"]["max"];
      data.interval = root["interval"];
      data.adcInput = root["adcInput"];

#ifdef DEBUG
      Serial << endl
             << "INFO: JSON: Buffer size: "
             << ESP_CONFIG_HARDWARE_BATTERYMETER_FILE_BUFFER
             << ", actual JSON size: " << jsonBuffer.size();
      if (ESP_CONFIG_HARDWARE_BATTERYMETER_FILE_BUFFER <
          jsonBuffer.size() + 10) {
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

void ESPDataAccess::save(uint8_t id, BATTERYMETER *data) {
  char fileName[25];
  sprintf(fileName, ESP_CONFIG_HARDWARE_BATTERYMETER_FILE_NAME, id);

#ifdef DEBUG
  Serial << endl << endl << "INFO: Opening file: " << fileName << " ... ";
#endif

  File configFile = LITTLEFS.open(fileName, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: Writing JSON: ";
#endif

    StaticJsonBuffer<ESP_CONFIG_HARDWARE_BATTERYMETER_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    JsonObject &voltage = root.createNestedObject("voltage");
    root["interval"] = data->interval;
    root["adcInput"] = data->adcInput;
    voltage["min"] = data->voltage.min;
    voltage["max"] = data->voltage.max;
    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "INFO: Data saved" << endl
           << "INFO: JSON: Buffer size: "
           << ESP_CONFIG_HARDWARE_BATTERYMETER_FILE_BUFFER
           << ", actual JSON size: " << jsonBuffer.size();
    if (ESP_CONFIG_HARDWARE_BATTERYMETER_FILE_BUFFER < jsonBuffer.size() + 10) {
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

void ESPDataAccess::createBatterymeterConfigurationFile() {
#ifdef DEBUG
  Serial << endl << F("INFO: Creating NTC sensor configuration files");
#endif
  BATTERYMETER data;
  data.adcInput = ESP_HARDWARE_ITEM_NOT_EXIST;
  data.interval = ESP_CONFIG_HARDWARE_BATTERYMETER_DEFAULT_INTERVAL;
  data.voltage.min = ESP_CONFIG_HARDWARE_BATTERYMETER_DEFAULT_MIN_VOLTAGE;
  data.voltage.max = ESP_CONFIG_HARDWARE_BATTERYMETER_DEFAULT_MAX_VOLTAGE;
  for (uint8_t i = 0; i < ESP_CONFIG_HARDWARE_BATTERYMETER_MAX_NUMBER; i++) {
    save(i, &data);
  }
}
#endif // ESP_CONFIG_FUNCTIONALITY_BATTERYMETER

#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
void ESPDataAccess::get(uint8_t id, ACS758_SENSOR &data) {
  char fileName[26];
  sprintf(fileName, ESP_CONFIG_HARDWARE_SENSOR_ACS758_FILE_NAME, id);

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
    StaticJsonBuffer<ESP_CONFIG_HARDWARE_SENSOR_ACS758_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      data.interval = root["interval"];
      data.adcInput = root["adcInput"];
      data.type = root["type"];
      data.vcc = root["vcc"];
      data.currentCutOff = root["currentCutOff"];

#ifdef DEBUG
      Serial << endl
             << "INFO: JSON: Buffer size: "
             << ESP_CONFIG_HARDWARE_SENSOR_ACS758_FILE_BUFFER
             << ", actual JSON size: " << jsonBuffer.size();
      if (ESP_CONFIG_HARDWARE_SENSOR_ACS758_FILE_BUFFER <
          jsonBuffer.size() + 10) {
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

void ESPDataAccess::save(uint8_t id, ACS758_SENSOR *data) {
  char fileName[26];
  sprintf(fileName, ESP_CONFIG_HARDWARE_SENSOR_ACS758_FILE_NAME, id);

#ifdef DEBUG
  Serial << endl << endl << "INFO: Opening file: " << fileName << " ... ";
#endif

  File configFile = LITTLEFS.open(fileName, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: Writing JSON: ";
#endif

    StaticJsonBuffer<ESP_CONFIG_HARDWARE_SENSOR_ACS758_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["interval"] = data->interval;
    root["adcInput"] = data->adcInput;
    root["type"] = data->type;
    root["currentCutOff"] = data->currentCutOff;
    root["vcc"] = data->vcc;
    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "INFO: Data saved" << endl
           << "INFO: JSON: Buffer size: "
           << ESP_CONFIG_HARDWARE_SENSOR_ACS758_FILE_BUFFER
           << ", actual JSON size: " << jsonBuffer.size();
    if (ESP_CONFIG_HARDWARE_SENSOR_ACS758_FILE_BUFFER <
        jsonBuffer.size() + 10) {
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

void ESPDataAccess::createACS758SensorConfigurationFile() {
#ifdef DEBUG
  Serial << endl << F("INFO: Creating ACS758 sensor configuration files");
#endif
  ACS758_SENSOR data;
  data.adcInput = ESP_HARDWARE_ITEM_NOT_EXIST;
  data.interval = ESP_CONFIG_HARDWARE_SENSOR_ACS758_DEFAULT_INTERVAL;
  data.type = ESP_CONFIG_HARDWARE_SENSOR_ACS758_DEFAULT_TYPE;
  data.currentCutOff =
      ESP_CONFIG_HARDWARE_SENSOR_ACS758_DEFAULT_CURRENT_CUT_OFF;
  data.vcc = ESP_CONFIG_HARDWARE_SENSOR_ACS758_DEFAULT_VCC;
  for (uint8_t i = 0; i < ESP_CONFIG_HARDWARE_SENSOR_ACS758_MAX_NUMBER; i++) {
    save(i, &data);
  }
}
#endif // ESP_CONFIG_HARDWARE_SENSOR_ACS758

#ifdef ESP_CONFIG_API_MQTT
void ESPDataAccess::get(uint8_t id, MQTT_BROKER &data) {
  char fileName[24];
  sprintf(fileName, ESP_CONFIG_API_MQTT_FILE_NAME, id);

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
    StaticJsonBuffer<ESP_CONFIG_API_MQTT_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif
      sprintf(data.host, root["host"] | "");
      sprintf(data.ip, root["ip"] | "");
      data.port = root["port"] | ESP_CONFIG_API_MQTT_DEFAULT_PORT;
      sprintf(data.user, root["user"] | "");
      sprintf(data.password, root["password"] | "");
      sprintf(data.lwt.topic, root["lwt"] | "");
      data.timeout = root["timeout"] | ESP_CONFIG_API_MQTT_DEFAULT_TIMEOUT;
      data.qos = root["qos"] | ESP_CONFIG_API_MQTT_DEFAULT_QOS;
      data.retain = root["retain"] | ESP_CONFIG_API_MQTT_DEFAULT_RETAIN;

#ifdef DEBUG
      Serial << endl
             << "INFO: JSON: Buffer size: " << ESP_CONFIG_API_MQTT_FILE_BUFFER
             << ", actual JSON size: " << jsonBuffer.size();
      if (ESP_CONFIG_API_MQTT_FILE_BUFFER < jsonBuffer.size() + 10) {
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

void ESPDataAccess::save(uint8_t id, MQTT_BROKER *data) {
  char fileName[24];
  sprintf(fileName, ESP_CONFIG_API_MQTT_FILE_NAME, id);

#ifdef DEBUG
  Serial << endl << endl << "INFO: Opening file: " << fileName << " ... ";
#endif

  File configFile = LITTLEFS.open(fileName, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "INFO: Writing JSON: ";
#endif
    StaticJsonBuffer<ESP_CONFIG_API_MQTT_FILE_BUFFER> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["ip"] = data->ip;
    root["host"] = data->host;
    root["port"] = data->port;
    root["user"] = data->user;
    root["password"] = data->password;
    root["lwt"] = data->lwt.topic;
    root["retain"] = data->retain;
    root["qos"] = data->qos;
    root["timeout"] = data->timeout;
    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "INFO: Data saved" << endl
           << "INFO: JSON: Buffer size: " << ESP_CONFIG_API_MQTT_FILE_BUFFER
           << ", actual JSON size: " << jsonBuffer.size();
    if (ESP_CONFIG_API_MQTT_FILE_BUFFER < jsonBuffer.size() + 10) {
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

void ESPDataAccess::createMQTTBrokerConfigurationFile() {
#ifdef DEBUG
  Serial << endl << F("INFO: Creating MQTT Broker configuration files");
#endif
  MQTT_BROKER data;
  data.host[0] = ESP_EMPTY_STRING;
  data.ip[0] = ESP_EMPTY_STRING;
  data.user[0] = ESP_EMPTY_STRING;
  data.password[0] = ESP_EMPTY_STRING;
  data.port = ESP_CONFIG_API_MQTT_DEFAULT_PORT;
  data.lwt.topic[0] = ESP_EMPTY_STRING;
  data.timeout = ESP_CONFIG_API_MQTT_DEFAULT_TIMEOUT;
  data.qos = ESP_CONFIG_API_MQTT_DEFAULT_QOS;
  data.retain = ESP_CONFIG_API_MQTT_DEFAULT_RETAIN;
  for (uint8_t i = 0; i < ESP_CONFIG_API_MQTT_MAX_NUMBER; i++) {
    save(i, &data);
  }
}

#endif // ESP_CONFIG_API_MQTT
#include "ESP-Web-Server.h"

ESPWebServer::ESPWebServer() {}

#if defined(ESP_CONFIG_HARDWARE_LED) && defined(ESP_CONFIG_HARDWARE_I2C)
void ESPWebServer::begin(ESPDataAccess *_Data, ESPDevice *_Device, ESPLED *_LED,
                         TwoWire *_WirePort0, TwoWire *_WirePort1) {
  SystemLED = _LED;
  Site.begin(_Device, _Data, _WirePort0, _WirePort1);
  begin(_Data, _Device);
}

#elif defined(ESP_CONFIG_HARDWARE_LED) && !defined(ESP_CONFIG_HARDWARE_I2C)
void ESPWebServer::begin(ESPDataAccess *_Data, ESPDevice *_Device,
                         ESPLED *_LED) {
  SystemLED = _LED;
  Site.begin(_Device, _Data);
  begin(_Data, _Device);
}

#elif !defined(ESP_CONFIG_HARDWARE_LED) && defined(ESP_CONFIG_HARDWARE_I2C)
void ESPWebServer::begin(ESPDataAccess *_Data, ESPDevice *_Device,
                         TwoWire *_WirePort0, TwoWire *_WirePort1) {
  Site.begin(_Device, _Data, _WirePort0, _WirePort1);
  begin(_Data, _Device);
}
#endif

void ESPWebServer::begin(ESPDataAccess *_Data, ESPDevice *_Device) {
  Server.begin(80);
  Data = _Data;
  Device = _Device;
}

String ESPWebServer::generateSite(SITE_PARAMETERS *siteConfig, String &page) {

  if (siteConfig->twoColumns) {
    Site.generateTwoColumnsLayout(page, siteConfig->rebootTime);
  } else {
    Site.generateOneColumnLayout(page, siteConfig->rebootTime);
  }

  if (siteConfig->form) {
    page.concat("<form  method=\"post\" action=\"/?c=");
    page.concat(ESP_SERVER_CMD_SAVE);
    page.concat("&o=");
    page.concat(siteConfig->ID);
    if (siteConfig->deviceID != ESP_HARDWARE_ITEM_NOT_EXIST) {
      page.concat("&i=");
      page.concat(siteConfig->deviceID);
    }
    page.concat("\">");
  }

  switch (siteConfig->ID) {
  case ESP_CONFIG_SITE_INDEX: {
    Site.siteIndex(page);
    break;
  }
  case ESP_CONFIG_SITE_FIRST_TIME_CONNECTING: {
    Site.siteConnecting(page);
    break;
  }
  case ESP_CONFIG_SITE_EXIT: {
    Site.siteExit(page, siteConfig->rebootMode);
    break;
  }
  case ESP_CONFIG_SITE_RESET: {
    Site.siteReset(page);
    break;
  }
  case ESP_CONFIG_SITE_POST_RESET: {
    Site.sitePostReset(page);
    break;
  }
  case ESP_CONFIG_SITE_UPGRADE: {
    Site.siteUpgrade(page);
    break;
  }
  case ESP_CONFIG_SITE_POST_UPGRADE: {
    Site.sitePostUpgrade(page, upgradeFailed);
    break;
  }
  case ESP_CONFIG_SITE_FIRST_TIME: {
    Site.siteNetwork(page);
    break;
  }
  case ESP_CONFIG_SITE_INDEX_CONFIGURATION: {
    Site.siteIndexConfiguration(page);
    break;
  }
  case ESP_CONFIG_SITE_DEVICE: {
    Site.siteDevice(page);
    break;
  }
  case ESP_CONFIG_SITE_NETWORK: {
    Site.siteNetwork(page);
    break;
  }
#ifdef ESP_CONFIG_HARDWARE_I2C
  case ESP_CONFIG_SITE_I2C: {
    Site.siteI2CBUS(page, siteConfig->deviceID);
    break;
  }
#endif // ESP_CONFIG_HARDWARE_I2C
#ifdef ESP_CONFIG_HARDWARE_UART
  case ESP_CONFIG_SITE_UART: {
    Site.siteUARTBUS(page, siteConfig->deviceID);
    break;
  }
#endif // ESP_CONFIG_HARDWARE_UART
#ifdef ESP_CONFIG_HARDWARE_LED
  case ESP_CONFIG_SITE_LED: {
    Site.siteLED(page, siteConfig->deviceID);
    break;
  }
#endif // ESP_CONFIG_HARDWARE_LED
#ifdef ESP_CONFIG_HARDWARE_SWITCH
  case ESP_CONFIG_SITE_SWITCH: {
    Site.siteSwitch(page, siteConfig->deviceID);
    break;
  }
#endif // ESP_CONFIG_HARDWARE_SWITCH
#ifdef ESP_CONFIG_HARDWARE_ADC
  case ESP_CONFIG_SITE_ADC: {
    Site.siteADC(page, siteConfig->deviceID);
    break;
  }
#endif // ESP_CONFIG_HARDWARE_ADC
#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
  case ESP_CONFIG_SITE_BINARY_SENSOR: {
    Site.siteBinarySensor(page, siteConfig->deviceID);
    break;
  }
#endif // ESP_CONFIG_HARDWARE_SENSOR_BINARY
#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
  case ESP_CONFIG_SITE_DS18B20_SENSOR: {
    Site.siteDS18B20Sensor(page, siteConfig->deviceID);
    break;
  }
#endif // ESP_CONFIG_HARDWARE_SENSOR_DS18B20
#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
  case ESP_CONFIG_SITE_NTC_SENSOR: {
    Site.siteNTCSensor(page, siteConfig->deviceID);
    break;
  }
#endif // ESP_CONFIG_HARDWARE_SENSOR_NTC
#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
  case ESP_CONFIG_SITE_BATTERYMETER: {
    Site.siteBatterymeter(page, siteConfig->deviceID);
    break;
  }
#endif // ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
  case ESP_CONFIG_SITE_ACS758: {
    Site.siteACS758(page, siteConfig->deviceID);
    break;
  }
#endif // ESP_CONFIG_HARDWARE_SENSOR_ACS758
  }

  if (siteConfig->form) {

    if (siteConfig->formButton) {
      page.concat("<input type=\"submit\" class=\"b bs\" value=\"");
      page.concat(L_SAVE);
      page.concat("\">");
    }
    page.concat("</form>");
  }

  Site.generateFooter(page, (Device->getMode() == ESP_MODE_NORMAL ||
                             Device->getMode() == ESP_MODE_CONFIGURATION)
                                ? true
                                : false);

  page.replace("{{s.lang}}", L_LANGUAGE_SHORT);
  page.replace("{{f.version}}", ESP_FIRMWARE_VERSION);
  page.replace("{{f.name}}", L_FIRMWARE_NAME);
  /* Translations */
  page.replace("{{L_DONATE}}", L_DONATE);
  page.replace("{{L_VERSION}}", L_VERSION);

  return page;
}

void ESPWebServer::generate(boolean upload) {

  if (getOptionName()) {
    return;
  }

#ifdef ESP_CONFIG_HARDWARE_LED
  SystemLED->on();
#endif

  String page;

  page.reserve(ESP_MAX_PAGE_SIZE);

  if (_refreshConfiguration) {
    _refreshConfiguration = false;
    Device->begin(Data);
  }

  SITE_PARAMETERS siteConfig;

  siteConfig.ID = getSiteID();
  uint8_t command = getCommand();
  siteConfig.deviceID = getID();

  if (!upload) {

    if (command == ESP_SERVER_CMD_SAVE) {
      switch (siteConfig.ID) {
      case ESP_CONFIG_SITE_FIRST_TIME: {
        NETWORK configuration;
        get(configuration);
        Data->save(&configuration);
        siteConfig.twoColumns = false;
        siteConfig.reboot = true;
        siteConfig.rebootMode = ESP_MODE_CONFIGURATION;
        siteConfig.form = false;
        siteConfig.ID = ESP_CONFIG_SITE_FIRST_TIME_CONNECTING;
        break;
      }
      case ESP_CONFIG_SITE_RESET: {
        siteConfig.ID = ESP_CONFIG_SITE_POST_RESET;
        siteConfig.reboot = true;
        siteConfig.rebootMode = ESP_MODE_FIRST_TIME_LAUNCH;
        siteConfig.rebootTime = 15;
        siteConfig.form = false;
        siteConfig.twoColumns = false;
        break;
      }
      case ESP_CONFIG_SITE_DEVICE: {
        DEVICE configuration;
        get(configuration);
        Data->save(&configuration);
        break;
      }
      case ESP_CONFIG_SITE_NETWORK: {
        NETWORK configuration;
        get(configuration);
        Data->save(&configuration);
        break;
      }
#ifdef ESP_CONFIG_HARDWARE_I2C
      case ESP_CONFIG_SITE_I2C: {
        I2CBUS configuration;
        get(configuration);
        Data->save(siteConfig.deviceID, &configuration);
        break;
      }
#endif
#ifdef ESP_CONFIG_HARDWARE_UART
      case ESP_CONFIG_SITE_UART: {
        UARTBUS configuration;
        get(configuration);
        Data->save(siteConfig.deviceID, &configuration);
        break;
      }
#endif
#ifdef ESP_CONFIG_HARDWARE_LED
      case ESP_CONFIG_SITE_LED: {
        LED configuration;
        get(configuration);
        Data->save(siteConfig.deviceID, &configuration);
        break;
      }
#endif
#ifdef ESP_CONFIG_HARDWARE_SWITCH
      case ESP_CONFIG_SITE_SWITCH: {
        SWITCH configuration;
        get(configuration);
        Data->save(siteConfig.deviceID, &configuration);
        break;
      }
#endif
#ifdef ESP_CONFIG_HARDWARE_ADC
      case ESP_CONFIG_SITE_ADC: {
        ADC configuration;
        get(configuration);
        Data->save(siteConfig.deviceID, &configuration);
        break;
      }
#endif
#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
      case ESP_CONFIG_SITE_BINARY_SENSOR: {
        BINARY_SENSOR configuration;
        get(configuration);
        Data->save(siteConfig.deviceID, &configuration);
        break;
      }
#endif
#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
      case ESP_CONFIG_SITE_DS18B20_SENSOR: {
        DS18B20_SENSOR configuration;
        get(configuration);
        Data->save(siteConfig.deviceID, &configuration);
        break;
      }
#endif
#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
      case ESP_CONFIG_SITE_NTC_SENSOR: {
        NTC_SENSOR configuration;
        get(configuration);
        Data->save(siteConfig.deviceID, &configuration);
        break;
      }
#endif
#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
      case ESP_CONFIG_SITE_BATTERYMETER: {
        BATTERYMETER configuration;
        get(configuration);
        Data->save(siteConfig.deviceID, &configuration);
        break;
      }
#endif
#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
      case ESP_CONFIG_SITE_ACS758: {
        ACS758_SENSOR configuration;
        get(configuration);
        Data->save(siteConfig.deviceID, &configuration);
        break;
      }
#endif
      }
    } else if (command == ESP_SERVER_CMD_NONE) {
      switch (siteConfig.ID) {
      case ESP_CONFIG_SITE_INDEX: {
        siteConfig.form = false;
        siteConfig.twoColumns = false;
        if (siteConfig.deviceID != ESP_MODE_NORMAL &&
            siteConfig.deviceID != ESP_HARDWARE_ITEM_NOT_EXIST) {
          siteConfig.rebootMode = siteConfig.deviceID;
          siteConfig.ID = ESP_CONFIG_SITE_EXIT;
          siteConfig.reboot = true;
          siteConfig.rebootTime = 10;
        }
        break;
      }
      case ESP_CONFIG_SITE_INDEX_CONFIGURATION: {
        siteConfig.form = false;
        break;
      }
      case ESP_CONFIG_SITE_EXIT: {
        siteConfig.reboot = true;
        siteConfig.rebootMode = ESP_MODE_NORMAL;
        siteConfig.rebootTime = 10;
        siteConfig.form = false;
        siteConfig.twoColumns = false;
        break;
      }
      case ESP_CONFIG_SITE_FIRST_TIME: {
        siteConfig.twoColumns = false;
        break;
      }
      case ESP_CONFIG_SITE_RESET: {
        siteConfig.formButton = false;
        break;
      }
      case ESP_CONFIG_SITE_UPGRADE: {
        siteConfig.form = false;
        break;
      }
      case ESP_CONFIG_SITE_POST_UPGRADE: {
        if (!upload) {
          siteConfig.form = false;
          siteConfig.twoColumns = false;
          siteConfig.rebootTime = 15;
          siteConfig.reboot = true;
          siteConfig.rebootMode = Device->getMode();
        }
        break;
      }
      }
    }
  }

  if (upload) {
    delay(0);
  } else {

#ifdef DEBUG
    Serial << endl
           << F("INFO: Generating ")
           << (siteConfig.twoColumns ? F("Two Columns") : F("One Column"))
           << F(" site: ") << siteConfig.ID;
    Serial << F(", device ID: ") << siteConfig.deviceID;
    Serial << F(", Command: ") << command;
    Serial << F(", Reboot: ") << (siteConfig.reboot ? F("Yes") : F("No"));
    Serial << F(", Mode: ") << siteConfig.rebootMode;
    Serial << F(", Time: ") << siteConfig.rebootTime;
#endif

    generateSite(&siteConfig, page);

    publishHTML(page);
  }

  /* Rebooting device */
  if (siteConfig.reboot) {
    Device->reboot(siteConfig.rebootMode);
  }

#ifdef ESP_CONFIG_HARDWARE_LED
  SystemLED->off();
#endif
}

/* Methods related to the url request */

boolean ESPWebServer::getOptionName() {
  /* Recived HTTP API Command */

  if (Server.hasArg("command")) {
    Server.arg("command").toCharArray(httpCommand.command,
                                      sizeof(httpCommand.command));
    if (Server.arg("device")) {
      Server.arg("device").toCharArray(httpCommand.device,
                                       sizeof(httpCommand.device));
    } else {
      memset(httpCommand.device, 0, sizeof httpCommand.device);
    }
    if (Server.arg("name")) {
      Server.arg("name").toCharArray(httpCommand.name,
                                     sizeof(httpCommand.name));
    } else {
      memset(httpCommand.name, 0, sizeof httpCommand.name);
    }

    if (Server.arg("source")) {
      Server.arg("source").toCharArray(httpCommand.source,
                                       sizeof(httpCommand.source));
    } else {
      memset(httpCommand.source, 0, sizeof httpCommand.source);
    }
    receivedHTTPCommand = true;
  }

  return receivedHTTPCommand;
}

uint8_t ESPWebServer::getSiteID() {

  if (Device->getMode() == ESP_MODE_NETWORK_NOT_SET) {
    return ESP_CONFIG_SITE_FIRST_TIME;
  } else if (Device->getMode() == ESP_MODE_NORMAL) {
    return ESP_CONFIG_SITE_INDEX;
  } else {
    if (Server.hasArg("o")) {
      return Server.arg("o").toInt();
    } else {
      return ESP_CONFIG_SITE_INDEX_CONFIGURATION;
    }
  }
}

uint8_t ESPWebServer::getCommand() {
  if (Server.hasArg("c")) {
    return Server.arg("c").toInt();
  } else {
    return ESP_SERVER_CMD_NONE;
  }
}

uint8_t ESPWebServer::getID() {

  if (Server.hasArg("i")) {
    return Server.arg("i").toInt();
  } else {
    return ESP_HARDWARE_ITEM_NOT_EXIST;
  }
}

/* Server methods */

HTTPCOMMAND ESPWebServer::getHTTPCommand() {
  receivedHTTPCommand = false;
  return httpCommand;
}

void ESPWebServer::listener() { Server.handleClient(); }

boolean ESPWebServer::httpAPIlistener() { return receivedHTTPCommand; }

void ESPWebServer::publishHTML(String &page) {
  uint16_t pageSize = page.length();

#ifdef DEBUG
  Serial << endl << F("INFO: Site streaming started. Size : ") << pageSize;

  if (pageSize + 100 > ESP_MAX_PAGE_SIZE) {
    Serial << endl
           << endl
           << F("ERROR: Page size buffor ") << ESP_MAX_PAGE_SIZE
           << F("B too small : ") << pageSize << F(" ... ");
  }
#endif

  Server.sendHeader("Content-Length", String(page.length()));
  Server.setContentLength(pageSize);
  if (pageSize > ESP_PAGE_CHUNK_SIZE) {
    Server.send(200, "text/html", page.substring(0, ESP_PAGE_CHUNK_SIZE));
    uint16_t transfered = ESP_PAGE_CHUNK_SIZE;
    uint16_t nextChunk;
    while (transfered < pageSize) {
      nextChunk = transfered + ESP_PAGE_CHUNK_SIZE < pageSize
                      ? transfered + ESP_PAGE_CHUNK_SIZE
                      : pageSize;
#ifdef DEBUG
      Serial << F(".");
#endif

      Server.sendContent(page.substring(transfered, nextChunk));
      transfered = nextChunk;
    }
  } else {
    Server.send(200, "text/html", page);
  }

#ifdef DEBUG
  Serial << endl << F("INFO: Site published");
#endif
}

void ESPWebServer::handle(const char *uri,
                          WebServer::THandlerFunction handler) {
  Server.on(uri, handler);
}

void ESPWebServer::handleFirmwareUpgrade(
    const char *uri, WebServer::THandlerFunction handlerUpgrade,
    WebServer::THandlerFunction handlerUpload) {
  Server.on(uri, HTTP_POST, handlerUpgrade, handlerUpload);
}

void ESPWebServer::onNotFound(WebServer::THandlerFunction fn) {
  Server.onNotFound(fn);
}

/* Reading Server data */

void ESPWebServer::get(DEVICE &data) {
  if (Server.arg("name").length() > 0) {
    Server.arg("name").toCharArray(data.name, sizeof(data.name));
  } else {
    data.name[0] = ESP_EMPTY_STRING;
  }
#ifdef ESP_CONFIG_HARDWARE_LED
  data.noOfLEDs = Server.arg("led").length() > 0
                      ? Server.arg("led").toInt()
                      : ESP_CONFIG_HARDWARE_LED_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_SWITCH
  data.noOfSwitches = Server.arg("switch").length() > 0
                          ? Server.arg("switch").toInt()
                          : ESP_CONFIG_HARDWARE_SWITCH_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_ADC
  data.noOfADCs = Server.arg("adc").length() > 0
                      ? Server.arg("adc").toInt()
                      : ESP_CONFIG_HARDWARE_ADC_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_I2C
  data.noOfI2Cs = Server.arg("i2c").length() > 0
                      ? Server.arg("i2c").toInt()
                      : ESP_CONFIG_HARDWARE_I2C_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_UART
  data.noOfUARTs = Server.arg("uart").length() > 0
                       ? Server.arg("uart").toInt()
                       : ESP_CONFIG_HARDWARE_UART_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
  data.noOfBinarySensors =
      Server.arg("binarySensor").length() > 0
          ? Server.arg("binarySensor").toInt()
          : ESP_CONFIG_HARDWARE_SENSOR_BINARY_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
  data.noOfDS18B20s = Server.arg("ds18b20Sensor").length() > 0
                          ? Server.arg("ds18b20Sensor").toInt()
                          : ESP_CONFIG_HARDWARE_SENSOR_DS18B20_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
  data.noOfNTCs = Server.arg("NTCSensor").length() > 0
                      ? Server.arg("NTCSensor").toInt()
                      : ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
  data.noOfACS758s = Server.arg("acs758Sensor").length() > 0
                         ? Server.arg("acs758Sensor").toInt()
                         : ESP_CONFIG_HARDWARE_SENSOR_ACS758_DEFAULT_NUMBER;
#endif

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
  data.noOfBatterymeters =
      Server.arg("batterymeter").length() > 0
          ? Server.arg("batterymeter").toInt()
          : ESP_CONFIG_HARDWARE_BATTERYMETER_DEFAULT_NUMBER;
#endif
}

void ESPWebServer::get(NETWORK &data) {
  if (Server.arg("ssid").length() > 0) {
    Server.arg("ssid").toCharArray(data.ssid, sizeof(data.ssid));
  } else {
    data.ssid[0] = ESP_EMPTY_STRING;
  }

  if (Server.arg("password").length() > 0) {
    Server.arg("password").toCharArray(data.password, sizeof(data.password));
  } else {
    data.password[0] = ESP_EMPTY_STRING;
  }

  if (Server.arg("ip").length() > 0) {
    Server.arg("ip").toCharArray(data.ip, sizeof(data.ip));
  } else {
    data.ip[0] = ESP_EMPTY_STRING;
  }

  if (Server.arg("gateway").length() > 0) {
    Server.arg("gateway").toCharArray(data.gateway, sizeof(data.gateway));
  } else {
    data.gateway[0] = ESP_EMPTY_STRING;
  }

  if (Server.arg("subnet").length() > 0) {
    Server.arg("subnet").toCharArray(data.subnet, sizeof(data.subnet));
  } else {
    data.subnet[0] = ESP_EMPTY_STRING;
  }

  data.noConnectionAttempts = Server.arg("na").length() > 0
                                  ? Server.arg("na").toInt()
                                  : ESP_CONFIG_NETWORK_CONNECTION_ATTEMPTS;

  data.waitTimeConnections =
      Server.arg("wc").length() > 0
          ? Server.arg("wc").toInt()
          : ESP_CONFIG_NETWORK_TIME_BETWEEN_CONNECTION_ATTEMPTS;

  data.waitTimeSeries =
      Server.arg("ws").length() > 0
          ? Server.arg("ws").toInt()
          : ESP_CONFIG_NETWORK_SLEEP_TIME_BETWEEN_FAILED_CONNECTION_ATTEMPTS;

  data.isDHCP = Server.arg("dhcp").length() > 0 ? true : false;
}

#ifdef ESP_CONFIG_HARDWARE_I2C
void ESPWebServer::get(I2CBUS &data) {
  data.SCL = Server.arg("scl").length() > 0 ? Server.arg("scl").toInt()
                                            : ESP_HARDWARE_ITEM_NOT_EXIST;

  data.SDA = Server.arg("sda").length() > 0 ? Server.arg("sda").toInt()
                                            : ESP_HARDWARE_ITEM_NOT_EXIST;

  data.frequency = Server.arg("frequency").length() > 0
                       ? Server.arg("frequency").toInt()
                       : ESP_CONFIG_HARDWARE_I2C_DEFAULT_FREQUENCY;
}
#endif

#ifdef ESP_CONFIG_HARDWARE_UART
void ESPWebServer::get(UARTBUS &data) {
  data.RXD = Server.arg("rxd").length() > 0 ? Server.arg("rxd").toInt()
                                            : ESP_HARDWARE_ITEM_NOT_EXIST;

  data.TXD = Server.arg("txd").length() > 0 ? Server.arg("txd").toInt()
                                            : ESP_HARDWARE_ITEM_NOT_EXIST;
}
#endif

#ifdef ESP_CONFIG_HARDWARE_LED
void ESPWebServer::get(LED &data) {
  data.gpio = Server.arg("gpio").length() > 0 ? Server.arg("gpio").toInt()
                                              : ESP_HARDWARE_ITEM_NOT_EXIST;
  data.reverseState = Server.arg("reverse").length() > 0 ? true : false;
}
#endif

#ifdef ESP_CONFIG_HARDWARE_SWITCH
void ESPWebServer::get(SWITCH &data) {
  data.gpio = Server.arg("gpio").length() > 0 ? Server.arg("gpio").toInt()
                                              : ESP_HARDWARE_ITEM_NOT_EXIST;

  data.functionality = Server.arg("functionality").length() > 0
                           ? Server.arg("functionality").toInt()
                           : ESP_CONFIG_HARDWARE_SWITCH_FUNCTIONALITY_MULTI;

  data.type = Server.arg("type").length() > 0
                  ? Server.arg("type").toInt()
                  : ESP_CONFIG_HARDWARE_SWITCH_DEFAULT_TYPE;

  data.pinMode = Server.arg("pin").length() > 0
                     ? Server.arg("pin").toInt()
                     : ESP_CONFIG_HARDWARE_SWITCH_DEFAULT_PIN_MODE;

  data.bouncing = Server.arg("bouncing").length() > 0
                      ? Server.arg("bouncing").toInt()
                      : ESP_CONFIG_HARDWARE_SWITCH_DEFAULT_BOUNCING;
}
#endif

#ifdef ESP_CONFIG_HARDWARE_ADC
void ESPWebServer::get(ADC &data) {
  data.gpio = Server.arg("gpio").length() > 0 ? Server.arg("gpio").toInt()
                                              : ESP_HARDWARE_ITEM_NOT_EXIST;

  data.interval = Server.arg("interval").length() > 0
                      ? Server.arg("interval").toInt()
                      : ESP_CONFIG_HARDWARE_ADC_DEFAULT_INTERVAL;

  data.numberOfSamples = Server.arg("samples").length() > 0
                             ? Server.arg("samples").toInt()
                             : ESP_CONFIG_HARDWARE_ADC_DEFAULT_SAMPLES;

  data.resolution = Server.arg("resolution").length() > 0
                        ? Server.arg("resolution").toInt()
                        : ESP_CONFIG_HARDWARE_ADC_DEFAULT_RESOLUTION;

  data.maxVCC = Server.arg("vcc").length() > 0
                    ? Server.arg("vcc").toFloat()
                    : ESP_CONFIG_HARDWARE_ADC_DEFAULT_MAX_VCC;

  data.divider.Ra = Server.arg("ra").length() > 0
                        ? Server.arg("ra").toFloat()
                        : ESP_CONFIG_HARDWARE_ADC_DEFAULT_DIVIDER_RESISTOR;

  data.divider.Rb = Server.arg("rb").length() > 0
                        ? Server.arg("rb").toFloat()
                        : ESP_CONFIG_HARDWARE_ADC_DEFAULT_DIVIDER_RESISTOR;

#ifdef ESP_CONFIG_HARDWARE_ADS1115
  data.i2c.id = Server.arg("i2c").length() > 0 ? Server.arg("i2c").toInt()
                                               : ESP_HARDWARE_ITEM_NOT_EXIST;

  data.i2c.address = Server.arg("address").length() > 0
                         ? Server.arg("address").toInt()
                         : ESP_HARDWARE_ITEM_NOT_EXIST;

  data.i2c.inputId = Server.arg("input").length() > 0
                         ? Server.arg("input").toInt()
                         : ESP_HARDWARE_ITEM_NOT_EXIST;

  data.i2c.gain = Server.arg("gain").length() > 0
                      ? Server.arg("gain").toInt()
                      : ESP_CONFIG_HARDWARE_ADS1115_DEFAULT_GAIN;

  /* Data validation */
  if (data.i2c.id != ESP_HARDWARE_ITEM_NOT_EXIST &&
      data.i2c.address != ESP_HARDWARE_ITEM_NOT_EXIST) {

    if (data.gpio != ESP_HARDWARE_ITEM_NOT_EXIST) {
      data.gpio = ESP_HARDWARE_ITEM_NOT_EXIST;
    }

    data.maxVCC =
        data.i2c.gain == GAIN_TWOTHIRDS
            ? 6.144
            : (data.i2c.gain == GAIN_ONE
                   ? 4.096
                   : (data.i2c.gain == GAIN_TWO
                          ? 2.048
                          : (data.i2c.gain == GAIN_FOUR
                                 ? 1.024
                                 : (data.i2c.gain == GAIN_EIGHT
                                        ? 0.512
                                        : (data.i2c.gain == GAIN_SIXTEEN
                                               ? 0.256
                                               : 6.144)))));
  }

  data.i2c.samplesPerSecond = Server.arg("samplesPerSecond").length() > 0
                                  ? Server.arg("samplesPerSecond").toInt()
                                  : ESP_CONFIG_HARDWARE_ADS1115_DEFAULT_SAMPLES;

#endif // ESP_CONFIG_HARDWARE_I2C
}
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
void ESPWebServer::get(BINARY_SENSOR &data) {
  data.gpio = Server.arg("gpio").length() > 0 ? Server.arg("gpio").toInt()
                                              : ESP_HARDWARE_ITEM_NOT_EXIST;

  data.interval = Server.arg("interval").length() > 0
                      ? Server.arg("interval").toInt()
                      : ESP_CONFIG_HARDWARE_SENSOR_BINARY_DEFAULT_INTERVAL;

  data.bouncing = Server.arg("bouncing").length() > 0
                      ? Server.arg("bouncing").toInt()
                      : ESP_CONFIG_HARDWARE_SENSOR_BINARY_DEFAULT_BOUNCING;
}
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
void ESPWebServer::get(DS18B20_SENSOR &data) {
  ESPDS18B20Sensor _Sensor;
  data.gpio = Server.arg("gpio").length() > 0 ? Server.arg("gpio").toInt()
                                              : ESP_HARDWARE_ITEM_NOT_EXIST;

  data.interval = Server.arg("interval").length() > 0
                      ? Server.arg("interval").toInt()
                      : ESP_CONFIG_HARDWARE_SENSOR_DS18B20_DEFAULT_INTERVAL;

  data.unit = Server.arg("unit").length() > 0
                  ? Server.arg("unit").toInt()
                  : ESP_CONFIG_HARDWARE_SENSOR_DS18B20_DEFAULT_UNIT;

  data.correction = Server.arg("correction").length() > 0
                        ? Server.arg("correction").toFloat()
                        : ESP_CONFIG_HARDWARE_SENSOR_DS18B20_DEFAULT_CORRECTION;

  if (Server.arg("address").length() > 0) {
    char address[17];
    Server.arg("address").toCharArray(address, 17);
    _Sensor.addressToInt(address, data.address);
  } else {
    _Sensor.addressNULL(data.address);
  }
}
#endif // ESP_CONFIG_HARDWARE_SENSOR_DS18B20

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
void ESPWebServer::get(NTC_SENSOR &data) {
  data.resistor = Server.arg("resistor").length() > 0
                      ? Server.arg("resistor").toFloat()
                      : ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_RESISTOR;

  data.vcc = Server.arg("vcc").length() > 0
                 ? Server.arg("vcc").toFloat()
                 : ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_VCC;

  data.coefficients.A.value = Server.arg("A").length() > 0
                                  ? Server.arg("A").toFloat()
                                  : ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_A;

  data.coefficients.B.value = Server.arg("B").length() > 0
                                  ? Server.arg("B").toFloat()
                                  : ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_B;

  data.coefficients.C.value = Server.arg("C").length() > 0
                                  ? Server.arg("C").toFloat()
                                  : ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_C;

  data.coefficients.A.precision =
      Server.arg("AP").length() > 0
          ? Server.arg("AP").toInt()
          : ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_A_PRECISION;

  data.coefficients.B.precision =
      Server.arg("BP").length() > 0
          ? Server.arg("BP").toInt()
          : ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_B_PRECISION;

  data.coefficients.C.precision =
      Server.arg("CP").length() > 0
          ? Server.arg("CP").toInt()
          : ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_C_PRECISION;

  data.interval = Server.arg("interval").length() > 0
                      ? Server.arg("interval").toInt()
                      : ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_INTERVAL;

  data.unit = Server.arg("unit").length() > 0
                  ? Server.arg("unit").toInt()
                  : ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_UNIT;

  data.correction = Server.arg("correction").length() > 0
                        ? Server.arg("correction").toFloat()
                        : ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_CORRECTION;

  data.adcInput = Server.arg("adc").length() > 0 ? Server.arg("adc").toInt()
                                                 : ESP_HARDWARE_ITEM_NOT_EXIST;
}
#endif // ESP_CONFIG_HARDWARE_SENSOR_NTC

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
void ESPWebServer::get(BATTERYMETER &data) {
  data.voltage.min = Server.arg("vMin").length() > 0
                         ? Server.arg("vMin").toFloat()
                         : ESP_CONFIG_HARDWARE_BATTERYMETER_DEFAULT_MIN_VOLTAGE;

  data.voltage.max = Server.arg("vMax").length() > 0
                         ? Server.arg("vMax").toFloat()
                         : ESP_CONFIG_HARDWARE_BATTERYMETER_DEFAULT_MAX_VOLTAGE;

  data.interval = Server.arg("interval").length() > 0
                      ? Server.arg("interval").toInt()
                      : ESP_CONFIG_HARDWARE_BATTERYMETER_DEFAULT_INTERVAL;

  data.adcInput = Server.arg("adc").length() > 0 ? Server.arg("adc").toInt()
                                                 : ESP_HARDWARE_ITEM_NOT_EXIST;
}
#endif // ESP_CONFIG_FUNCTIONALITY_BATTERYMETER

#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
void ESPWebServer::get(ACS758_SENSOR &data) {
  data.interval = Server.arg("interval").length() > 0
                      ? Server.arg("interval").toInt()
                      : ESP_CONFIG_HARDWARE_SENSOR_ACS758_DEFAULT_INTERVAL;

  data.adcInput = Server.arg("adc").length() > 0 ? Server.arg("adc").toInt()
                                                 : ESP_HARDWARE_ITEM_NOT_EXIST;

  data.type = Server.arg("type").length() > 0 ? Server.arg("type").toInt()
                                              : ESP_HARDWARE_ITEM_NOT_EXIST;
}
#endif // ESP_CONFIG_HARDWARE_SENSOR_ACS758

/* AFE Firmware for smart home devices, Website: https://afe.smartnydom.pl/ */

#include "ESP-Sites-Generator.h"

ESPSitesGenerator::ESPSitesGenerator() {}

void ESPSitesGenerator::begin(ESPDevice *_Device, ESPDataAccess *_Data) {
  Device = _Device;
  Data = _Data;
}

#ifdef ESP_CONFIG_HARDWARE_I2C
void ESPSitesGenerator::begin(ESPDevice *_Device, ESPDataAccess *_Data,
                              TwoWire *_WirePort0, TwoWire *_WirePort1) {
  WirePort0 = _WirePort0;
  WirePort1 = _WirePort1;
  begin(_Device, _Data);
}
#endif

void ESPSitesGenerator::generateHeader(String &page, uint16_t redirect) {

  page.concat(FPSTR(HTTP_HEADER));

  if (redirect > 0) {
    page.replace("{{s.redirect}}", "<meta http-equiv=\"refresh\" content=\"" +
                                       String(redirect) + "; url=/\">");
  } else {
    page.replace("{{s.redirect}}", "");
  }

  page.concat("<h3 class=\"la\">Firmware v");
  page.concat(ESP_FIRMWARE_VERSION);
  page.concat("</h3>");

  page.concat("<div id=\"c\">");
}

void ESPSitesGenerator::generateOneColumnLayout(String &page,
                                                uint16_t redirect) {
  generateHeader(page, redirect);
  page.concat("<div id=\"r\">");
}

void ESPSitesGenerator::generateTwoColumnsLayout(String &page,
                                                 uint16_t redirect) {

  Device->begin(Data);

  generateHeader(page, redirect);
  page.concat("<div id=\"l\">");

  page.concat("<h4 class=\"ltit\">");
  page.concat(L_FIRMWARE_NAME);
  page.concat("</h4><ul class=\"lst\">");

  /* Gnerating Menu */
  addMenuItem(page, L_DEVICE, ESP_CONFIG_SITE_DEVICE);
  addMenuItem(page, L_NETWORK, ESP_CONFIG_SITE_NETWORK);

#ifdef ESP_CONFIG_HARDWARE_I2C
  if (Device->configuration.noOfI2Cs > 0) {
    addMenuHeaderItem(page, "I2C BUS");
    addMenuSubItem(page, "I2C", Device->configuration.noOfI2Cs,
                   ESP_CONFIG_SITE_I2C);
  }
#endif // ESP_CONFIG_HARDWARE_I2C

#ifdef ESP_CONFIG_HARDWARE_UART
  if (Device->configuration.noOfUARTs > 0) {
    addMenuHeaderItem(page, "UART BUS");
    addMenuSubItem(page, "UART", Device->configuration.noOfUARTs,
                   ESP_CONFIG_SITE_UART);
  }
#endif // ESP_CONFIG_HARDWARE_UART

#ifdef ESP_CONFIG_HARDWARE_LED
  if (Device->configuration.noOfLEDs > 0) {
    addMenuHeaderItem(page, L_LEDS);
    addMenuSubItem(page, "LED", Device->configuration.noOfLEDs,
                   ESP_CONFIG_SITE_LED);
  }
#endif

#ifdef ESP_CONFIG_HARDWARE_SWITCH
  if (Device->configuration.noOfSwitches > 0) {
    addMenuHeaderItem(page, L_BUTTONS_SWITCHES);
    addMenuSubItem(page, L_SWITCH, Device->configuration.noOfSwitches,
                   ESP_CONFIG_SITE_SWITCH);
  }
#endif // AFE_CONFIG_HARDWARE_SWITCH

#ifdef ESP_CONFIG_HARDWARE_ADC
  if (Device->configuration.noOfADCs > 0) {
    addMenuHeaderItem(page, L_ANALOG_INPUTS);
    addMenuSubItem(page, L_INPUT, Device->configuration.noOfADCs,
                   ESP_CONFIG_SITE_ADC);
  }
#endif // ESP_CONFIG_HARDWARE_ADC

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
  if (Device->configuration.noOfADCs > 0 &&
      Device->configuration.noOfBatterymeters > 0) {
    addMenuHeaderItem(page, L_BATTERY_METERS);
    addMenuSubItem(page, L_BATTERY_METER,
                   Device->configuration.noOfBatterymeters,
                   ESP_CONFIG_SITE_BATTERYMETER);
  }
#endif // ESP_CONFIG_FUNCTIONALITY_BATTERYMETER

#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
  if (Device->configuration.noOfBinarySensors > 0) {
    addMenuHeaderItem(page, L_BINARY_SENSOR);
    addMenuSubItem(page, L_SENSOR, Device->configuration.noOfBinarySensors,
                   ESP_CONFIG_SITE_BINARY_SENSOR);
  }
#endif // ESP_CONFIG_HARDWARE_SENSOR_BINARY

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
  if (Device->configuration.noOfDS18B20s > 0) {
    addMenuHeaderItem(page, L_DS18B20_SENSOR);
    addMenuSubItem(page, L_SENSOR, Device->configuration.noOfDS18B20s,
                   ESP_CONFIG_SITE_DS18B20_SENSOR);
  }
#endif // ESP_CONFIG_HARDWARE_SENSOR_DS18B20

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
  if (Device->configuration.noOfNTCs > 0) {
    addMenuHeaderItem(page, L_NTC_SENSOR);
    addMenuSubItem(page, L_NTC_TERMISTOR, Device->configuration.noOfNTCs,
                   ESP_CONFIG_SITE_NTC_SENSOR);
  }
#endif // ESP_CONFIG_HARDWARE_SENSOR_NTC

#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
  if (Device->configuration.noOfACS758s > 0) {
    addMenuHeaderItem(page, L_ACS758_SENSOR);
    addMenuSubItem(page, L_SENSOR, Device->configuration.noOfACS758s,
                   ESP_CONFIG_SITE_ACS758);
  }
#endif // ESP_CONFIG_HARDWARE_SENSOR_NTC

  addMenuItem(page, L_FIRMWARE_UPGRADE, ESP_CONFIG_SITE_UPGRADE);
  addMenuItem(page, L_RESET_DEVICE, ESP_CONFIG_SITE_RESET);
  addMenuItem(page, L_FINISH_CONFIGURATION, ESP_CONFIG_SITE_EXIT);

  /* Information section */
  page.concat("</ul></div><div id=\"r\">");
}

void ESPSitesGenerator::siteConnecting(String &page) {
  page.concat("<p>Connecting</p>");
}

void ESPSitesGenerator::siteUpgrade(String &page) {
  openSection(page, L_FIRMWARE_UPGRADE, L_DONT_PLUG_OFF);
  page.concat(FPSTR(HTTP_SITE_UPGRADE));
  page.replace("{{L_SELECT_FIRMWARE}}", L_SELECT_FIRMWARE);
  page.replace("{{L_UPGRADE_INFO}}", L_UPGRADE_INFO);
  page.replace("{{L_UPGRADE}}", L_UPGRADE);
  closeSection(page);
}

void ESPSitesGenerator::sitePostUpgrade(String &page, boolean status) {
  openSection(page, L_FIRMWARE_UPGRADE, "");
  page.concat("<ul>");
  if (status) {
    page.concat("<li style=\"color:red\">");
    page.concat(L_UPGRADE_FAILED);
  } else {
    page.concat("<li>");
    page.concat(L_UPGRADE_SUCCESSFUL);
  }
  page.concat("</li><li>");
  page.concat(L_DEVICE_WILL_BE_REBOOTED);
  page.concat("...</li>");
  closeSection(page);
}

void ESPSitesGenerator::siteReset(String &page) {
  openSection(page, L_RESTORING_DEFAULT_SETTING, "");
  page.concat(FPSTR(HTTP_SITE_RESET_TO_DEFAULTS));
  page.replace("{{L_WARNING}}", L_WARNING);
  page.replace("{{L_CONFIGURATION_WILL_BE_REMOVED}}",
               L_CONFIGURATION_WILL_BE_REMOVED);
  page.replace("{{L_RESTORE_DEFAULT_SETTINGS}}", L_RESTORE_DEFAULT_SETTINGS);
  closeSection(page);
}

void ESPSitesGenerator::sitePostReset(String &page) {
  openSection(page, L_RESTORING_DEFAULT_SETTING, "");
  page.concat(FPSTR(HTTP_SITE_POST_RESET));
  page.replace("{{L_UPGRADE_IN_PROGRESS}}", L_UPGRADE_IN_PROGRESS);
  page.replace("{{L_CONNECT_TO_HOTSPOT_AFTER_UPGRADE}}",
               L_CONNECT_TO_HOTSPOT_AFTER_UPGRADE);
  closeSection(page);
}

void ESPSitesGenerator::siteExit(String &page, uint8_t command) {
  openSection(page, L_REBOOT, "");
  page.concat("<fieldset>");
  page += "<div class=\"cf\"><ul><li>";
  page += F(L_REBOOT_IN_PROGRESS);
  page += "</li><li>";
  if (command != ESP_MODE_ACCESS_POINT) {
    page += F(L_SITE_WILL_BE_RELOADED);
  } else {
    page += F(L_CONNECT_TO_HOTSPOT_AFTER_UPGRADE);
    page += ": <a href=\"http://192.168.5.1\">http://192.168.5.1</a></p>";
  }
  page += "</li></ul></div>";
  closeSection(page);
}

void ESPSitesGenerator::generateFooter(String &page, boolean extended) {
  if (Device->getMode() == ESP_MODE_NORMAL) {
    page.concat(FPSTR(HTTP_FOOTER_CONNECTED));
  }

  page.concat("</div></div>");

  if (extended) {
    page.concat(FPSTR(HTTP_FOOTER_EXTENDED));
  }

  page.concat("</body></html>");
}

void ESPSitesGenerator::openSection(String &page, const char *title,
                                    const char *description) {
  page.concat(FPSTR(HTTP_FORM_BLOCK_HEADER));
  page.replace("{{title}}", title);
  page.replace("{{description}}", description);
}

void ESPSitesGenerator::closeSection(String &page) {
  page.concat(FPSTR(HTTP_FORM_BLOCK_CLOSURE));
}

void ESPSitesGenerator::addListOfGPIOs(String &item, const char *field,
                                       uint8_t selected, const char *title) {

  item.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
  item.replace("{{item.name}}", field);
  item.replace("{{item.label}}", title);
  item.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  item.replace("{{item.value}}", String(ESP_HARDWARE_ITEM_NOT_EXIST));
  item.replace("{{item.label}}", L_NONE);
  item.replace("{{item.selected}}", selected == ESP_HARDWARE_ITEM_NOT_EXIST
                                        ? " selected=\"selected\""
                                        : "");

  for (uint8_t i = 0; i < ESP_NUMBER_OF_GPIOS; i++) {
    item.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));

    item.replace("{{item.value}}", String(pgm_read_byte(GPIOS + i)));
    item.replace("{{item.label}}", String(pgm_read_byte(GPIOS + i)));
    item.replace("{{item.selected}}", selected == pgm_read_byte(GPIOS + i)
                                          ? " selected=\"selected\""
                                          : "");
  }
  item.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));
}

void ESPSitesGenerator::_addListOfHardware(String &page, uint8_t noOfItems,
                                           uint8_t noOffConnected,
                                           const char *field, const char *label,
                                           uint8_t index, uint8_t noneValue,
                                           boolean disabled) {
  page.concat("<div class=\"cf\"><label>");
  page.concat(label);
  page.concat("</label><select name=\"");
  page.concat(field);
  page.concat("\"");
  if (disabled) {
    page.concat(" disabled=\"disabled\"");
  }
  page.concat("><option value=\"");
  page.concat(noneValue);
  page.concat("\"");
  page.concat((noOffConnected == noneValue ? " selected=\"selected\"" : ""));
  page.concat(">");
  page.concat(L_NONE);
  page.concat("</option>");
  /* @TODO not a nice code with this index. It can't be different than 0
   * or 1. So far only 0,1 are planned */
  if (!disabled) { // generate other values if item is not vis
    for (uint8_t i = index; i < noOfItems + index; i++) {
      page.concat("<option value=\"");
      page.concat(i);
      page.concat("\"");
      page.concat(noOffConnected == i ? " selected=\"selected\"" : "");
      page.concat(">");
      page.concat(i + (index == 0 ? 1 : 0));
      page.concat("</option>");
    }
  }
  page.concat("</select>");
  if (disabled) {
    page.concat("<span class=\"hint\">(");
    page.concat(L_PRO_VERSION);
    page.concat(")</span>");
  }

  page.concat("</div>");
}

void ESPSitesGenerator::addListOfHardwareItem(String &page, uint8_t noOfItems,
                                              uint8_t noOffConnected,
                                              const char *field,
                                              const char *label,
                                              boolean disabled) {
  _addListOfHardware(page, noOfItems, noOffConnected, field, label, 1, 0,
                     disabled);
}

void ESPSitesGenerator::addMenuItem(String &item, const char *title,
                                    uint8_t siteId) {
  item.concat(FPSTR(HTTP_MENU_ITEM));
  item.replace("{{item.title}}", title);
  item.replace("{{site.id}}", String(siteId));
}

void ESPSitesGenerator::addMenuHeaderItem(String &item, const char *title) {
  item.concat(FPSTR(HTTP_MENU_SUBITEMS_HEADER));
  item.replace("{{item.title}}", title);
}

void ESPSitesGenerator::addMenuSubItem(String &item, const char *title,
                                       uint8_t numberOfItems, uint8_t siteId) {
  for (uint8_t i = 0; i < numberOfItems; i++) {
    item.concat(FPSTR(HTTP_MENU_SUBITEM));
    item.replace("{{item.title}}", title);
    item.replace("{{item.id}}", String(i));
    item.replace("{{item.id.display}}", String(i + 1));
    item.replace("{{site.id}}", String(siteId));
  }
}

void ESPSitesGenerator::addInputFormItem(String &item, const char *type,
                                         const char *name, const char *label,
                                         const char *value, const char *size,
                                         const char *min, const char *max,
                                         const char *step, const char *hint,
                                         boolean readonly) {
  item.concat("<div class=\"cf\"><label>");
  item.concat(label);
  item.concat("</label><input name=\"");
  item.concat(name);
  item.concat("\" type=\"");
  item.concat(type);
  item.concat("\" ");
  if (readonly) {
    item.concat("readonly=\"readonly\" ");
  }
  if (strcmp(size, "?") != 0) {
    item.concat("maxlength=\"");
    item.concat(size);
    item.concat("\" ");
  }
  if (strcmp(type, "number") == 0) {
    if (strcmp(min, "?") != 0) {
      item.concat("min=\"");
      item.concat(min);
      item.concat("\" ");
    }
    if (strcmp(max, "?") != 0) {
      item.concat("max=\"");
      item.concat(max);
      item.concat("\" ");
    }
    if (strcmp(step, "?") != 0) {
      item.concat("step=\"");
      item.concat(step);
      item.concat("\" ");
    }
  }
  item.concat("value=\"");
  item.concat(value);
  item.concat("\">");
  if (strcmp(size, "?") != 0) {
    item.concat("<span class=\"hint\">Max ");
    item.concat(size);
    item.concat(" ");
    item.concat(F(L_NUMBER_OF_CHARS));
    item.concat("</span>");
  }
  if (strcmp(type, "number") == 0) {
    if (strcmp(min, "?") != 0 && strcmp(max, "?") != 0) {
      item.concat("<span class=\"hint\"> ");
      item.concat(F(L_RANGE));
      item.concat(" ");
      item.concat(min);
      item.concat(" - ");
      item.concat(max);
      if (strcmp(hint, "?") != 0) {
        item.concat(" ");
        item.concat(hint);
      }
      item.concat("</span>");
    } else if (strcmp(hint, "?") != 0) {
      item.concat("<span class=\"hint\">");
      item.concat(hint);
      item.concat("</span>");
    }
  }
  item.concat("</div>");
}

void ESPSitesGenerator::addCheckboxFormItem(String &item, const char *name,
                                            const char *label,
                                            const char *value,
                                            boolean checked) {
  item.concat(FPSTR(HTTP_ITEM_CHECKBOX));
  item.replace("{{item.name}}", name);
  item.replace("{{item.label}}", label);
  item.replace("{{item.value}}", value);
  item.replace("{{item.checked}}", checked ? "checked=\"checked\"" : "");
}

/************** SITES ****************/

void ESPSitesGenerator::siteIndex(String &page) {
  DEVICE configuration;
  configuration = Device->configuration;
  openSection(page, L_LAUNCH_CONFIGURATION_PANEL, "");
  page += "<form method=\"post\"><div class=\"cf\"><input type=\"submit\" "
          "class=\"b bs\" "
          "value=\"";
  page += F(L_NORMAL_MODE);
  page += "\" formaction=\"/?o=0&i=";
  page += ESP_MODE_CONFIGURATION;
  page += "\" /> <input type=\"submit\" class=\"b be\" value=\"";
  page += F(L_HOTSPOT_MODE);
  page += "\" formaction=\"/?o=0&i=";
  page += ESP_MODE_ACCESS_POINT;
  page += "\" /></div></form>";
  closeSection(page);
}

void ESPSitesGenerator::siteIndexConfiguration(String &page) {
  page.concat("INDEX");
}

void ESPSitesGenerator::siteDevice(String &page) {
  DEVICE configuration;
  Data->get(configuration);
  openSection(page, L_DEVICE, "");

#ifdef ESP_CONFIG_HARDWARE_LED
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_LED_MAX_NUMBER,
                        configuration.noOfLEDs, "led", L_NUMBER_OF_LEDS);
#endif

#ifdef ESP_CONFIG_HARDWARE_SWITCH
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_SWITCH_MAX_NUMBER,
                        configuration.noOfSwitches, "switch",
                        L_NUMBER_OF_SWITCHES);
#endif
#ifdef ESP_CONFIG_HARDWARE_ADC
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_ADC_MAX_NUMBER,
                        configuration.noOfADCs, "adc", L_NUMBER_OF_ADCS);
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_SENSOR_BINARY_MAX_NUMBER,
                        configuration.noOfBinarySensors, "binarySensor",
                        L_NUMBER_OF_BINARY_SENSORS);

#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_SENSOR_DS18B20_MAX_NUMBER,
                        configuration.noOfDS18B20s, "ds18b20Sensor",
                        L_NUMBER_OF_DS18B20_SENSORS);

#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_SENSOR_NTC_MAX_NUMBER,
                        configuration.noOfNTCs, "NTCSensor",
                        L_NUMBER_OF_NTC_SENSORS);

#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_SENSOR_ACS758_MAX_NUMBER,
                        configuration.noOfACS758s, "acs758Sensor",
                        L_NUMBER_OF_ACS758);
#endif

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_BATTERYMETER_MAX_NUMBER,
                        configuration.noOfBatterymeters, "batterymeter",
                        L_NUMBER_OF_BATTERYMETERS);

#endif

  closeSection(page);

  openSection(page, L_BUSES, "");
#ifdef ESP_CONFIG_HARDWARE_I2C
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_I2C_MAX_NUMBER,
                        configuration.noOfI2Cs, "i2c", L_NUMBER_OF_I2C);
#endif
#ifdef ESP_CONFIG_HARDWARE_UART
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_UART_MAX_NUMBER,
                        configuration.noOfUARTs, "uart", L_NUMBER_OF_UART);
#endif
  closeSection(page);
}

void ESPSitesGenerator::siteNetwork(String &page) {
  NETWORK configuration;
  Data->get(configuration);
  WiFiScanClass WiFis;

  openSection(page, L_NETWORK_CONFIGURATION, L_NETWORK_CONFIGURATION_INFO);
  char _ssid[sizeof(configuration.ssid)];

  page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
  page.replace("{{item.label}}", L_SSID);
  page.replace("{{item.name}}", "ssid");

#ifdef DEBUG
  Serial << endl << "Searching for WiFi networks: ";
#endif
  int numberOfNetworks = WiFis.scanNetworks();

#ifdef DEBUG
  Serial << endl << " - found: " << numberOfNetworks;
#endif

  for (int i = 0; i < numberOfNetworks; i++) {

#ifdef DEBUG
    Serial << endl << " - " << WiFis.SSID(i);
#endif
    page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
    page.replace("{{item.value}}", WiFis.SSID(i));
    WiFis.SSID(i).toCharArray(_ssid, sizeof(_ssid));
    page.replace("{{item.label}}", _ssid);
    page.replace("{{item.selected}}", strcmp(_ssid, configuration.ssid) == 0
                                          ? " selected=\"selected\""
                                          : "");
  }
  page.concat("</select>");

  page += "<input type=\"submit\" class =\"b bc\" value=\"";
  page += L_REFRESH;
  page += "\" formaction=\"/?o=";
  page += ESP_CONFIG_SITE_NETWORK;
  page += "&c=0\"></div>";
  addInputFormItem(page, "password", "password", L_PASSWORD,
                   configuration.password, "32");

  closeSection(page);

  openSection(page, L_DEVICE_IP, L_DEVICE_IP_INFO);

  addCheckboxFormItem(page, "dhcp", L_DHCP_ENABLED, "1", configuration.isDHCP);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_TEXT, "ip", L_IP_ADDRESS,
                   configuration.ip);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_TEXT, "gateway", L_GATEWAY,
                   configuration.gateway);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_TEXT, "subnet", L_SUBNET,
                   configuration.subnet);

  closeSection(page);

  char _int[4];
  sprintf(_int, "%d", configuration.noConnectionAttempts);

  openSection(page, L_ADVANCED, "");

  page += "<fieldset>";

  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "na",
                   L_NUMBER_OF_CONNECTIONS, _int, ESP_FORM_ITEM_SKIP_PROPERTY,
                   "1", "255", "1");

  sprintf(_int, "%d", configuration.waitTimeConnections);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "wc",
                   L_TIME_BETWEEN_CONNECTIONS, _int,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "1", "255", "1", L_SECONDS);

  sprintf(_int, "%d", configuration.waitTimeSeries);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "ws", L_SLEEP_TIME, _int,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "1", "255", "1", L_SECONDS);

  closeSection(page);
}

#ifdef ESP_CONFIG_HARDWARE_I2C
void ESPSitesGenerator::siteI2CBUS(String &page, uint8_t id) {
  I2CBUS configuration;
  Data->get(id, configuration);
  openSection(page, "I2C", "");
  addListOfGPIOs(page, "sda", configuration.SDA, "SDA");
  addListOfGPIOs(page, "scl", configuration.SCL, "SCL");
  char _int[7];
  sprintf(_int, "%d", configuration.frequency);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "frequency", L_FREQUENCY,
                   _int, ESP_FORM_ITEM_SKIP_PROPERTY, "100000", "400000", "1",
                   "Hz");
  closeSection(page);
}

void ESPSitesGenerator::addI2CSelectFormItem(String &page, uint8_t id,
                                             uint8_t address,
                                             const char *label) {

  ESPI2CScanner I2CScanner;
  if (id == 0) {
    I2CScanner.begin(WirePort0);
  } else {
    I2CScanner.begin(WirePort1);
  }

  page.concat(FPSTR(HTTP_ITEM_SCANNED_I2C_ADDRESSES_HEADER));
  page.replace("{{item.label}}", label);
  page.replace("{{L_NONE}}", L_NONE);
  page.replace("{{item.selected}}", address == ESP_HARDWARE_ITEM_NOT_EXIST
                                        ? "selected=\"selected\""
                                        : "");
#ifdef DEBUG
  Serial << endl << "INFO: Scanning for devices on I2C" << endl;
#endif
  for (byte addressToScan = 1; addressToScan < 127; addressToScan++) {
    if (I2CScanner.scan(addressToScan)) {
      page.concat(FPSTR(HTTP_ITEM_SCANNED_I2C_ADDRESSES));
      page.replace("{{item.value}}", String(addressToScan));
      page.replace("{{item.selected}}",
                   addressToScan == address ? "selected=\"selected\"" : "");
      page.replace("{{device.address}}", String(addressToScan, HEX));
      page.replace("{{device.name}}", I2CScanner.getName(addressToScan));
    }
  }
  page.concat("</select></div>");
}

#endif

#ifdef ESP_CONFIG_HARDWARE_UART
void ESPSitesGenerator::siteUARTBUS(String &page, uint8_t id) {
  UARTBUS configuration;
  Data->get(id, configuration);
  openSection(page, "UART", "");
  addListOfGPIOs(page, "rxd", configuration.RXD, "RXD");
  addListOfGPIOs(page, "txd", configuration.TXD, "TXD");
  closeSection(page);
}
#endif

#ifdef ESP_CONFIG_HARDWARE_LED
void ESPSitesGenerator::siteLED(String &page, uint8_t id) {
  LED configuration;
  Data->get(id, configuration);
  char title[7];
  sprintf(title, "LED #%d", id + 1);
  openSection(page, title, "");
  addListOfGPIOs(page, "gpio", configuration.gpio);
  addCheckboxFormItem(page, "reverse", L_CHANGE_LED_INDICATION, "1",
                      configuration.reverseState);
  closeSection(page);
}
#endif

#ifdef ESP_CONFIG_HARDWARE_SWITCH
void ESPSitesGenerator::siteSwitch(String &page, uint8_t id) {
  SWITCH configuration;
  Data->get(id, configuration);
  char title[30];
  sprintf(title, "%s #%d", L_SWITCH_BUTTON, id + 1);
  openSection(page, title, "");
  addListOfGPIOs(page, "gpio", configuration.gpio);

  /* Item: PinMode */
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
  page.replace("{{item.label}}", "PinMode");
  page.replace("{{item.name}}", "pin");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.value}}", String(INPUT));
  page.replace("{{item.label}}", "INPUT");
  page.replace("{{item.selected}}",
               configuration.pinMode == INPUT ? " selected=\"selected\"" : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.value}}", String(INPUT_PULLUP));
  page.replace("{{item.label}}", "INPUT_PULLUP");
  page.replace("{{item.selected}}", configuration.pinMode == INPUT_PULLUP
                                        ? " selected=\"selected\""
                                        : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));

  /* Item: Functionality */
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
  page.replace("{{item.label}}", L_FUNCTIONALITY);
  page.replace("{{item.name}}", "functionality");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.value}}",
               String(ESP_CONFIG_HARDWARE_SWITCH_FUNCTIONALITY_NONE));
  page.replace("{{item.label}}", L_NONE);
  page.replace("{{item.selected}}",
               configuration.functionality ==
                       ESP_CONFIG_HARDWARE_SWITCH_FUNCTIONALITY_NONE
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.value}}",
               String(ESP_CONFIG_HARDWARE_SWITCH_FUNCTIONALITY_MULTI));
  page.replace("{{item.label}}", L_SYSTEM_BUTTON);
  page.replace("{{item.selected}}",
               configuration.functionality ==
                       ESP_CONFIG_HARDWARE_SWITCH_FUNCTIONALITY_MULTI
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));

  /* Item: Switch type */
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
  page.replace("{{item.label}}", L_TYPE);
  page.replace("{{item.name}}", "type");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.value}}",
               String(ESP_CONFIG_HARDWARE_SWITCH_TYPE_MONO_STABLE));
  page.replace("{{item.label}}", L_MONOSTABLE);
  page.replace("{{item.selected}}",
               configuration.type == ESP_CONFIG_HARDWARE_SWITCH_TYPE_MONO_STABLE
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.value}}",
               String(ESP_CONFIG_HARDWARE_SWITCH_TYPE_BI_STABLE));
  page.replace("{{item.label}}", L_BISTABLE);
  page.replace("{{item.selected}}",
               configuration.type == ESP_CONFIG_HARDWARE_SWITCH_TYPE_BI_STABLE
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));
  page.concat(FPSTR(HTTP_ITEM_HINT));
  page.replace("{{item.hint}}", L_SENSITIVENESS_HINT);

  /* Item: Bouncing */
  char _number[4];
  sprintf(_number, "%d", configuration.bouncing);

  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "bouncing", L_SENSITIVENESS,
                   _number, ESP_FORM_ITEM_SKIP_PROPERTY, "0", "999", "1",
                   L_MILISECONDS);

  closeSection(page);
}
#endif

#ifdef ESP_CONFIG_HARDWARE_ADC
void ESPSitesGenerator::siteADC(String &page, uint8_t id) {
  ADC configuration;
  Data->get(id, configuration);
  char _number[13];

  openSection(page, L_ANALOG_INPUT, "");

#ifdef ESP_CONFIG_HARDWARE_ADS1115
  if (Device->configuration.noOfI2Cs) {
    page.concat(FPSTR(HTTP_ITEM_HINT));
    page.replace("{{item.hint}}", L_GPIO_ANALOG_INPUT);
  }
#endif

  addListOfGPIOs(page, "gpio", configuration.gpio, "GPIO");

#ifdef ESP_CONFIG_HARDWARE_ADS1115
  if (Device->configuration.noOfI2Cs) {
    page.concat(FPSTR(HTTP_ITEM_HINT));
    page.replace("{{item.hint}}", L_ADS1115_ANALOG_INPUT);

    /* Item: I2C Bus selection */
    page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
    page.replace("{{item.label}}", "I2C BUS");
    page.replace("{{item.name}}", "i2c");
    page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
    page.replace("{{item.label}}", L_NONE);
    page.replace("{{item.value}}", String(ESP_HARDWARE_ITEM_NOT_EXIST));
    page.replace("{{item.selected}}",
                 configuration.i2c.inputId == ESP_HARDWARE_ITEM_NOT_EXIST
                     ? " selected=\"selected\""
                     : "");
    for (uint8_t i = 0; i < Device->configuration.noOfI2Cs; i++) {
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
      page.replace("{{item.label}}", String(i + 1));
      page.replace("{{item.value}}", String(i));
      page.replace("{{item.selected}}",
                   configuration.i2c.id == i ? " selected=\"selected\"" : "");
    }
    page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));

    /* Refresh button */
    page.concat(FPSTR(HTTP_ITEM_REFRESH_BUTTON));
    page.replace("{{item.label}}", L_REFRESH_SETTINGS_ADS1115);

    if (configuration.i2c.id != ESP_HARDWARE_ITEM_NOT_EXIST) {

      /* Item: I2C devices */
      addI2CSelectFormItem(page, configuration.i2c.id,
                           configuration.i2c.address, L_ADS1115_ADDRESS);

      /* Item: Analog Input ID */
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
      page.replace("{{item.label}}", L_ANALOG_INPUT);
      page.replace("{{item.name}}", "input");
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
      page.replace("{{item.label}}", L_NONE);
      page.replace("{{item.value}}", String(ESP_HARDWARE_ITEM_NOT_EXIST));
      page.replace("{{item.selected}}",
                   configuration.i2c.inputId == ESP_HARDWARE_ITEM_NOT_EXIST
                       ? " selected=\"selected\""
                       : "");

      char _ain[6];
      for (uint8_t i = 0; i < ESP_CONFIG_HARDWARE_ADS1115_MAX_INPUTS; i++) {
        page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
        sprintf(_ain, "AIN%d", i);
        page.replace("{{item.label}}", _ain);
        page.replace("{{item.value}}", String(i));
        page.replace("{{item.selected}}", configuration.i2c.inputId == i
                                              ? " selected=\"selected\""
                                              : "");
      }

      page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));

      /* Item: Number of samples per m.second */
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
      page.replace("{{item.label}}", L_ADS1115_NO_OF_SAMPLES_PER_SECOND);
      page.replace("{{item.name}}", "samplesPerSecond");
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
      page.replace("{{item.label}}", String(128));
      page.replace("{{item.value}}", String(ADS1115_REG_CONFIG_DR_128SPS));
      page.replace("{{item.selected}}", configuration.i2c.samplesPerSecond ==
                                                ADS1115_REG_CONFIG_DR_128SPS
                                            ? " selected=\"selected\""
                                            : "");
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
      page.replace("{{item.label}}", String(250));
      page.replace("{{item.value}}", String(ADS1115_REG_CONFIG_DR_250SPS));
      page.replace("{{item.selected}}", configuration.i2c.samplesPerSecond ==
                                                ADS1115_REG_CONFIG_DR_250SPS
                                            ? " selected=\"selected\""
                                            : "");
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
      page.replace("{{item.label}}", String(490));
      page.replace("{{item.value}}", String(ADS1115_REG_CONFIG_DR_490SPS));
      page.replace("{{item.selected}}", configuration.i2c.samplesPerSecond ==
                                                ADS1115_REG_CONFIG_DR_490SPS
                                            ? " selected=\"selected\""
                                            : "");
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
      page.replace("{{item.label}}", String(920));
      page.replace("{{item.value}}", String(ADS1115_REG_CONFIG_DR_920SPS));
      page.replace("{{item.selected}}", configuration.i2c.samplesPerSecond ==
                                                ADS1115_REG_CONFIG_DR_920SPS
                                            ? " selected=\"selected\""
                                            : "");
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
      page.replace("{{item.label}}", String(1600));
      page.replace("{{item.value}}", String(ADS1115_REG_CONFIG_DR_1600SPS));
      page.replace("{{item.selected}}", configuration.i2c.samplesPerSecond ==
                                                ADS1115_REG_CONFIG_DR_1600SPS
                                            ? " selected=\"selected\""
                                            : "");
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
      page.replace("{{item.label}}", String(2400));
      page.replace("{{item.value}}", String(ADS1115_REG_CONFIG_DR_2400SPS));
      page.replace("{{item.selected}}", configuration.i2c.samplesPerSecond ==
                                                ADS1115_REG_CONFIG_DR_2400SPS
                                            ? " selected=\"selected\""
                                            : "");
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
      page.replace("{{item.label}}", String(3330));
      page.replace("{{item.value}}", String(ADS1115_REG_CONFIG_DR_3300SPS));
      page.replace("{{item.selected}}", configuration.i2c.samplesPerSecond ==
                                                ADS1115_REG_CONFIG_DR_3300SPS
                                            ? " selected=\"selected\""
                                            : "");

      page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));

      /* Item: Gain */
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));

      page.replace("{{item.label}}", L_ADS1115_GAIN);
      page.replace("{{item.name}}", "gain");
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
      page.replace("{{item.label}}", "2/3 +/-6.144V");
      page.replace("{{item.value}}", String(GAIN_TWOTHIRDS));
      page.replace("{{item.selected}}", configuration.i2c.gain == GAIN_TWOTHIRDS
                                            ? " selected=\"selected\""
                                            : "");
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
      page.replace("{{item.label}}", "1 +/-4.096V");
      page.replace("{{item.value}}", String(GAIN_ONE));
      page.replace("{{item.selected}}", configuration.i2c.gain == GAIN_ONE
                                            ? " selected=\"selected\""
                                            : "");
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
      page.replace("{{item.label}}", "2 +/-2.048V");
      page.replace("{{item.value}}", String(GAIN_TWO));
      page.replace("{{item.selected}}", configuration.i2c.gain == GAIN_TWO
                                            ? " selected=\"selected\""
                                            : "");
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
      page.replace("{{item.label}}", "4 +/-1.024V");
      page.replace("{{item.value}}", String(GAIN_FOUR));
      page.replace("{{item.selected}}", configuration.i2c.gain == GAIN_FOUR
                                            ? " selected=\"selected\""
                                            : "");
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
      page.replace("{{item.label}}", "8 +/-0.512V");
      page.replace("{{item.value}}", String(GAIN_EIGHT));
      page.replace("{{item.selected}}", configuration.i2c.gain == GAIN_EIGHT
                                            ? " selected=\"selected\""
                                            : "");
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
      page.replace("{{item.label}}", "16 +/-0.256V");
      page.replace("{{item.value}}", String(GAIN_SIXTEEN));
      page.replace("{{item.selected}}", configuration.i2c.gain == GAIN_SIXTEEN
                                            ? " selected=\"selected\""
                                            : "");

      page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));
    }
  }
#endif

  closeSection(page);

  openSection(page, L_READS, "");

  sprintf(_number, "%d", configuration.interval);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "interval",
                   L_MEASURMENTS_INTERVAL, _number, ESP_FORM_ITEM_SKIP_PROPERTY,
                   "20", "3600000", "1", L_MILISECONDS);

  sprintf(_number, "%d", configuration.numberOfSamples);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "samples",
                   L_NUMBER_OF_SAMPLES, _number, ESP_FORM_ITEM_SKIP_PROPERTY,
                   "1", "999", "1");

  closeSection(page);

  openSection(page, L_ADC_INPUT_PARAMETERS, "");

  sprintf(_number, "%-.4f", (float)configuration.maxVCC);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "vcc", L_MEASURED_VOLTAGE,
                   _number, ESP_FORM_ITEM_SKIP_PROPERTY, "0", "24", "0.0001",
                   configuration.i2c.address != ESP_HARDWARE_ITEM_NOT_EXIST &&
                           configuration.i2c.id != ESP_HARDWARE_ITEM_NOT_EXIST
                       ? L_ADS1115_SET_BY_GAIN
                       : "V",
                   configuration.i2c.address != ESP_HARDWARE_ITEM_NOT_EXIST &&
                           configuration.i2c.id != ESP_HARDWARE_ITEM_NOT_EXIST
                       ? true
                       : false);

  sprintf(_number, "%d", (uint32_t)configuration.resolution);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "resolution",
                   L_ADC_RESOLUTION, _number, ESP_FORM_ITEM_SKIP_PROPERTY,
                   "1023", "65535", "1");

  closeSection(page);

  openSection(page, L_VOLTAGE_DIVIDER, "");

  sprintf(_number, "%d", (uint32_t)configuration.divider.Ra);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "ra", "R[a]", _number,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "0", "90000000", "1", "Om");

  sprintf(_number, "%d", (uint32_t)configuration.divider.Rb);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "rb", "R[b]", _number,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "0", "90000000", "1", "Om");

  double maxVCCToMeasure;
  if (configuration.divider.Ra == 0 || configuration.divider.Rb == 0) {
    maxVCCToMeasure = configuration.maxVCC;
  } else {
    maxVCCToMeasure =
        configuration.maxVCC /
        ((double)configuration.divider.Rb /
         ((double)configuration.divider.Rb + (double)configuration.divider.Ra));
  }

#ifdef DEBUG
  Serial << endl
         << "INFO: Max voltage possible to measure is: " << maxVCCToMeasure;
#endif

  sprintf(_number, "%-.6f", (float)maxVCCToMeasure);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "max",
                   L_MEASURED_DIVIDER_VOLTAGE, _number,
                   ESP_FORM_ITEM_SKIP_PROPERTY, ESP_FORM_ITEM_SKIP_PROPERTY,
                   ESP_FORM_ITEM_SKIP_PROPERTY, ESP_FORM_ITEM_SKIP_PROPERTY,
                   L_REFRESHED_AFTER_SAVE, true);

  closeSection(page);
}

#endif // ESP_CONFIG_HARDWARE_ADC

#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
void ESPSitesGenerator::siteBinarySensor(String &page, uint8_t id) {
  BINARY_SENSOR configuration;
  Data->get(id, configuration);
  char _number[13];

  openSection(page, L_BINARY_SENSOR, "");

  /* Item: GPIO */
  addListOfGPIOs(page, "gpio", configuration.gpio, "GPIO");

  /* Item: Interval */
  sprintf(_number, "%d", configuration.interval);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "interval",
                   L_MEASURMENTS_INTERVAL, _number, ESP_FORM_ITEM_SKIP_PROPERTY,
                   "20", "3600000", "1", L_MILISECONDS);

  /* Item: Bouncing */
  sprintf(_number, "%d", configuration.bouncing);

  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "bouncing", L_SENSITIVENESS,
                   _number, ESP_FORM_ITEM_SKIP_PROPERTY, "0", "999", "1",
                   L_MILISECONDS);

  closeSection(page);
}
#endif // ESP_CONFIG_HARDWARE_SENSOR_BINARY

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
void ESPSitesGenerator::siteDS18B20Sensor(String &page, uint8_t id) {

  ESPDS18B20Sensor _Sensor;
  DS18B20Addresses _addresses;
  uint8_t numberOfFoundSensors;
  DS18B20_SENSOR configuration;
  Data->get(id, configuration);
  char _number[13];

  openSection(page, L_DS18B20_SENSOR, "");

  /* Item: GPIO */
  addListOfGPIOs(page, "gpio", configuration.gpio, "GPIO");

  numberOfFoundSensors = _Sensor.scan(configuration.gpio, _addresses);

  if (numberOfFoundSensors > 0) {

    page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
    page.replace("{{item.label}}", L_ADDRESS);
    page.replace("{{item.name}}", "address");

    char _scannedAddressText[17];
    char _configAddressText[17];
    for (uint8_t i = 0; i < numberOfFoundSensors; i++) {
      _Sensor.addressToChar(_addresses[i], _scannedAddressText);
      _Sensor.addressToChar(configuration.address, _configAddressText);
      page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
      page.replace("{{item.label}}", _scannedAddressText);
      page.replace("{{item.value}}", _scannedAddressText);
      page.replace("{{item.selected}}",
                   memcmp(_addresses[i], configuration.address,
                          sizeof(_addresses[i])) == 0
                       ? " selected=\"selected\""
                       : "");
    }
    page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));
  }

  /* Item: Interval */
  sprintf(_number, "%d", configuration.interval);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "interval",
                   L_MEASURMENTS_INTERVAL, _number, ESP_FORM_ITEM_SKIP_PROPERTY,
                   "20", "3600000", "1", L_MILISECONDS);

  /* Item: Unit */
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
  page.replace("{{item.label}}", L_UNIT);
  page.replace("{{item.name}}", "unit");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", L_TEMPERATURE_C);
  page.replace("{{item.value}}",
               String(ESP_CONFIG_FUNCTIONALITY_TEMPERATURE_UNIT_CELSIUS));
  page.replace("{{item.selected}}",
               configuration.unit ==
                       ESP_CONFIG_FUNCTIONALITY_TEMPERATURE_UNIT_CELSIUS
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", L_TEMPERATURE_F);
  page.replace("{{item.value}}",
               String(ESP_CONFIG_FUNCTIONALITY_TEMPERATURE_UNIT_FARENHIAT));
  page.replace("{{item.selected}}",
               configuration.unit ==
                       ESP_CONFIG_FUNCTIONALITY_TEMPERATURE_UNIT_FARENHIAT
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));

  /* Item: Correction */
  sprintf(_number, "%-.3f", configuration.correction);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "correction",
                   L_TEMPERATURE_CORRECTIONS, _number,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "-99.999", "99.999", "0.001");

  closeSection(page);
}
#endif // ESP_CONFIG_HARDWARE_SENSOR_DS18B20

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
void ESPSitesGenerator::siteNTCSensor(String &page, uint8_t id) {
  NTC_SENSOR configuration;
  Data->get(id, configuration);
  char _number[11];

  openSection(page, L_NTC_SENSOR, "");

  /* Item: ADC */
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
  page.replace("{{item.label}}", L_ANALOG_INPUT);
  page.replace("{{item.name}}", "adc");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", L_NONE);
  page.replace("{{item.value}}", String(ESP_HARDWARE_ITEM_NOT_EXIST));
  page.replace("{{item.selected}}",
               configuration.adcInput == ESP_HARDWARE_ITEM_NOT_EXIST
                   ? " selected=\"selected\""
                   : "");
  for (uint8_t i = 0; i < Device->configuration.noOfADCs; i++) {
    page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
    page.replace("{{item.label}}", String(i + 1));
    page.replace("{{item.value}}", String(i));
    page.replace("{{item.selected}}",
                 configuration.adcInput == i ? " selected=\"selected\"" : "");
  }
  page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));

  /* Item: Vcc */
  sprintf(_number, "%-.4f", configuration.vcc);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "vcc", L_NTC_VCC, _number,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "0", "10", "0.0001", "V");

  /* Item: R */
  sprintf(_number, "%d", configuration.resistor);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "resistor", L_NTC_RESISTOR,
                   _number, ESP_FORM_ITEM_SKIP_PROPERTY, "0", "9999999", "1",
                   "Om");

  /* Item: Interval */
  sprintf(_number, "%d", configuration.interval);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "interval",
                   L_MEASURMENTS_INTERVAL, _number, ESP_FORM_ITEM_SKIP_PROPERTY,
                   "20", "3600000", "1", L_MILISECONDS);

  /* Item: Unit */
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
  page.replace("{{item.label}}", L_UNIT);
  page.replace("{{item.name}}", "unit");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", L_TEMPERATURE_C);
  page.replace("{{item.value}}",
               String(ESP_CONFIG_FUNCTIONALITY_TEMPERATURE_UNIT_CELSIUS));
  page.replace("{{item.selected}}",
               configuration.unit ==
                       ESP_CONFIG_FUNCTIONALITY_TEMPERATURE_UNIT_CELSIUS
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", L_TEMPERATURE_F);
  page.replace("{{item.value}}",
               String(ESP_CONFIG_FUNCTIONALITY_TEMPERATURE_UNIT_FARENHIAT));
  page.replace("{{item.selected}}",
               configuration.unit ==
                       ESP_CONFIG_FUNCTIONALITY_TEMPERATURE_UNIT_FARENHIAT
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));

  /* Item: Correction */
  sprintf(_number, "%-.3f", configuration.correction);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "correction",
                   L_TEMPERATURE_CORRECTIONS, _number,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "-99.999", "99.999", "0.001");
  closeSection(page);

  openSection(page, L_NTC_COEFFICIENT_A, L_NTC_COEFFICIENT_DESC);

  /* Item: A */
  sprintf(_number, "%-.6lf", configuration.coefficients.A.value);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "A", "Wartość", _number,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "0", "999.999999", "0.000001");

  /* Item: Precision */
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
  page.replace("{{item.label}}", L_FLOAT_PRECISION);
  page.replace("{{item.name}}", "AP");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "A / 1");
  page.replace("{{item.value}}", String(ESP_CONFIG_HARDWARE_FLOAT_PRECISION_0));
  page.replace("{{item.selected}}",
               configuration.coefficients.A.precision ==
                       ESP_CONFIG_HARDWARE_FLOAT_PRECISION_0
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "A / 1,000");
  page.replace("{{item.value}}", String(ESP_CONFIG_HARDWARE_FLOAT_PRECISION_3));
  page.replace("{{item.selected}}",
               configuration.coefficients.A.precision ==
                       ESP_CONFIG_HARDWARE_FLOAT_PRECISION_3
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "A / 1,000,000");
  page.replace("{{item.value}}", String(ESP_CONFIG_HARDWARE_FLOAT_PRECISION_6));
  page.replace("{{item.selected}}",
               configuration.coefficients.A.precision ==
                       ESP_CONFIG_HARDWARE_FLOAT_PRECISION_6
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "A / 1,000,000,000");
  page.replace("{{item.value}}", String(ESP_CONFIG_HARDWARE_FLOAT_PRECISION_9));
  page.replace("{{item.selected}}",
               configuration.coefficients.A.precision ==
                       ESP_CONFIG_HARDWARE_FLOAT_PRECISION_9
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));

  closeSection(page);

  openSection(page, L_NTC_COEFFICIENT_B, L_NTC_COEFFICIENT_DESC);

  /* Item: B */
  sprintf(_number, "%-.6lf", configuration.coefficients.B.value);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "B", "Wartość", _number,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "0", "999.999999", "0.000001");

  /* Item: Precision */
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
  page.replace("{{item.label}}", L_FLOAT_PRECISION);
  page.replace("{{item.name}}", "BP");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "B / 1");
  page.replace("{{item.value}}", String(ESP_CONFIG_HARDWARE_FLOAT_PRECISION_0));
  page.replace("{{item.selected}}",
               configuration.coefficients.B.precision ==
                       ESP_CONFIG_HARDWARE_FLOAT_PRECISION_0
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "B / 1,000");
  page.replace("{{item.value}}", String(ESP_CONFIG_HARDWARE_FLOAT_PRECISION_3));
  page.replace("{{item.selected}}",
               configuration.coefficients.B.precision ==
                       ESP_CONFIG_HARDWARE_FLOAT_PRECISION_3
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "B / 1,000,000");
  page.replace("{{item.value}}", String(ESP_CONFIG_HARDWARE_FLOAT_PRECISION_6));
  page.replace("{{item.selected}}",
               configuration.coefficients.B.precision ==
                       ESP_CONFIG_HARDWARE_FLOAT_PRECISION_6
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "B / 1,000,000,000");
  page.replace("{{item.value}}", String(ESP_CONFIG_HARDWARE_FLOAT_PRECISION_9));
  page.replace("{{item.selected}}",
               configuration.coefficients.B.precision ==
                       ESP_CONFIG_HARDWARE_FLOAT_PRECISION_9
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));

  closeSection(page);

  openSection(page, L_NTC_COEFFICIENT_C, L_NTC_COEFFICIENT_DESC);

  /* Item: C */
  sprintf(_number, "%-.6lf", configuration.coefficients.C.value);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "C", "Wartość", _number,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "0", "999.999999", "0.000001");

  /* Item: Precision */
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
  page.replace("{{item.label}}", L_FLOAT_PRECISION);
  page.replace("{{item.name}}", "CP");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "C / 1");
  page.replace("{{item.value}}", String(ESP_CONFIG_HARDWARE_FLOAT_PRECISION_0));
  page.replace("{{item.selected}}",
               configuration.coefficients.C.precision ==
                       ESP_CONFIG_HARDWARE_FLOAT_PRECISION_0
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "C / 1,000");
  page.replace("{{item.value}}", String(ESP_CONFIG_HARDWARE_FLOAT_PRECISION_3));
  page.replace("{{item.selected}}",
               configuration.coefficients.C.precision ==
                       ESP_CONFIG_HARDWARE_FLOAT_PRECISION_3
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "C / 1,000,000");
  page.replace("{{item.value}}", String(ESP_CONFIG_HARDWARE_FLOAT_PRECISION_6));
  page.replace("{{item.selected}}",
               configuration.coefficients.C.precision ==
                       ESP_CONFIG_HARDWARE_FLOAT_PRECISION_6
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "C / 1,000,000,000");
  page.replace("{{item.value}}", String(ESP_CONFIG_HARDWARE_FLOAT_PRECISION_9));
  page.replace("{{item.selected}}",
               configuration.coefficients.C.precision ==
                       ESP_CONFIG_HARDWARE_FLOAT_PRECISION_9
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));

  closeSection(page);
}
#endif // ESP_CONFIG_HARDWARE_SENSOR_NTC

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
void ESPSitesGenerator::siteBatterymeter(String &page, uint8_t id) {
  BATTERYMETER configuration;
  Data->get(id, configuration);
  char _number[17];

  openSection(page, L_BATTERY_METER, "");

  /* Item: ADC */
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
  page.replace("{{item.label}}", L_ANALOG_INPUT);
  page.replace("{{item.name}}", "adc");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", L_NONE);
  page.replace("{{item.value}}", String(ESP_HARDWARE_ITEM_NOT_EXIST));
  page.replace("{{item.selected}}",
               configuration.adcInput == ESP_HARDWARE_ITEM_NOT_EXIST
                   ? " selected=\"selected\""
                   : "");
  for (uint8_t i = 0; i < Device->configuration.noOfADCs; i++) {
    page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
    page.replace("{{item.label}}", String(i + 1));
    page.replace("{{item.value}}", String(i));
    page.replace("{{item.selected}}",
                 configuration.adcInput == i ? " selected=\"selected\"" : "");
  }
  page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));

  /* Item: Interval */
  sprintf(_number, "%d", configuration.interval);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "interval",
                   L_MEASURMENTS_INTERVAL, _number, ESP_FORM_ITEM_SKIP_PROPERTY,
                   "20", "3600000", "1", L_MILISECONDS);

  /* Item: Min V */
  sprintf(_number, "%-.4f", configuration.voltage.min);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "vMin", L_BATTERY_MIN_LEVEL,
                   _number, ESP_FORM_ITEM_SKIP_PROPERTY, "0", "200", "0.0001",
                   "V");

  /* Item: Max V */
  sprintf(_number, "%-.4f", configuration.voltage.max);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "vMax", L_BATTERY_MAX_LEVEL,
                   _number, ESP_FORM_ITEM_SKIP_PROPERTY, "0", "200", "0.0001",
                   "V");

  closeSection(page);
}
#endif // ESP_CONFIG_FUNCTIONALITY_BATTERYMETER

#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
void ESPSitesGenerator::siteACS758(String &page, uint8_t id) {
  ACS758_SENSOR configuration;
  Data->get(id, configuration);
  char _number[8];

  openSection(page, L_ACS758_SENSOR, "");

  /* Item: ADC */
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
  page.replace("{{item.label}}", L_ANALOG_INPUT);
  page.replace("{{item.name}}", "adc");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", L_NONE);
  page.replace("{{item.value}}", String(ESP_HARDWARE_ITEM_NOT_EXIST));
  page.replace("{{item.selected}}",
               configuration.adcInput == ESP_HARDWARE_ITEM_NOT_EXIST
                   ? " selected=\"selected\""
                   : "");
  for (uint8_t i = 0; i < Device->configuration.noOfADCs; i++) {
    page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
    page.replace("{{item.label}}", String(i + 1));
    page.replace("{{item.value}}", String(i));
    page.replace("{{item.selected}}",
                 configuration.adcInput == i ? " selected=\"selected\"" : "");
  }
  page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));

  
  /* Item: type */
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
  page.replace("{{item.label}}", L_TYPE);
  page.replace("{{item.name}}", "type");
    page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", L_SELECT);
  page.replace("{{item.value}}",
               String(ESP_HARDWARE_ITEM_NOT_EXIST));
  page.replace("{{item.selected}}",
               configuration.type == ESP_HARDWARE_ITEM_NOT_EXIST
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "ACS758LCB 50A B");
  page.replace("{{item.value}}",
               String(ESP_CONFIG_HARDWARE_SENSOR_ACS758LCB_050B));
  page.replace("{{item.selected}}",
               configuration.type == ESP_CONFIG_HARDWARE_SENSOR_ACS758LCB_050B
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "ACS758LCB 50A U");
  page.replace("{{item.value}}",
               String(ESP_CONFIG_HARDWARE_SENSOR_ACS758LCB_050U));
  page.replace("{{item.selected}}",
               configuration.type == ESP_CONFIG_HARDWARE_SENSOR_ACS758LCB_050U
                   ? " selected=\"selected\""
                   : "");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "ACS758LCB 100A B");
  page.replace("{{item.value}}",
               String(ESP_CONFIG_HARDWARE_SENSOR_ACS758LCB_100B));
  page.replace("{{item.selected}}",
               configuration.type == ESP_CONFIG_HARDWARE_SENSOR_ACS758LCB_100B
                   ? " selected=\"selected\""
                   : "");         
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "ACS758LCB 100A U");
  page.replace("{{item.value}}",
               String(ESP_CONFIG_HARDWARE_SENSOR_ACS758LCB_100U));
  page.replace("{{item.selected}}",
               configuration.type == ESP_CONFIG_HARDWARE_SENSOR_ACS758LCB_100U
                   ? " selected=\"selected\""
                   : "");    
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "ACS758KCB 150A B");
  page.replace("{{item.value}}",
               String(ESP_CONFIG_HARDWARE_SENSOR_ACS758KCB_150B));
  page.replace("{{item.selected}}",
               configuration.type == ESP_CONFIG_HARDWARE_SENSOR_ACS758KCB_150B
                   ? " selected=\"selected\""
                   : "");   
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "ACS758KCB 150A U");
  page.replace("{{item.value}}",
               String(ESP_CONFIG_HARDWARE_SENSOR_ACS758KCB_150U));
  page.replace("{{item.selected}}",
               configuration.type == ESP_CONFIG_HARDWARE_SENSOR_ACS758KCB_150U
                   ? " selected=\"selected\""
                   : "");      
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "ACS758ECB 200A B");
  page.replace("{{item.value}}",
               String(ESP_CONFIG_HARDWARE_SENSOR_ACS758ECB_200B));
  page.replace("{{item.selected}}",
               configuration.type == ESP_CONFIG_HARDWARE_SENSOR_ACS758ECB_200B
                   ? " selected=\"selected\""
                   : "");     
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", "ACS758ECB 200A U");
  page.replace("{{item.value}}",
               String(ESP_CONFIG_HARDWARE_SENSOR_ACS758ECB_200U));
  page.replace("{{item.selected}}",
               configuration.type == ESP_CONFIG_HARDWARE_SENSOR_ACS758ECB_200U
                   ? " selected=\"selected\""
                   : "");                                                                                                                    
  page.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));

    /* Item: Interval */
  sprintf(_number, "%d", configuration.interval);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "interval",
                   L_MEASURMENTS_INTERVAL, _number, ESP_FORM_ITEM_SKIP_PROPERTY,
                   "20", "3600000", "1", L_MILISECONDS);

  
  /* Item: VCC */
  sprintf(_number, "%-.6f", configuration.vcc);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "vcc",
                   L_VCC, _number, ESP_FORM_ITEM_SKIP_PROPERTY,
                   "2", "6", "0.000001", "V");


  /* Item: Current CutOff */
  sprintf(_number, "%-.2f", configuration.currentCutOff);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "currentCutOff",
                   L_ACS758_CURRENT_CUTOFF, _number, ESP_FORM_ITEM_SKIP_PROPERTY,
                   "0", "200", "0.01", "A");
                   

  closeSection(page);
}
#endif // ESP_CONFIG_HARDWARE_SENSOR_ACS758
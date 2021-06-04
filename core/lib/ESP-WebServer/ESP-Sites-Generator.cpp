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
  page += FPSTR(HTTP_HEADER);
  if (redirect > 0) {
    page.replace("{{s.r}}", "<meta http-equiv=\"refresh\" content=\"" +
                                String(redirect) + "; url=/\">");
  } else {
    page.replace("{{s.r}}", "");
  }
  page.concat(F("<div class=\"c\">"));
}

void ESPSitesGenerator::generateEmptyMenu(String &page, uint16_t redirect) {
  generateHeader(page, redirect);
  page.concat(F("<div class=\"l\">{{A}}<small style=\"opacity:.3\">"));
  page.concat(F(L_VERSION));
  page.concat(F(" {{f.v}}</small></div><div class=\"r\">"));
}

void ESPSitesGenerator::generateMenu(String &page, uint16_t redirect) {
  Device->begin(Data);

  generateHeader(page, redirect);
  page.concat(F("<div class=\"l\">{{A}}<small style=\"opacity:.3\">"));
  page.concat(F(L_VERSION));
  page.concat(F(" {{f.v}}</small><ul class=\"lst\">"));

  page.concat(FPSTR(HTTP_MENU_HEADER));
  page.replace("{{m.h}}", F("Menu"));

  /* Gnerating Menu */
  addMenuItem(page, F(L_DEVICE), ESP_CONFIG_SITE_DEVICE);

  page.concat(FPSTR(HTTP_MENU_HEADER));
  page.replace("{{m.h}}", F(L_CONNECTIONS));

  addMenuItem(page, F(L_NETWORK), ESP_CONFIG_SITE_NETWORK);

/* I2C */
#ifdef ESP_CONFIG_HARDWARE_I2C
  if (Device->configuration.noOfI2Cs > 0) {
    addMenuHeaderItem(page, F("I2C BUS"));
    addMenuSubItem(page, "I2C", Device->configuration.noOfI2Cs,
                   ESP_CONFIG_SITE_I2C);
  }
#endif // ESP_CONFIG_HARDWARE_I2C

/* UART */
#ifdef ESP_CONFIG_HARDWARE_UART
  if (Device->configuration.noOfUARTs > 0) {
    addMenuHeaderItem(page, F("UART BUS"));
    addMenuSubItem(page, "UART", Device->configuration.noOfUARTs,
                   ESP_CONFIG_SITE_UART);
  }
#endif // ESP_CONFIG_HARDWARE_UART

  page.concat(FPSTR(HTTP_MENU_HEADER));
  page.replace("{{m.h}}", F(L_HARDWARE));

#ifdef ESP_CONFIG_HARDWARE_LED
  if (Device->configuration.noOfLEDs > 0) {
    addMenuHeaderItem(page, F(L_LEDS));
    addMenuSubItem(page, "LED", Device->configuration.noOfLEDs,
                   ESP_CONFIG_SITE_LED);
  }
#endif // ESP_CONFIG_HARDWARE_LED

#ifdef ESP_CONFIG_HARDWARE_SWITCH
  if (Device->configuration.noOfSwitches > 0) {
    addMenuHeaderItem(page, F(L_BUTTONS_SWITCHES));
    addMenuSubItem(page, L_SWITCH, Device->configuration.noOfSwitches,
                   ESP_CONFIG_SITE_SWITCH);
  }
#endif // ESP_CONFIG_HARDWARE_SWITCH

#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
  if (Device->configuration.noOfBinarySensors > 0) {
    addMenuHeaderItem(page, F(L_BINARY_SENSOR));
    addMenuSubItem(page, L_SENSOR, Device->configuration.noOfBinarySensors,
                   ESP_CONFIG_SITE_BINARY_SENSOR);
  }
#endif // ESP_CONFIG_HARDWARE_SENSOR_BINARY

/* Sensor DS18B20 */
#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
  if (Device->configuration.noOfDS18B20s > 0) {

    addMenuHeaderItem(page, F(L_DS18B20_SENSORS));
    addMenuSubItem(page, L_SENSOR, Device->configuration.noOfDS18B20s,
                   ESP_CONFIG_SITE_DS18B20_SENSOR);
  }
#endif // ESP_CONFIG_HARDWARE_SENSOR_DS18B20

#ifdef ESP_CONFIG_HARDWARE_ADC
  if (Device->configuration.noOfADCs > 0) {
    addMenuHeaderItem(page, F(L_ANALOG_INPUTS));
    addMenuSubItem(page, L_INPUT, Device->configuration.noOfADCs,
                   ESP_CONFIG_SITE_ADC);
  }
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
  if (Device->configuration.noOfNTCs > 0) {
    addMenuHeaderItem(page, F(L_NTC_SENSOR));
    addMenuSubItem(page, L_NTC_TERMISTOR, Device->configuration.noOfNTCs,
                   ESP_CONFIG_SITE_NTC_SENSOR);
  }
#endif // ESP_CONFIG_HARDWARE_SENSOR_NTC

#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
  if (Device->configuration.noOfACS758s > 0) {
    addMenuHeaderItem(page, F(L_ACS758_SENSOR));
    addMenuSubItem(page, L_SENSOR, Device->configuration.noOfACS758s,
                   ESP_CONFIG_SITE_ACS758);
  }
#endif // ESP_CONFIG_HARDWARE_SENSOR_NTC

  page.concat(FPSTR(HTTP_MENU_HEADER));
  page.replace("{{m.h}}", F(L_FUNCTIONS));

/* System LED */
#ifdef ESP_CONFIG_HARDWARE_LED
  if (Device->configuration.noOfLEDs > 0) {
    addMenuItem(page, F(L_LED_SYSTEM), ESP_CONFIG_SITE_SYSTEM_LED);
  }
#endif

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
  if (Device->configuration.noOfADCs > 0 &&
      Device->configuration.noOfBatterymeters > 0) {
    addMenuHeaderItem(page, F(L_BATTERY_METERS));
    addMenuSubItem(page, L_BATTERY_METER,
                   Device->configuration.noOfBatterymeters,
                   ESP_CONFIG_SITE_BATTERYMETER);
  }
#endif // ESP_CONFIG_FUNCTIONALITY_BATTERYMETER

  page.concat(FPSTR(HTTP_MENU_HEADER));
  page.replace("{{m.h}}", F(L_FIRMWARE));

// addMenuItem(page, F(L_PASSWORD_SET_PASSWORD), ESP_CONFIG_SITE_PASSWORD);
#ifndef ESP_CONFIG_OTA_NOT_UPGRADABLE
  addMenuItem(page, F(L_FIRMWARE_UPGRADE), ESP_CONFIG_SITE_UPGRADE);
#endif
  addMenuItem(page, F(L_RESET_DEVICE), ESP_CONFIG_SITE_RESET);

  page.concat(F("</ul><h4></h4><ul class=\"lst\">"));

  addMenuItem(page, F(L_FINISH_CONFIGURATION), ESP_CONFIG_SITE_EXIT);

  /* Information section */
  page.concat(F("</ul></div><div class=\"r\">"));
}

void ESPSitesGenerator::siteConnecting(String &page) {
  page.concat("<p>Connecting</p>");
}

void ESPSitesGenerator::siteUpgrade(String &page) {

  openSection(page, F(L_UPGRADE_FROM_FILE), F(""));

  page.concat(F("<form method=\"post\" action=\"upgrade?o="));
  page += ESP_CONFIG_SITE_POST_UPGRADE;
  page.concat(
      F("\" enctype=\"multipart/form-data\"><div "
        "class=\"cf\"><label>{{L1}}</label><input "
        "class=\"bs\" "
        "name=\"update\" type=\"file\" accept=\".bin\"></div><input "
        "style=\"margin-top:1.5em\" type=\"submit\" value=\"{{L2}}\" class=\"b "
        "be\"></form>"));

  page.replace("{{L1}}", F(L_UPGRADE_SELECT_FIRMWARE));
  page.replace("{{L2}}", F(L_UPGRADE));
  closeSection(page);
  /*
    openMessageSection(page, F(L_UPGRADE_FIRMWAR_YOUR_CURRENT_FIRMWARE), F(""));
    page.concat(FPSTR(HTTP_MESSAGE_LINE_ITEM));
    page.replace("{{I}}", F(L_UPGRADE_FIRMWARE_VERSION));
    page.concat(FPSTR(HTTP_MESSAGE_LINE_ITEM));
    page.replace("{{I}}", F(L_UPGRADE_FIRMWARE_DEVICE_NAME));
    page.concat(FPSTR(HTTP_MESSAGE_LINE_ITEM));
    page.replace("{{I}}", F(L_UPGRADE_FIRMWARE_API));
    page.concat(FPSTR(HTTP_MESSAGE_LINE_ITEM));
    page.replace("{{I}}", F(L_UPGRADE_FIRMWARE_DEVICE_ID));
    closeMessageSection(page);
  */
}

void ESPSitesGenerator::sitePostUpgrade(String &page, boolean status) {
  openMessageSection(page, F(L_FIRMWARE_UPGRADE), F(""));
  page.concat(FPSTR(HTTP_MESSAGE_LINE_ITEM));
  if (!status) {
    page.replace("{{I}}", F(L_UPGRADE_FAILED));
  } else {
    page.replace("{{I}}", F(L_UPGRADE_SUCCESSFUL));
  }
  page.concat(FPSTR(HTTP_MESSAGE_LINE_ITEM));
  page.replace("{{I}}", F(L_UPGRADE_DEVICE_WILL_BE_REBOOTED));
  closeMessageSection(page);
}

void ESPSitesGenerator::siteReset(String &page) {
  openMessageSection(page, F(L_UPGRADE_RESTORING_DEFAULT_SETTING), F(""));
  page.concat(FPSTR(HTTP_MESSAGE_LINE_ITEM));
  page.replace("{{I}}", F(L_RESTORE_CONFIGURATION_WILL_BE_REMOVED));
  page.concat(F("</ul>"));
  page.concat(
      F("<input style=\"margin-top:1.5em\" type=\"submit\" class=\"b be\" "
        "value=\"{{L}}\">"));
  page.replace("{{L}}", F(L_UPGRADE_RESTORE_DEFAULT_SETTINGS));
  closeSection(page);
}

void ESPSitesGenerator::sitePostReset(String &page) {
  openMessageSection(page, F(L_UPGRADE_RESTORING_DEFAULT_SETTING), F(""));
  page.concat(FPSTR(HTTP_MESSAGE_LINE_ITEM));
  page.replace("{{I}}", F(L_RESTORE_IN_PROGRESS));
  page.concat(FPSTR(HTTP_MESSAGE_LINE_ITEM));
  page.replace("{{I}}",
               F(L_RESTORE_NETWORK_CONNECT_TO_HOTSPOT_AFTER_UPGRADE_AFE));
  page.concat(FPSTR(HTTP_MESSAGE_LINE_ITEM));
  page.replace("{{I}}", F(L_RESTORE_NETWORK_OPEN_PANEL));
  closeMessageSection(page);
}

void ESPSitesGenerator::siteExit(String &page, uint8_t command) {
  openMessageSection(page, F(L_UPGRADE_REBOOT), F(""));

  page.concat(FPSTR(HTTP_MESSAGE_LINE_ITEM));
  page.replace("{{I}}", F(L_UPGRADE_REBOOT_IN_PROGRESS));

  page.concat(FPSTR(HTTP_MESSAGE_LINE_ITEM));
  if (command != ESP_MODE_ACCESS_POINT) {
    page.replace("{{I}}", F(L_UPGRADE_SITE_WILL_BE_RELOADED));
  } else {
    page.replace("{{I}}",
                 F(L_RESTORE_NETWORK_CONNECT_TO_HOTSPOT_AFTER_UPGRADE));
    page.concat(FPSTR(HTTP_MESSAGE_LINE_ITEM));
    page.replace("{{I}}", F(L_RESTORE_NETWORK_OPEN_PANEL));
  }

  closeMessageSection(page);
}

void ESPSitesGenerator::generateFooter(String &page, boolean extended) {
  /*
  if (Device->getMode() == ESP_MODE_NORMAL && RestAPI->accessToWAN()) {
    RestAPI->sent(_HtmlResponse, ESP_CONFIG_JSONRPC_REST_METHOD_BOTTOM_TEXT);
    if (_HtmlResponse.length() > 0) {
      page.concat(_HtmlResponse);
    }
  }
*/
  page.concat(F("</div></div>"));

  page.replace("{{A}}",
               F("<h1 style=\"margin-bottom:0\">{{firmware.name}}</h1>"));

#if defined(ESP_4MB)
  page.replace("{{f.s}}", F("4Mb"));
#elif defined(ESP_2MB)
  page.replace("{{f.s}}", F("2Mb"));
#else
  page.replace("{{f.s}}", F("1Mb"));
#endif

#if defined(ESP8285)
  page.replace("{{f.e}}", F("8285"));
#elif defined(ESP32)
  page.replace("{{f.e}}", F("32"));
#else
  page.replace("{{f.e}}", F("8266"));
#endif

  page.replace("{{f.n}}", deviceID);
  page.replace("{{f.l}}", L_LANGUAGE_SHORT);

  page.replace("{{firmware.name}}", F(ESP_FIRMWARE_NAME));
  page.replace("{{f.v}}", ESP_FIRMWARE_VERSION);

  page.concat(F("</body></html>"));
}

void ESPSitesGenerator::openSection(String &page, const char *title,
                                    const __FlashStringHelper *description) {
  page.concat(FPSTR(HTTP_FORM_BLOCK_HEADER));
  page.replace("{{T}}", title);
  page.replace("{{D}}", description);
}

void ESPSitesGenerator::openSection(String &page,
                                    const __FlashStringHelper *title,
                                    const __FlashStringHelper *description) {
  page.concat(FPSTR(HTTP_FORM_BLOCK_HEADER));
  page.replace("{{T}}", title);
  page.replace("{{D}}", description);
}

void ESPSitesGenerator::openMessageSection(
    String &page, const char *title, const __FlashStringHelper *description) {
  openSection(page, title, description);
  page.concat(F("<ul class=\"lst\">"));
}

void ESPSitesGenerator::openMessageSection(
    String &page, const __FlashStringHelper *title,
    const __FlashStringHelper *description) {
  openSection(page, title, description);
  page.concat(F("<ul class=\"lst\">"));
}

void ESPSitesGenerator::closeSection(String &page) {
  page.concat(FPSTR(HTTP_FORM_BLOCK_CLOSURE));
}

void ESPSitesGenerator::closeMessageSection(String &page) {
  page.concat(F("</ul>"));
  page.concat(FPSTR(HTTP_FORM_BLOCK_CLOSURE));
}

void ESPSitesGenerator::addListOfGPIOs(String &item,
                                       const __FlashStringHelper *field,
                                       uint8_t selected, const char *title) {

  item.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
  item.replace("{{i.n}}", field);
  item.replace("{{i.l}}", title);
  item.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  item.replace("{{i.v}}", String(ESP_HARDWARE_ITEM_NOT_EXIST));
  item.replace("{{i.l}}", F(L_NONE));
  item.replace("{{i.s}}", selected == ESP_HARDWARE_ITEM_NOT_EXIST
                              ? F(" selected=\"selected\"")
                              : F(""));

  for (uint8_t i = 0; i < ESP_NUMBER_OF_GPIOS; i++) {
    item.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));

    item.replace("{{i.v}}", String(pgm_read_byte(GPIOS + i)));
    item.replace("{{i.l}}", String(pgm_read_byte(GPIOS + i)));
    item.replace("{{i.s}}", selected == pgm_read_byte(GPIOS + i)
                                ? F(" selected=\"selected\"")
                                : F(""));
  }
  item.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));
}

void ESPSitesGenerator::addListOfHardwareItem(String &page, uint8_t noOfItems,
                                              uint8_t noOffConnected,
                                              const __FlashStringHelper *field,
                                              const __FlashStringHelper *label,
                                              boolean disabled) {
  page.concat(F("<div class=\"cf\"><label>"));
  page.concat(label);
  page.concat(F("</label><select name=\""));
  page.concat(field);
  page.concat(F("\""));
  if (disabled) {
    page.concat(F(" disabled=\"disabled\""));
  }
  page.concat(F("><option value=\"0\""));
  page.concat((noOffConnected == 0 ? F(" selected=\"selected\"") : F("")));
  page.concat(F(">"));
  page.concat(F(L_NONE));
  page.concat(F("</option>"));
  if (!disabled) {
    for (uint8_t i = 1; i < (noOfItems + 1); i++) {
      page.concat(F("<option value=\""));
      page.concat(i);
      page.concat(F("\""));
      page.concat(noOffConnected == i ? F(" selected=\"selected\"") : F(""));
      page.concat(F(">"));
      page.concat(i);
      page.concat(F("</option>"));
    }
  }
  page.concat(F("</select>"));
  /*
  if (disabled) {
    page.concat(F("<span class=\"hint\">("));
    page.concat(F(L_PRO_VERSION));
    page.concat(F(")</span>"));
  }
  */
  page.concat(F("</div>"));
}

void ESPSitesGenerator::addInputFormItem(String &item, const char *type,
                                         const char *name, const char *label,
                                         const char *value, const char *size,
                                         const char *min, const char *max,
                                         const char *step, const char *hint,
                                         boolean readonly) {
  item.concat(F("<div class=\"cf\"><label>"));
  item.concat(label);
  item.concat(F("</label><input name=\""));
  item.concat(name);
  item.concat(F("\" type=\""));
  item.concat(type);
  item.concat(F("\" "));
  if (readonly) {
    item.concat(F("readonly=\"readonly\" "));
  }
  if (strcmp(size, "?") != 0) {
    item.concat(F("maxlength=\""));
    item.concat(size);
    item.concat(F("\" "));
  }
  if (strcmp(type, "number") == 0) {
    if (strcmp(min, "?") != 0) {
      item.concat(F("min=\""));
      item.concat(min);
      item.concat(F("\" "));
    }
    if (strcmp(max, "?") != 0) {
      item.concat(F("max=\""));
      item.concat(max);
      item.concat(F("\" "));
    }
    if (strcmp(step, "?") != 0) {
      item.concat(F("step=\""));
      item.concat(step);
      item.concat(F("\" "));
    }
  }
  item.concat(F("value=\""));
  item.concat(value);
  item.concat(F("\">"));
  if (strcmp(size, "?") != 0) {
    item.concat(F("<span class=\"hint\">Max "));
    item.concat(size);
    item.concat(F(" "));
    item.concat(F(L_NUMBER_OF_CHARS));
    item.concat(F("</span>"));
  }
  if (strcmp(type, "number") == 0) {
    if (strcmp(min, "?") != 0 && strcmp(max, "?") != 0) {
      item.concat(F("<span class=\"hint\">"));
      item.concat(F(L_RANGE));
      item.concat(F(" "));
      item.concat(min);
      item.concat(F(" - "));
      item.concat(max);
      if (strcmp(hint, "?") != 0) {
        item.concat(F(" "));
        item.concat(hint);
      }
      item.concat(F("</span>"));
    } else if (strcmp(hint, "?") != 0) {
      item.concat(F("<span class=\"hint\">"));
      item.concat(hint);
      item.concat(F("</span>"));
    }
  }
  item.concat(F("</div>"));
}

void ESPSitesGenerator::_addSelectionFormItem(
    String &item, boolean type, const char *name, const char *label,
    const char *value, boolean checked, const char *hint, boolean disabled) {
  item.concat(FPSTR(HTTP_ITEM_CHECKBOX));
  item.replace("{{i.t}}", type ? "checkbox" : "radio");
  item.replace("{{i.n}}", name);
  item.replace("{{i.l}}", label);
  item.replace("{{i.v}}", value);
  item.replace("{{i.c}}", checked ? " checked=\"checked\"" : "");
  item.replace("{{i.d}}", disabled ? " disabled=\"disabled\"" : "");
  item.replace("{{i.h}}",
               strcmp(hint, ESP_FORM_ITEM_SKIP_PROPERTY) != 0
                   ? "<span class=\"hint\">(" + String(hint) + ")</span>"
                   : "");
}

void ESPSitesGenerator::addCheckboxFormItem(String &item, const char *name,
                                            const char *label,
                                            const char *value, boolean checked,
                                            const char *hint,
                                            boolean disabled) {
  _addSelectionFormItem(item, true, name, label, value, checked, hint,
                        disabled);
}

void ESPSitesGenerator::addRadioButtonFormItem(
    String &item, const char *name, const char *label, const char *value,
    boolean checked, const char *hint, boolean disabled) {
  _addSelectionFormItem(item, false, name, label, value, checked, hint,
                        disabled);
}

void ESPSitesGenerator::addMenuItem(String &item,
                                    const __FlashStringHelper *title,
                                    uint8_t siteId) {
  item.concat(FPSTR(HTTP_MENU_ITEM));
  item.replace("{{i.i}}", FPSTR(title));
  char _number[3];
  sprintf(_number, "%d", siteId);
  item.replace("{{s.i}}", _number);
}

void ESPSitesGenerator::addMenuItemExternal(String &item,
                                            const __FlashStringHelper *title,
                                            const __FlashStringHelper *url) {
  item.concat(FPSTR(HTTP_MENU_ITEM_EXTERNAL));
  item.replace("{{i.i}}", title);
  item.replace("{{s.u}}", url);
}

void ESPSitesGenerator::addMenuHeaderItem(String &item,
                                          const __FlashStringHelper *title) {
  item.concat(FPSTR(HTTP_MENU_SUBITEMS_HEADER));
  item.replace("{{i.i}}", FPSTR(title));
}

void ESPSitesGenerator::addMenuSubItem(String &item, const char *title,
                                       uint8_t numberOfItems, uint8_t siteId) {
  for (uint8_t i = 0; i < numberOfItems; i++) {
    item.concat(FPSTR(HTTP_MENU_SUBITEM));
    item.replace("{{i.i}}", title);
    item.replace("{{i.D}}", String(i));
    item.replace("{{i.y}}", String(i + 1));
    item.replace("{{s.i}}", String(siteId));
  }
}

void ESPSitesGenerator::addSelectFormItemOpen(
    String &item, const __FlashStringHelper *name,
    const __FlashStringHelper *label) {
  item.concat(FPSTR(HTTP_ITEM_SELECT_OPEN));
  item.replace("{{i.l}}", label);
  item.replace("{{i.n}}", name);
}

void ESPSitesGenerator::addSelectOptionFormItem(String &item, const char *label,
                                                const char *value,
                                                boolean selected) {
  item.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  item.replace("{{i.v}}", value);
  item.replace("{{i.l}}", label);
  item.replace("{{i.s}}", selected ? " selected=\"selected\"" : "");
}

void ESPSitesGenerator::addSelectFormItemClose(String &item) {
  item.concat(FPSTR(HTTP_ITEM_SELECT_CLOSE));
}

/************** SITES ****************/

void ESPSitesGenerator::siteIndex(String &page) {
  DEVICE configuration;
  configuration = Device->configuration;

  openSection(page, F(L_INDEX_LAUNCH_CONFIGURATION_PANEL),
              F(L_INDEX_LAUNCH_CONFIGURATION_PANEL_HINT));

  page.concat(F("<form method=\"post\"><div class=\"cf\"><input name=\"p\" "
                "type=\"password\" "
                "placeholder=\""));
  page.concat(F(L_PASSWORD));
  page.concat(F("\"> <input type=\"submit\" class=\"b bs\" "
                "value=\""));
  page.concat(F(L_INDEX_NORMAL_MODE));
  page.concat(F("\" formaction=\"/?o=0&i="));
  page += ESP_MODE_CONFIGURATION;
  page.concat(F("\" /> <input type=\"submit\" class=\"b be\" value=\""));
  page.concat(F(L_INDEX_HOTSPOT_MODE));
  page.concat(F("\" formaction=\"/?o=0&i="));
  page += ESP_MODE_ACCESS_POINT;
  page.concat(F("\" /></div></form>"));
  closeSection(page);
}

void ESPSitesGenerator::siteIndexConfiguration(String &page) {
  page.concat("INDEX");
}

void ESPSitesGenerator::siteDevice(String &page) {
  DEVICE configuration;
  Data->get(configuration);
  openSection(page, F(L_DEVICE), F(""));

#ifdef ESP_CONFIG_HARDWARE_LED
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_LED_MAX_NUMBER,
                        configuration.noOfLEDs, F("led"),
                        F(L_DEVICE_NUMBER_OF_LEDS));
#endif

#ifdef ESP_CONFIG_HARDWARE_SWITCH
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_SWITCH_MAX_NUMBER,
                        configuration.noOfSwitches, F("switch"),
                        F(L_DEVICE_NUMBER_OF_SWITCHES));
#endif
#ifdef ESP_CONFIG_HARDWARE_ADC
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_ADC_MAX_NUMBER,
                        configuration.noOfADCs, F("adc"),
                        F(L_DEVICE_NUMBER_OF_ADCS));
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_SENSOR_BINARY_MAX_NUMBER,
                        configuration.noOfBinarySensors, F("binarySensor"),
                        F(L_DEVICE_NUMBER_OF_BINARY_SENSORS));

#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_SENSOR_DS18B20_MAX_NUMBER,
                        configuration.noOfDS18B20s, F("ds18b20Sensor"),
                        F(L_DEVICE_NUMBER_OF_DS18B20_SENSORS));

#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_SENSOR_NTC_MAX_NUMBER,
                        configuration.noOfNTCs, F("NTCSensor"),
                        F(L_DEVICE_NUMBER_OF_NTC_SENSORS));

#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_SENSOR_ACS758_MAX_NUMBER,
                        configuration.noOfACS758s, F("acs758Sensor"),
                        F(L_DEVICE_NUMBER_OF_ACS758));
#endif

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_BATTERYMETER_MAX_NUMBER,
                        configuration.noOfBatterymeters, F("batterymeter"),
                        F(L_DEVICE_NUMBER_OF_BATTERYMETERS));

#endif

  closeSection(page);

  openSection(page, F(L_BUSES), F(""));
#ifdef ESP_CONFIG_HARDWARE_I2C
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_I2C_MAX_NUMBER,
                        configuration.noOfI2Cs, F("i2c"),
                        F(L_DEVICE_NUMBER_OF_I2C));
#endif
#ifdef ESP_CONFIG_HARDWARE_UART
  addListOfHardwareItem(page, ESP_CONFIG_HARDWARE_UART_MAX_NUMBER,
                        configuration.noOfUARTs, F("uart"),
                        F(L_DEVICE_NUMBER_OF_UART));
#endif
  closeSection(page);
}

void ESPSitesGenerator::siteNetwork(String &page) {
  NETWORK configuration;
  char _ip[18];
  char _int[4];
  Data->get(configuration);
  WiFiScanClass WiFi;

  /* Section: WiFi selection, user and password */
  openSection(page, F(L_NETWORK_CONFIGURATION),
              F(L_NETWORK_CONFIGURATION_INFO));

  addSelectFormItemOpen(page, F("ssid"), F(L_NETWORK_SSID));

#ifdef DEBUG
  Serial << endl << F("Searching for WiFi networks: ");
#endif
  int numberOfNetworks = WiFi.scanNetworks();

  char _ssid[sizeof(configuration.ssid)];

#ifdef DEBUG
  Serial << endl << F(" - found: ") << numberOfNetworks;
#endif

  for (int i = 0; i < numberOfNetworks; i++) {

#ifdef DEBUG
    Serial << endl << " - " << WiFi.SSID(i);
#endif

    WiFi.SSID(i).toCharArray(_ssid, sizeof(_ssid));
    addSelectOptionFormItem(page, _ssid, _ssid,
                            strcmp(_ssid, configuration.ssid) == 0);
  }
  page.concat(F("</select>"));

  page.concat(F("<input type=\"submit\" class =\"b bc\" value=\""));
  page.concat(F(L_NETWORK_REFRESH));
  page.concat(F("\" formaction=\"/?o="));
  page += ESP_CONFIG_SITE_NETWORK;
  page.concat(F("&c=0\"></div>"));

  addInputFormItem(page, ESP_FORM_ITEM_TYPE_PASSWORD, "password", L_PASSWORD,
                   configuration.password, "32");

  closeSection(page);

  /* Section: DHCP or Fixed IP */
  openSection(page, F(L_NETWORK_DEVICE_IP), F(L_NETWORK_DEVICE_IP_INFO));
  addCheckboxFormItem(page, "dhcp", L_NETWORK_DHCP_ENABLED, "1",
                      configuration.isDHCP);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_TEXT, "ip", L_IP_ADDRESS,
                   configuration.ip);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_TEXT, "gateway", L_NETWORK_GATEWAY,
                   configuration.gateway);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_TEXT, "subnet", L_NETWORK_SUBNET,
                   configuration.subnet);
  closeSection(page);

  /* Section: Backup WiFI */
  openSection(page, F(L_NETWORK_BACKUP_CONFIGURATION),
              F(L_NETWORK_BACKUP_CONFIGURATION_HINT));

  addSelectFormItemOpen(page, F("ssidBackup"), F(L_NETWORK_SSID));

  addSelectOptionFormItem(page, L_NETWOK_NONE_BACKUP_SSID, L_NONE,
                          strcmp(ESP_CONFIG_NETWORK_DEFAULT_NONE_SSID,
                                 configuration.ssidBackup) == 0);

  for (int i = 0; i < numberOfNetworks; i++) {
    WiFi.SSID(i).toCharArray(_ssid, sizeof(_ssid));
    addSelectOptionFormItem(page, _ssid, _ssid,
                            strcmp(_ssid, configuration.ssidBackup) == 0);
  }
  page.concat(F("</select>"));

  addInputFormItem(page, ESP_FORM_ITEM_TYPE_PASSWORD, "passwordBackup",
                   L_PASSWORD, configuration.passwordBackup, "32");

  sprintf(_int, "%d", configuration.noFailuresToSwitchNetwork);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "fs",
                   L_NETWORK_SWITCH_TO_BACKUP, _int,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "1", "255", "1");

  closeSection(page);

  /* Section: Advanced settings */
  openSection(page, F(L_NETWORK_ADVANCED), F(""));

  sprintf(_int, "%d", configuration.noConnectionAttempts);

  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "na",
                   L_NETWORK_NUMBER_OF_CONNECTIONS, _int,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "1", "255", "1");

  sprintf(_int, "%d", configuration.waitTimeConnections);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "wc",
                   L_NETWORK_TIME_BETWEEN_CONNECTIONS, _int,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "1", "255", "1", L_SECONDS);

  sprintf(_int, "%d", configuration.waitTimeSeries);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "ws", L_NETWORK_SLEEP_TIME,
                   _int, ESP_FORM_ITEM_SKIP_PROPERTY, "1", "255", "1",
                   L_SECONDS);

  closeSection(page);
}

#ifdef ESP_CONFIG_HARDWARE_I2C
void ESPSitesGenerator::siteI2CBUS(String &page, uint8_t id) {
  I2CBUS configuration;
  Data->get(id, configuration);
  openSection(page, F("I2C"), F(""));
  addListOfGPIOs(page, F("sda"), configuration.SDA, "SDA");
  addListOfGPIOs(page, F("scl"), configuration.SCL, "SCL");
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
  openSection(page, F("UART"), F(""));
  addListOfGPIOs(page, F("rxd"), configuration.RXD, "RXD");
  addListOfGPIOs(page, F("txd"), configuration.TXD, "TXD");
  closeSection(page);
}
#endif

#ifdef ESP_CONFIG_HARDWARE_LED
void ESPSitesGenerator::siteLED(String &page, uint8_t id) {
  LED configuration;
  Data->get(id, configuration);
  char title[7];
  sprintf(title, "LED #%d", id + 1);
  openSection(page, title, F(""));
  addListOfGPIOs(page, F("gpio"), configuration.gpio);
  addCheckboxFormItem(page, "reverse", L_LED_CHANGE_INDICATION, "1",
                      configuration.reverseState);
  closeSection(page);
}

void ESPSitesGenerator::siteSystemLED(String &page) {
  uint8_t configuration = Data->getSystemLEDId();
  openSection(page, F(L_LED_SYSTEM), F(L_LED_SYSTEM_INFO));
  addLEDSelectionItem(page, configuration);
  closeSection(page);
}

void ESPSitesGenerator::addLEDSelectionItem(String &item, uint8_t id) {
  char _id[4];
  char _label[4];
  addSelectFormItemOpen(item, F("id"), F("LED"));
  sprintf(_id, "%d", ESP_HARDWARE_ITEM_NOT_EXIST);
  addSelectOptionFormItem(item, L_NONE, _id, id == ESP_HARDWARE_ITEM_NOT_EXIST);
  for (uint8_t i = 0; i < Device->configuration.noOfLEDs; i++) {
    sprintf(_label, "%d", i + 1);
    sprintf(_id, "%d", i);
    addSelectOptionFormItem(item, _label, _id, id == i);
  }
  addSelectFormItemClose(item);
}

#endif

#ifdef ESP_CONFIG_HARDWARE_SWITCH
void ESPSitesGenerator::siteSwitch(String &page, uint8_t id) {
  SWITCH configuration;
  Data->get(id, configuration);
  char title[30];
  sprintf(title, "%s #%d", L_SWITCH_BUTTON, id + 1);
  openSection(page, title, F(""));
  addListOfGPIOs(page, F("gpio"), configuration.gpio);

  /* Item: PinMode */
  addSelectFormItemOpen(page, F("pin"), F("PinMode"));
  addSelectOptionFormItem(page, "INPUT", "1", configuration.pinMode == INPUT);
  addSelectOptionFormItem(page, "INPUT PULLUP", "5",
                          configuration.pinMode == INPUT_PULLUP);
  addSelectOptionFormItem(page, "INPUT PULLDOWN", "9",
                          configuration.pinMode == INPUT_PULLDOWN);
  addSelectFormItemClose(page);

  /* Item: Functionality */
  addSelectFormItemOpen(page, F("functionality"), F(L_SWITCH_FUNCTIONALITY));
  addSelectOptionFormItem(page, L_NONE, "0",
                          configuration.functionality ==
                              ESP_CONFIG_HARDWARE_SWITCH_FUNCTIONALITY_NONE);
  addSelectOptionFormItem(page, L_SWITCH_SYSTEM_BUTTON, "1",
                          configuration.functionality ==
                              ESP_CONFIG_HARDWARE_SWITCH_FUNCTIONALITY_MULTI);
  addSelectFormItemClose(page);

  /* Item: Switch type */
  addSelectFormItemOpen(page, F("type"), F(L_SWITCH_TYPE));
  addSelectOptionFormItem(page, L_SWITCH_MONOSTABLE, "0",
                          configuration.type ==
                              ESP_CONFIG_HARDWARE_SWITCH_TYPE_MONO_STABLE);
  addSelectOptionFormItem(page, L_SWITCH_BISTABLE, "1",
                          configuration.type ==
                              ESP_CONFIG_HARDWARE_SWITCH_TYPE_BI_STABLE);
  addSelectFormItemClose(page);

  /* Item: Bouncing */
  char _number[4];
  sprintf(_number, "%d", configuration.bouncing);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "bouncing", L_SENSITIVENESS,
                   _number, ESP_FORM_ITEM_SKIP_PROPERTY, "0", "999", "1",
                   L_MILISECONDS);

  addCheckboxFormItem(page, "reverse", L_SWITCH_REVERSE, "1",
                      configuration.reverseState);

  closeSection(page);
}
#endif

#ifdef ESP_CONFIG_HARDWARE_ADC
void ESPSitesGenerator::siteADC(String &page, uint8_t id) {
  ADC configuration;
  Data->get(id, configuration);
  char _number[13];

  openSection(page, F(L_ANALOG_INPUT), F(""));

#ifdef ESP_CONFIG_HARDWARE_ADS1115
  if (Device->configuration.noOfI2Cs) {
    page.concat(FPSTR(HTTP_ITEM_HINT));
    page.replace("{{i.h}}", L_GPIO_ANALOG_INPUT);
  }
#endif

  addListOfGPIOs(page, F("gpio"), configuration.gpio, "GPIO");

#ifdef ESP_CONFIG_HARDWARE_ADS1115
  char _numberText1[2];
  char _numberText2[2];
  if (Device->configuration.noOfI2Cs) {
    page.concat(FPSTR(HTTP_ITEM_HINT));
    page.replace("{{i.h}}", L_ADS1115_ANALOG_INPUT);

    /* Item: I2C Bus selection */

    addSelectFormItemOpen(page, F("i2c"), F("I2C BUS"));
    addSelectOptionFormItem(page, L_NONE, "255",
                            configuration.i2c.inputId ==
                                ESP_HARDWARE_ITEM_NOT_EXIST);
    for (uint8_t i = 0; i < Device->configuration.noOfI2Cs; i++) {
      sprintf(_numberText1, "%d", (i + 1));
      sprintf(_numberText2, "%d", i);
      addSelectOptionFormItem(page, _numberText1, _numberText2,
                              configuration.i2c.id == i);
    }
    addSelectFormItemClose(page);

    /* Refresh button */
    page.concat(FPSTR(HTTP_ITEM_REFRESH_BUTTON));
    page.replace("{{item.label}}", L_REFRESH_SETTINGS_ADS1115);

    if (configuration.i2c.id != ESP_HARDWARE_ITEM_NOT_EXIST) {

      /* Item: I2C devices */
      addI2CSelectFormItem(page, configuration.i2c.id,
                           configuration.i2c.address, L_ADS1115_ADDRESS);

      /* Item: Analog Input ID */
      addSelectFormItemOpen(page, F("input"), F(L_ANALOG_INPUT));
      addSelectOptionFormItem(page, L_NONE, "255",
                              configuration.i2c.inputId ==
                                  ESP_HARDWARE_ITEM_NOT_EXIST);
      char _analogPinIdText[6];
      for (uint8_t i = 0; i < ESP_CONFIG_HARDWARE_ADS1115_MAX_INPUTS; i++) {
        sprintf(_analogPinIdText, "AIN%d", i);
        sprintf(_numberText1, "%d", i);
        addSelectOptionFormItem(page, _analogPinIdText, _numberText1,
                                configuration.i2c.inputId == i);
      }
      addSelectOptionFormItem(page, "AIN0-1", "4",
                              configuration.i2c.inputId == 4);
      addSelectOptionFormItem(page, "AIN2-3", "5",
                              configuration.i2c.inputId == 5);

      addSelectFormItemClose(page);

      /* Item: Number of samples per m.second */
      addSelectFormItemOpen(page, F("samplesPerSecond"),
                            F(L_ADS1115_NO_OF_SAMPLES_PER_SECOND));
      addSelectOptionFormItem(page, "128", "0",
                              configuration.i2c.samplesPerSecond ==
                                  ADS1115_REG_CONFIG_DR_128SPS);
      addSelectOptionFormItem(page, "250", "32",
                              configuration.i2c.samplesPerSecond ==
                                  ADS1115_REG_CONFIG_DR_128SPS);
      addSelectOptionFormItem(page, "490", "64",
                              configuration.i2c.samplesPerSecond ==
                                  ADS1115_REG_CONFIG_DR_490SPS);
      addSelectOptionFormItem(page, "920", "96",
                              configuration.i2c.samplesPerSecond ==
                                  ADS1115_REG_CONFIG_DR_920SPS);
      addSelectOptionFormItem(page, "1600", "128",
                              configuration.i2c.samplesPerSecond ==
                                  ADS1115_REG_CONFIG_DR_1600SPS);
      addSelectOptionFormItem(page, "2400", "160",
                              configuration.i2c.samplesPerSecond ==
                                  ADS1115_REG_CONFIG_DR_2400SPS);
      addSelectOptionFormItem(page, "3300", "192",
                              configuration.i2c.samplesPerSecond ==
                                  ADS1115_REG_CONFIG_DR_3300SPS);
      addSelectFormItemClose(page);

      /* Item: Gain */
      addSelectFormItemOpen(page, F("gain"), F(L_ADS1115_GAIN));
      addSelectOptionFormItem(page, "2/3 +/-6.144V", "0",
                              configuration.i2c.gain == GAIN_TWOTHIRDS);
      addSelectOptionFormItem(page, "1 +/-4.096V", "512",
                              configuration.i2c.gain == GAIN_ONE);
      addSelectOptionFormItem(page, "2 +/-2.048V", "1024",
                              configuration.i2c.gain == GAIN_TWO);
      addSelectOptionFormItem(page, "4 +/-1.024V", "1536",
                              configuration.i2c.gain == GAIN_FOUR);
      addSelectOptionFormItem(page, "8 +/-0.512V", "2048",
                              configuration.i2c.gain == GAIN_EIGHT);
      addSelectOptionFormItem(page, "16 +/-0.256V", "2560",
                              configuration.i2c.gain == GAIN_SIXTEEN);
      addSelectFormItemClose(page);
    }
  }
#endif

  closeSection(page);

  openSection(page, F(L_READS), F(""));

  /* Item: Interval */
  sprintf(_number, "%d", configuration.interval);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "interval",
                   L_MEASURMENTS_INTERVAL, _number, ESP_FORM_ITEM_SKIP_PROPERTY,
                   "20", "3600000", "1", L_MILISECONDS);

  /* Item: Number of samples */
  sprintf(_number, "%d", configuration.numberOfSamples);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "samples",
                   L_NUMBER_OF_SAMPLES, _number, ESP_FORM_ITEM_SKIP_PROPERTY,
                   "1", "999", "1");

  closeSection(page);

  openSection(page, F(L_ADC_INPUT_PARAMETERS), F(""));

  /* Item: Max VCC */
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

  /* Item: Resolution */
  sprintf(_number, "%d", (uint32_t)configuration.resolution);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "resolution",
                   L_ADC_RESOLUTION, _number, ESP_FORM_ITEM_SKIP_PROPERTY,
                   "1023", "65535", "1");

  closeSection(page);

  openSection(page, F(L_VOLTAGE_DIVIDER), F(""));

  /* Item: Divider Resistor A */
  sprintf(_number, "%d", (uint32_t)configuration.divider.Ra);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "ra", "R[a]", _number,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "0", "90000000", "1", "Om");

  /* Item: Divider Resistor B */
  sprintf(_number, "%d", (uint32_t)configuration.divider.Rb);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "rb", "R[b]", _number,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "0", "90000000", "1", "Om");

  /* Item: Max VCC to measure */
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

  openSection(page, F(L_BINARY_SENSOR), F(""));

  /* Item: GPIO */
  addListOfGPIOs(page, F("gpio"), configuration.gpio, "GPIO");

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

  openSection(page, F(L_DS18B20_SENSOR), F(""));

  /* Item: GPIO */
  addListOfGPIOs(page, F("gpio"), configuration.gpio, "GPIO");

  /* Item: Sensor address */

  numberOfFoundSensors = _Sensor.scan(configuration.gpio, _addresses);

  if (numberOfFoundSensors > 0) {
    addSelectFormItemOpen(page, F("address"), F(L_ADDRESS));
    char _scannedAddressText[17];
    char _configAddressText[17];
    for (uint8_t i = 0; i < numberOfFoundSensors; i++) {
      _Sensor.addressToChar(_addresses[i], _scannedAddressText);
      _Sensor.addressToChar(configuration.address, _configAddressText);
      addSelectOptionFormItem(page, _scannedAddressText, _scannedAddressText,
                              memcmp(_addresses[i], configuration.address,
                                     sizeof(_addresses[i])) == 0);
    }
    page.concat(F("</select><input type=\"submit\" class =\"b bc\" "
                  "value=\"" L_DS18B20_SEARCH "\"></div>"));
  } else {
    page.concat(F("<p class=\"cm\">" L_DS18B20_NO_SENSOR "</p>"));
    page.concat(
        F("<input type=\"submit\" class =\"b bc\" value=\"" L_DS18B20_SEARCH
          "\"><br /><br />"));
  }

  /* Item: Interval */
  sprintf(_number, "%d", configuration.interval);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "interval",
                   L_MEASURMENTS_INTERVAL, _number, ESP_FORM_ITEM_SKIP_PROPERTY,
                   "1000", "3600000", "1", L_SECONDS);

  /* Item: Unit */
  addSelectFormItemOpen(page, F("unit"), F(L_UNITS));
  addSelectOptionFormItem(
      page, "C", "0",
      configuration.unit == ESP_CONFIG_FUNCTIONALITY_TEMPERATURE_UNIT_CELSIUS);
  addSelectOptionFormItem(
      page, "F", "1", configuration.unit ==
                          ESP_CONFIG_FUNCTIONALITY_TEMPERATURE_UNIT_FARENHIAT);
  addSelectFormItemClose(page);

  /* Item: Correction */
  sprintf(_number, "%-.3f", configuration.correction);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "correction",
                   L_DS18B20_TEMPERATURE_CORRECTION, _number,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "-99.999", "99.999", "0.001");

  /* Item: Resolution */
  addSelectFormItemOpen(page, F("resolution"), F(L_DS18B20_RESOLUTION));
  addSelectOptionFormItem(
      page, L_DS18B20_RESOLUTION_9B, "9",
      configuration.resolution ==
          ESP_CONFIG_HARDWARE_SENSOR_DS18B20_DEFAULT_RESOLUTION_9B);
  addSelectOptionFormItem(
      page, L_DS18B20_RESOLUTION_10B, "10",
      configuration.resolution ==
          ESP_CONFIG_HARDWARE_SENSOR_DS18B20_DEFAULT_RESOLUTION_10B);
  addSelectOptionFormItem(
      page, L_DS18B20_RESOLUTION_11B, "11",
      configuration.resolution ==
          ESP_CONFIG_HARDWARE_SENSOR_DS18B20_DEFAULT_RESOLUTION_11B);
  addSelectOptionFormItem(
      page, L_DS18B20_RESOLUTION_12B, "12",
      configuration.resolution ==
          ESP_CONFIG_HARDWARE_SENSOR_DS18B20_DEFAULT_RESOLUTION_12B);

  addSelectFormItemClose(page);

  closeSection(page);
}
#endif // ESP_CONFIG_HARDWARE_SENSOR_DS18B20

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
void ESPSitesGenerator::siteNTCSensor(String &page, uint8_t id) {
  NTC_SENSOR configuration;
  Data->get(id, configuration);
  char _number[11];

  openSection(page, F(L_NTC_SENSOR), F(""));

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

  openSection(page, F(L_NTC_COEFFICIENT_A), F(L_NTC_COEFFICIENT_DESC));

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

  openSection(page, F(L_NTC_COEFFICIENT_B), F(L_NTC_COEFFICIENT_DESC));

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

  openSection(page, F(L_NTC_COEFFICIENT_C), F(L_NTC_COEFFICIENT_DESC));

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
  char _numberText1[17];
  char _numberText2[2];

  openSection(page, F(L_BATTERY_METER), F(""));

  /* Item: ADC */
  addSelectFormItemOpen(page, F("adc"), F(L_ANALOG_INPUT));
  addSelectOptionFormItem(page, L_NONE, "255", configuration.adcInput ==
                                                   ESP_HARDWARE_ITEM_NOT_EXIST);

  for (uint8_t i = 0; i < Device->configuration.noOfADCs; i++) {
    sprintf(_numberText1, "%d", i);
    sprintf(_numberText2, "%d", (i + 1));
    addSelectOptionFormItem(page, _numberText2, _numberText1,
                            configuration.adcInput == i);
  }

  addSelectFormItemClose(page);

  /* Item: Interval */
  sprintf(_numberText1, "%d", configuration.interval);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "interval",
                   L_MEASURMENTS_INTERVAL, _numberText1,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "20", "3600000", "1",
                   L_MILISECONDS);

  /* Item: Min V */
  sprintf(_numberText1, "%-.4f", configuration.voltage.min);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "vMin", L_BATTERY_MIN_LEVEL,
                   _numberText1, ESP_FORM_ITEM_SKIP_PROPERTY, "0", "200",
                   "0.0001", "V");

  /* Item: Max V */
  sprintf(_numberText1, "%-.4f", configuration.voltage.max);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "vMax", L_BATTERY_MAX_LEVEL,
                   _numberText1, ESP_FORM_ITEM_SKIP_PROPERTY, "0", "200",
                   "0.0001", "V");

  closeSection(page);
}
#endif // ESP_CONFIG_FUNCTIONALITY_BATTERYMETER

#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758
void ESPSitesGenerator::siteACS758(String &page, uint8_t id) {
  ACS758_SENSOR configuration;
  Data->get(id, configuration);
  char _number[8];

  openSection(page, F(L_ACS758_SENSOR), F(""));

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
  page.replace("{{item.label}}", L_SWITCH_TYPE);
  page.replace("{{item.name}}", "type");
  page.concat(FPSTR(HTTP_ITEM_SELECT_OPTION));
  page.replace("{{item.label}}", L_SELECT);
  page.replace("{{item.value}}", String(ESP_HARDWARE_ITEM_NOT_EXIST));
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
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "vcc", L_VCC, _number,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "2", "6", "0.000001", "V");

  /* Item: Current CutOff */
  sprintf(_number, "%-.2f", configuration.currentCutOff);
  addInputFormItem(page, ESP_FORM_ITEM_TYPE_NUMBER, "currentCutOff",
                   L_ACS758_CURRENT_CUTOFF, _number,
                   ESP_FORM_ITEM_SKIP_PROPERTY, "0", "200", "0.01", "A");

  closeSection(page);
}
#endif // ESP_CONFIG_HARDWARE_SENSOR_ACS758
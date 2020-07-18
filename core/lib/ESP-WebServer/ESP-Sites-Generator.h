/* AFE Firmware for smart home devices, Website: https://afe.smartnydom.pl/ */

#ifndef _ESP_Sites_Generator_h
#define _ESP_Sites_Generator_h

#include "arduino.h"

#include <ESP-Data-Access.h>
#include <ESP-Device.h>
#include <ESP-Site-components.h>
#include <WiFiScan.h>

#ifdef DEBUG
#include <Streaming.h>
#endif

#if FIRMWARE_LANGUAGE == 0
#include <ESP-pl_PL.h>
#else
#include <ESP-en_EN.h>
#endif

#ifdef ESP_CONFIG_HARDWARE_I2C
#include <ESP-I2C-Scanner.h>
#include <Wire.h>
#endif

#ifdef ESP_CONFIG_HARDWARE_ADS1115
#include <Adafruit_ADS1115.h>
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
#include <ESP-Sensor-DS18B20.h>
#endif

class ESPSitesGenerator {

private:
  ESPDataAccess *Data;
  ESPDevice *Device;
  char deviceID[17];

  void generateHeader(String &page, uint16_t redirect);

  /* Method generates GPIO selecton list */
  void addListOfGPIOs(String &item, const char *field, uint8_t selected,
                      const char *title = "GPIO");

  /* Method addes configuration block to the site */
  void openSection(String &page, const char *, const char *);
  void closeSection(String &page);

  /* It uses addListOfHardwareItem() */
  void _addListOfHardware(String &item, uint8_t noOfItems,
                          uint8_t noOffConnected, const char *field,
                          const char *label, uint8_t index, uint8_t noneValue,
                          boolean disabled = false);

  void addListOfHardwareItem(String &item, uint8_t noOfItems,
                             uint8_t noOffConnected, const char *field,
                             const char *label, boolean disabled = false);

  void addInputFormItem(String &item, const char *type, const char *name,
                        const char *label, const char *value,
                        const char *size = ESP_FORM_ITEM_SKIP_PROPERTY,
                        const char *min = ESP_FORM_ITEM_SKIP_PROPERTY,
                        const char *max = ESP_FORM_ITEM_SKIP_PROPERTY,
                        const char *step = ESP_FORM_ITEM_SKIP_PROPERTY,
                        const char *hint = ESP_FORM_ITEM_SKIP_PROPERTY,
                        boolean readonly = false);

  void addCheckboxFormItem(String &item, const char *name, const char *label,
                           const char *value, boolean checked);

  void addMenuItem(String &item, const char *title, uint8_t siteId);
  void addMenuHeaderItem(String &item, const char *title);
  void addMenuSubItem(String &item, const char *title, uint8_t numberOfItems,
                      uint8_t siteId);

#ifdef ESP_CONFIG_HARDWARE_I2C
  TwoWire *WirePort0;
  TwoWire *WirePort1;
  void addI2CSelectFormItem(String &page, uint8_t id, uint8_t address,
                            const char *label);
#endif

#ifdef ESP_CONFIG_HARDWARE_I2C
  void begin(ESPDevice *, ESPDataAccess *);
#endif

public:
  /* Constructor*/
  ESPSitesGenerator();

#ifdef ESP_CONFIG_HARDWARE_I2C
  void begin(ESPDevice *, ESPDataAccess *, TwoWire *_WirePort0,
             TwoWire *_WirePort1);
#else
  void begin(ESPDevice *, ESPDataAccess *);
#endif

  /* Method generates site header with menu. When redirect param is diff than 0
    then it will redirect page to main page after redirect param time (in sec)
   */
  void generateOneColumnLayout(String &page, uint16_t redirect = 0);
  void generateTwoColumnsLayout(String &page, uint16_t redirect = 0);

  /* Method generates site footer */
  void generateFooter(String &page, boolean extended = false);

  void siteConnecting(String &page);

  /* These methods generates firmware upgrade sections */
  void siteUpgrade(String &page);
  void sitePostUpgrade(String &page, boolean status);

  /* Method generate restore to defaults section. Command = 0 is pre-reset site,
   * 1 is a post reset site */
  void siteReset(String &page);
  void sitePostReset(String &page);

  /* Method addes info that device is being reset */
  void siteExit(String &page, uint8_t command);

  /* Method generates section shown when device is in norma mode */
  void siteIndex(String &page);

  void siteIndexConfiguration(String &page);
  void siteDevice(String &page);
  void siteNetwork(String &page);

#ifdef ESP_CONFIG_HARDWARE_I2C
  void siteI2CBUS(String &page, uint8_t id);
#endif

#ifdef ESP_CONFIG_HARDWARE_UART
  void siteUARTBUS(String &page, uint8_t id);
#endif

#ifdef ESP_CONFIG_HARDWARE_LED
  void siteLED(String &page, uint8_t id);
#endif

#ifdef ESP_CONFIG_HARDWARE_SWITCH
  void siteSwitch(String &page, uint8_t id);
#endif

#ifdef ESP_CONFIG_HARDWARE_ADC
  void siteADC(String &page, uint8_t id);
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
  void siteBinarySensor(String &page, uint8_t id);
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
  void siteDS18B20Sensor(String &page, uint8_t id);
#endif

};

#endif

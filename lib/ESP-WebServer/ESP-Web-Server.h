#ifndef _ESP_Web_Server_h
#define _ESP_Web_Server_h

#include "arduino.h"

#include <ESP-Data-Access.h>
#include <ESP-Device.h>
#include <ESP-Sites-Generator.h>
#include <WebServer.h>
#include <WiFiClient.h>

#ifdef ESP_CONFIG_HARDWARE_LED
#include <ESP-LED.h>
#endif

#ifdef ESP_CONFIG_HARDWARE_I2C
#include <Wire.h>
#endif

#ifdef DEBUG
#include <Streaming.h>
#endif

struct SITE_PARAMETERS {
  uint8_t ID;
  boolean twoColumns = true;
  uint8_t deviceID = ESP_HARDWARE_ITEM_NOT_EXIST;
  boolean reboot = false;
  uint8_t rebootMode = 0;
  uint16_t rebootTime = 0;
  boolean form = true;
  boolean formButton = true;
};

class ESPWebServer {

private:
  WebServer Server;
  ESPDevice *Device;
  ESPDataAccess *Data;

#ifdef ESP_CONFIG_HARDWARE_LED
  ESPLED *SystemLED;
#endif
  // It stores last HTTP API request
  HTTPCOMMAND httpCommand;
  // Once HTTP API requet is recieved it's set to true
  boolean receivedHTTPCommand = false;

  /* when it's set to true device configuration is refreshed. Required by
   * generate() method */
  boolean _refreshConfiguration = false;

  /* Used to auto-logoff from the config panel */
  unsigned long howLongInConfigMode = 0;

  ESPSitesGenerator Site;

  boolean upgradeFailed = false;

  /* Method gets url Option parameter value */
  boolean getOptionName();
  uint8_t getCommand();
  uint8_t getSiteID();
  uint8_t getID();

  /* Generates HTML response (site) */
  String generateSite(SITE_PARAMETERS *siteConfig, String &page);

  /* Reading POST data */
  void get(DEVICE &data);
  void get(NETWORK &data);

#ifdef ESP_CONFIG_HARDWARE_I2C
  void get(I2CBUS &data);
#endif
#ifdef ESP_CONFIG_HARDWARE_UART
  void get(UARTBUS &data);
#endif
#ifdef ESP_CONFIG_HARDWARE_LED
  void get(LED &data);
#endif
#ifdef ESP_CONFIG_HARDWARE_SWITCH
  void get(SWITCH &data);
#endif
#ifdef ESP_CONFIG_HARDWARE_ADC
  void get(ADC &data);
#endif

#if defined(ESP_CONFIG_HARDWARE_LED) || defined(ESP_CONFIG_HARDWARE_I2C)
  void begin(ESPDataAccess *, ESPDevice *);
#endif

public:
  ESPWebServer();

  /* Method pushes HTML site from WebServer */
  void publishHTML(String &page);

/* Method initialize WebServer and Updater server */
#if defined(ESP_CONFIG_HARDWARE_LED) && defined(ESP_CONFIG_HARDWARE_I2C)
  void begin(ESPDataAccess *, ESPDevice *, ESPLED *, TwoWire *_WirePort0,
             TwoWire *_WirePort1);
#elif defined(ESP_CONFIG_HARDWARE_LED) && !defined(ESP_CONFIG_HARDWARE_I2C)
  void begin(ESPDataAccess *, ESPDevice *, ESPLED *);
#elif !defined(ESP_CONFIG_HARDWARE_LED) && defined(ESP_CONFIG_HARDWARE_I2C)
  void begin(ESPDataAccess *, ESPDevice *, TwoWire *_WirePort0,
             TwoWire *_WirePort1);
#else
  void begin(ESPDataAccess *, ESPDevice *);
#endif

  /* Method listens for HTTP requests */
  void listener();

  /* Method listens for onNotFound */
  void onNotFound(WebServer::THandlerFunction fn);

  /* Method adds URL for listen */
  void handle(const char *uri, WebServer::THandlerFunction handler);
  void handleFirmwareUpgrade(const char *uri,
                             WebServer::THandlerFunction handlerUpgrade,
                             WebServer::THandlerFunction handlerUpload);

  /* Method generate HTML side. It reads also data from HTTP requests
   * arguments
   * and pass them to Configuration Panel class */
  void generate(boolean upload = false);

  /* Method listens for HTTP API requests. If get True command is in
   * httpCommand
   */
  boolean httpAPIlistener();

  /* Method reads HTTP API Command */
  HTTPCOMMAND getHTTPCommand();
};

#endif

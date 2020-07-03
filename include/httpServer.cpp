#include <ESP-Web-Server.h>
ESPWebServer HTTPServer;
void handleFavicon(void);
void handleHTTPRequests(void);
void handleOnNotFound(void);
void initializeHTTPServer(void);

/***** Body ******/

void handleFavicon(void){};

void handleOnNotFound(void) {
  String page = "<head><meta http-equiv=\"refresh\" content=\"0; "
                "url=http://192.168.5.1/\" /></head><body><p>";
  page += L_OPENING_CONFIG_PANEL;
  page += "</p></body>";
  HTTPServer.publishHTML(page);
};

void handleHTTPRequests(void) { HTTPServer.generate(); };
void handleUpload(void) { HTTPServer.generate(true); };

void initializeHTTPServer(void) {
  /* Initializing HTTP HTTPServer */
  HTTPServer.handle("/", handleHTTPRequests);
  HTTPServer.handle("/favicon.ico", handleFavicon);
  HTTPServer.handleFirmwareUpgrade("/upgrade", handleHTTPRequests,
                                   handleUpload);
  HTTPServer.onNotFound(handleOnNotFound);

#if defined(ESP_CONFIG_HARDWARE_LED) && defined(ESP_CONFIG_HARDWARE_I2C)
  HTTPServer.begin(&Data, &Device, &Led, &WirePort0, &WirePort1);
#elif defined(ESP_CONFIG_HARDWARE_LED) && !defined(ESP_CONFIG_HARDWARE_I2C)
  HTTPServer.begin(&Data, &Device, &Led);
#elif !defined(ESP_CONFIG_HARDWARE_LED) && defined(ESP_CONFIG_HARDWARE_I2C)
  HTTPServer.begin(&Data, &Device, &WirePort0, &WirePort1);
#else
  HTTPServer.begin(&Data, &Device);
#endif

#ifdef DEBUG
  Serial << endl << F("INFO: HTTP Server initialized");
#endif
}
/* ESP Firmware for smart home devices, Website: https://ESP.smartnydom.pl/ */

#include "ESP-Wifi.h"

ESPWiFi::ESPWiFi() {}

#ifdef ESP_CONFIG_HARDWARE_LED
void ESPWiFi::begin(ESPDevice *_Device, ESPDataAccess *_Data, ESPLED *_LED,
                    uint8_t mode) {
  Led = _LED;
  initialize(_Device, _Data, mode);
}
#else
void ESPWiFi::begin(ESPDevice *_Device, ESPDataAccess *_Data, uint8_t mode) {
  initialize(_Device, _Data, mode);
}
#endif

void ESPWiFi::initialize(ESPDevice *_Device, ESPDataAccess *_Data,
                         uint8_t mode) {
  Data = _Data;
  Device = _Device;
  WiFiMode = mode;
  if (WiFiMode == ESP_MODE_NORMAL || WiFiMode == ESP_MODE_CONFIGURATION) {
    Data->get(configuration);
  }

#ifdef DEBUG
  Serial << endl << F("INFO: Device is in mode: ") << WiFiMode;
#endif
  WiFi.setHostname(Device->configuration.name);
  WiFi.persistent(false);

  if (WiFiMode == ESP_MODE_ACCESS_POINT ||
      WiFiMode == ESP_MODE_NETWORK_NOT_SET) {
#ifdef DEBUG
    Serial << endl << F("INFO: Starting HotSpot: ");
#endif
    IPAddress apIP(192, 168, 5, 1);
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ESP_HOSTNAME);
    delay(2000);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

#ifdef DEBUG
    Serial << F("completed");
#endif
  } else {
#ifdef DEBUG
    Serial << endl << F("INFO: Starting WiFi: in WIFI_STA mode");
#endif

    if (!configuration.isDHCP) {
      IPAddress ip;
      if (!ip.fromString(configuration.ip)) {
#ifdef DEBUG
        Serial << endl
               << "ERROR: Problem with WIFI IP address: " << configuration.ip;
#endif
      }
      IPAddress gateway;
      if (!gateway.fromString(configuration.gateway)) {
#ifdef DEBUG
        Serial << endl
               << "ERROR: Problem with WIFI gateway address: "
               << configuration.gateway;
#endif
      }
      IPAddress subnet;
      if (!subnet.fromString(configuration.subnet)) {
#ifdef DEBUG
        Serial << endl
               << "ERROR: Problem with WIFI subnet address: "
               << configuration.subnet;
#endif
      }

      WiFi.config(ip, gateway, subnet);
#ifdef DEBUG
      Serial << endl << "INFO: Settting fixed IP";
#endif
    }

    WiFi.mode(WIFI_STA);
  }
}

void ESPWiFi::listener() {
  if (!(WiFiMode == ESP_MODE_ACCESS_POINT ||
        WiFiMode == ESP_MODE_NETWORK_NOT_SET)) {
    if (!connected()) {
      if (sleepMode) {
        if (millis() - sleepStartTime >= configuration.waitTimeSeries * 1000) {
          sleepMode = false;
        }
      } else {
        if (delayStartTime == 0) {
          delayStartTime = millis();
          if (connections == 0) {

            /* Checking if WiFi is configured */
            if (strlen(configuration.ssid) == 0 ||
                strlen(configuration.password) == 0) {
#ifdef DEBUG
              Serial
                  << endl
                  << F("WARN: WiFI is not configured. Going to configuration "
                       "mode");
#endif
              Device->reboot(ESP_MODE_NETWORK_NOT_SET);
            }

            WiFi.begin(configuration.ssid, configuration.password);
#ifdef DEBUG
            Serial << endl << F("INFO: Starting establishing WiFi connection ");
            Serial << endl << "INFO: SSID: " << configuration.ssid;
#endif
          }
        }

#ifdef ESP_CONFIG_HARDWARE_LED
        if (ledStartTime == 0) {
          ledStartTime = millis();
        }

        if (millis() > ledStartTime + 500) {
          Led->toggle();
          ledStartTime = 0;
        }
#endif

        if (millis() >
            delayStartTime + (configuration.waitTimeConnections * 1000)) {
          connections++;
          delay(10);
#ifdef DEBUG
          Serial << endl
                 << F("INFO: WiFi connection attempt: ") << connections
                 << F(" from ") << configuration.noConnectionAttempts
                 << F(", IP(") << WiFi.localIP() << F(")") << F(" WL-Status=")
                 << WiFi.status();
#endif
          delayStartTime = 0;
        }

        if (connections == configuration.noConnectionAttempts) {
          sleepMode = true;
          WiFi.disconnect();
          sleepStartTime = millis();
          delayStartTime = 0;

#ifdef ESP_CONFIG_HARDWARE_LED
          ledStartTime = 0;
          Led->off();
#endif

          connections = 0;
#ifdef DEBUG
          Serial << endl
                 << F("WARN: Not able to connect.Going to sleep mode for ")
                 << configuration.waitTimeSeries << F("sec.");
#endif
        }
      }
    } else {
      if (connections > 0) {
        connections = 0;
        delayStartTime = 0;

#ifdef ESP_CONFIG_HARDWARE_LED
        ledStartTime = 0;
        Led->off();
#endif
      }
    }
  }
}

boolean ESPWiFi::connected() {
  if (WiFi.status() == WL_CONNECTED) {
    if (disconnected) {
      eventConnectionEstablished = true;
      disconnected = false;
#ifdef DEBUG
      Serial << endl
             << F("INFO: WiFi Connection established") << F(", MAC: ")
             << WiFi.macAddress() << F(", IP: ") << WiFi.localIP();
#endif
    }
  } else {
    disconnected = true;
  }
  return !disconnected;
}

boolean ESPWiFi::eventConnected() {
  boolean returnValue = eventConnectionEstablished;
  eventConnectionEstablished = false;
  return returnValue;
}

/*
uint16_t ESPWiFi::getJSON(const String &url, String &response) {
  http.begin(url);
  uint16_t httpCode = http.GET();
  if (httpCode == 200) {
    response = http.getString();
  } else {
    response = "";
  }
  http.end();
  return httpCode;
}
*/
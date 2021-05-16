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

  /* Checking if backup configuration exists and setting a flag */
  if (strlen(configuration.ssidBackup) > 0 &&
      strcmp(configuration.ssidBackup, ESP_CONFIG_NETWORK_DEFAULT_NONE_SSID) !=
          0 &&
      strlen(configuration.passwordBackup) > 0) {
    isBackupConfigurationSet = true;
#ifdef DEBUG
    Serial << endl
           << F("INFO: WIFI: Bakcup configuration exist. SSID: ")
           << configuration.ssidBackup;
  } else {
    Serial << endl << F("INFO: WIFI: Bakcup configuration does NOT exist");
#endif
  } /* Endif: Checking if backup configuration exists and setting a flag */

#ifdef DEBUG
  Serial << endl << F("INFO: WiFi: Device is in mode: ") << WiFiMode;
#endif

  if (WiFiMode == ESP_MODE_ACCESS_POINT ||
      WiFiMode == ESP_MODE_NETWORK_NOT_SET) {
#ifdef DEBUG
    Serial << endl << F("INFO: WiFi: Starting HotSpot: ");
#endif
    IPAddress apIP(192, 168, 5, 1);
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ESP_HOSTNAME);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

#ifdef DEBUG
    Serial << F("completed");
#endif
  } else {
#ifdef DEBUG
    Serial << endl << F("INFO: WiFi: In WIFI_STA mode");
#endif

    if (!configuration.isDHCP) {
      IPAddress ip;
      if (!ip.fromString(configuration.ip)) {
#ifdef DEBUG
        Serial << endl
               << "ERROR: WiFi: Problem with WIFI IP address: " << configuration.ip;
#endif
      }
      IPAddress gateway;
      if (!gateway.fromString(configuration.gateway)) {
#ifdef DEBUG
        Serial << endl
               << "ERROR: WiFi: Problem with WIFI gateway address: "
               << configuration.gateway;
#endif
      }
      IPAddress subnet;
      if (!subnet.fromString(configuration.subnet)) {
#ifdef DEBUG
        Serial << endl
               << "ERROR: WiFi: Problem with WIFI subnet address: "
               << configuration.subnet;
#endif
      }

      WiFi.config(ip, gateway, subnet);
#ifdef DEBUG
      Serial << endl << "INFO: WiFi: Settting fixed IP";
#endif
    }

    WiFi.mode(WIFI_STA);
  }
}

void ESPWiFi::switchConfiguration() {
  isPrimaryConfiguration = isPrimaryConfiguration ? false : true;
  noOfFailures = 0;
  WiFi.persistent(false);
  WiFi.disconnect(true);
  if (WiFi.setHostname(Device->configuration.name)) {
#ifdef DEBUG
    Serial << endl
           << F("INFO: WIFI: Hostname set to: ") << Device->configuration.name;
  } else {
    Serial << endl
           << F("ERROR: WIFI: Hostname NOT set: ")
           << Device->configuration.name;
#endif
  }
  WiFi.setSleep(false);

  /* Setting Fixed IP for Primary Configuration if set */
  if (isPrimaryConfiguration && !configuration.isDHCP) {
    IPAddress ip;
    if (!ip.fromString(configuration.ip)) {
#ifdef DEBUG
      Serial << endl
             << F("ERROR: WIFI: Problem with WIFI IP address: ")
             << configuration.ip;
#endif
    }
    IPAddress gateway;
    if (!gateway.fromString(configuration.gateway)) {
#ifdef DEBUG
      Serial << endl
             << F("ERROR: WIFI: Problem with WIFI gateway address: ")
             << configuration.gateway;
#endif
    }
    IPAddress subnet;
    if (!subnet.fromString(configuration.subnet)) {
#ifdef DEBUG
      Serial << endl
             << F("ERROR: WIFI: Problem with WIFI subnet address: ")
             << configuration.subnet;
#endif
    }

    WiFi.config(ip, gateway, subnet);
#ifdef DEBUG
    Serial << endl << F("INFO: WIFI: Settting fixed IP");
#endif
  } else if (!isPrimaryConfiguration && !configuration.isDHCP) {
    WiFi.config((uint32_t)0x00000000, (uint32_t)0x00000000,
                (uint32_t)0x00000000);

  } /* Endif: Setting Fixed IP for Primary Configuration if set */

  WiFi.mode(WIFI_STA);

#ifdef DEBUG
  Serial << endl
         << F("INFO: WIFI: ")
         << (isPrimaryConfiguration ? F("Primary") : F("Backup"))
         << F(" configuration set");
#endif
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

            if (isPrimaryConfiguration) {
              WiFi.begin(configuration.ssid, configuration.password);
            } else {
              WiFi.begin(configuration.ssidBackup,
                                    configuration.passwordBackup);
            }

            WiFi.begin(configuration.ssid, configuration.password);
#ifdef DEBUG
            Serial << endl << F("INFO: WiFi: Starting establishing WiFi connection ");
            Serial << endl << "INFO: WiFi: SSID: " << configuration.ssid;
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
                 << F("WARN: WiFi: Not able to connect. Going to sleep mode for ")
                 << configuration.waitTimeSeries << F("sec.");
#endif

          /* Switching configurations */
          if (isBackupConfigurationSet) {
            noOfFailures++;
            if (noOfFailures == configuration.noFailuresToSwitchNetwork) {
              switchConfiguration();
            }
          } /* Endif: Switching configurations */
        }
      }
    } else {
      if (connections > 0) {
        connections = 0;
        delayStartTime = 0;
        noOfFailures = 0;

#ifdef ESP_CONFIG_HARDWARE_LED
        ledStartTime = 0;
        Led->off();
#endif

#ifdef DEBUG
        Serial << endl
               << F("INFO: WIFI: Setting hostname to: ")
               << Device->configuration.name;
#endif
        if (WiFi.setHostname(Device->configuration.name)) {
#ifdef DEBUG
          Serial << F(" ... Success");
        } else {
          Serial << F(" ... Error");
#endif
        }
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
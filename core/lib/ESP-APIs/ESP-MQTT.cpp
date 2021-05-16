/* ESP Firmware for smart home devices, Website: https://ESP.smartnydom.pl/ */

#include "ESP-MQTT.h"

ESPMQTT::ESPMQTT(){};

#ifdef ESP_CONFIG_HARDWARE_LED
void ESPMQTT::begin(uint8_t id, ESPDataAccess *Data, char *deviceName,
                    ESPLED *Led) {
  _Led = Led;
  begin(id, Data, deviceName);
}
#endif

void ESPMQTT::begin(uint8_t id, ESPDataAccess *Data, char *deviceName) {
  _Data = Data;
  _deviceName = deviceName;
  _Data->get(id, configuration);
  _Data->get(networkConfiguration);

  //const esp_mqtt_client_config_t mqtt_cfg = {.uri = "mqtt://mqtt.eclipse.org"  };
  //esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
  //esp_mqtt_client_start(client);


  if (strlen(configuration.ip) > 0) {
    IPAddress ip;
    if (ip.fromString(configuration.ip)) {
    }
#ifdef DEBUG
    else {
      Serial << endl
             << F("ERROR: Problem with MQTT IP address: ") << configuration.ip;
    }
#endif
  } else if (strlen(configuration.host) > 0) {
  } else {
    isConfigured = false;
  }

  Data = {};

#ifdef DEBUG
  Serial << endl
         << F("INFO: MQTT Configuration") << endl
         << F(" - Host: ") << configuration.host << endl
         << F(" - IP: ") << configuration.ip << endl
         << F(" - Port: ") << configuration.port << endl
         << F(" - User: ") << configuration.user << endl
         << F(" - Password: ") << configuration.password << endl
         << F(" - Timeout: ") << configuration.timeout << endl
         << F(" - Retain: ") << configuration.retain << endl
         << F(" - QOS: ") << configuration.qos << endl
         << F(" - LWT: ") << configuration.lwt.topic;
#endif
}

#ifdef ESP_CONFIG_API_PROCESS_REQUESTS
void ESPMQTT::subscribe(const char *topic) {

  if (strlen(topic) > 0) {
#ifdef ESP_CONFIG_HARDWARE_LED
    _Led->on();
#endif

#ifdef DEBUG
    Serial << endl << F(" - ") << topic;
#endif
#ifdef ESP_CONFIG_HARDWARE_LED
    _Led->off();
#endif
  }
}
#endif

void ESPMQTT::disconnect() {}

boolean ESPMQTT::listener() {
  boolean _ret = false;

  return _ret;
}

void ESPMQTT::connect() {

  if (isConfigured) {
    if (sleepMode) {
      if (millis() - sleepStartTime >=
          networkConfiguration.waitTimeSeries * 1000) {
        sleepMode = false;
      }
    } else {
#ifdef ESP_CONFIG_HARDWARE_LED
      if (ledStartTime == 0) {
        ledStartTime = millis();
      }
#endif
      if (delayStartTime == 0) {
        delayStartTime = millis();
        /* Connecing to MQTT Broker depending on LWT topics being set or no */

        boolean _connected;

        // connect here

        if (_connected) {
          eventConnectionEstablished = true;
          delayStartTime = 0;
#ifdef ESP_CONFIG_HARDWARE_LED
          ledStartTime = 0;
          _Led->off();
#endif
          connections = 0;

#ifdef DEBUG
          Serial << endl << F("INFO: Connected to MQTT Broker");
#endif

          return;
        }
      }
#ifdef ESP_CONFIG_HARDWARE_LED
      if (millis() > ledStartTime + 500) {
        _Led->toggle();
        ledStartTime = 0;
      }
#endif
      if (millis() >
          delayStartTime + (networkConfiguration.waitTimeConnections * 1000)) {

        connections++;
        yield();
#ifdef DEBUG
        Serial << endl
               << F("INFO: MQTT Connection attempt: ") << connections + 1
               << F(" from ") << networkConfiguration.noConnectionAttempts
               << F(", connection status: ") << "satus here"
               << F(", connection time: ") << millis() - delayStartTime
               << F("ms");

#endif
        delayStartTime = 0;
      }

      if (connections >= networkConfiguration.noConnectionAttempts) {
        sleepMode = true;
        sleepStartTime = millis();

        delayStartTime = 0;
#ifdef ESP_CONFIG_HARDWARE_LED
        ledStartTime = 0;
        _Led->off();
#endif
        connections = 0;

#ifdef DEBUG
        Serial << endl
               << F("WARN: MQTT: Not able to connect to MQTT.Going to sleep "
                    "mode for ")
               << networkConfiguration.waitTimeSeries << F("sec.");
#endif
      }
    }
  }
}

void ESPMQTT::setReconnectionParams(
    uint8_t no_connection_attempts,
    uint8_t duration_between_connection_attempts,
    uint8_t duration_between_next_connection_attempts_series) {
  networkConfiguration.noConnectionAttempts = no_connection_attempts;
  networkConfiguration.waitTimeConnections =
      duration_between_connection_attempts;
  networkConfiguration.waitTimeSeries =
      duration_between_next_connection_attempts_series;
}

boolean ESPMQTT::connected() {
  boolean returnValue = eventConnectionEstablished;
  eventConnectionEstablished = false;
  return returnValue;
}

boolean ESPMQTT::publish(const char *topic, const char *message) {

  boolean pubslishingStatus = false;

  if (true) {
#ifdef ESP_CONFIG_HARDWARE_LED
    _Led->on();
#endif
#ifdef DEBUG
    Serial << endl << F("----------- Publish MQTT -----------");
    Serial << endl << F("Topic: ") << topic;
    Serial << endl << F("Message: ") << message;
#endif
    if (strlen(topic) > 0) {
      // pubslishingStatus = Broker.publish(topic, message);
    }
#ifdef DEBUG
    else {
      Serial << endl << F("WARN: No MQTT topic.");
    }
#endif
#ifdef ESP_CONFIG_HARDWARE_LED
    _Led->off();
#endif
#ifdef DEBUG
    Serial << endl
           << F("Status: ")
           << (pubslishingStatus ? F("published") : F("NOT pubslished"));
    Serial << endl << F("------------------------------------");
#endif
  }

  return pubslishingStatus;
}
#ifndef _ESP_MQTT_h
#define _ESP_MQTT_h

#include <Configuration.h>

#ifdef ESP_CONFIG_API_MQTT

#include "arduino.h"

#include <ESP-Data-Access.h>
#include <MQTT-Structure.h>
#include <NETWORK-Structure.h>
#include <mqtt_client.h>


#ifdef DEBUG
#include <Streaming.h>
#endif

#ifdef ESP_CONFIG_HARDWARE_LED
#include <ESP-LED.h>
#endif

class ESPMQTT {

private:
  ESPDataAccess *_Data;
  char *_deviceName;
  NETWORK networkConfiguration;

#ifdef ESP_CONFIG_HARDWARE_LED
  ESPLED *_Led;
  unsigned long ledStartTime = 0;
#endif

  unsigned long sleepStartTime = 0;
  boolean sleepMode = false;
  boolean isConfigured =
      true; // if it's falsed it does not connect to MQTT Broker

  uint8_t connections = 0;
  unsigned long delayStartTime = 0;
  boolean eventConnectionEstablished = false;

  /* Sets parameters related to reconnection to MQTT Broker if there was
   * problems to connect to it */
  void setReconnectionParams(
      uint8_t no_connection_attempts,
      uint8_t duration_between_connection_attempts,
      uint8_t duration_between_next_connection_attempts_series);

  /* Connecting to MQTT Broker */
  void connect();

  /* Method turns off MQTT API */
  void disconnect();

public:
  MQTT_MESSAGE message;
  MQTT_BROKER configuration;

  /* Constructor: it sets all necessary parameters */
  ESPMQTT();

/* Initialization of the class */
#ifdef ESP_CONFIG_HARDWARE_LED
  void begin(uint8_t id, ESPDataAccess *Data, char *deviceName, ESPLED *Led);
#endif

  void begin(uint8_t id, ESPDataAccess *Data, char *deviceName);


  /* Methods establishes connection from MQTT Broker, subscribed and set relay
 * default values */
  boolean listener();

  /* Method returns true if device connected to MQTT Broker */
  boolean connected();

  /* Methods publishes a message to MQTT Broker */
  boolean publish(const char *topic, const char *message);

  /* Methods subsribes to topic in the MQTT Broker */
  void subscribe(const char *);

};

#endif // ESP_CONFIG_API_MQTT
#endif // _ESP_MQTT_h
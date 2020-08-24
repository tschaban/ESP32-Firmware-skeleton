#ifdef ESP_CONFIG_API_MQTT

#include <ESP-MQTT.h>
ESPMQTT MQTTAPIs[ESP_CONFIG_API_MQTT_MAX_NUMBER];

void initializeMQTTAPIs(void);
void eventsListnerMQTTAPIs(void);

/***** Body ******/

void initializeMQTTAPIs(void) {
  for (uint8_t i = 0; i < Device.configuration.noOfMQTTAPIs; i++) {
#ifdef ESP_CONFIG_HARDWARE_LED
    MQTTAPIs[i].begin(i, &Data, "AS", &Led);
#else
    MQTTAPIs[i].begin(i, &Data, "AS");
#endif // ESP_CONFIG_HARDWARE_LED
  }
}

void eventsListnerMQTTAPIs(void) {

  /* Listens for switch events */
  for (uint8_t i = 0; i < Device.configuration.noOfMQTTAPIs; i++) {
  }
}

#endif // ESP_CONFIG_API_MQTT
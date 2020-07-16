#include "ESP-Sensor-DS18B20.h"

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20

ESPDS18B20Sensor::ESPDS18B20Sensor(){};

void ESPDS18B20Sensor::begin(ESPDataAccess *_Data, uint8_t id) {
  Data = _Data;
  Data->get(id, configuration);

  configuration.gpio = 14;
  configuration.interval = 10000;

  WireBUS.begin(configuration.gpio);
  Sensor.setOneWire(&WireBUS);
  _initialized = false;
}

float ESPDS18B20Sensor::getTemperature() {
  float temperature = -127;
  if (_initialized) {
    // OneWire wireProtocol(configuration.gpio);
    // DallasTemperature sensor(&wireProtocol);
    Sensor.begin();

    do {
      Sensor.requestTemperatures();
      temperature = configuration.unit ==
                            ESP_CONFIG_FUNCTIONALITY_TEMPERATURE_UNIT_CELSIUS
                        ? Sensor.getTempCByIndex(0)
                        : Sensor.getTempFByIndex(0);
    } while (temperature == 85.0 || temperature == (-127.0));
  }
  return temperature + configuration.correction;
}

float ESPDS18B20Sensor::getLatestTemperature() {
  ready = false;
  return currentTemperature;
}

boolean ESPDS18B20Sensor::isReady() {
  if (ready) {
    ready = false;
    return true;
  } else {
    return false;
  }
}

void ESPDS18B20Sensor::listener() {
  if (_initialized) {
    unsigned long time = millis();

    if (startTime == 0) { // starting timer. used for switch sensitiveness
      startTime = time;
    }

    if (time - startTime >= configuration.interval * 1000) {
      float newTemperature = getTemperature();
      currentTemperature = newTemperature;
      ready = true;
      startTime = 0;
    }
  }
}

void ESPDS18B20Sensor::scan(uint8_t gpio, DS18B20Addresses &addresses) {

#ifdef DEBUG
  Serial << endl << "INFO: Scanning for DS18B20 sensors on GPIO: " << gpio;
  Serial << endl << " - Wire Bus initialized";
  Sensor.setOneWire(&WireBUS);
#endif
  WireBUS.begin(gpio);
  WireBUS.reset();
  Sensor.begin();
  numberOfDevicesOnBus = Sensor.getDS18Count();
#ifdef DEBUG
  Serial << endl
         << " - Number of detected DS18B20 sensors: " << numberOfDevicesOnBus;
#endif

  /* @TODO This is a workaround as getDS18Count doesn't retun number of sensor
   */
  if (numberOfDevicesOnBus == 0) {
    numberOfDevicesOnBus = ESP_CONFIG_HARDWARE_SENSOR_DS18B20_MAX_NUMBER;
#ifdef DEBUG
    Serial << endl
           << " - WARN: No sensors found. Hard scanning for "
           << numberOfDevicesOnBus << " addresses";
#endif
  }

  if (numberOfDevicesOnBus > 0) {
    DeviceAddress _address;

    for (uint8_t i = 0; i < numberOfDevicesOnBus; i++) {
      Sensor.getAddress(_address, i);

      if (_address[0] != 0) {
        if (i == 0 || (i > 0 && (memcmp(addresses[i - 1], _address,
                                        sizeof(addresses[i - 1])) != 0))) {

          memcpy(addresses[i], _address, sizeof(_address[0]) * 8);
        } else {
          break;
        }
      } else {
        break;
      }
#ifdef DEBUG
      Serial << endl
             << " - Found sensor: " << _HEX(addresses[i][0]) << ":"
             << addresses[i][1] << ":" << addresses[i][2] << ":"
             << addresses[i][3] << ":" << addresses[i][4] << ":"
             << addresses[i][5] << ":" << addresses[i][6] << ":"
             << addresses[i][7];

      Sensor.requestTemperatures();
      Serial << endl << " - Temperature : " << Sensor.getTempC(addresses[i]);

#endif
    }
  }
}

#endif // ESP_CONFIG_HARDWARE_SENSOR_DS18B20

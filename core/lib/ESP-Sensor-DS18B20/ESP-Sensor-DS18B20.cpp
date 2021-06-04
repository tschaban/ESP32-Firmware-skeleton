#include "ESP-Sensor-DS18B20.h"

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20

ESPDS18B20Sensor::ESPDS18B20Sensor(){};

void ESPDS18B20Sensor::begin(ESPDataAccess *_Data, uint8_t id) {
  Data = _Data;
  Data->get(id, configuration);
  WireBUS.begin(configuration.gpio);
  Sensor.setOneWire(&WireBUS);
  Sensor.begin();

  if (Sensor.isConnected(configuration.address)) {
    _initialized = true;
  } else {
    _initialized = false;
#ifdef DEBUG
    char addressTxt[17];
    addressToChar(configuration.address, addressTxt);
    Serial << endl
           << "WARN: Sensor DS18B20[" << addressTxt
           << "] not found. Not initialized";
#endif
  }
}

float ESPDS18B20Sensor::getCurrentTemperature() {
  float temperature = DEVICE_DISCONNECTED_C;
  if (_initialized) {
#ifdef DEBUG
    char addressTxt[17];
    addressToChar(configuration.address, addressTxt);
    Serial << endl
           << "INFO: Reading temperature from DS18B20[" << addressTxt << "] ";
#endif

    if (readTimeOut == 0) {
      readTimeOut = millis();
    }

    if (Sensor.isConnected(configuration.address)) {

      Sensor.requestTemperaturesByAddress(configuration.address);

      do {
        temperature = configuration.unit ==
                              ESP_CONFIG_FUNCTIONALITY_TEMPERATURE_UNIT_CELSIUS
                          ? Sensor.getTempC(configuration.address)
                          : Sensor.getTempF(configuration.address);
        if (millis() - readTimeOut >
            ESP_CONFIG_HARDWARE_SENSOR_DS18B20_READ_TIMEOUT) {
          break;
        }
      } while (temperature == 85.0 || temperature == (-127.0));
      temperature = temperature + configuration.correction;
    }
  }
#ifdef DEBUG
  else {
    Serial << ": NOT CONNECTED: ";
  }
  Serial << ": " << temperature
         << ", read duration: " << (millis() - readTimeOut) << "msec.";
#endif
  currentTemperature = temperature;
  readTimeOut = 0;
  return temperature;
}

float ESPDS18B20Sensor::getTemperature() { return currentTemperature; }

boolean ESPDS18B20Sensor::listener() {
  boolean ready = false;
  if (_initialized) {
    unsigned long time = millis();
    if (startTime == 0) { // starting timer. used for switch sensitiveness
      startTime = time;
    }
    if (time - startTime >= configuration.interval) {
      if (getCurrentTemperature() != DEVICE_DISCONNECTED_C)
        ready = true;
      startTime = 0; // It's set to 0 to allow other code to execude, just after
                     // reading the data
    }
  }
  return ready;
}

uint8_t ESPDS18B20Sensor::scan(uint8_t gpio, DS18B20Addresses &addresses) {
  uint8_t _found = 0;
  uint8_t numberOfDevicesOnBus = 0;
#ifdef DEBUG
  Serial << endl << "INFO: Scanning for DS18B20 sensors on GPIO: " << gpio;
  Serial << endl << " - Wire Bus initialized";
  Sensor.setOneWire(&WireBUS);
#endif
  WireBUS.begin(gpio);
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
          _found++;
        } else {
          break;
        }
      } else {
        break;
      }
#ifdef DEBUG
      Serial << endl
             << " - Found sensor: " << addresses[i][0] << ":" << addresses[i][1]
             << ":" << addresses[i][2] << ":" << addresses[i][3] << ":"
             << addresses[i][4] << ":" << addresses[i][5] << ":"
             << addresses[i][6] << ":" << addresses[i][7];

      Sensor.requestTemperatures();
      Serial << endl << " - Temperature : " << Sensor.getTempC(addresses[i]);

#endif
    }
  }
  return _found;
}

void ESPDS18B20Sensor::addressToChar(DeviceAddress &address,
                                     char *addressString) {
  sprintf(addressString, "%02X%02X%02X%02X%02X%02X%02X%02X", address[0],
          address[1], address[2], address[3], address[4], address[5],
          address[6], address[7]);
}

void ESPDS18B20Sensor::addressToInt(char *addressString,
                                    DeviceAddress &address) {

  int x;
  for (uint8_t i = 0; i < ESP_CONFIG_HARDWARE_SENSOR_DS18B20_ADDRESS_LENGTH;
       i++) {
    x = 0;
    for (uint8_t index = 0; index < 2; index++) {
      char c = *addressString;
      if (c >= '0' && c <= '9') {
        x *= 16;
        x += c - '0';
      } else if (c >= 'A' && c <= 'F') {
        x *= 16;
        x += (c - 'A') + 10;
      }
      addressString++;
    }
    address[i] = x;
  }
}

void ESPDS18B20Sensor::addressNULL(DeviceAddress &address) {
  for (uint8_t i = 0; i < ESP_CONFIG_HARDWARE_SENSOR_DS18B20_ADDRESS_LENGTH;
       i++) {
    address[i] = 0;
  }
}

#endif // ESP_CONFIG_HARDWARE_SENSOR_DS18B20

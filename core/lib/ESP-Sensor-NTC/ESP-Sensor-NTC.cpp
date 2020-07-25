
#include "ESP-Sensor-NTC.h"

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC

ESPNTCSensor::ESPNTCSensor(){};

#ifdef ESP_CONFIG_HARDWARE_ADS1115
void ESPNTCSensor::begin(ESPDataAccess *_Data, TwoWire *_WirePort0,
                         TwoWire *_WirePort1, uint8_t id) {
  Data = _Data;
  Data->get(id, configuration);
  if (configuration.adcInput == ESP_HARDWARE_ITEM_NOT_EXIST) {
    ADCInput.begin(_Data, _WirePort0, _WirePort1, configuration.adcInput);
    ADCInput.setInterval(configuration.interval);
    _initialized = true;
  }

#ifdef DEBUG
  if (_initialized) {
    Serial << endl << "INFO: NTC[" << id << "] initialized";
  } else {
    Serial << endl << "WARN: NTC[" << id << "] NOT initialized";
  }
#endif
}
#else

void ESPNTCSensor::begin(ESPDataAccess *_Data, uint8_t id) {
  Data = _Data;
  Data->get(id, configuration);
  if (configuration.adcInput == ESP_HARDWARE_ITEM_NOT_EXIST) {
    ADCInput.begin(_Data, configuration.adcInput);
    ADCInput.setInterval(configuration.interval);
    _initialized = true;
  }
#ifdef DEBUG
  if (_initialized) {
    Serial << endl << "INFO: NTC[" << id << "] initialized";
  } else {
    Serial << endl << "WARN: NTC[" << id << "] NOT initialized";
  }
#endif
}
#endif

boolean ESPNTCSensor::listener() {
  ready = false;
  if (_initialized) {
    if (ADCInput.listener()) {
      double rNTC = (10000 * ADCInput.data.voltageCalculated) /
                    (configuration.vcc - ADCInput.data.voltageCalculated);
      rNTC = log(rNTC);
      temperature = (1 / (configuration.coefficients.A +
                          (configuration.coefficients.B +
                           (configuration.coefficients.C * rNTC * rNTC)) *
                              rNTC)) -
                    273.15 + configuration.correction;
      ready = true;
    }
  }
  return ready;
}

#endif // ESP_CONFIG_HARDWARE_SENSOrNTC

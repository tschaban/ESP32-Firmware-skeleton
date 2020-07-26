
#include "ESP-Batterymeter.h"

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER

ESPBatterymeter::ESPBatterymeter(){};

#ifdef ESP_CONFIG_HARDWARE_ADS1115
void ESPBatterymeter::begin(ESPDataAccess *_Data, TwoWire *_WirePort0,
                            TwoWire *_WirePort1, uint8_t id) {

#ifdef DEBUG
  Serial << endl
         << "INFO: Batterymeter[" << id << "]"
         << " Initializing";
  Serial << endl
         << "INFO: Batterymeter[" << id << "]"
         << " reading configuration";
#endif
  Data = _Data;
  Data->get(id, configuration);
  if (configuration.adcInput != ESP_HARDWARE_ITEM_NOT_EXIST) {
#ifdef DEBUG
    Serial << endl
           << "INFO: Batterymeter[" << id << "]"
           << " initializing ADC";
#endif
    ADCInput.begin(_Data, _WirePort0, _WirePort1, configuration.adcInput);
#ifdef DEBUG
    Serial << endl
           << "INFO: Batterymeter[" << id << "]"
           << " setting interval " << configuration.interval << "msec";
#endif
    ADCInput.setInterval(configuration.interval);
    _initialized = true;
  }

#ifdef DEBUG
  if (_initialized) {
    Serial << endl << "INFO: Batterymeter[" << id << "] initialized";
  } else {
    Serial << endl << "WARN: Batterymeter[" << id << "] NOT initialized";
  }
#endif
}
#else

void ESPBatterymeter::begin(ESPDataAccess *_Data, uint8_t id) {
  Data = _Data;
  Data->get(id, configuration);
  if (configuration.adcInput == ESP_HARDWARE_ITEM_NOT_EXIST) {
    ADCInput.begin(_Data, configuration.adcInput);
    ADCInput.setInterval(configuration.interval);
    _initialized = true;
  }
#ifdef DEBUG
  if (_initialized) {
    Serial << endl << "INFO: Batterymeter[" << id << "] initialized";
  } else {
    Serial << endl << "WARN: Batterymeter[" << id << "] NOT initialized";
  }
#endif
}
#endif

boolean ESPBatterymeter::listener() {
  if (ready)
    ready = false;
  if (_initialized) {
    if (ADCInput.listener()) {

      data.voltage = ADCInput.data.voltageCalculated;
      if (data.voltage >= configuration.voltage.max) {
        data.percentage = 100;
      } else if (data.voltage <= configuration.voltage.min) {
        data.percentage = 0;
      } else if (configuration.voltage.max - configuration.voltage.min > 0) {
        data.percentage =
            (data.voltage - configuration.voltage.min) * 100 /
            (configuration.voltage.max - configuration.voltage.min);
      } else {
        data.percentage = 0;
      }
      ready = true;
    }
  }
#ifdef DEBUG
  if (ready) {
    Serial << endl
           << "INFO: Battery on ADC[" << configuration.adcInput
           << "] : Voltage: " << data.voltage
           << "v, Percentage: " << data.percentage << "%";
  }
#endif

  return ready;
}

#endif // ESP_CONFIG_FUNCTIONALITY_BATTERYMETER

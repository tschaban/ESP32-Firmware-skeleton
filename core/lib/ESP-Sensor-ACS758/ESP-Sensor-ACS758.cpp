
#include "ESP-Sensor-ACS758.h"

#ifdef ESP_CONFIG_HARDWARE_SENSOR_ACS758

ESPACS758Sensor::ESPACS758Sensor(){};

#ifdef ESP_CONFIG_HARDWARE_ADS1115
void ESPACS758Sensor::begin(ESPDataAccess *_Data, TwoWire *_WirePort0,
                            TwoWire *_WirePort1, uint8_t id) {
  Data = _Data;
  Data->get(id, configuration);
  if (configuration.adcInput != ESP_HARDWARE_ITEM_NOT_EXIST) {
    ADCInput.begin(_Data, _WirePort0, _WirePort1, configuration.adcInput);
    ADCInput.setInterval(configuration.interval);
    /* set quiescent Output voltage for selected model */
    QOV = voltageOffset[configuration.type] * VCC;
    /* convert current cut off to mV */
    cutOff = sensitivity[temperatureOffset][configuration.type] / cutOffLimit;

    _initialized = true;
  }

#ifdef DEBUG
  if (_initialized) {
    Serial << endl
           << "INFO: ACS758[" << id << "] initialized" << endl
           << "INFO: ACS758 Configuration: ";
  } else {
    Serial << endl << "WARN: ACS758[" << id << "] NOT initialized";
  }
#endif
}
#else

void ESPACS758Sensor::begin(ESPDataAccess *_Data, uint8_t id) {
  Data = _Data;
  Data->get(id, configuration);
  if (configuration.adcInput == ESP_HARDWARE_ITEM_NOT_EXIST) {
    ADCInput.begin(_Data, configuration.adcInput);
    ADCInput.setInterval(configuration.interval);
    _initialized = true;
  }
#ifdef DEBUG
  if (_initialized) {
    Serial << endl
           << "INFO: ACS758[" << id << "] initialized" << endl
           << "INFO: ACS758 Configuration: ";

  } else {
    Serial << endl << "WARN: ACS758[" << id << "] NOT initialized";
  }
#endif
}
#endif

boolean ESPACS758Sensor::listener() {
  if (ready)
    ready = false;
  if (_initialized) {
    if (ADCInput.listener()) {

#ifdef DEBUG
      Serial << endl << "INFO: ACS758 Sensor: calcuating current";
#endif

      /* 0.007 is a value to make voltage zero when there is no current */
      Serial << " INFO: ACS758: QOV: " << QOV
             << ", sensitivity: " << sensitivity[temperatureOffset][configuration.type]
             << "mA/V, cutOff: " << cutOff;
      voltage = ADCInput.data.voltageCalculated - QOV;

      if (abs(voltage) > cutOff) {
        current = voltage / sensitivity[temperatureOffset][configuration.type];
      } else {
        current = 0;
      }

#ifdef DEBUG
      Serial << endl
             << "INFO: ACS758 Data: Voltage: " << voltage
             << "V, Current: " << current << "A";
#endif

      ready = true;
    }
  }
  return ready;
}

void ESPACS758Sensor::setTemperatureOffset(uint8_t offset) {
  if (offset >= 0 && offset <= 4) {
    temperatureOffset = offset;
  }
}

#endif // ESP_CONFIG_HARDWARE_SENSOR_ACS758

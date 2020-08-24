
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
    setQuiescentOutputVoltage(calculateQuiescentOutputVoltage());
    /* convert current cut off to voltage cut off */
    if (configuration.currentCutOff > 0) {
      cutOffVoltage =
          settingsSensitivity[temperatureOffset][configuration.type] /
          configuration.currentCutOff;
    } else {
      cutOffVoltage = 0;
    }
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
      Serial << " INFO: ACS758: quiescentOutputVoltage: "
             << quiescentOutputVoltage << ", settingsSensitivity: "
             << settingsSensitivity[temperatureOffset][configuration.type]
             << "mA/V, cutOffVoltage: " << cutOffVoltage;
      outputVoltage = ADCInput.data.voltageCalculated - quiescentOutputVoltage;

      if (abs(outputVoltage) > cutOffVoltage) {
        current = outputVoltage /
                  settingsSensitivity[temperatureOffset][configuration.type];
      } else {
        current = 0;
      }

#ifdef DEBUG
      Serial << endl
             << "INFO: ACS758 Data: Voltage: " << outputVoltage
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

/* Setting manually VCC */
void ESPACS758Sensor::setVcc(float voltage) {
  configuration.vcc = voltage;
  setQuiescentOutputVoltage(calculateQuiescentOutputVoltage());
}

/* Setting the Quiescent output voltage, it can be set manually using this
 * method */
void ESPACS758Sensor::setQuiescentOutputVoltage(float voltage) {
  quiescentOutputVoltage = voltage;
}

/* Calculates Quiescent output voltage based on the particular device settings
 * and vcc */
float ESPACS758Sensor::calculateQuiescentOutputVoltage() {
  return settingsVoltageOffset[configuration.type] * configuration.vcc;
}

#endif // ESP_CONFIG_HARDWARE_SENSOR_ACS758


#include "ESP-Sensor-NTC.h"

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC

ESPNTCSensor::ESPNTCSensor(){};

#ifdef ESP_CONFIG_HARDWARE_ADS1115
void ESPNTCSensor::begin(ESPDataAccess *_Data, TwoWire *_WirePort0,
                         TwoWire *_WirePort1, uint8_t id) {
  Data = _Data;
  Data->get(id, configuration);
  if (configuration.adcInput != ESP_HARDWARE_ITEM_NOT_EXIST) {
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
    Serial << endl
           << "INFO: NTC[" << id << "] initialized" << endl
           << "INFO: NTC Configuration: ";
    Serial << endl
           << " - Balancing resistor: " << configuration.resistor / 1000
           << "kOm";
    Serial << endl << " - VCC: " << configuration.vcc;
    Serial << endl
           << " - Coefficient A: " << configuration.coefficients.A.value
           << ", Precision: " << configuration.coefficients.A.precision;
    Serial << endl
           << " - Coefficient B: " << configuration.coefficients.B.value
           << ", Precision: " << configuration.coefficients.B.precision;
    Serial << endl
           << " - Coefficient C: " << configuration.coefficients.C.value
           << ", Precision: " << configuration.coefficients.C.precision;

  } else {
    Serial << endl << "WARN: NTC[" << id << "] NOT initialized";
  }
#endif
}
#endif

boolean ESPNTCSensor::listener() {
  if (ready)
    ready = false;
  if (_initialized) {
    if (ADCInput.listener()) {

#ifdef DEBUG
      Serial << endl << "INFO: NTC Sensor: calcuating temperature";
#endif

      double rNTC = (configuration.resistor * ADCInput.data.voltageCalculated) /
                    (configuration.vcc - ADCInput.data.voltageCalculated);

#ifdef DEBUG
      Serial << endl
             << " - Voltage measured: " << ADCInput.data.voltageCalculated;
      Serial << endl << " - Resistancy on NTC: " << rNTC;
#endif

      rNTC = log(rNTC);

      temperature =
          (1 / ((configuration.coefficients.A.value /
                 (configuration.coefficients.A.precision ==
                          ESP_CONFIG_HARDWARE_FLOAT_PRECISION_0
                      ? 1
                      : configuration.coefficients.A.precision ==
                                ESP_CONFIG_HARDWARE_FLOAT_PRECISION_3
                            ? 1000
                            : configuration.coefficients.A.precision ==
                                      ESP_CONFIG_HARDWARE_FLOAT_PRECISION_6
                                  ? 1000000
                                  : 1000000000)) +
                ((ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_B /
                  (configuration.coefficients.B.precision ==
                           ESP_CONFIG_HARDWARE_FLOAT_PRECISION_0
                       ? 1
                       : configuration.coefficients.B.precision ==
                                 ESP_CONFIG_HARDWARE_FLOAT_PRECISION_3
                             ? 1000
                             : configuration.coefficients.B.precision ==
                                       ESP_CONFIG_HARDWARE_FLOAT_PRECISION_6
                                   ? 1000000
                                   : 1000000000)) +
                 ((ESP_CONFIG_HARDWARE_SENSOR_NTC_DEFAULT_C /
                   (configuration.coefficients.C.precision ==
                            ESP_CONFIG_HARDWARE_FLOAT_PRECISION_0
                        ? 1
                        : configuration.coefficients.C.precision ==
                                  ESP_CONFIG_HARDWARE_FLOAT_PRECISION_3
                              ? 1000
                              : configuration.coefficients.C.precision ==
                                        ESP_CONFIG_HARDWARE_FLOAT_PRECISION_6
                                    ? 1000000
                                    : 1000000000)) *
                  rNTC * rNTC)) *
                    rNTC));

#ifdef DEBUG
      Serial << endl << " - Temperature: " << temperature << "Kalvins";
/*
             << " do porowniania "
             << (1 / (0.001129148 +
                      (0.000234125 + (0.0000000876741 * rNTC * rNTC)) * rNTC));
*/
#endif

      temperature = temperature - 273.15 + configuration.correction;

#ifdef DEBUG
      Serial << endl
             << " - Temperature after corrections: " << temperature << "C ";
#endif

      ready = true;
    }
  }
  return ready;
}

#endif // ESP_CONFIG_HARDWARE_SENSOrNTC

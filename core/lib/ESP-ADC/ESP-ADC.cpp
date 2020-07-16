#include "ESP-ADC.h"

#ifdef ESP_CONFIG_HARDWARE_ADC

ESPADC::ESPADC(){};

void ESPADC::begin(ESPDataAccess *_Data, uint8_t id) {

#ifdef ESP_CONFIG_HARDWARE_ADS1115
  readFromGPIO = true;
#endif

  Data = _Data;
  Data->get(id, configuration);

#ifdef DEBUG
  Serial << endl << endl << F("------------ AC VCC Input ------------");
  Serial << endl
         << F("- Initialized") << endl
         << F("- GPIO: ") << configuration.gpio
#ifdef ESP_CONFIG_HARDWARE_ADS1115
         << endl
         << F("- I2C BUS: ") << configuration.i2c.id << endl
         << F("- ADS1115 Address: ") << configuration.i2c.address << endl
         << F("- ADS1115 ADC ID: ") << configuration.i2c.inputId << endl
         << F("- ADS1115 Gain: ") << configuration.i2c.gain << endl
         << F("- ADS1115 Samples/Sec: ") << configuration.i2c.samplesPerSecond

#endif
         << endl
         << F("- Interval: ") << configuration.interval << endl
         << F("- No of Samples: ") << configuration.numberOfSamples << endl
         << F("- ADC Input max V: ") << configuration.maxVCC << endl
         << F("- ADC Input Resolution: ") << configuration.resolution << endl
         << F("- R[A]: ") << configuration.divider.Ra << endl
         << F("- R[B]: ") << configuration.divider.Rb
#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
         << endl
         << F("- Battery min voltage: ") << configuration.battery.minVoltage
         << endl
         << F("- Battery max voltage: ") << configuration.battery.maxVoltage
#endif
         << endl
         << F("-------------------------------------");

#endif

#ifdef ESP_CONFIG_HARDWARE_ADS1115
  if (configuration.i2c.id != ESP_HARDWARE_ITEM_NOT_EXIST &&
      configuration.i2c.inputId != ESP_HARDWARE_ITEM_NOT_EXIST &&
      configuration.i2c.address != ESP_HARDWARE_ITEM_NOT_EXIST) {

    if (configuration.i2c.id == 0) {
      WirePort = WirePort0;
    } else if (configuration.i2c.id == 1) {
      WirePort = WirePort1;
    }
    ADS1115Input.begin(WirePort, configuration.i2c.address);
    ADS1115Input.setGain((adsGain_t)configuration.i2c.gain);
    readFromGPIO = false;
    _initialized = true;
  }

#endif

  // If no GPIO and ADS1115 than ADC input not initialized */
  if (!_initialized && configuration.gpio != ESP_HARDWARE_ITEM_NOT_EXIST) {
    _initialized = true;
  }
}

#ifdef ESP_CONFIG_HARDWARE_ADS1115
void ESPADC::begin(ESPDataAccess *_Data, TwoWire *_WirePort0,
                   TwoWire *_WirePort1, uint8_t id) {
  WirePort0 = _WirePort0;
  WirePort1 = _WirePort1;
  begin(_Data, id);
}
#endif

boolean ESPADC::isReady() {
  if (ready) {
    ready = false;
    return true;
  } else {
    return false;
  }
}

void ESPADC::listener() {

  if (_initialized) {
    unsigned long time = millis();

    if (startTime == 0) {
      startTime = time;
    }

    if (time - startTime >= configuration.interval) {

      if (counterOfSamplings < configuration.numberOfSamples) {

#ifdef ESP_CONFIG_HARDWARE_ADS1115
        if (readFromGPIO) {
#endif
          temporaryAnalogData += analogRead(configuration.gpio);
#ifdef ESP_CONFIG_HARDWARE_ADS1115
        } else {
          temporaryAnalogData +=
              ADS1115Input.readADC_SingleEnded(configuration.i2c.inputId);
        }
#endif

        counterOfSamplings++;
      } else {
        data.raw =
            (uint16_t)(temporaryAnalogData / configuration.numberOfSamples);

        data.percent = (float)data.raw * 100 / configuration.resolution;
        data.voltage = (double)(configuration.maxVCC * data.raw /
                                configuration.resolution);
        if (configuration.divider.Rb > 0) {
          data.voltageCalculated = (data.voltage * (configuration.divider.Ra +
                                                    configuration.divider.Rb)) /
                                   configuration.divider.Rb;
        } else {
          data.voltageCalculated = data.voltage;
        }

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
        if (data.voltageCalculated >= configuration.battery.maxVoltage) {
          data.batteryPercent = 100;
        } else if (data.voltageCalculated <= configuration.battery.minVoltage) {
          data.batteryPercent = 0;
        } else if (configuration.battery.maxVoltage -
                       configuration.battery.minVoltage >
                   0) {
          data.batteryPercent =
              (data.voltageCalculated - configuration.battery.minVoltage) *
              100 / (configuration.battery.maxVoltage -
                     configuration.battery.minVoltage);
        } else {
          data.batteryPercent = 0;
        }
#endif

#ifdef DEBUG
        Serial << endl
               << F("INFO: Reading data from ADC: ") << endl
#ifdef ESP_CONFIG_HARDWARE_ADS1115
               << (readFromGPIO ? " - internal ADC used" : " - ADS1115 used")
               << endl
#else
               << " - internal ADC used" << endl
#endif
               << F(" - Number of samples: ") << counterOfSamplings << endl
               << F(" - Raw = ") << data.raw << endl
               << F(" - Percent = ") << data.percent << endl
               << F(" - Voltage = ") << data.voltage << endl
               << F(" - VoltageCalculated = ") << data.voltageCalculated << endl
#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
               << F(" - Battery level = ") << data.batteryPercent << endl
#endif
               << F(" - Sampling time = ")
               << millis() - startTime - configuration.interval
               << F("msec.");
#endif

        counterOfSamplings = 0;
        temporaryAnalogData = 0;
        ready = true;
        startTime = 0;
      }
    }
  }
}

#endif // ESP_CONFIG_HARDWARE_ADC
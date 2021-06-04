#include "ESP-ADC.h"

#ifdef ESP_CONFIG_HARDWARE_ADC

ESPADC::ESPADC(){};

void ESPADC::begin(ESPDataAccess *_Data, uint8_t id, boolean forBatteryMeter) {

#ifdef ESP_CONFIG_HARDWARE_ADS1115
  readFromGPIO = true;
#endif

  Data = _Data;
  Data->get(id, configuration);

#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
  /* Checking if ADC input is used by Battery Meter if so, it's not initalized,
   * unless forBatteryMeter = true */
  if (!forBatteryMeter) {
    ESPDevice _Device;
    _Device.begin(_Data);
    BATTERYMETER _Battery;
    for (uint8_t i = 0; i < _Device.configuration.noOfBatterymeters; i++) {
      _Data->get(i, _Battery);
      if (_Battery.adcInput == id) {
#ifdef DEBUG
        Serial << endl
               << "INFO: ADC: Input used by battery meter. Not initalizing as "
                  "standalone ADC input";
#endif
        return;
      }
    }
  }
#endif

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
         << F("- R[B]: ") << configuration.divider.Rb << endl
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

void ESPADC::setInterval(uint32_t interval) {
  configuration.interval = interval;
}

#ifdef ESP_CONFIG_HARDWARE_ADS1115
void ESPADC::begin(ESPDataAccess *_Data, TwoWire *_WirePort0,
                   TwoWire *_WirePort1, uint8_t id, boolean forBatteryMeter) {
  WirePort0 = _WirePort0;
  WirePort1 = _WirePort1;
  begin(_Data, id, forBatteryMeter);
}
#endif

boolean ESPADC::listener() {
  if (ready)
    ready = false;
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

          if (configuration.i2c.inputId < 4) {
            temporaryAnalogData +=
                ADS1115Input.readADC_SingleEnded(configuration.i2c.inputId);
          } else if (configuration.i2c.inputId == 4) {
            temporaryAnalogData += ADS1115Input.readADC_Differential_0_1();
          } else if (configuration.i2c.inputId == 5) {
            temporaryAnalogData += ADS1115Input.readADC_Differential_2_3();
          }
        }
#endif

        counterOfSamplings++;
      } else {
        data.raw =
            (uint16_t)(temporaryAnalogData / configuration.numberOfSamples);

        if (data.raw <= ESP_CONFIG_HARDWARE_ADS1115_DEFAULT_RESOLUTION) {
          data.voltage =
              (double)(configuration.maxVCC * data.raw /
                       ESP_CONFIG_HARDWARE_ADS1115_DEFAULT_RESOLUTION);
          data.percent = (float)data.raw * 100 /
                         ESP_CONFIG_HARDWARE_ADS1115_DEFAULT_RESOLUTION;
        } else {
          data.voltage =
              (double)(-1 * configuration.maxVCC *
                       (ESP_CONFIG_HARDWARE_ADS1115_DEFAULT_16B_RESOLUTION -
                        data.raw) /
                       configuration.resolution);
          data.percent =
              (float)(ESP_CONFIG_HARDWARE_ADS1115_DEFAULT_16B_RESOLUTION -
                      data.raw) *
              -100 / ESP_CONFIG_HARDWARE_ADS1115_DEFAULT_RESOLUTION;
        }

        if (configuration.divider.Rb > 0) {
          data.voltageCalculated = (data.voltage * (configuration.divider.Ra +
                                                    configuration.divider.Rb)) /
                                   configuration.divider.Rb;
        } else {
          data.voltageCalculated = data.voltage;
        }

#ifdef DEBUG
        char _numberToText[10];
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
               << F(" - Percent = ") << data.percent << endl;
        sprintf(_numberToText, "%.6f", data.voltage);
        Serial << F(" - Voltage = ") << _numberToText << endl;
        sprintf(_numberToText, "%.6f", data.voltageCalculated) << endl;

        Serial << F(" - VoltageCalculated = ") << _numberToText << endl;
        Serial << F(" - Sampling time = ")
               << millis() - startTime - configuration.interval << F("msec.");
#endif

        counterOfSamplings = 0;
        temporaryAnalogData = 0;
        ready = true;
        startTime = 0; // It's set to 0 to allow other code to execude, just
                       // after reading the data
      }
    }
  }
  return ready;
}

#endif // ESP_CONFIG_HARDWARE_ADC
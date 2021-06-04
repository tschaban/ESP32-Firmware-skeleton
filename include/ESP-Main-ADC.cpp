#ifdef ESP_CONFIG_HARDWARE_ADC

#include <ESP-ADC.h>

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
#include <NXB-Configuration.h>
ESPADC ADCInput;
ADC_DATA ADCData;
double currentAmpers = 0;
double currentPower = 0;

uint16_t lastPower = 0;
uint16_t lastCurrent = 0;
uint16_t _power = 0;
uint16_t _current = 0;

#else /* Generic verson */
ESPADC ADCInput[ESP_CONFIG_HARDWARE_ADC_MAX_NUMBER];

#endif /* End Generic verson */

void initializeADC(void);
void eventsListnerADC(void);

/***** Body ******/

void initializeADC(void) {

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
  if (Device.configuration.noOfADCs > 0) {
    ADCInput.begin(&Data, &WirePort0, &WirePort1, 0);
    Screen.setPowerBar(0);
    Screen.setElectricityCurrent(0);
    Screen.setElectricityPower(0);
  }
#ifdef DEBUG
  Serial << endl << "INFO: ADC for Watt measures initialized";
#endif

#else /* Generic verson */

  for (uint8_t i = 0; i < Device.configuration.noOfADCs; i++) {
#ifdef ESP_CONFIG_HARDWARE_ADS1115
    ADCInput[i].begin(&Data, &WirePort0, &WirePort1, i);
#else
    ADCInput[i].begin(&Data, i);
#endif
#ifdef DEBUG
    Serial << endl << "INFO: ADC(" << i + 1 << ") initialized";
#endif
  }

#endif /* End Generic verson */
};

void eventsListnerADC(void) {

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
  if (ADCInput.listener()) {
    ADCData = ADCInput.data;

    currentAmpers =
        (double)((WATTOMETER_SHUNT_MAX_CURRENT * ADCData.voltageCalculated) /
                 WATTOMETER_SHUNT_MAX_VOLTAGE_AT_MAX_CURRENT);

    if (currentAmpers >= 0) {
      _current = (uint32_t)round(currentAmpers * 100);
    } else {
      _current = (uint32_t)round(currentAmpers * -100);
    }


    if (_current != lastPower) {
      lastCurrent = _current;
      Screen.setElectricityCurrent(lastCurrent);
    }

    currentPower = currentAmpers * Batterymeter.data.voltage;

    if (currentPower >= 0) {
      _power = (uint32_t)round(currentPower);
    } else {
      _power = (uint32_t)round(currentPower * -1);
    }

    if (_power != lastPower) {
      lastPower = _power;
      Screen.setElectricityPower(lastPower);
  //    Screen.setPowerBar((uint8_t)round((100 * _power) / WATTOMETER_MAX_POWER));
    }

#ifdef DEBUG
    Serial << endl
           << "INFO: WATTOMETER: " << endl
           << " - Current Ampers: " << currentAmpers;
    Serial << endl << " - Battery voltage: " << Batterymeter.data.voltage;
    Serial << endl << " - Watts: " << currentPower;

#endif
  }

#else /* Generic verson */

  /* Listens for switch events */
  for (uint8_t i = 0; i < Device.configuration.noOfADCs; i++) {
    if (ADCInput[i].listener()) {
      ADC_DATA ADCData;
      ADCData = ADCInput[i].data;

      switch (i) {
      case 0: {
        break;
      }
      case 1: {
        break;
      }
      }

#ifdef DEBUG
      Serial << endl
             << "INFO: Data from ADC(" << i + 1
             << "): in buffer. Ready for processing." << endl
             << "INFO: Publishing: " << ADCData.voltageCalculated << endl;
#endif

      // HERE CODE FOR ADC
    }
  }
#endif /* End Generic verson */
};

#endif // ESP_CONFIG_HARDWARE_ADC

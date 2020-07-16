#ifdef ESP_CONFIG_HARDWARE_ADC

#include <ESP-ADC.h>
ESPADC ADCInput[ESP_CONFIG_HARDWARE_ADC_MAX_NUMBER];
void initializeADC(void);
void eventsListnerADC(void);

/***** Body ******/

void initializeADC(void) {
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
};

void eventsListnerADC(void) {

  /* Listens for switch events */
  for (uint8_t i = 0; i < Device.configuration.noOfADCs; i++) {
    ADCInput[i].listener();
    if (ADCInput[i].isReady()) {
      char _number[10];
      if (i == 0) {
        sprintf(_number, "%-.4f", ADCInput[i].data.voltageCalculated);
        p0_t0.setText(_number);
      } else if (i == 1) {
        sprintf(_number, "%-.4f", ADCInput[i].data.voltageCalculated);
        p0_t1.setText(_number);
      }
#ifdef DEBUG
      Serial << endl
             << "INFO: Data from ADC(" << i + 1
             << "): in buffer. Ready for processing." << endl
             << "INFO: Publishing: " << _number << endl;
#endif

      // HERE CODE FOR ADC
    }
  }
}

#endif // ESP_CONFIG_HARDWARE_ADC

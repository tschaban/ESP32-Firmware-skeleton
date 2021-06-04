#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER

#include <ESP-Batterymeter.h>

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
ESPBatterymeter Batterymeter;
double lastBatteryVoltage = 0;
uint16_t batterVoltage = 0;
float lastBatteryPercent = 0;
#else  /* Generic verson */
ESPBatterymeter Batterymeter[ESP_CONFIG_HARDWARE_BATTERYMETER_MAX_NUMBER];
#endif /* End Generic verson */

void initializeBatterymeter(void);
void eventsListnerBatterymeter(void);

/***** Body ******/

void initializeBatterymeter(void) {

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
  if (Device.configuration.noOfBatterymeters > 0) {
    Batterymeter.begin(&Data, &WirePort0, &WirePort1, 0);
    Screen.setBatteryVoltage(0);
    Screen.setBatteryPercent(0);
  }

#else /* Generic verson */
  for (uint8_t i = 0; i < Device.configuration.noOfBatterymeters; i++) {
#ifdef ESP_CONFIG_HARDWARE_ADS1115
    Batterymeter[i].begin(&Data, &WirePort0, &WirePort1, i);
#else
    Batterymeter[i].begin(&Data, i);
#endif
  }
#endif /* End Generic verson */
};

void eventsListnerBatterymeter(void) {

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
  if (Batterymeter.listener()) {

    batterVoltage = (uint16_t)trunc(round(Batterymeter.data.voltage * 10));

    if (lastBatteryVoltage != batterVoltage) {
      lastBatteryVoltage = batterVoltage;
      Screen.setBatteryVoltage(lastBatteryVoltage);
    }

    if (lastBatteryPercent != Batterymeter.data.percentage) {
      lastBatteryPercent = round(Batterymeter.data.percentage);
    }
  }
#else /* Generic verson */
  for (uint8_t i = 0; i < Device.configuration.noOfBatterymeters; i++) {
    if (Batterymeter[i].listener()) {
      char _numberToText[10];
      sprintf(_numberToText, "B:%-.2fv", Batterymeter.data.voltage);
      p0_t0.setText(_numberToText);
      sprintf(_numberToText, "B:%-.2f%%", Batterymeter.data.percentage);
      p0_t1.setText(_numberToText);
      // HERE CODE FOR Batterymeter
    }
  }

#endif /* End Generic verson */

  /* Listens for switch events */
}

#endif // ESP_CONFIG_FUNCTIONALITY_BATTERYMETER

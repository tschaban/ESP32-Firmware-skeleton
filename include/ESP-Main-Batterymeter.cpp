#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER

#include <ESP-Batterymeter.h>
ESPBatterymeter Batterymeter[ESP_CONFIG_HARDWARE_BATTERYMETER_MAX_NUMBER];
void initializeBatterymeter(void);
void eventsListnerBatterymeter(void);

/***** Body ******/

void initializeBatterymeter(void) {
  for (uint8_t i = 0; i < Device.configuration.noOfBatterymeters; i++) {
#ifdef ESP_CONFIG_HARDWARE_ADS1115
    Batterymeter[i].begin(&Data, &WirePort0, &WirePort1, i);
#else
    Batterymeter[i].begin(&Data, i);
#endif
  }
};

void eventsListnerBatterymeter(void) {

  /* Listens for switch events */
  for (uint8_t i = 0; i < Device.configuration.noOfBatterymeters; i++) {
    if (Batterymeter[i].listener()) {
      char _number[20];
      if (i == 0) {
        sprintf(_number, "B:%-.2fv", Batterymeter[i].data.voltage);
        p0_t0.setText(_number);
        sprintf(_number, "B:%-.2f%%", Batterymeter[i].data.percentage);
        p0_t1.setText(_number);
      }

      // HERE CODE FOR Batterymeter
    }
  }
}

#endif // ESP_CONFIG_FUNCTIONALITY_BATTERYMETER

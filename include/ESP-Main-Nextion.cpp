#ifdef ESP_CONFIG_HARDWARE_NEXTION

#include <Nextion.h>

NexText p0_t0 = NexText(0, 1, "t0");

void initializeNextion(void);

/***** Body ******/

void initializeNextion(void) {
  nexInit();
#ifdef DEBUG
  Serial << endl << F("INFO: Nextion LCD initialized");
#endif // DEBUG
};
#endif // ESP_CONFIG_HARDWARE_NEXTION

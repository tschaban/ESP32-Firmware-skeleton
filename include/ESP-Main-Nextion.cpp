#ifdef ESP_CONFIG_HARDWARE_NEXTION

#include <Nextion.h>

NexText p0_t0 = NexText(0, 1, "t0");
NexText p0_t1 = NexText(0, 2, "t1");
NexText p0_t2 = NexText(0, 3, "t2");
NexText p0_t3 = NexText(0, 4, "t3");
NexText p0_t4 = NexText(0, 5, "t4");
NexText p0_t5 = NexText(0, 6, "t5");
NexText p0_t6 = NexText(0, 7, "t5");

void initializeNextion(void);

/***** Body ******/

void initializeNextion(void) {
#ifdef DEBUG
  Serial << endl << F("INFO: Nextion LCD ");
#endif // DEBUG
  nexInit(ESP_CONFIG_HARDWARE_NEXTION_HARDWARE_SERIAL_SPEED,
          ESP_CONFIG_HARDWARE_NEXTION_DEBUGGER_SERIAL_SPEED);
#ifdef DEBUG
  Serial << F("initialized");
#endif // DEBUG
};
#endif // ESP_CONFIG_HARDWARE_NEXTION

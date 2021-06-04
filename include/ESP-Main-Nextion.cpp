#ifdef ESP_CONFIG_HARDWARE_NEXTION

#include <Nextion.h>

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
#include <NXB-LCD.h>
SCREEN Screen;

#else  /* Generic verson */
NexText p0_t0 = NexText(0, 1, "t0"); // Bateria V
NexText p0_t1 = NexText(0, 2, "t1"); // Bateria %
NexText p0_t2 = NexText(0, 3, "t2"); // NTC
NexText p0_t3 = NexText(0, 4, "t3"); // DS18B20[0]
NexText p0_t4 = NexText(0, 5, "t4");
NexText p0_t5 = NexText(0, 6, "t5");
NexText p0_t6 = NexText(0, 7, "t6");
#endif /* End Generic verson */

void initializeNextion(void);
void eventsListnerNextion(void);

/***** Body ******/

void initializeNextion(void) {
#ifdef DEBUG
  Serial << endl << F("INFO: Nextion LCD ");
#endif // DEBUG
  nexInit(ESP_CONFIG_HARDWARE_NEXTION_HARDWARE_SERIAL_SPEED,
          ESP_CONFIG_HARDWARE_NEXTION_DEBUGGER_SERIAL_SPEED);

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
  Screen.set(SCREEN_SPLASH);
  Screen.setTextAtSplashScreen("Booting...");
#endif

  Screen.begin(&Data);
  Screen.setTextAtSplashScreen("Running...");

#ifdef DEBUG
  Serial << F("initialized");
#endif // DEBUG

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
  Screen.showSyncStatus();
#else  /* Generic verson */
#endif /* End Generic verson */
};

void eventsListnerNextion(void) {

}

#endif // ESP_CONFIG_HARDWARE_NEXTION

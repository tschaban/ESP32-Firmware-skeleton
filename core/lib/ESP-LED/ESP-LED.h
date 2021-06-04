/* ESP Firmware for smart home devices, Website: https://ESP.smartnydom.pl/ */

#ifndef _ESP_LED_h
#define _ESP_LED_h

#include <Configuration.h>
#ifdef ESP_CONFIG_HARDWARE_LED

#include "arduino.h"
#include <ESP-Data-Access.h>
#include <LED-Structure.h>

class ESPLED {

private:
  LED LEDConfiguration;
  ESPDataAccess *Data;
  boolean _initialized = false;
  boolean blinking = false;
  unsigned long interval;
  unsigned long previousMillis = 0;

  /* Method turns on/off LED */
  void set(uint8_t state);

public:
  /* Constructor */
  ESPLED();

  /* Constructor: gpio is GPIO to where LED is connected to */
  boolean begin(ESPDataAccess *, uint8_t id);

  /* Turns on LED */
  void on();

  /* Turn off LED */
  void off();

  /* Method change the LED to opposite state */
  void toggle();

  /* Method gets LED state */
  boolean get();

  /* Blink LED. Duration how lon LED is ON can be set by input parameter (in
   * milli)*/
  void blink(unsigned int duration = 100);

  /* Turns on LED blinking with interval as input paramters. It's in
   * milliseconds */
  void blinkingOn(unsigned long blinking_interval);

  /* Turns off LED blinking */
  void blinkingOff();

  /* Returns true if LED is blinking, false if not */
  boolean isBlinking();

  /* Method must be added to main loop in order to enable continues LED blinking
   */
  void loop();
};

#endif // ESP_CONFIG_HARDWARE_LED

#endif // _ESP_LED_h

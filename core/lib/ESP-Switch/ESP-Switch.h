#ifndef _ESP_Switch_h
#define _ESP_Switch_h

#include <Configuration.h>
#ifdef ESP_CONFIG_HARDWARE_SWITCH

#include <arduino.h>

#include <ESP-Data-Access.h>

#ifdef ESP_CONFIG_HARDWARE_LED
#include <ESP-LED.h>
#endif

#ifdef DEBUG
#include <Streaming.h>
#endif

class ESPSwitch {

public:
  SWITCH configuration;

  /* Constructors */
  ESPSwitch();

/* Init switch */
#ifdef ESP_CONFIG_HARDWARE_LED
  void begin(uint8_t id, ESPDataAccess *, ESPLED *);
#else
  void begin(uint8_t id, ESPDataAccess *);
#endif // ESP_CONFIG_HARDWARE_LED

  /* Method: returns TRUE if state of the switch is pressed. It does not mean it
   * has to be pressed physically (applicable for BiStable switch types */
  boolean getState();
  boolean getPhisicalState();

  boolean getGPIOState();
   
  /* Method returns true if switch has been pressed. Sensitiveness it taken into
   * account. It does not mean switch is pressed physically. Once True capture
   * getState() method should be called to get the state of the Switch */
  boolean isPressed(boolean phisically = false);

  unsigned long pressEvent();

  /* Method has to be added to the loop in order to listen for switch changes */
  void listener();
  unsigned long whenButtonPressed(void);
  void resetButtonPressedTimer(unsigned long time = 0);

private:
  boolean _initialized = false;
  boolean state;
  boolean previousState; // Actually this stores current switch state

  unsigned long startTime = 0;
  unsigned long howLongPressed = 0;

  boolean pressed = false; // It's set to true once button pressed physically
  boolean _pressed = false;

  boolean phisicallyPressed = false;
  boolean phisicallyState = false;

  ESPDataAccess *Data;

#ifdef ESP_CONFIG_HARDWARE_LED
  ESPLED *Led;
  unsigned long ledTimer = 0;
  uint8_t ledTimerCounter = 0;
  unsigned long ledOnstart = 0;
  uint8_t ledOnCounter = 0;
  boolean ledOn = false;

#endif

  void initialize(uint8_t id, ESPDataAccess *);
};

#endif // ESP_CONFIG_HARDWARE_SWITCH

#endif // _AFE_Switch_h

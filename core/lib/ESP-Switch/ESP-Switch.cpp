#include "ESP-Switch.h"

#include <Configuration.h>
#ifdef ESP_CONFIG_HARDWARE_SWITCH

ESPSwitch::ESPSwitch(){};

#ifdef ESP_CONFIG_HARDWARE_LED
void ESPSwitch::begin(uint8_t id, ESPDataAccess *_Data, ESPLED *_Led) {
  Led = _Led;
  initialize(id, _Data);
}
#else
void ESPSwitch::begin(uint8_t id, ESPDataAccess *_Data) {
  initialize(id, _Data);
}
#endif // ESP_CONFIG_HARDWARE_LED

void ESPSwitch::initialize(uint8_t id, ESPDataAccess *_Data) {
  Data = _Data;
  Data->get(id, configuration);
  pinMode(configuration.gpio, configuration.pinMode);
  state = digitalRead(configuration.gpio);
  previousState = state;
  phisicallyState = state;
  _initialized = true;
}

boolean ESPSwitch::getState() { return state; }

boolean ESPSwitch::getPhisicalState() { return phisicallyState; }

boolean ESPSwitch::isPressed(boolean phisically) {
  if (phisically) {
    if (phisicallyPressed) {
      phisicallyPressed = false;
      return true;
    } else {
      return false;
    }
  } else {
    if (pressed) {
      pressed = false;
      return true;
    } else {
      return false;
    }
  }
}

unsigned long ESPSwitch::pressEvent() {
  unsigned long _ret = howLongPressed;
  howLongPressed = 0;
  return _ret <= configuration.bouncing ? 0 : _ret;
}

void ESPSwitch::listener() {
  if (_initialized) {
    boolean currentState = digitalRead(configuration.gpio);
    unsigned long time = millis();

    if (currentState != previousState) { // buttons has been pressed

      if (startTime == 0) { // starting timer. used for switch bouncing
        startTime = time;
      }

      if (time - startTime >=
          configuration.bouncing) { // switch prssed, bouncing
                                    // taken into account, processing
                                    // event
        if (configuration.type == ESP_CONFIG_HARDWARE_SWITCH_TYPE_MONO_STABLE) {

          if (!_pressed) { // This is set only once when switch is pressed
            state = !state;
            _pressed = true;
            pressed = true;
            phisicallyPressed = true;
            phisicallyState = currentState;
          }
#ifdef ESP_CONFIG_HARDWARE_LED
          /* LED blinking while switch pressed and hold with intervals:
           * ESP_CONFIG_HARDWARE_SWITCH_PRESS_FUNCTIONS_INTERVAL */
            if (ledTimer == 0) {
              ledTimer = millis();
            }

            if (millis() - ledTimer >=
                ledTimerCounter *
                    ESP_CONFIG_HARDWARE_SWITCH_PRESS_FUNCTIONS_INTERVAL) {
              ledTimerCounter++;
              ledOnstart = millis();
              ledOnCounter = 0;
#ifdef DEBUG
              Serial << endl
                     << "INFO: Switch pressed for: "
                     << (millis() - ledTimer) / 1000 << "sec";
#endif
            }

            if (ledOnstart > 0 && millis() - ledOnstart >= ledOnCounter * 200 &&
                !ledOn) {
              ledOn = true;
              Led->on();
            }

            if (ledOn && millis() - ledOnstart >= 100 + (ledOnCounter * 200)) {
              ledOn = false;
              ledOnCounter++;
              if (ledOnCounter >= ledTimerCounter) {
                ledOnstart = 0;
                ledOnCounter = 0;
              }
              Led->off();
            }
#endif           // ESP_CONFIG_HARDWARE_LED
        } else { // This is BI-stable code
          state = !state;
          previousState = currentState;
          pressed = true;
          phisicallyPressed = true;
          phisicallyState = currentState;
        }
      }
    } else if (currentState == previousState && startTime > 0 &&
               configuration.type ==
                   ESP_CONFIG_HARDWARE_SWITCH_TYPE_MONO_STABLE) {

        howLongPressed = millis() - startTime;
#ifdef ESP_CONFIG_HARDWARE_LED
        ledTimerCounter = 0;
        ledTimer = 0;
        ledOnstart = 0;
        ledOnCounter = 0;
#endif // ESP_CONFIG_HARDWARE_LED
      startTime = 0;
      _pressed = false;
      phisicallyPressed = true;
      phisicallyState = currentState;
    }
  }
}

#endif // ESP_CONFIG_HARDWARE_SWITCH

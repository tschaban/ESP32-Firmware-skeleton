#include "ESP-LED.h"

#ifdef ESP_CONFIG_HARDWARE_LED

ESPLED::ESPLED() {}

boolean ESPLED::begin(ESPDataAccess *_Data, uint8_t id) {
  if (id != ESP_HARDWARE_ITEM_NOT_EXIST) {
    Data = _Data;
    Data->get(id, LEDConfiguration);

#ifdef DEBUG
    Serial << endl
           << "INFO: Initializing LED, GPIO: " << LEDConfiguration.gpio
           << ", Reverse? " << (LEDConfiguration.reverseState ? "YES" : "NO");
#endif

    pinMode(LEDConfiguration.gpio, OUTPUT);
    LEDConfiguration.reverseState ? digitalWrite(LEDConfiguration.gpio, LOW)
                                  : digitalWrite(LEDConfiguration.gpio, HIGH);
    _initialized = true;
  }
  return _initialized;
}

void ESPLED::on() {
  if (LEDConfiguration.reverseState) {
    set(HIGH);
  } else {
    set(LOW);
  }
}

void ESPLED::off() {
  if (LEDConfiguration.reverseState) {
    set(LOW);
  } else {
    set(HIGH);
  }
}

void ESPLED::blink(unsigned int duration) {
  on();
  delay(duration);
  off();
}

void ESPLED::blinkingOn(unsigned long blinking_interval) {
  interval = blinking_interval;
  blinking = true;
}

void ESPLED::blinkingOff() { blinking = false; }

boolean ESPLED::isBlinking() { return blinking; }

void ESPLED::loop() {

  if (_initialized && blinking) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      toggle();
    }
  }
}

void ESPLED::set(uint8_t state) {
  if (_initialized) {
    if (digitalRead(LEDConfiguration.gpio) != state) {
      digitalWrite(LEDConfiguration.gpio, state);
    }
  }
}

void ESPLED::toggle() {
  if (_initialized) {
    digitalRead(LEDConfiguration.gpio) == HIGH
        ? digitalWrite(LEDConfiguration.gpio, LOW)
        : digitalWrite(LEDConfiguration.gpio, HIGH);
  }
}

#endif // ESP_CONFIG_HARDWARE_LED
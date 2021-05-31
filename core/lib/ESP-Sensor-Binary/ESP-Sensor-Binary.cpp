#include "ESP-Sensor-Binary.h"

#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY

// Interuption counter
volatile static unsigned long interuptionsCounter0 = 0;
volatile static unsigned long previousInteruption0 = 0;
volatile static unsigned long bouncing0 = 0;

void IRAM_ATTR handleImpuls0() {
  if (millis() - previousInteruption0 > bouncing0) {
    interuptionsCounter0++;
///* Crashes if many interuptions 
#ifdef DEBUG
    Serial << endl
           << F("INFO:  Binary sensor: New interuption: counter: ")
           << interuptionsCounter0;
#endif
//*/
  }
///*
#ifdef DEBUGA
  else {
    Serial << F(".");
  }
#endif
//*/
  previousInteruption0 = millis();
};


void IRAM_ATTR handleImpulsR() {
 Serial << endl << "RISING";
};


void IRAM_ATTR handleImpulsF() {
 Serial << endl << "FALLING ";
};

void IRAM_ATTR handleImpulsC() {
 Serial << endl << "CHANGE ";
};

void IRAM_ATTR handleImpulsL() {
 Serial << endl << "LOW ";
};


ESPSensorBinary::ESPSensorBinary(){};

void ESPSensorBinary::begin(ESPDataAccess *_Data, uint8_t id) {
  Data = _Data;
  Data->get(id, configuration);
  _id = id;

  if (configuration.gpio != ESP_HARDWARE_ITEM_NOT_EXIST) {

    pinMode(configuration.gpio, INPUT_PULLUP);
    switch (_id) {
    case 0: {
      attachInterrupt(digitalPinToInterrupt(configuration.gpio), handleImpulsC,CHANGE );
      attachInterrupt(digitalPinToInterrupt(configuration.gpio), handleImpulsR,RISING );
      attachInterrupt(digitalPinToInterrupt(configuration.gpio), handleImpulsL,LOW );
      attachInterrupt(digitalPinToInterrupt(configuration.gpio), handleImpuls0,FALLING );
      bouncing0 = configuration.bouncing;
      break;
    }
    case 1: {
    }
    case 2: {
    }
    case 3: {
    }
    }

    _initialized = true;
  }

#ifdef DEBUG
  if (_initialized) {
    Serial << endl << F("INFO: Binary sensor initialized and working");
  } else {
    Serial << endl << F("WARN: Binary sensor NOT initialized");
  }
#endif
}

void ESPSensorBinary::get(uint32_t &noOfImpulses, uint32_t &duration) {
  duration = millis() - counterStarted;
  if (duration < 0) { // used previous duration if timer rollouts
    duration = _previousDuration;
  }

  switch (_id) {
  case 0: {
    noOfImpulses = interuptionsCounter0;
    interuptionsCounter0 = 0;
    break;
  }
  case 1: {
  }
  case 2: {
  }
  case 3: {
  }
  }

  _previousDuration = duration;
  counterStarted = 0; // It's set to 0 to allow other code to execude, just
                      // after reading the data
#ifdef DEBUG
  Serial << endl
         << F("INFO: Binary sensor: Impulses: ") << noOfImpulses
         << F(", during: ") << (duration / 1000) << F("sec.");
#endif
}

boolean ESPSensorBinary::listener(void) {
  if (_initialized) {
    if (counterStarted == 0) {
      counterStarted = millis();
    }
    if (millis() - counterStarted >= configuration.interval) {
      _ret = true;
    } else {
      _ret = false;
    }
  } else { // Not initialized
    _ret = false;
  }
  return _ret;
}

#endif // ESP_CONFIG_HARDWARE_SENSOR_BINARY
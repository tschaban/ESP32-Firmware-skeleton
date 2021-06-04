#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY

#include <ESP-Sensor-Binary.h>

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
#include <NXB-Speedometer.h>
ESPSensorBinary BinarySensor;
SPEEDOMETER Speedometer;
ESPLED BikeLED;
int16_t durationBlinkBikeLED;
int16_t lastDurationBlinkBikeLED = 0;
uint32_t timerBikeLED = 0;
uint32_t SpeedometerImpulses, SpeedometerDuration;

uint8_t lastCurrentSpeed = 0;
uint8_t lastAvgSpeed = 0;
uint8_t lastMaxSpeed = 0;
uint8_t lastProgressBarSpeed = 0;

uint16_t lastTimeRide = 0;
uint16_t lastTotalDistance = 0;
uint16_t lastTripDistance = 0;
uint16_t distanceFormated = 0;

#else
ESPSensorBinary BinarySensor[ESP_CONFIG_HARDWARE_SENSOR_BINARY_MAX_NUMBER];
#endif

void initializeBinarySensor(void);
void eventsListnerBinarySensor(void);

/***** Body ******/

void initializeBinarySensor(void) {
#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
  if (Device.configuration.noOfBinarySensors > 0) {
    BinarySensor.begin(&Data, 0);
    Speedometer.begin(&Data, BinarySensor.configuration.interval);
    BikeLED.begin(&Data, 1);
    BikeLED.off();
  }
  Screen.setCurrentSpeed(lastCurrentSpeed);
  Screen.setAvgSpeed(lastAvgSpeed);
  Screen.setMaxSpeed(lastMaxSpeed);
  Screen.setPregressBarSpeed(lastProgressBarSpeed);
  Screen.setTotalDistance(lastTotalDistance);
  Screen.setTripDistance(lastTripDistance);
  Screen.setRideTime(lastTimeRide);
#else /* Generic verson */
  for (uint8_t i = 0; i < Device.configuration.noOfBinarySensors; i++) {
    BinarySensor[i].begin(&Data, i);
#ifdef DEBUG
    Serial << endl << "INFO: Binary Sensor(" << i + 1 << ") initialized";
#endif
  }
#endif /* End Generic verson */
};

void eventsListnerBinarySensor(void) {

#ifdef NXTBIKECOMPUTER /* NxtBike Computer */
  if (BinarySensor.listener()) {

    BinarySensor.get(SpeedometerImpulses, SpeedometerDuration);
    Speedometer.calculate(SpeedometerImpulses, SpeedometerDuration);
    BinarySensor.setInterval(Speedometer.refreshFrequency);

    if (lastCurrentSpeed != (uint8_t)round(Speedometer.data.speed.current)) {
      lastCurrentSpeed = (uint8_t)round(Speedometer.data.speed.current);
      Screen.setCurrentSpeed(lastCurrentSpeed);
    }

    if (lastAvgSpeed != (uint8_t)round(Speedometer.data.speed.avarage)) {
      lastAvgSpeed = (uint8_t)round(Speedometer.data.speed.avarage);
      Screen.setAvgSpeed(lastAvgSpeed);
    }

    if (lastMaxSpeed != (uint8_t)round(Speedometer.data.speed.max)) {
      lastMaxSpeed = (uint8_t)round(Speedometer.data.speed.max);
      Screen.setMaxSpeed(lastMaxSpeed);
    }

    if (lastProgressBarSpeed != Speedometer.data.speed.maxPercent) {
      lastProgressBarSpeed = (uint8_t)round(Speedometer.data.speed.maxPercent);
      Screen.setPregressBarSpeed(lastProgressBarSpeed);
    }

    if (lastTotalDistance != (uint16_t)round(Speedometer.data.distance.total)) {
      lastTotalDistance = (uint16_t)round(Speedometer.data.distance.total);
      Screen.setTotalDistance(lastTotalDistance);
    }

    distanceFormated = (uint16_t)round(Speedometer.data.distance.current * 100);
    if (lastTripDistance != distanceFormated) {
      lastTripDistance = distanceFormated;
      Screen.setTripDistance(lastTripDistance);
    }
  }

  Speedometer.timer(Speedometer.data.speed.current > 0 ? true : false);

  if (lastTimeRide != Speedometer.data.timer) {
    lastTimeRide = Speedometer.data.timer;
    Screen.setRideTime(lastTimeRide);
  }

  if (Speedometer.data.speed.current > 0) {
    durationBlinkBikeLED =
        SPEEDOMETER_LED_MAX_BLINKING_DURATION -
        (SPEEDOMETER_LED_INCREMENT_CHANGE * Speedometer.data.speed.current);

    if (durationBlinkBikeLED < SPEEDOMETER_LED_MIN_BLINKING_DURATION)
      durationBlinkBikeLED = SPEEDOMETER_LED_MIN_BLINKING_DURATION;
  } else if (Speedometer.data.speed.current == 0 &&
             durationBlinkBikeLED != SPEEDOMETER_LED_STOP_BLINKING_DURATION) {
    durationBlinkBikeLED = SPEEDOMETER_LED_STOP_BLINKING_DURATION;
  }

  if (lastDurationBlinkBikeLED != durationBlinkBikeLED) {
    lastDurationBlinkBikeLED = durationBlinkBikeLED;
    BikeLED.blinkingOn(durationBlinkBikeLED);
  }

  BikeLED.loop();

#else
  /* Listens for switch events */
  for (uint8_t i = 0; i < Device.configuration.noOfBinarySensors; i++) {
    if (BinarySensor[i].listener()) {
      // HERE CODE FOR BINARY SESNOR
      char _number[10];
      sprintf(_number, "%.2f", Speedometer.data.speed.current);
      p0_t2.setText(_number);

      sprintf(_number, "%.2f", Speedometer.data.distance.current);
      p0_t3.setText(_number);
    }
  }
#endif
}

#endif // ESP_CONFIG_HARDWARE_SENSOR_BINARY

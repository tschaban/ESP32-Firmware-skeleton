/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#include "NXB-Speedometer.h"

SPEEDOMETER::SPEEDOMETER() {}

void SPEEDOMETER::begin(ESPDataAccess *_Data, uint16_t refreshTime) {
  Data = _Data;
  Data->NXBGet(data);
  if (data.distance.total <= (double)SPEEDOMETER_DEFAULT_TOTAL_DISTANCE) {
    Data->NXBGet(data, true);
    Data->NXBSave(&data);
  }



  timerTime = millis();
  timer1s = millis();
  refreshFrequency = refreshTime;
  binarySensorRefresTime = refreshTime;
}

void SPEEDOMETER::calculate(uint8_t impulseCounter, uint32_t duration) {
  /*
  #ifdef DEBUG
    Serial << endl
           << F("INFO: Speedometer: calculating speedometer data: Number of "
                "impulses: ")
           << impulseCounter << F(", during: ") << duration << F("msec");
  #endif
  */
  if (impulseCounter > 1) {
    uint8_t _impulseCounter = impulseCounter;
    uint32_t _lastImpulseTime = duration;
    uint32_t _firstImpulseTime = 0;

    double distanceFromLastCheck =
        (double)((_impulseCounter - 1) * SPEEDOMETER_WHEEL_SIZE) / 100000;
    double measureTime =
        (double)(_lastImpulseTime - _firstImpulseTime) / 3600000;

    data.speed.current = distanceFromLastCheck / measureTime;

    refreshFrequency =
        SPEEDOMETER_NUMBER_OF_IMPULSES_EXPTECTED *
        ((_lastImpulseTime - _firstImpulseTime) / _impulseCounter);

    if (refreshFrequency > binarySensorRefresTime) {
      refreshFrequency = binarySensorRefresTime;
    }

    /* Calculating distance */


    data.distance.current +=
        (double)((double)(_impulseCounter * SPEEDOMETER_WHEEL_SIZE) / 100000);
    data.distance.total +=
        (double)((double)(_impulseCounter * SPEEDOMETER_WHEEL_SIZE) / 100000);

  } else {
    data.speed.current = 0;
    refreshFrequency = binarySensorRefresTime;
  }

  if (data.speed.current > data.speed.max) {
    data.speed.max = data.speed.current;
  }

  data.speed.maxPercent = (data.speed.current / SPEEDOMETER_MAX_SPEED) * 100;

#ifdef DEBUG
  Serial << endl
         << F("INFO: Speedometer") << endl
         << F(" - Current speed: ") << data.speed.current << F("km/h") << endl
         << F(" - Max speed: ") << data.speed.current << F("km/h") << endl
         << F(" - Avg speed: ") << data.speed.avarage << F("km/h") << endl
         << F(" - Current distance: ") << data.distance.current << F("km")
         << endl
         << F(" - Total distance: ") << data.distance.total << F("km") << endl
         << F(" - Time: ") << data.timer << F("min") << endl
         << F(" - Time in move: ") << data.timeInMove << F("sec") << endl;
#endif
}

void SPEEDOMETER::reset() {
  data.distance.current = 0;
  data.timer = 0;
  data.timeInMove = 0;
  data.speed.avarage = 0;
  data.speed.max = 0;
}

void SPEEDOMETER::timer(boolean ride) {
  if (millis() - timerTime >= 60000) {
    data.timer++;
    timerTime = millis();
    if (data.timer > 0) {
      data.speed.avarage = data.timeInMove > 0
                               ? (double)data.distance.current /
                                     (double)((double)data.timeInMove / 60 / 60)
                               : 0;
    }
  }

  if (ride) {
    timer1sDuration = millis() - timer1s;
    if (timer1sDuration >= 1000) {
      timer1s = millis();
      data.timeInMove += timer1sDuration / 1000;
    }
  } else {
    timer1s = millis();
  }
}

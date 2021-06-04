#ifndef _speedometer_h
#define _speedometer_h

#include <arduino.h>
#include <ESP-Data-Access.h>
#include <NXB-Configuration.h>

#ifdef DEBUG
#include <Streaming.h>
#endif

class SPEEDOMETER {

public:
  SpeedometerDataType data;
  uint16_t refreshFrequency = 0;
  
  /* Constructors */
  SPEEDOMETER();
  


  void begin(ESPDataAccess *_Data, uint16_t refreshTime);
  void calculate(uint8_t impulseCounter, uint32_t duration);
  void reset();
  void timer(boolean ride = false);

private:
  ESPDataAccess *Data;
  uint32_t firstImpulseTime = 0;
  uint32_t lastImpulseTime = 0;
  uint32_t timerTime = 0;
  uint32_t timer1s = 0;
  uint32_t timer1sDuration = 0;

  uint16_t binarySensorRefresTime = 0;


};

#endif

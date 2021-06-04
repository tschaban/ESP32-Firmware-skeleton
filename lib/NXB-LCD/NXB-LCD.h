/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#ifndef _nxb_screen_h
#define _nxb_screen_h

#include <ESP-Data-Access.h>
#include <NXB-Configuration.h>
#include <Nextion.h>
#include <arduino.h>


#ifdef DEBUG
#include <Streaming.h>
#endif

class SCREEN {
public:
  SCREEN();
  void begin(ESPDataAccess *);
  void set(uint8_t id);
  void change();
  void changeTheme();

  void setBatteryVoltage(uint16_t voltage);
  void setBatteryPercent(uint8_t percent);

  void setCurrentSpeed(uint8_t speed);
  void setMaxSpeed(uint8_t speed);
  void setAvgSpeed(uint8_t speed);
  void setPregressBarSpeed(uint8_t percent);
  void setRideTime(uint16_t time);
  void setTripDistance(uint16_t distance);
  void setTotalDistance(uint16_t distance);

  void setElectricityPower(uint32_t power);
  void setElectricityCurrent(uint32_t current);
  void setTemperatureOutside(uint16_t temperature);
  void setTemperatureInFrame(uint16_t temperature);

  void setTextAtSplashScreen(const char *);

  void setMenuPregressBarSpeed(uint8_t percent);

  void setPowerBar(uint8_t percent);

  void showSyncStatus(uint8_t status = SYNC_COMPLETED);
  uint8_t getSyncStatus();

  uint8_t getActiveScreenID();

private:
  ESPDataAccess *Data;
  LCDScreenConfigurationType configuration;
  LCDScreenCurrentConfigurationType currentScreenConfiguration;

  uint8_t currentSyncDataStatus = SYNC_WAITING_TO_SYNC;

  NexText S1Status = NexText(0, 1, "S1Status");

  NexVariable S2MaxSpeed = NexVariable(1, 1, "S2MaxSpeed");
  NexVariable S2AvgSpeed = NexVariable(1, 2, "S2AvgSpeed");
  NexVariable S2Minutes = NexVariable(1, 3, "S2Minutes");
  NexVariable S2DistTotal = NexVariable(1, 4, "S2DistTotal");
  NexVariable S2BatLevel = NexVariable(1, 5, "S2BatLevel");
  NexVariable S2Speed = NexVariable(1, 6, "S2Speed");
  NexVariable S2BatVoltage = NexVariable(1, 8, "S2BatVolt");
  NexVariable S2DistTrip = NexVariable(1, 9, "S2DistTrip");

  NexVariable S2Power = NexVariable(1, 11, "S2Power");
  NexVariable S2Current = NexVariable(1, 12, "S2Current");

  NexVariable S2TempAir = NexVariable(1, 12, "S2TempAir");
  NexVariable S2TempFrame = NexVariable(1, 11, "S2TempFrame");

  NexProgressBar S2SpeedProg = NexProgressBar(1, 7, "S2SpeedProg");
  NexProgressBar CProgBar = NexProgressBar(1, 1, "CProgBar");
  NexProgressBar S3PowerBar = NexProgressBar(1, 13, "S3PowerBar");
};
#endif

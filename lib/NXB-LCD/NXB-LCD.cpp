#include "NXB-LCD.h"

SCREEN::SCREEN() {}

void SCREEN::begin(ESPDataAccess *_Data) {
  Data = _Data;
  Data->NXBGetScreen(currentScreenConfiguration);
#ifdef DEBUG
  Serial << endl
         << F("Setting screen to: ") << currentScreenConfiguration.screenID
         << F("; Theme: ") << currentScreenConfiguration.themeID;
#endif
  set(currentScreenConfiguration.screenID);
}

void SCREEN::change() {
  switch (currentScreenConfiguration.screenID) {
  case SCREEN_SPLASH:
    set(SCREEN_SPEEDOMETER);
    break;
  case SCREEN_SPEEDOMETER:
    set(SCREEN_ELECTRICITY);
    break;
  case SCREEN_ELECTRICITY:
    set(SCREEN_TEMPERATURE);
    break;
  case SCREEN_TEMPERATURE:
    set(SCREEN_SPEED);
    break;
  case SCREEN_SPEED:
    set(SCREEN_SPEEDOMETER);
    break;
  }
}

void SCREEN::set(uint8_t id) {
#ifdef DEBUG
  Serial << endl
         << F("Changing screen to: ") << id << F("; Theme: ")
         << currentScreenConfiguration.themeID;
#endif
  switch (id) {
  case SCREEN_SPLASH:
    sendCommand("page S0");
    currentScreenConfiguration.screenID = SCREEN_SPLASH;
    break;
  case SCREEN_SPEEDOMETER:
    if (currentScreenConfiguration.themeID == THEME_NORMAL) {
      sendCommand("page S1");
    } else if (currentScreenConfiguration.themeID == THEME_LIGHT) {
      sendCommand("page S1L");
    } else {
      sendCommand("page S1D");
    }
    currentScreenConfiguration.screenID = SCREEN_SPEEDOMETER;
    break;
  case SCREEN_SPEED:
    if (currentScreenConfiguration.themeID == THEME_NORMAL) {
      sendCommand("page S2");
    } else if (currentScreenConfiguration.themeID == THEME_LIGHT) {
      sendCommand("page S2L");
    } else {
      sendCommand("page S2D");
    }
    currentScreenConfiguration.screenID = SCREEN_SPEED;
    break;
  case SCREEN_ELECTRICITY:
    if (currentScreenConfiguration.themeID == THEME_NORMAL) {
      sendCommand("page S3");
    } else if (currentScreenConfiguration.themeID == THEME_LIGHT) {
      sendCommand("page S3");
    } else {
      sendCommand("page S3");
    }
    currentScreenConfiguration.screenID = SCREEN_ELECTRICITY;
    break;
  case SCREEN_TEMPERATURE:
    if (currentScreenConfiguration.themeID == THEME_NORMAL) {
      sendCommand("page S4");
    } else if (currentScreenConfiguration.themeID == THEME_LIGHT) {
      sendCommand("page S4");
    } else {
      sendCommand("page S4");
    }
    currentScreenConfiguration.screenID = SCREEN_TEMPERATURE;
    break;
  case SCREEN_BUTTON_ACCESS_POINT:
    sendCommand("page CAP");
    currentScreenConfiguration.screenID = SCREEN_BUTTON_ACCESS_POINT;
    break;
  case SCREEN_BUTTON_CANCEL:
    sendCommand("page CCA");
    currentScreenConfiguration.screenID = SCREEN_BUTTON_CANCEL;
    break;
  case SCREEN_BUTTON_CHANGE_THEME:
    sendCommand("page CCT");
    currentScreenConfiguration.screenID = SCREEN_BUTTON_CHANGE_THEME;
    break;
  case SCREEN_BUTTON_CONNECT_TO_WIFI:
    sendCommand("page CCW");
    currentScreenConfiguration.screenID = SCREEN_BUTTON_CONNECT_TO_WIFI;
    break;
  case SCREEN_BUTTON_RESET_METER:
    sendCommand("page CRM");
    currentScreenConfiguration.screenID = SCREEN_BUTTON_RESET_METER;
    break;
  }
  if (currentScreenConfiguration.screenID < SCREEN_SPLASH) {
    Data->NXBSaveSceen(&currentScreenConfiguration);
  }
}

void SCREEN::changeTheme() {
  currentScreenConfiguration.themeID++;
  if (currentScreenConfiguration.themeID > 3) {
    currentScreenConfiguration.themeID = 1;
  }
  set(currentScreenConfiguration.screenID);
}

void SCREEN::showSyncStatus(uint8_t status) {
  if (status == currentSyncDataStatus) {
    return;
  } else {

    switch (status) {
    case SYNC_COMPLETED:
      sendCommand("vis S1SyncG,1");
      break;
    case SYNC_NEW_DATA:
      sendCommand("vis S1SyncA,1");
      break;
    case SYNC_WAITING_TO_SYNC:
      sendCommand("vis S1SyncR,1");
      break;
    }

    if (status != SYNC_COMPLETED) {
      sendCommand("vis S1SyncG,0");
    }
    if (status != SYNC_NEW_DATA) {
      sendCommand("vis S1SyncA,0");
    }
    if (status != SYNC_WAITING_TO_SYNC) {
      sendCommand("vis S1SyncR,0");
    }

    currentSyncDataStatus = status;
  }
}

uint8_t SCREEN::getSyncStatus() { return currentSyncDataStatus; }

void SCREEN::setBatteryVoltage(uint16_t voltage) {
  S2BatVoltage.setValue(voltage);
}

void SCREEN::setBatteryPercent(uint8_t percent) {
  S2BatLevel.setValue(percent);
}

void SCREEN::setCurrentSpeed(uint8_t speed) { S2Speed.setValue(speed); }

void SCREEN::setMaxSpeed(uint8_t speed) { S2MaxSpeed.setValue(speed); }

void SCREEN::setAvgSpeed(uint8_t speed) { S2AvgSpeed.setValue(speed); }

void SCREEN::setPregressBarSpeed(uint8_t percent) {
  S2SpeedProg.setValue(percent);
}

void SCREEN::setRideTime(uint16_t time) { S2Minutes.setValue(time); }

void SCREEN::setTripDistance(uint16_t distance) {
  S2DistTrip.setValue(distance);
}

void SCREEN::setTotalDistance(uint16_t distance) {
  S2DistTotal.setValue(distance);
}

void SCREEN::setElectricityPower(uint32_t power) { S2Power.setValue(power); }

void SCREEN::setElectricityCurrent(uint32_t current) {
  S2Current.setValue(current);
}

void SCREEN::setTemperatureOutside(uint16_t temperature) {
  S2TempAir.setValue(temperature);
}

void SCREEN::setTemperatureInFrame(uint16_t temperature) {
  S2TempFrame.setValue(temperature);
}

void SCREEN::setMenuPregressBarSpeed(uint8_t percent) {
  CProgBar.setValue(percent);
}

void SCREEN::setTextAtSplashScreen(const char *status) {
  S1Status.setText(status);
}

void SCREEN::setPowerBar(uint8_t percent) { S3PowerBar.setValue(percent); }

uint8_t SCREEN::getActiveScreenID() {
  return currentScreenConfiguration.screenID;
}

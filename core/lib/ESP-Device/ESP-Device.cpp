/* AFE Firmware for smart home devices, Website: https://afe.smartnydom.pl/ */

#include "ESP-Device.h"

ESPDevice::ESPDevice() {}

void ESPDevice::begin(ESPDataAccess *_Data) {
  Data = _Data;
  deviceMode = Data->getDeviceMode();
  Data->get(configuration);
}

void ESPDevice::reboot(uint8_t mode) {
  saveMode(mode);
  delay(1000);
#ifdef DEBUG
  Serial << endl << "WARN: Restarting ... " << endl << endl;
#endif    
  ESP.restart();
}

uint8_t ESPDevice::getMode() { return deviceMode; }

void ESPDevice::saveMode(uint8_t mode) { Data->saveDeviceMode(mode); }
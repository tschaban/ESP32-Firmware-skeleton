#ifndef _ESP_main_h
#define _ESP_main_h

#include "arduino.h"

#ifdef DEBUG
#include <Streaming.h>
#endif

#include <Configuration.h>
#include <ESP-Data-Access.h>
#include <ESP-Device.h>
#include <ESP-WiFi.h>

#if FIRMWARE_LANGUAGE == 0
#include <pl_PL.h>
#else
#include <en_EN.h>
#endif

ESPDataAccess Data;
ESPDevice Device;
ESPWiFi Network;

#ifdef ESP_CONFIG_HARDWARE_LED
#include "led.cpp"
#endif

#ifdef ESP_CONFIG_HARDWARE_SWITCH
#include "switch.cpp"
#endif

#ifdef ESP_CONFIG_HARDWARE_I2C
#include "i2c.cpp"
#endif

#ifdef ESP_CONFIG_HARDWARE_ADC
#include "adc.cpp"
#endif

#include "httpServer.cpp"



#endif // _ESP_main_h
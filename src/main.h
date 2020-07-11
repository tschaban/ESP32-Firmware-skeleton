#ifndef _ESP_main_h
#define _ESP_main_h

#include <arduino.h>

#ifdef DEBUG
#include <Streaming.h>
#endif

#include <Configuration.h>
#include <ESP-Data-Access.h>
#include <ESP-Device.h>
#include <ESP-WiFi.h>

#if FIRMWARE_LANGUAGE == 0
#include <ESP-pl_PL.h>
#else
#include <ESP-en_EN.h>
#endif

ESPDataAccess Data;
ESPDevice Device;
ESPWiFi Network;

#ifdef ESP_CONFIG_HARDWARE_NEXTION
#include <ESP-Main-Nextion.cpp>
#endif

#ifdef ESP_CONFIG_HARDWARE_LED
#include <ESP-Main-LED.cpp>
#endif

#ifdef ESP_CONFIG_HARDWARE_SWITCH
#include <ESP-Main-Switch.cpp>
#endif

#ifdef ESP_CONFIG_HARDWARE_I2C
#include <ESP-Main-I2C.cpp>
#endif

#ifdef ESP_CONFIG_HARDWARE_ADC
#include <ESP-Main-ADC.cpp>
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
#include <ESP-Main-BinarySensor.cpp>
#endif

#include <ESP-Main-HTTPServer.cpp>

#endif // _ESP_main_h
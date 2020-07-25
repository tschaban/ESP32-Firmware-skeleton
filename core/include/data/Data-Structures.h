#ifndef _Data_Structures_h
#define _Data_Structures_h

#include "arduino.h"

#include <Configuration.h>

#include <DEVICE-Structure.h>
#include <FIRMWARE-Structure.h>
#include <HTTP-COMMAND-Structure.h>
#include <NETWORK-Structure.h>

#ifdef ESP_CONFIG_HARDWARE_I2C
#include <I2C-Structure.h>
#endif

#ifdef ESP_CONFIG_HARDWARE_UART
#include <UART-Structure.h>
#endif

#ifdef ESP_CONFIG_HARDWARE_LED
#include <LED-Structure.h>
#endif

#ifdef ESP_CONFIG_HARDWARE_SWITCH
#include <SWITCH-Structure.h>
#endif

#ifdef ESP_CONFIG_HARDWARE_ADC
#include <ADC-Structure.h>
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_BINARY
#include <BINARY-Sensor-Structure.h>
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_DS18B20
#include <DS18B20-Sensor-Structure.h>
#endif

#ifdef ESP_CONFIG_HARDWARE_SENSOR_NTC
#include <NTC-Sensor-Structure.h>
#endif

#endif

/* AFE Firmware for smart home devices, Website: https://afe.smartnydom.pl/ */

#ifndef _ESP_UART_Structure_h
#define _ESP_UART_Structure_h

#include "arduino.h"

#include <Configuration.h>
#ifdef ESP_CONFIG_HARDWARE_UART

struct UARTBUS {
  uint8_t RXD;
  uint8_t TXD;
};

#endif // ESP_CONFIG_HARDWARE_UART
#endif // _ESP_UART_Structure_h

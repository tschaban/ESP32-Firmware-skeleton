#ifndef _nxb_configuration_h
#define _nxb_configuration_h

#include <arduino.h>

#define WATTOMETER_SHUNT_MAX_CURRENT 100
#define WATTOMETER_SHUNT_MAX_VOLTAGE_AT_MAX_CURRENT 0.075
#define WATTOMETER_MAX_POWER 5040


#define SPEEDOMETER_DATA_ARCHIVE_TIME 10000
#define SPEEDOMETER_DATA_ARCHIVE_TIME_BACKUP 20000
#define SPEEDOMETER_DATA_ARCHIVE_SAFE_SPEED 15

#define SPEEDOMETER_WHEEL_SIZE 217

#define SPEEDOMETER_LED_STOP_BLINKING_DURATION 3000
#define SPEEDOMETER_LED_MAX_BLINKING_DURATION 1000
#define SPEEDOMETER_LED_MIN_BLINKING_DURATION 10
#define SPEEDOMETER_LED_INCREMENT_CHANGE 22

#define SPEEDOMETER_DEFAULT_TOTAL_DISTANCE 16190
#define SPEEDOMETER_MAX_SPEED 55

#define SPEEDOMETER_BATTERY_LEVEL_REFRESH_TIME 5 // in sec
#define SPEEDOMETER_TEMPERATURE_REFRESH_TIME 10  // in sec
#define SPEEDOMETER_NUMBER_OF_IMPULSES_EXPTECTED 5

#define SPEEDOMETER_BACKUP_RESTORE_TIME 600 // in sec

#define SPEEDOMETER_DATA_SAVE_FREQUENCY 10 // in sec
#define SPEEDOMETER_DATA_SAVE_SPEED 40     // in sec

#define SCREEN_SPEEDOMETER 0
#define SCREEN_SPEED 1
#define SCREEN_ELECTRICITY 2
#define SCREEN_TEMPERATURE 3

#define SCREEN_SPLASH 10
#define SCREEN_BUTTON_CHANGE_THEME 11
#define SCREEN_BUTTON_RESET_METER 12
#define SCREEN_BUTTON_CONNECT_TO_WIFI 13
#define SCREEN_BUTTON_ACCESS_POINT 14
#define SCREEN_BUTTON_CANCEL 15


#define SCREEN_BUTTON_MENU_SHOW_TIME 2000
#define SCREEN_BUTTON_MENU_ITEM_DURATION 2000
#define SCREEN_BUTTON_MENU_PROGRESS_BUR_INITIAL 7


#define SCREEN_BUTTON_BOUNCING 50

#define SYNC_COMPLETED 0
#define SYNC_NEW_DATA 1
#define SYNC_WAITING_TO_SYNC 2

#define THEME_NORMAL 1
#define THEME_LIGHT 2
#define THEME_DARK 3


#define FILE_SPEEDOMETER "/nxb-speedometter.json"
#define FILE_CURRENTSCREEN "/nxb-current-screen.json"
#define FILE_SPEEDOMETER_BACKUP "/nxb-speedometter.archive.json"


#define FILE_CURRENTSCREEN_BUFFER 100
#define FILE_SPEEDOMETER_BUFFER 200

#define FILE_NOT_OPENED 0
#define FILE_OPEN_FOR_READ 1
#define FILE_OPEN_FOR_WRITE 2

/* Data Types */

struct LCDScreenConfigurationType {
  uint8_t buttonGPIO;
  uint8_t bouncing;
};

struct LCDScreenCurrentConfigurationType {
  uint8_t screenID = SCREEN_SPEEDOMETER;
  uint8_t themeID = THEME_NORMAL;
};


struct SpeedometerSpeedType {
  double current;
  double avarage;
  double max;
  uint8_t maxPercent;
};

struct SpeedometerDistanceType {
  double current;
  double total;
};

struct SpeedometerDataType {
  SpeedometerSpeedType speed;
  SpeedometerDistanceType distance;
  uint16_t timer;
  uint16_t timeInMove;
};

struct ElectricityeDataType {
  int8_t batterPercent;
  double batterVoltage;
  double current;
  double power;
};
#endif

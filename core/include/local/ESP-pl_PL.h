/* AFE Firmware for smart home devices, Website: https://afe.smartnydom.pl/ */

#ifndef _LANG_PL_h
#define _LANG_PL_h

#define L_LANGUAGE "pl-PL"
#define L_LANGUAGE_SHORT "pl"

/* Firmware names */
#define L_FIRMWARE_NAME "Firmware"


/* HTTP API */
#define L_DEVICE_NOT_EXIST "\"Urządzenie o takiej nazwie nie istnieje\""
#define L_COMMAND_NOT_IMPLEMENTED "\"Komeda nie jest zaimplementowana\""

/* Upgrades */
#define L_UPGRADED_TO_NEW_VERSION                                              \
  "Została zainstalowana nowa wersja AFE Firmware"
#define L_UPGRADED_TO_NEW_VERSION_TYPE                                         \
  "Został zainstalowany nowy typ AFE Firmware. Wymagana jest ponowna "        \
  "konfiguracja urządzenia."
#define L_PASWORD_PROTECTED "\"Operacja niemożliwa. Konfiguracja zabezpieczona hasłem\""

#define L_DONATE "&#128077; Wesprzyj jeśli soft Ci się przydał"

/* Menu */
#define L_DEVICE "Urządzenie"
#define L_NETWORK "Sieć WiFi"
//#define L_MQTT_BROKER "MQTT Broker"
//#define L_DOMOTICZ_SERVER "Serwer Domoticz"
#define L_LEDS "LEDy"
#define L_RELAYS_CONFIGURATION "Konfiguracja przekaźników"
#define L_RELAY "Przekaźnik"
#define L_BUTTONS_SWITCHES "Przyciski"
#define L_SWITCH "Przycisk"
#define L_ANALOG_INPUT "Wejście analogowe"
#define L_ANALOG_INPUTS "Wejścia analogowe"
#define L_INPUT "Wejście"
#define L_BUSES "Magistrale"
#define L_FIRMWARE_UPGRADE "Aktualizacja oprogramowania"
#define L_RESET_DEVICE "Ustawienia początkowe"
#define L_FINISH_CONFIGURATION "Zakoncz konfigurację"
//#define L_INFORMATION "INFORMACJE"
#define L_DOCUMENTATION "Dokumentacja"
#define L_SETTINGS "Ustawienia"
#define L_SETTINGS_HOT_SPOT "Ustawienia (Tryb HotSpot)"
//#define L_PRO_VERSION "Wersja PRO"
#define L_CONNECTED "Podłączony"
#define L_DISCONNECTED "Odłączony"

/* Forms commons */
#define L_NUMBER_OF_CHARS "znaków"
#define L_ENABLED "włączone"
#define L_USERNAME "Nazwa użytkownika"
#define L_PASSWORD "Hasło"
#define L_SECONDS "sekundy"
#define L_MILISECONDS "milisekundy"
#define L_IP_ADDRESS "Adres IP"
#define L_NONE "Brak"
#define L_NAME "Nazwa"
#define L_SAVE "Zapisz"
#define L_HELP "Pomoc"
#define L_VERSION "Wersja"
#define L_YES "Tak"
#define L_NO "Nie"
#define L_SENSOR "Czujnik"
#define L_DISTANCE_UNIT "Jednostka odległości"
#define L_CM "Centrymetry"
#define L_M "Metry"
#define L_KM "Kilometry"
#define L_MILES "Mile"

/* Form: index */
#define L_WRONG_PASSWORD "Hasło nie jest poprawne"
#define L_NORMAL_MODE "Tryb normalny"
#define L_HOTSPOT_MODE "Tryb HotSpot"
#define L_LAUNCH_CONFIGURATION_PANEL "Uruchom: Panel Konfiguracyjny"
#define L_OPENING_CONFIG_PANEL "Otwieram panel konfiguracyjny AFE Firmware"

/* Form: device coniguration */
#define L_DEVICE_NAME "Nazwa urządzenia"
#define L_DEVICE_SECTION_INFO                                                  \
  "Nazwa jest wykorzystywana jako nazwa urządzenia w Twojej lokalnej sieci "  \
  "WiFi oraz jako nazwa hotspot'a urządzenia"
#define L_HARDWARE_CONFIGURATION "Konfiguracja urządzenia"
#define L_HARDWARE_CONFIGURATION_INFO                                          \
  "Wybierz podłączone elementy do urządzenia"
#define L_NUMBER_OF_LEDS "Ilość Led'ów"
#define L_NUMBER_OF_RELAYS "Ilość przekaźników"
#define L_NUMBER_OF_SWITCHES "Ilość przycisków"
#define L_NUMBER_OF_ADCS "Ilość wejść ADC"
#define L_NUMBER_OF_I2C "Ilość magistral I2C"
#define L_NUMBER_OF_UART "Ilość magistral UART"
#define L_NUMBER_OF_BINARY_SENSORS "Ilość czujników binarnych"

#define L_DO_MEASURE_ADC "Pomiary z wejścia analogowego"
#define L_DEVICE_CONTROLLING "Sterowanie urządzeniem"
#define L_DEVICE_CONTROLLING_INFO                                              \
  "Włączanie / Wyłączanie mechanizmów sterowania urządzeniem"





#ifdef ESP_CONFIG_HARDWARE_GATE
#define L_CONTROLLED_GATES "Kontrolowane bramy/drzwi"
#endif

#ifdef ESP_CONFIG_API_DOMOTICZ_ENABLED
#define L_DOMOTICZ_VERSION_410 "4.10x i wcześniejsze"
#define L_DOMOTICZ_VERSION_2020 "2020.x i późniejsze"
#endif

#define L_AUTOLOGOUT_TITLE "Automatyczne zakończenie konfiguracji"
#define L_AUTOLOGOUT_DESCRIPTION "Konfiguracja urządzenia zostanie automatycznie wyłączona po 10min. braku akcji w panelu konfiguracyjnym"

/* Form: network configuration */
#define L_NETWORK_CONFIGURATION "Konfiguracja sieci WiFi"
#define L_NETWORK_CONFIGURATION_INFO                                               \
  "Urządzenie bez dostępu do sieci będzie działać tylko w trybie sterowania " \
  "ręcznego"
#define L_SSID "Nazwa sieci WiFi"
#define L_REFRESH "Odśwież"
#define L_DHCP_ENABLED "Konfiguracja przez DHCP"
#define L_GATEWAY "Bramka"
#define L_SUBNET "Maska sieci"
#define L_DEVICE_IP "IP urządzenia"
#define L_DEVICE_IP_INFO                                                       \
  "Możesz skonfigurować adres IP urządzenia ręcznie lub automatycznie za " \
  "pośrednictwem DHCP"
#define L_NUMBER_OF_CONNECTIONS "Ilość prób łączenia się"
#define L_TIME_BETWEEN_CONNECTIONS "Czas między próbami łączenia się"
#define L_SLEEP_TIME "Czas po jakim powtórzyć próby łączenia się"
#define L_ADVANCED "Zaawansowane"
#define L_DEVICE_CONNECTS "Urządzenie łaczy się z siecią"
#define L_CONNECT_TO "Połącz się z siecią WiFi"
#define L_CONNECT "Połącz"
#define L_SEARCH_FOR_IP_ADDRESS                                                \
  "Następnie w konfigurację routera WiFi, wyszukaj adres IP urządzenia o "  \
  "adresie MAC"
#define L_FINISH_NETWORK_CONFIGURATION                                         \
  "Dokończ konfigurację wpisując adres IP urządzenia w przeglądarce"

/* Form: MQTT Broker */
#define L_MQTT_TOPIC "Temat"
#define L_MQTT_TOPIC_LWT "Temat wiadomości LWT"
#define L_MQTT_IDX_LWT "IDX dla wiadomości LWT"
#define L_MQTT_CONFIGURATION_INFO                                              \
  "Wprowadź adres hosta np. localhost lub adres IP"
#define L_MQTT_TOPIC_EMPTY                                                     \
  "Jeśli nie zostanie wprowadzone, wiadomość nie będzie wysłana do MQTT " \
  "Brokera"
#define L_TIMEOUT "Limit czasu odpowiedzi"

/* Form:Domoticz server configuration */
#define L_PROTOCOL "Protokół"
#define L_DOMOTICZ_CONFIGURATION "Serwer Domoticz"
#define L_DOMOTICZ_CONFIGURATION_INFO                                          \
  "Wprowadź adres hosta np. localhost lub adres IP"
#define L_NO_IF_IDX_0                                                          \
  "Jeśli IDX jest 0 to wartość nie będzie wysyłana do Domoticz"


/* Form: Led configuration */
#ifdef ESP_CONFIG_HARDWARE_LED
/* Form: Led configuration */
#define L_CHANGE_LED_INDICATION "Zmień świecenie diody LED na odwrotne"

/* Form: System LED configuration */
#define L_SYSTEM_LED "LED systemowy"
#define L_SYSTEM_LED_INFO                                                      \
  "Wybierz diodę LED, która będzie sygnalizowała stan urządzenia oraz "   \
  "występujące zdarzenia"

#endif

/* Form: relay */
#define L_DEFAULT_VALUES "Wartości domyślne"
#define L_DEFAULT_POWER_RESTORED "Po przywróceniu zasilania"
#define L_NO_ACTION "Brak akcji"
#define L_ON "Włączony"
#define L_OFF "Wyłączony"
#define L_LAST_KNOWN_STATE "Ostatnia zapamiętana wartość"
#define L_OPPOSITE_TO_LAST_KNOWN_STATE "Przeciwna do ostatniej zapamiętanej"
#define L_DEFAULT_MQTT_CONNECTED "Po podłączeniu do brokera MQTT"
#define L_DEFAULT_GET_FROM_MQTT                                                \
  "Wartość z systemu sterowania przekaźnikiem (przez MQTT)"
#define L_AUTOMATIC_SWITCHING_OFF "Automatyczne wyłączenie przekaźnika"
#define L_IMPULSE_DURATION "Długośc impulsu"
#define L_SWITCH_OFF_AFTER "Wyłącz po"
#define L_NO_ACTION_IF_0 "Brak akcji jeśli jest 0"
#define L_THERMAL_PROTECTION "Zabezpieczenie termiczne"
#define L_SWITCH_OFF_ABOVE "Wyłącz powyżej"
#define L_RANGE "Zakres"
#define L_SELECT_LED_4_RELAY "Wybierz LED sygnalizujący stan przekaźnika"
#define L_RELAY_MQTT_TOPIC "Temat MQTT sterujący przekaźnikiem"

/* Form: Switch */
#define L_FUNCTIONALITY "Funkcja"
#define L_SYSTEM_BUTTON "Przycisk systemowy"
#ifdef ESP_CONFIG_FUNCTIONALITY_RELAY
#define L_CONTROL_RELAY "Tylko sterowanie przekaźnikiem"
#endif
#ifdef ESP_CONFIG_FUNCTIONALITY_GATE
#define L_CONTROL_GATE "Tylko sterowanie bramą"
#endif
#define L_RELAY_CONTROLLED_BY_SWITCH "Sterowanie"
#define L_TYPE "Typ"
#define L_MONOSTABLE "Monostabilny"
#define L_BISTABLE "Bistabilny"
#define L_SENSITIVENESS "Czułość"
#define L_SENSITIVENESS_HINT                                                         \
  "Czułość należy ustawić metodą prób, aż uzyska się pożądane działanie " \
  "przycisku podczas jego wciskania"
#define L_SWITCH_BUTTON "Przycisk / Włącznik"
#define L_SWITCH_MQTT_TOPIC "Temat MQTT do monitorowania stanu przycisku"

/* Form: Analog Input */
#define L_GPIO_ANALOG_INPUT "Wejście analogowe z GPIO"
#define L_ADS1115_ANALOG_INPUT "Wejście analogowe z ADS1115"
#define L_ADS1115_ADDRESS "Adres ADS1115"
#define L_REFRESH_SETTINGS_ADS1115 "Skanuj dostępne przetworniki ADS1115"
#define L_READS "Odczyty"
#define L_ADC_INPUT_PARAMETERS "Parametery wejścia ADC"
#define L_ADC_RESOLUTION "Rozdzielczość"
#define L_ADS1115_NO_OF_SAMPLES_PER_SECOND "Ilość próbek na sekundę"
#define L_ADS1115_GAIN "Wzmocnienie"
#define L_ADS1115_SET_BY_GAIN "V. Ustawiane automatycznie przez ADS1115"
#define L_CANT_CHANGE "brak możliwości zmiany"
#define L_MEASURMENTS_INTERVAL "Interwał odczytów"
#define L_MEASURED_VOLTAGE "Max napięcie na wejściu ADC"
#define L_MEASURED_DIVIDER_VOLTAGE "Max napięcie na wejściu dzielnika"
#define L_REFRESHED_AFTER_SAVE "Przeliczone po zapisaniu. Tylko do oczytu"
#define L_NUMBER_OF_SAMPLES "Ilość próbek do uśrednienia odczytu"
#define L_RAW_DATA "IDX Surowe Dane"
#define L_PERCENT "IDX Procent"
#define L_VOLTAGE "IDX Napięcie na wejściu"
#define L_VOLTAGE_CALCULATED "IDX Napięcie przeliczone"
#define L_RESISTOR "Rezystor"
#define L_VOLTAGE_DIVIDER "Dzielnik napięcia"
#define L_ADC_MQTT_TOPIC "Temat MQTT dla informacji z ADC"
#ifdef ESP_CONFIG_FUNCTIONALITY_BATTERYMETER
#define L_BATTERY_METER "Pomiar naładowania baterii"
#define L_BATTERY_MQTT_TOPIC "Temat MQTT Stanu baterii"
#define L_BATTERY_MIN_LEVEL "Minimalny poziom baterii"
#define L_BATTERY_MAX_LEVEL "Maksymalny poziom baterii"
#endif


#define L_BINARY_SENSOR "Czujnik binarny / impulsów"


/* Form: upgrade and post upgrade */
#define L_SELECT_FIRMWARE "Wybierz Firmware"
#define L_UPGRADE_INFO                                                             \
  "Po zakończeniu aktualizacji urządzenie zostanie automatycznie "               \
  "zresetowane<br><br><strong>Uwaga:</strong> po aktualizacji nie odłączaj "     \
  "urządzenia przez co najmniej 1min.<br>Urządzenie formatuje pamięć i wgrywa " \
  "domyślne ustawienia.<br><strong>Ten proces nie może zostać "                 \
  "przerwany</strong>"
#define L_UPGRADE "Aktualizuj"
#define L_DONT_PLUG_OFF                                                        \
  "<strong>UWAGA</strong>: nie odłączaj urządzenia od źródła zasilania " \
  "podczas aktualizacji"
#define L_UPGRADE_FAILED "Aktualizacja nie powiodła się"
#define L_UPGRADE_SUCCESSFUL "Aktualizacja zakończona pomyślnie"
#define L_DEVICE_WILL_BE_REBOOTED                                              \
  "Po 15 sekundach oprogramowanie zostanie przeładowane. Proszę czekać"
#define L_RESTORE_DEFAULT_SETTINGS "Przywróć ustawienia początkowe"
#define L_WARNING "Uwaga"
#define L_CONFIGURATION_WILL_BE_REMOVED                                            \
  "przywrócenie ustawień początkowych usuwa wszystkie ustawienia urządzenia, " \
  "włącznie z konfiguracją sieci WiFi"
#define L_UPGRADE_IN_PROGRESS "Trwa przywracanie ustawień początkowych"
#define L_CONNECT_TO_HOTSPOT_AFTER_UPGRADE                                     \
  "Po 20 sekundach połącz się z siecią WiFi o nazwie: "                    \
  "<strong>AFE-Device</strong>, a następnie połącz się z panelem "         \
  "konfiguracyjnym pod adresem"
#define L_RESTORING_DEFAULT_SETTING "Przywracanie ustawień początkowych"
#define L_REBOOT_IN_PROGRESS "Trwa restart urządzenia"
#define L_SITE_WILL_BE_RELOADED                                                \
  "Strona zostanie przeładowana automatycznie... czekaj"
#define L_REBOOT "Restart urządzenia"

/* Form: password */
#define L_SET_PASSWORD "Ustaw hasło"
#define L_SET_PASSWORD_TO_PANEL "Ustaw hasło do Panelu Konfiguracyjnego"
#define L_SET_PASSWORD_INFO                                                    \
  "Jeśli nie pamiętasz hasła, zresetuj urządzenie do stanu początkowego"
#define L_PROTECT_BY_PASSWORD "Zabezpiecz hasłem"

/* Form: Pro version */
#define L_PRO_VERSION "Wersja PRO"
#define L_KEY "Klucz"
#define L_VALID "Aktualny"
#define L_PRO_CANNOT_BE_COFIGURED                                              \
  "Konieczne jest podłączenie do Internetu, aby skonfigurować wersję PRO"

/* Form: Contactron */
#ifdef ESP_CONFIG_HARDWARE_CONTACTRON
#define L_LED_ASSIGNED_TO_SENSOR "LED przypisany do czujnika"
#define L_SET_CONTACTRON_SENSITIVENESS                                                   \
  "Czułość należy ustawić eksperymentalnie, aż uzyska się pożądane działanie " \
  "czujnika magnetycznego"
#define L_MAGNETIC_SENSOR "Czujnik magnetyczny"
#define L_MAGNETIC_SENSORS "Czujniki magnetyczne"
#define L_NUMBER_OF_MAGNETIC_SENSORS "Ilość czujników magnetycznych"
#define L_CONTACTRON_MQTT_TOPIC "Temat MQTT do monitorowania kontaktronu"
#endif

/* I2C */
#ifdef ESP_CONFIG_HARDWARE_I2C
#define L_ADDRESS "Adres"
#define L_FREQUENCY "Częstotliwość"
#endif

/* Anemometer Sensor */
#ifdef ESP_CONFIG_HARDWARE_ANEMOMETER_SENSOR
#define L_ANEMOMETER_SENSOR "Czujnik siły wiatru"
#define L_ANEMOMETER_SENSITIVENESS_HINT "Czułość czujnika należy ustawić metodą prób i błędów, aż do uzyskania zamierzonego efektu. Im wartość jest mniejsza tym czułość jest większa"
#define L_ANEMOMETER_CALIBRATION "Kalibracja anemometru"
#define L_ANEMOMETER_IMPULSE_DISTANCE_HINT "Odległość jaką wiatr przebędzie w jednym impulsie anemometra"
#define L_ANEMOMETER_IMPULSE_DISTANCE "Odległość"
#endif

/* Rainmeter Sensor */
#ifdef ESP_CONFIG_HARDWARE_RAINMETER_SENSOR
#define L_RAINMETER "Czujnik deszczu"
#define L_RAINMETER_CALIBRATION "Rozdzielczość czujnika deszczu"
#define L_RAINMETER_RESOLUTION "Rozdzielczość"
#endif


/* Generic Sensors */
#ifdef ESP_CONFIG_TEMPERATURE
#define L_TEMPERATURE "Temperatura"
#define L_IDX_TEMPERATURE "IDX Temperatura"
#ifndef L_CORRECTIONS
#define L_CORRECTIONS "Korekty"
#endif
#ifndef L_UNITS
#define L_UNITS "Jednostki"
#endif
#endif

#ifdef ESP_CONFIG_HUMIDITY
#define L_HUMIDITY "Wilgotność"
#define L_IDX_HUMIDITY "IDX Wilgotność"
#ifdef ESP_CONFIG_TEMPERATURE
#define L_IDX_DEW_POINT "IDX Punkt rosy"
#define L_IDX_HEAT_INDEX "IDX Temp.odczuwalna"
#define L_IDX_TEMP_HUM "IDX Temp/Wilgotność"
#ifdef ESP_CONFIG_PRESSURE
#define L_IDX_TEMP_HUM_BAR "IDX Temp/Wilg/Bar"
#endif
#endif
#ifndef L_CORRECTIONS
#define L_CORRECTIONS "Korekty"
#endif
#ifndef L_UNITS
#define L_UNITS "Jednostki"
#endif
#endif

#ifdef ESP_CONFIG_PRESSURE
#define L_PRESSURE "Ciśnienie"
#define L_IDX_PRESSURE "IDX Ciśnienie"
#define L_IDX_ALT "Czujnik: wysokość n.p.m"
#ifdef ESP_CONFIG_TEMPERATURE
#define L_IDX_RELATIVE_PRESSURE "IDX Ciśnienie względne"
#endif
#ifndef L_CORRECTIONS
#define L_CORRECTIONS "Korekty"
#endif
#ifndef L_UNITS
#define L_UNITS "Jednostki"
#endif
#endif




#endif

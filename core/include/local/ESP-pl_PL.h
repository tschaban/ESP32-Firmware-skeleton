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
#define L_ADDRESS "Adres"
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
#define L_SELECT "-- Wybierz --"
#define L_VCC "Napięcie zasilania"
#define L_HARDWARE "Sprzęt"
#define L_CONNECTIONS "Połączenia"
#define L_FUNCTIONS "Funkcje"
#define L_FIRMWARE "Firmware"
#define L_SENSITIVENESS "Czułość"
#define L_RANGE "Zakres"
#define L_UNIT "Jednostka"
#define L_UNITS "Jednostki"

/* Form: index */
#define L_INDEX_WRONG_PASSWORD "Hasło nie jest poprawne"
#define L_INDEX_NORMAL_MODE "Tryb normalny"
#define L_INDEX_HOTSPOT_MODE "Tryb HotSpot"
#define L_INDEX_LAUNCH_CONFIGURATION_PANEL "Urządzenie jest w trybie operacyjnym"
#define L_INDEX_LAUNCH_CONFIGURATION_PANEL_HINT "Aby uruchomić panel konfiguracyjny użyj jednego z poniższych przycisków"
#define L_INDEX_OPENING_CONFIG_PANEL "Otwieram panel konfiguracyjny AFE Firmware"

/* Form: device coniguration */
#define L_DEVICE_NAME "Nazwa urządzenia"
#define L_DEVICE_SECTION_INFO                                                  \
  "Nazwa jest wykorzystywana jako nazwa urządzenia w Twojej lokalnej sieci "  \
  "WiFi oraz jako nazwa hotspot'a urządzenia"
#define L_DEVICE_HARDWARE_CONFIGURATION "Konfiguracja urządzenia"
#define L_DEVICE_HARDWARE_CONFIGURATION_INFO                                          \
  "Wybierz podłączone elementy do urządzenia"
#define L_DEVICE_NUMBER_OF_LEDS "Ilość Led'ów"
#define L_DEVICE_NUMBER_OF_RELAYS "Ilość przekaźników"
#define L_DEVICE_NUMBER_OF_SWITCHES "Ilość przycisków"
#define L_DEVICE_NUMBER_OF_ADCS "Ilość wejść ADC"
#define L_DEVICE_NUMBER_OF_I2C "Ilość magistral I2C"
#define L_DEVICE_NUMBER_OF_UART "Ilość magistral UART"
#define L_DEVICE_NUMBER_OF_BINARY_SENSORS "Ilość czujników binarnych"
#define L_DEVICE_NUMBER_OF_DS18B20_SENSORS "Ilość czujników DS18B20"
#define L_DEVICE_NUMBER_OF_NTC_SENSORS "Ilość termistorów NTC"
#define L_DEVICE_NUMBER_OF_BATTERYMETERS "Ilość miernków baterii"
#define L_DEVICE_NUMBER_OF_ACS758 "Ilość czujników ACS758"
#define L_DEVICE_CONTROLLING "Sterowanie urządzeniem"
#define L_DEVICE_CONTROLLING_INFO                                              \
  "Włączanie / Wyłączanie mechanizmów sterowania urządzeniem"


/* Autologoff */
#define L_AUTOLOGOUT_TITLE "Automatyczne zakończenie konfiguracji"
#define L_AUTOLOGOUT_DESCRIPTION "Konfiguracja urządzenia zostanie automatycznie wyłączona po 10min. braku akcji w panelu konfiguracyjnym"

/* Form: network configuration */
#define L_NETWORK_CONFIGURATION "Konfiguracja sieci WiFi"
#define L_NETWORK_CONFIGURATION_INFO "Urządzenie bez dostępu do sieci będzie działać tylko w trybie sterowania ręcznego"
#define L_NETWORK_SSID "Nazwa sieci WiFi"
#define L_NETWORK_REFRESH "Odśwież"
#define L_NETWORK_DHCP_ENABLED "Konfiguracja przez DHCP"
#define L_NETWORK_GATEWAY "Bramka"
#define L_NETWORK_SUBNET "Maska sieci"
#define L_NETWORK_DEVICE_IP "IP urządzenia"
#define L_NETWORK_DEVICE_IP_INFO "Możesz skonfigurować adres IP urządzenia ręcznie lub automatycznie za pośrednictwem DHCP"
#define L_NETWORK_NUMBER_OF_CONNECTIONS "Ilość prób łączenia się"
#define L_NETWORK_TIME_BETWEEN_CONNECTIONS "Czas między próbami łączenia się"
#define L_NETWORK_SLEEP_TIME "Czas po jakim powtórzyć próby łączenia się"
#define L_NETWORK_ADVANCED "Zaawansowane"
#define L_NETWORK_ALMOST "Prawie jesteśmy na miejscu!"
#define L_NETWORK_DEVICE_CONNECTS "Urządzenie łaczy się z siecią"
#define L_NETWORK_CONNECT_TO "Połącz się z siecią WiFi"
//#define L_NETWORK_CONNECT "Połącz"
#define L_NETWORK_SEARCH_FOR_IP_ADDRESS "Następnie w konfigurację routera WiFi, wyszukaj adres IP urządzenia o adresie MAC"
#define L_NETWORK_FINISH_NETWORK_CONFIGURATION  "Dokończ konfigurację wpisując adres IP urządzenia w przeglądarce"
#define L_NETWOK_NONE_BACKUP_SSID "--- Brak ---"
#define L_NETWORK_BACKUP_CONFIGURATION "Zapasowa konfiguracja WiFi"
#define L_NETWORK_BACKUP_CONFIGURATION_HINT "Działa tylko z routerami z włączonym DHCPd"
#define L_NETWORK_SWITCH_TO_BACKUP "Liczba błędów połączeń przed uruchomieniem konfiguracji zapasowej"

/* Form: Led configuration */
#define L_LED_CHANGE_INDICATION "Zmień świecenie diody LED na odwrotne"
#define L_LED_SYSTEM "LED systemowy"
#define L_LED_SYSTEM_INFO "Wybierz diodę LED, która będzie sygnalizowała stan urządzenia oraz występujące zdarzenia"

/* Form: Switch */
#define L_SWITCH_FUNCTIONALITY "Funkcja"
#define L_SWITCH_SYSTEM_BUTTON "Przycisk systemowy"
#define L_SWITCH_CONTROL_RELAY "Tylko sterowanie przekaźnikiem"
#define L_SWITCH_CONTROL_GATE "Tylko sterowanie bramą"
#define L_SWITCH_RELAY_CONTROLLED "Sterowanie"
#define L_SWITCH_TYPE "Typ"
#define L_SWITCH_MONOSTABLE "Monostabilny"
#define L_SWITCH_BISTABLE "Bistabilny"
#define L_SWITCH_SENSITIVENESS_HINT "Czułość należy ustawić metodą prób, aż uzyska się pożądane działanie przycisku podczas jego wciskania"
#define L_SWITCH_BUTTON "Przycisk / Włącznik"
#define L_SWITCH_MQTT_TOPIC "Temat MQTT do monitorowania stanu przycisku"
#define L_SWITCH_REVERSE "Odwróć"

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
#define L_BATTERY_METERS "Mierniki poziomów baterii"
#define L_BATTERY_METER "Miernik baterii"
#define L_BATTERY_MQTT_TOPIC "Temat MQTT Stanu baterii"
#define L_BATTERY_MIN_LEVEL "Minimalny poziom baterii"
#define L_BATTERY_MAX_LEVEL "Maksymalny poziom baterii"
#endif


#define L_BINARY_SENSOR "Czujnik binarny / impulsów"

/* DS18B20 */
#define L_DS18B20_SENSOR "Czujnik temperatury DS18B20"
#define L_DS18B20_SENSORS "Czujniki DS18B20"
#define L_DS18B20_SENT_ONLY_CHANGES "Wysyłać dane tylko, gdy wartość temperatury zmieni się"
#define L_DS18B20_TEMPERATURE_CORRECTION "Korekta wartości o"
#define L_DS18B20_MQTT_TOPIC "MQTT Temat informacji z czujnika DS18B20"
#define L_DS18B20_SEARCH "Skanuj GPIO"
#define L_DS18B20_NO_SENSOR "Żaden czujnik nie został jeszcze znaleziony. Sprawdź, czy jest poprawnie podłączony, a następnie przeskanuj GPIO"
#define L_DS18B20_RESOLUTION "Rozdzielczość"
#define L_DS18B20_RESOLUTION_9B "Niska (9bit)"
#define L_DS18B20_RESOLUTION_10B "Dostateczna (10bit)"
#define L_DS18B20_RESOLUTION_11B "Dobra (11bit)"
#define L_DS18B20_RESOLUTION_12B "Wysoka (12bit)"


#define L_NTC_SENSOR "Termistor NTC"
#define L_NTC_COEFFICIENT_A "Współczynnik A"
#define L_NTC_COEFFICIENT_B "Współczynnik B"
#define L_NTC_COEFFICIENT_C "Współczynnik C"
#define L_NTC_COEFFICIENT_DESC "Współczynnik Steinhart–Hart'a"
#define L_NTC_VCC "Napięcie zasilania"
#define L_NTC_RESISTOR "Rezystor"
#define L_NTC_TERMISTOR "Termistor"
#define L_FLOAT_PRECISION "Precyzja"

#define L_ACS758_SENSOR "Czujnik ACS758"
#define L_ACS758_CURRENT_CUTOFF "Odcięcie pomiarów prądu"



/* Form: upgrade and post upgrade */
#define L_UPGRADE_SELECT_FIRMWARE "Wybierz Firmware"
#define L_UPGRADE_READ_BEFORE "Przeczytaj przed aktualizacją oprogramowania"

#define L_UPGRADE_INTERUPTED "Nie odświeżaj przeglądarki podczas aktualizacji"
#define L_UPGRADE_DONT_PLUG_OFF "Nie odłączaj urządzenia od źródła zasilania"
#define L_UPGRADE_TIME "Proces aktualizacji potrwa do minuty"
#define L_UPGRADE_AUTO_REBOOT "Urządzenie zostanie automatycznie uruchomione po ukończeniu aktualizacji"

#define L_UPGRADE_VIA_WAN "Pobierz i uaktualnij"
#define L_UPGRADE_VIA_WAN_HINT "Firmware zostanie automatycznie pobrane i wgrane do urządzenia"

#define L_UPGRADE_FROM_FILE "Załaduj plik *.bin"
#define L_UPGRADE "Aktualizuj"

#define L_UPGRADE_FIRMWAR_YOUR_CURRENT_FIRMWARE "Twoje aktualne oprogramowanie"
#define L_UPGRADE_FIRMWARE_VERSION "{{f.v}} ESP{{f.e}}.{{f.s}}"
#define L_UPGRADE_FIRMWARE_API "API: {{f.a}}"
#define L_UPGRADE_FIRMWARE_DEVICE_NAME "Urządzenie: {{f.d}}"
#define L_UPGRADE_FIRMWARE_DEVICE_ID "ID urządzenia: {{f.n}}"

#define L_UPGRADE_IN_PROGRESS "Aktualizacja w toku"

#define L_UPGRADE_FAILED "<span style=\"color:red\">Aktualizacja nie powiodła się</span>"
#define L_UPGRADE_SUCCESSFUL "Aktualizacja zakończona pomyślnie"
#define L_UPGRADE_DEVICE_WILL_BE_REBOOTED                                              \
  "Po 15 sekundach urządzenie zostanie zrestartowane. Proszę czekać ..."
#define L_UPGRADE_RESTORE_DEFAULT_SETTINGS "Przywróć ustawienia początkowe"
#define L_RESTORE_CONFIGURATION_WILL_BE_REMOVED                                        \
  "<strong> Ostrzeżenie:</strong> przywrócenie ustawień domyślnych spowoduje usunięcie aktualnej konfiguracji, w tym konfiguracja WiFi"
#define L_RESTORE_IN_PROGRESS "Trwa przywracanie konfiguracji początkowej"
#define L_RESTORE_NETWORK_CONNECT_TO_HOTSPOT_AFTER_UPGRADE "Po 20 sekundach połącz się z siecią Wi-Fi o nazwie twojego urządzenia" 
#define L_RESTORE_NETWORK_CONNECT_TO_HOTSPOT_AFTER_UPGRADE_AFE "Po 20 sekundach połącz się z siecią WiFi o nazwie <strong>AFE Device</strong>" 
#define L_RESTORE_NETWORK_OPEN_PANEL  "Następnie otwórz panel konfiguracyjny : <a href=\"http://192.168.5.1\">http://192.168.5.1</a>"
#define L_UPGRADE_RESTORING_DEFAULT_SETTING "Przywracanie ustawień domyślnych"
#define L_UPGRADE_REBOOT_IN_PROGRESS "Trwa ponowne uruchamianie"
#define L_UPGRADE_SITE_WILL_BE_RELOADED "Strona zostanie automatycznie przeładowana ... czekaj"
#define L_UPGRADE_REBOOT "Ponowne uruchamianie"


/* I2C */
#ifdef ESP_CONFIG_HARDWARE_I2C
#define L_FREQUENCY "Częstotliwość"
#endif


/* Generic Sensor: Temperature */
#define L_TEMPERATURE "Temperatura"
#define L_TEMPERATURE_CORRECTIONS "Korekta temperatury"
#define L_TEMPERATURE_C "Celsjusz"
#define L_TEMPERATURE_F "Fahrenheit"
#define L_CORRECTIONS "Korekty"



#endif

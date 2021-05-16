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
#define L_NUMBER_OF_DS18B20_SENSORS "Ilość czujników DS18B20"
#define L_NUMBER_OF_NTC_SENSORS "Ilość termistorów NTC"
#define L_NUMBER_OF_BATTERYMETERS "Ilość miernków baterii"
#define L_NUMBER_OF_ACS758 "Ilość czujników ACS758"
#define L_DO_MEASURE_ADC "Pomiary z wejścia analogowego"
#define L_DEVICE_CONTROLLING "Sterowanie urządzeniem"
#define L_DEVICE_CONTROLLING_INFO                                              \
  "Włączanie / Wyłączanie mechanizmów sterowania urządzeniem"



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
#ifdef ESP_CONFIG_FUNCTIONALITY_TEMPERATURE
#define L_TEMPERATURE "Temperatura"
#define L_TEMPERATURE_CORRECTIONS "Korekta temperatury"
#define L_UNIT "Jednostka"
#define L_TEMPERATURE_C "Celsjusz"
#define L_TEMPERATURE_F "Fahrenheit"
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

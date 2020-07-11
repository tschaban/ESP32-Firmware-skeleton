#ifdef ESP_CONFIG_HARDWARE_I2C

#include <Wire.h>
#ifdef DEBUG
#include <ESP-I2C-Scanner.h>
#endif
TwoWire WirePort0 = TwoWire(0);
TwoWire WirePort1 = TwoWire(1);
void initializeI2CBUS(void);

/***** Body ******/

void initializeI2CBUS(void) {
  if (Device.configuration.noOfI2Cs > 0) {
    I2CBUS I2CBUSConfiguration;
    Data.get(0, I2CBUSConfiguration);
    WirePort0.begin(I2CBUSConfiguration.SDA, I2CBUSConfiguration.SCL,
                    I2CBUSConfiguration.frequency);
#ifdef DEBUG
    Serial << endl
           << "INFO: I2C(0): SDA: " << I2CBUSConfiguration.SDA
           << ", SCL: " << I2CBUSConfiguration.SCL
           << ", Frequency: " << I2CBUSConfiguration.frequency / 1000
           << "Hz, initialized";

    ESPI2CScanner I2CBus;
    Serial << endl << "INFO: Scannings for devices on I2C(0)";
    I2CBus.begin(&WirePort0);
    I2CBus.scanAll();

#endif

    if (Device.configuration.noOfI2Cs > 1) {
      Data.get(1, I2CBUSConfiguration);
#ifdef DEBUG
      Serial << endl
             << "INFO: I2C(1): SDA: " << I2CBUSConfiguration.SDA
             << ", SCL: " << I2CBUSConfiguration.SCL
             << ", Frequency: " << I2CBUSConfiguration.frequency / 1000
             << "Hz, initialized";

      Serial << endl << "INFO: Scannings for devices on I2C(1)";
      I2CBus.begin(&WirePort1);
      I2CBus.scanAll();

#endif
      WirePort1.begin(I2CBUSConfiguration.SDA, I2CBUSConfiguration.SCL,
                      I2CBUSConfiguration.frequency);
    }
  }
};

#endif // ESP_CONFIG_HARDWARE_I2C

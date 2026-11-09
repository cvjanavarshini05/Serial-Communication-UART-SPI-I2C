
#include <Wire.h>
#include <Adafruit_BMP085.h>

#define BMP180_ADDRESS 0x77
#define CHIP_ID_REGISTER 0xD0
#define EXPECTED_CHIP_ID 0x55

Adafruit_BMP085 bmp;

bool sensorReady = false;

// Function to read BMP180 register
bool readRegister(uint8_t reg, uint8_t &value)
{
    Wire.beginTransmission((uint8_t)BMP180_ADDRESS);
    Wire.write(reg);

    if (Wire.endTransmission(false) != 0)
    {
        return false;
    }

    if (Wire.requestFrom((uint8_t)BMP180_ADDRESS, (uint8_t)1) != 1)
    {
        return false;
    }

    value = Wire.read();
    return true;
}

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    delay(500);

    Serial.println("BMP180 I2C Sensor Initializing...");

    uint8_t chipID;

    // Verify sensor ID before reading measurements
    if (!readRegister(CHIP_ID_REGISTER, chipID))
    {
        Serial.println("ERROR: Sensor not responding!");
        return;
    }

    Serial.print("Chip ID: 0x");
    Serial.println(chipID, HEX);

    if (chipID != EXPECTED_CHIP_ID)
    {
        Serial.println("ERROR: Incorrect sensor ID!");
        return;
    }

    Serial.println("BMP180 ID verified successfully!");

    // Initialize BMP180 sensor
    if (!bmp.begin(BMP085_ULTRAHIGHRES))
    {
        Serial.println("ERROR: BMP180 initialization failed!");
        return;
    }

    sensorReady = true;

    Serial.println("Sensor initialized successfully!");
    Serial.println("Temperature readings started.");
    Serial.println("--------------------------------");
}

void loop()
{
    if (!sensorReady)
    {
        delay(1000);
        return;
    }

    float temperature = bmp.readTemperature();

    if (isnan(temperature))
    {
        Serial.println("ERROR: Invalid temperature reading!");
    }
    else
    {
        Serial.print("Temperature: ");
        Serial.print(temperature, 2);
        Serial.println(" °C");
    }

    delay(1000);
}

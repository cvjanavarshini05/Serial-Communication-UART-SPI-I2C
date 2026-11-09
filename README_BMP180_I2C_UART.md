# Read a Real Sensor over I2C and Stream over UART

## 1. Project Overview

This project interfaces a BMP180 temperature sensor with an Arduino Uno using I2C. The Arduino first reads and verifies the sensor's chip ID. After successful verification, it reads the temperature, converts the measurement into degrees Celsius using the BMP180 datasheet compensation algorithm, and sends the result to the computer through UART using the Serial Monitor.

A new reading is displayed approximately once every second.

## 2. Objectives

- Establish I2C communication between Arduino Uno and BMP180.
- Verify the BMP180 chip ID before reading measurements.
- Read temperature data from the sensor.
- Convert the measurement into degrees Celsius using the sensor's calibration data.
- Stream readable temperature values to the computer through UART.
- Handle a missing or non-responsive sensor without waiting indefinitely.

## 3. Components Required

| Component | Quantity |
|---|---:|
| Arduino Uno | 1 |
| BMP180 sensor module | 1 |
| Breadboard | 1 |
| Jumper wires | As required |
| Wokwi simulator | 1 |

## 4. Circuit Connections

| BMP180 Pin | Arduino Uno Pin |
|---|---|
| VCC | 3.3V or supply specified for the breakout module |
| GND | GND |
| SDA | A4 |
| SCL | A5 |


## 5. Communication Protocols

### A. I2C Communication

I2C is used for communication between the Arduino Uno and BMP180.

- SDA carries data.
- SCL carries the clock signal.
- BMP180 7-bit I2C address: `0x77`.
- The Arduino `Wire` library handles I2C communication.

### B. UART Communication

UART sends the processed temperature readings from the Arduino to the computer.

The program initializes serial communication using:

`Serial.begin(9600);`

Set the Serial Monitor baud rate to **9600**.

## 6. Sensor Address and ID Verification

The program verifies the BMP180 chip ID before reading temperature data.

| Parameter | Value |
|---|---|
| I2C address | `0x77` |
| Chip ID register | `0xD0` |
| Expected chip ID | `0x55` |
| Calibration data | Stored in the sensor's internal EEPROM |

The program reads register `0xD0`. If the returned value is `0x55`, the sensor identity is verified. If the sensor does not acknowledge the I2C request or returns an unexpected ID, an error message is printed.

## 7. Temperature Measurement and Conversion

The BMP180 provides uncompensated temperature data and factory calibration coefficients stored in its internal EEPROM.

The temperature calculation uses these calibration coefficients and the compensation procedure specified in the BMP180 datasheet. The Adafruit BMP085 library performs this calculation when the program calls:

`bmp.readTemperature()`

The returned value is expressed in degrees Celsius (°C). The program therefore does not use an arbitrary conversion constant or treat raw sensor counts as temperature.

## 8. Program Operation

1. Initialize UART communication at 9600 baud.
2. Initialize the I2C interface.
3. Read the BMP180 chip ID from register `0xD0`.
4. Compare the returned ID with the expected value `0x55`.
5. Initialize the BMP180 library only after successful ID verification.
6. Read and compensate the temperature measurement.
7. Print the temperature in degrees Celsius.
8. Repeat approximately once every second.

If the sensor is missing or does not respond during ID verification, the program displays an error and does not attempt to use invalid measurement data.

## 9. Software and Libraries

- Arduino Uno board support package
- `Wire.h` — I2C communication
- `Adafruit_BMP085.h` — BMP180 initialization and datasheet-based temperature compensation

For Wokwi, add this line to the project's `libraries.txt` file:

`Adafruit BMP085 Library`

## 10. Expected Serial Monitor Output

The following is an illustrative example. Actual readings depend on the simulator or sensor environment.

```text
BMP180 I2C Sensor Initializing...
Chip ID: 0x55
BMP180 ID verified successfully!
Sensor initialized successfully!
Temperature readings started.
--------------------------------
Temperature: 29.45 °C
Temperature: 29.48 °C
Temperature: 29.50 °C
```

If the sensor is not detected, an error message may look like this:

```text
BMP180 I2C Sensor Initializing...
ERROR: Sensor not responding!
```

## 11. Simulation Platform

**Platform:** Wokwi

**Simulation Link:** Add your Wokwi shareable project link here.

**Evidence:** Add a screenshot of the running simulation and Serial Monitor showing the verified chip ID and live temperature readings.

## 12. Applications

- Temperature monitoring systems
- Environmental sensing devices
- Embedded data acquisition systems
- Weather monitoring stations
- Sensor-based automation systems

## 13. Conclusion

The project demonstrates a complete sensor acquisition and reporting pipeline. The Arduino Uno communicates with the BMP180 through I2C, verifies the chip ID before accepting measurement data, obtains the compensated temperature in degrees Celsius, and transmits the result to the computer through UART. It demonstrates practical sensor interfacing, register verification, datasheet-based conversion, and serial data communication.

## 14. References

1. Bosch Sensortec, *BMP180 Digital Pressure Sensor Data Sheet*.
2. Adafruit, *Adafruit BMP085 Library* documentation and source code.
3. Arduino, *Wire Library* documentation.

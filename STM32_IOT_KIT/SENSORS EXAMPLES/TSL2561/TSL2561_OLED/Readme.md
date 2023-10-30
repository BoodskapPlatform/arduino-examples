# STM32 - TSL2561 Light Sensor Data Reporting with OLED Display

This code is designed for the STM32F103C8T6 microcontroller to interface with a TSL2561 light sensor and report the light intensity readings on an OLED display. This README provides an overview of the code, prerequisites, hardware setup, and how to use it.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Libraries](#libraries)
- [Usage](#usage)

## Overview

This code interfaces with a TSL2561 light sensor via I2C, periodically reports light intensity readings, and displays them on an OLED screen. It uses the Adafruit TSL2561 library for sensor communication, the ArduinoJson library for JSON data serialization, and Adafruit GFX and Adafruit SSD1306 libraries for OLED display functionality.

## Prerequisites

### Hardware

- STM32F103C8T6 microcontroller
- TSL2561 light sensor
- Power source (3-5VDC)
- Ground connection
- I2C clock (SCL) and data (SDA) connections
- ST-Link programmer
- OLED display (128x64 pixels)

### Software

- Arduino IDE or other STM32 development environment
- Adafruit TSL2561 library
- ArduinoJson library
- Adafruit GFX library
- Adafruit SSD1306 library

## Hardware Setup

1. Connect (Tsl2561) the hardware as follows:

   - VCC: Connect to a power source between 5VDC.
   - GND: Connect to the ground.
   - SCL: Connect to the I2C clock pin (usually labeled SCL).
   - SDA: Connect to the I2C data pin (usually labeled SDA).


## Software Setup

Ensure you have the STM32 development environment set up, such as Arduino IDE  or STM32CubeIDE, and that you can compile and upload code to your STM32F103C8T6.

Install the required libraries:

- [Adafruit TSL2561 library](https://github.com/adafruit/Adafruit_TSL2561)
- [ArduinoJson library](https://arduinojson.org/)
- [Adafruit GFX library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306 library](https://github.com/adafruit/Adafruit_SSD1306)

## Libraries

To use this code, you'll need the following libraries:

- **Adafruit TSL2561**: The library for the TSL2561 light sensor.
- **ArduinoJson**: For working with JSON data.
- **Adafruit GFX**: Required for graphics on the OLED display.
- **Adafruit SSD1306**: Required for OLED display functionality.

## Usage

1. Upload the code to your STM32F103C8T6 microcontroller using the Arduino IDE or your preferred STM32 development environment and the ST-Link programmer.

2. Ensure your OLED display is connected to the appropriate I2c pins.

3. The code will display light intensity data on the OLED screen.

4. Monitor the serial output to see the light intensity readings.

- The code reads data from the TSL2561 sensor, displays it on the OLED screen, and prints the light intensity values in JSON format.

5. The code reports the light intensity readings at intervals based on the `Reporting_Interval` variable.


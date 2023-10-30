# STM32F103C8T6 - BH1750 Light Sensor Example

This code is designed for the STM32F103C8T6 microcontroller to interface with a BH1750 light sensor and report the light intensity readings. This README provides an overview of the code, prerequisites, hardware setup, and how to use it.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Libraries](#libraries)
- [Usage](#usage)


## Overview

This code interfaces with a BH1750 light sensor via the I2C interface and periodically reports light intensity readings. It uses the BH1750 library for sensor communication and the ArduinoJson library for JSON data serialization.

## Prerequisites

### Hardware

- STM32F103C8T6 microcontroller
- BH1750 light sensor
- I2C clock (SCL) and data (SDA) connections
- ST-Link programmer
- OLED

### Software

- Arduino IDE or other STM32 development environment

## Hardware Setup

1. Connect the hardware as follows:

   - VCC: Connect to a power source between 3.3v DC.
   - GND: Connect to the ground.
   - SCL: Connect to the I2C clock pin (usually labeled SCL).
   - SDA: Connect to the I2C data pin (usually labeled SDA).

## Software Setup

Ensure you have the STM32 development environment set up, such as Arduino IDE, and that you can compile and upload code to your STM32F103C8T6.

## Libraries

To use this code, you'll need the following libraries:

- **hp_BH1750**: The library for the BH1750 light sensor.
- **ArduinoJson**: For working with JSON data.
- **Adafruit SSD1306**: For interfacing with the OLED screen.
- **Adafruit GFX**: Graphics library for use with the SSD1306 OLED display.

Make sure to install the "Adafruit SSD1306" and "Adafruit GFX" libraries for interfacing with the OLED screen as part of your setup.


## ST-Link Programmer Setup

1. Connect your ST-Link programmer to the SWD pins on your STM32F103C8T6 microcontroller.
2. Make sure the ST-Link programmer is properly connected to your computer.


## Usage

1. Upload the code to your STM32F103C8T6 microcontroller using the Arduino IDE and ST-Link programmer.

2. Monitor the serial output to see the light intensity readings.

- The code reads the BH1750 sensor and prints the lux value in a JSON format.

3. The code reports the light intensity readings at intervals based on the `REPORTING_INTERVAL` variable.


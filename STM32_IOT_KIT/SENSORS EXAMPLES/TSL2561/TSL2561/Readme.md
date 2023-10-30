# STM32 - TSL2561 Light Sensor Data Reporting

This code is designed to interface with a TSL2561 light sensor using an STM32 microcontroller. It periodically reports light intensity readings. This README provides an overview of the code, prerequisites, hardware setup, and how to use it.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Libraries](#libraries)
- [ST-Link Programmer Setup](#st-link-programmer-setup)
- [Usage](#usage)

## Overview

This code interfaces with a TSL2561 light sensor using an STM32 microcontroller and periodically reports light intensity readings. It uses the Adafruit TSL2561 library for sensor communication and the ArduinoJson library for JSON data serialization.

## Prerequisites

### Hardware

- STM32 microcontroller (e.g., STM32F103C8T6)
- TSL2561 light sensor
- Ground connection
- I2C clock (SCL) and data (SDA) connections
- Serial monitor (for debugging)
- ST-Link programmer (for flashing the STM32)

### Software

- STM32 development environment (e.g.,Arduino IDE, PlatformIO, STM32CubeIDE)
- Adafruit TSL2561 library
- ArduinoJson library

## Hardware Setup

1. Connect the hardware as follows:

   - VCC: Connect to a power source between 5VDC.
   - GND: Connect to the ground.
   - SCL: Connect to the I2C clock pin (usually labeled SCL).
   - SDA: Connect to the I2C data pin (usually labeled SDA).

## Software Setup

Ensure you have the STM32 development environment set up, such as PlatformIO or STM32CubeIDE, and that you can compile and upload code to your STM32 microcontroller.

Install the required libraries:

- [Adafruit TSL2561 library](https://github.com/adafruit/Adafruit_TSL2561)
- [ArduinoJson library](https://arduinojson.org/)

## Libraries

To use this code, you'll need the following libraries:

- **Adafruit TSL2561**: The library for the TSL2561 light sensor.
- **ArduinoJson**: For working with JSON data.

## ST-Link Programmer Setup

1. Connect your ST-Link programmer to the SWD pins on your STM32 microcontroller.

2. Make sure the ST-Link programmer is properly connected to your computer.

## Usage

1. Upload the code to your STM32 microcontroller using your preferred STM32 development environment and the ST-Link programmer.

2. Monitor the serial output (e.g., Serial Monitor) to see the light intensity readings.

- The code reads data from the TSL2561 sensor and prints the light intensity values in JSON format.

3. The code reports the light intensity readings at intervals based on the `Reporting_Interval` variable.


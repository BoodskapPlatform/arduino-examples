# STM32F103C8T6 - Adafruit VL53L0X ToF Sensor with OLED Display

This code is designed for the STM32F103C8T6 microcontroller to interface with an Adafruit VL53L0X Time-of-Flight (ToF) distance sensor and display distance measurements on an OLED screen. This README provides an overview of the code, prerequisites, hardware setup, and how to use it.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Libraries](#libraries)
- [Usage](#usage)

## Overview

This code interfaces with an Adafruit VL53L0X Time-of-Flight (ToF) distance sensor to measure distances and displays the measurements on an OLED screen. It uses the Adafruit VL53L0X library for sensor communication, the ArduinoJson library for JSON data serialization, and the Adafruit SSD1306 library to control the OLED display.

## Prerequisites

### Hardware

- STM32F103C8T6 microcontroller
- Adafruit VL53L0X Time-of-Flight (ToF) distance sensor
- OLED display (128x64 pixels)
- Power source (3.3V)
- Ground connection
- I2C clock (SCL) and data (SDA) connections
- ST-Link programmer

### Software

- Arduino IDE or other STM32 development environment

## Hardware Setup

1. Connect the hardware as follows:

   - VCC: Connect to a power source between 3.3V.
   - GND: Connect to the ground.
   - SCL: Connect to the I2C clock pin (usually labeled SCL).
   - SDA: Connect to the I2C data pin (usually labeled SDA).
   - Connect the OLED display to the corresponding pins on the STM32F103C8T6.

## Software Setup

Ensure you have the STM32 development environment set up, such as ARDUINO IDE, and that you can compile and upload code to your STM32F103C8T6 using an ST-Link programmer.

## Libraries

To use this code, you'll need the following libraries:

- **Adafruit VL53L0X**: The library for the Adafruit VL53L0X Time-of-Flight (ToF) distance sensor.
- **ArduinoJson**: For working with JSON data.
- **Adafruit SSD1306**: For controlling the OLED display.

## Usage

1. Upload the code to your STM32F103C8T6 microcontroller using the Arduino IDE and an ST-Link programmer.

2. The OLED display will show distance measurements in millimeters.

3. The code reports distance measurements at intervals based on the `REPORTING_INTERVAL` variable, and JSON data will be printed to the serial monitor.

4. Monitor the serial output to see the JSON data, including distance measurements.


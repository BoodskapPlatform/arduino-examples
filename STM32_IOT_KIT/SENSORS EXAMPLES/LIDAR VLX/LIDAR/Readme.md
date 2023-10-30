# STM32F103C8T6 - Adafruit VL53L0X ToF Sensor Example

This code is designed for the STM32F103C8T6 microcontroller to interface with an Adafruit VL53L0X Time-of-Flight (ToF) distance sensor and report distance measurements. This README provides an overview of the code, prerequisites, hardware setup, and how to use it.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Libraries](#libraries)
- [Usage](#usage)

## Overview

This code interfaces with an Adafruit VL53L0X Time-of-Flight (ToF) distance sensor to measure distances and periodically reports the distance readings. It uses the Adafruit VL53L0X library for sensor communication and the ArduinoJson library for JSON data serialization.

## Prerequisites

### Hardware

- STM32F103C8T6 microcontroller
- Adafruit VL53L0X Time-of-Flight (ToF) distance sensor
- Power source (3.3v)
- Ground connection
- ST-Link programmer

### Software

- Arduino IDE or other STM32 development environment

## Hardware Setup

1. Connect the hardware as follows:

   - VCC: Connect to a power source between 3.3v.
   - GND: Connect to the ground.
   - SCL: Connect to the I2C clock pin (usually labeled SCL).
   - SDA: Connect to the I2C data pin (usually labeled SDA).

## Software Setup

Ensure you have the STM32 development environment set up, such as Arduino IDE, and that you can compile and upload code to your STM32F103C8T6.

## Libraries

To use this code, you'll need the following libraries:

- **Adafruit VL53L0X**: The library for the Adafruit VL53L0X Time-of-Flight (ToF) distance sensor.
- **ArduinoJson**: For working with JSON data.

## ST-Link Programmer Setup

1. Connect your ST-Link programmer to the SWD pins on your STM32F103C8T6 microcontroller.
2. Make sure the ST-Link programmer is properly connected to your computer.

## Usage

1. Upload the code to your STM32F103C8T6 microcontroller using the Arduino IDE and ST-Link programmer.

2. Monitor the serial output to see the distance measurements.

- The code reads the VL53L0X sensor and prints the distance value in a JSON format.

3. The code reports the distance measurements at intervals based on the `REPORTING_INTERVAL` variable.

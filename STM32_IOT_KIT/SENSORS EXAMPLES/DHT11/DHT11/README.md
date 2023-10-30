# STM32F103C8T6 - DHT11 Temperature and Humidity Sensor Example

This code is designed for the STM32F103C8T6 microcontroller to interface with a DHT11 temperature and humidity sensor and periodically report temperature and humidity readings as JSON data. This README provides an overview of the code, prerequisites, hardware setup, and how to use it.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Libraries](#libraries)
- [ST-Link Programmer Setup](#st-link-programmer-setup)
- [Usage](#usage)

## Overview

This code interfaces with a DHT11 temperature and humidity sensor and periodically reports the temperature and humidity readings as JSON data. It uses the DHT library for sensor communication and the ArduinoJson library for JSON data serialization.

## Prerequisites

### Hardware

- STM32F103C8T6 microcontroller
- DHT11 temperature and humidity sensor
- Data (DHT_PIN) connection
- ST-Link programmer for programming the microcontroller

### Software

- Arduino IDE or other STM32 development environment

## Hardware Setup

1. Connect the hardware as follows:

   - DHT11 sensor: Connect the sensor to the specified pin (DHT_PIN) on your STM32F103C8T6.

## Software Setup

Ensure you have the STM32 development environment set up, such as Arduino IDE, and that you can compile and upload code to your STM32F103C8T6.

## 3rd Party Libraries Required

To use this code, you need to install the following 3rd-party libraries via the Arduino Library Manager:

- **ArduinoJson 6.21.0** by Benoit Blanchon
- **Adafruit Unified Sensor 1.1.9** by Adafruit
- **DHT sensor library 1.1.4** by Adafruit

## ST-Link Programmer Setup

1. Connect your ST-Link programmer to the SWD pins on your STM32F103C8T6 microcontroller.

2. Make sure the ST-Link programmer is properly connected to your computer.

## Usage

1. Upload the code to your STM32F103C8T6 microcontroller using the Arduino IDE or your preferred STM32 development environment.

2. Monitor the serial output to see the temperature and humidity readings in JSON format.

- The code reads data from the DHT11 sensor and prints the JSON data to the serial monitor.

3. The code reports the data at intervals based on the `Reporting_Interval` variable. You can adjust the interval as needed in the code.


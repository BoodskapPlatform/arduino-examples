# STM32F103C8T6 - DHT11 Temperature and Humidity Sensor with OLED Display Example

This code is designed for the STM32F103C8T6 microcontroller to interface with a DHT11 temperature and humidity sensor and display the readings on an OLED screen. This README provides an overview of the code, prerequisites, hardware setup, and how to use it.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Libraries](#libraries)
- [ST-Link Programmer Setup](#st-link-programmer-setup)
- [Usage](#usage)

## Overview

This code interfaces with a DHT11 temperature and humidity sensor and displays the temperature and humidity readings on an OLED screen. It uses the DHT library for sensor communication, the Adafruit SSD1306 library for OLED display, and the ArduinoJson library for JSON data serialization. The code also includes functions for initializing and displaying data on the OLED screen.

## Prerequisites

### Hardware

- STM32F103C8T6 microcontroller
- DHT11 temperature and humidity sensor
- OLED display (Adafruit SSD1306 or similar)
- Data (DHT_PIN) connection
- ST-Link programmer for programming the microcontroller

### Software

- Arduino IDE or other STM32 development environment

## Hardware Setup

1. Connect the hardware as follows:

   - DHT11 sensor: Connect the sensor to the specified pin (DHT_PIN) on your STM32F103C8T6.
   - OLED display: Make necessary connections to your OLED display.

## Software Setup

Ensure you have the STM32 development environment set up, such as PlatformIO, and that you can compile and upload code to your STM32F103C8T6.

## Libraries

To use this code, you'll need the following libraries:

- **ArduinoJson**: For working with JSON data.
- **Adafruit_SSD1306**: For controlling the OLED display.
- **Adafruit_GFX**: Required by the Adafruit SSD1306 library.
- **Adafruit_Sensor**: Required by the DHT library.
- **DHT**: The library for the DHT11 temperature and humidity sensor.

## ST-Link Programmer Setup

1. Connect your ST-Link programmer to the SWD pins on your STM32F103C8T6 microcontroller.

2. Make sure the ST-Link programmer is properly connected to your computer.

## Usage

1. Upload the code to your STM32F103C8T6 microcontroller using the Arduino IDE or your preferred STM32 development environment.

2. The OLED display will show the temperature and humidity readings.

3. The code also serially prints the JSON data with temperature and humidity readings for further processing if needed.


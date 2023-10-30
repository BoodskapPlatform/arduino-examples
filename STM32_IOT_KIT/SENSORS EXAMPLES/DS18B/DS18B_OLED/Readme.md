# STM32F103C8T6 - DS18B20 Temperature Sensor with OLED Display Example

This code is designed for the STM32F103C8T6 microcontroller to interface with a DS18B20 temperature sensor and display temperature readings on an OLED screen. This README provides an overview of the code, prerequisites, hardware setup, and how to use it.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Libraries](#libraries)
- [ST-Link Programmer Setup](#st-link-programmer-setup)
- [Usage](#usage)

## Overview

This code interfaces with a DS18B20 temperature sensor using the OneWire and DallasTemperature libraries. It periodically reads the temperature in Celsius and Fahrenheit and displays the data on an OLED screen. The temperature readings are also reported as JSON data via the serial port.

## Prerequisites

### Hardware

- STM32F103C8T6 microcontroller
- DS18B20 temperature sensor
- OLED display
- Digital pin for connecting the DS18B20 sensor (defined as `SENSOR_PIN`)
- ST-Link programmer for programming the microcontroller

### Software

- Arduino IDE or other STM32 development environment

## Hardware Setup

1. Connect the hardware as follows:

   - DS18B20 sensor: Connect the sensor to the digital pin defined as `SENSOR_PIN` on your STM32F103C8T6.
   - OLED display: Set up the OLED display with the specified settings, as configured in the code.
   - ST-Link programmer: Connect the ST-Link programmer to the appropriate programming pins on your STM32F103C8T6 microcontroller.

## Software Setup

Ensure you have the STM32 development environment set up, such as PlatformIO, and that you can compile and upload code to your STM32F103C8T6.

## Libraries

To use this code, you'll need the following libraries:

1. **ArduinoJson**
   - **Author:** Benoit Blanchon
   - **Explanation:** ArduinoJson is a popular library for working with JSON data in Arduino-based projects. It allows you to easily create, parse, and manipulate JSON data in a memory-efficient manner. The library is widely used for serializing and deserializing data in JSON format. Benoit Blanchon is the primary author of ArduinoJson.

2. **OneWire**
   - **Author:** Paul Stoffregen (Based on the Dallas Semiconductor library)
   - **Explanation:** OneWire is a library that provides low-level communication with 1-wire devices, such as the DS18B20 temperature sensor. It allows you to send and receive data to and from 1-wire devices connected to a single wire. The library is based on the original Dallas Semiconductor library and is widely used for interfacing with 1-wire devices. Paul Stoffregen adapted it for the Arduino platform.

3. **DallasTemperature**
   - **Author:** Miles Burton (Based on the OneWire library)
   - **Explanation:** The DallasTemperature library is a higher-level library built on top of the OneWire library. It simplifies the process of working with Dallas/Maxim 1-wire temperature sensors, including the DS18B20. It provides functions for configuring and reading temperature sensors. The library is an extension of the OneWire library, with Miles Burton as its primary author.

4. **Adafruit_GFX** and **Adafruit_SSD1306**
   - **Author:** Adafruit Industries
   - **Explanation:** These libraries are from Adafruit Industries and are used to interface with OLED displays. Adafruit_GFX provides graphics functions, and Adafruit_SSD1306 is used to control OLED displays. These libraries are commonly used in projects involving graphical displays.


## ST-Link Programmer Setup

1. Connect your ST-Link programmer to the appropriate programming pins on your STM32F103C8T6 microcontroller.

2. Ensure that the ST-Link programmer is properly connected to your computer and recognized by your development environment.

## Usage

1. Upload the code to your STM32F103C8T6 microcontroller using the Arduino IDE or your preferred STM32 development environment.

2. The code will periodically read the temperature from the DS18B20 sensor and convert it to both Celsius and Fahrenheit.

3. The temperature readings, in both Celsius and Fahrenheit, will be displayed on the OLED screen.

4. The data is also reported as JSON

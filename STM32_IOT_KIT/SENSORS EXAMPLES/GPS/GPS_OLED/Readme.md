# STM32F103C8T6 - GPS Data Parsing with JSON Output

This code is designed for the STM32F103C8T6 microcontroller to parse GPS data received through USART3, extract latitude and longitude information, and output this information as JSON data via the serial port. Additionally, it displays the latitude and longitude on an OLED screen. This README provides an overview of the code, prerequisites, hardware setup, and how to use it.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Libraries](#libraries)
- [Usage](#usage)

## Overview

This code interfaces with a GPS module connected to USART3 and extracts latitude, longitude, time, and GPS fix information from the incoming NMEA sentences (GPRMC). It calculates latitude and longitude in decimal degrees, adjusts the time to Indian Standard Time (IST), and reports the data as JSON. Additionally, it displays the latitude and longitude on an OLED screen.

## Prerequisites

### Hardware

- STM32F103C8T6 microcontroller
- GPS module connected to USART3 (TX: PB10, RX: PB11)
- ST-Link programmer for programming the microcontroller
- OLED display (Adafruit SSD1306)
- Power source (3-5VDC)
- Ground connection

### Software

- STM32 development environment, such as PlatformIO
- Libraries (see [Libraries](#libraries) section)

## Hardware Setup

1. Connect the hardware as follows:

   - GPS module: Connect the module to the USART3 interface on your STM32F103C8T6 microcontroller.
   - ST-Link programmer: Connect the ST-Link programmer to the appropriate programming pins on your STM32F103C8T6.
   - OLED display: Connect the display to your STM32 microcontroller.

## Software Setup

Ensure you have the STM32 development environment set up, such as Arduino IDE, and that you can compile and upload code to your STM32F103C8T6.

## Libraries

To use this code, you'll need the following libraries:

1. **ArduinoJson**
   - **Author:** Benoit Blanchon
   - **Explanation:** ArduinoJson is a popular library for working with JSON data in Arduino-based projects. It allows you to easily create, parse, and manipulate JSON data in a memory-efficient manner. The library is widely used for serializing and deserializing data in JSON format. Benoit Blanchon is the primary author of ArduinoJson.

2. **Adafruit_GFX**
   - **Author:** Adafruit
   - **Explanation:** The Adafruit_GFX library is used for drawing graphics on displays, including OLED screens. It's part of the Adafruit family of libraries and is commonly used for creating graphical user interfaces and rendering text and shapes on displays.

3. **Adafruit_SSD1306**
   - **Author:** Adafruit
   - **Explanation:** The Adafruit_SSD1306 library is designed for controlling OLED displays based on the SSD1306 driver chip. This library works in conjunction with Adafruit_GFX to provide an easy way to display text and graphics on OLED screens.

## Usage

1. Upload the code to your STM32F103C8T6 microcontroller using the Arduino IDE, PlatformIO, or your preferred STM32 development environment.

2. Connect your GPS module to the USART3 interface on your microcontroller and ensure the GPS module is transmitting data.

3. Connect the OLED display to your STM32 microcontroller and make sure it's wired correctly.

4. The code will parse incoming GPS data and transform it into JSON format. The latitude and longitude are also displayed on the OLED screen.

5. The JSON data, including latitude, longitude, and GPS fix information, is sent to the serial port and can be accessed and used for your desired applications.


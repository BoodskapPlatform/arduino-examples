# STM32F103C8T6 - GPS Data Parsing with JSON Output

This code is designed for the STM32F103C8T6 microcontroller to parse GPS data received through USART3, extract latitude and longitude information, and output this information as JSON data via the serial port. This README provides an overview of the code, prerequisites, hardware setup, and how to use it.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Libraries](#libraries)
- [ST-Link Programmer](#st-link-programmer)
- [Usage](#usage)

## Overview

This code interfaces with a GPS module connected to USART3 and extracts latitude, longitude, time, and GPS fix information from the incoming NMEA sentences (GPRMC). It calculates latitude and longitude in decimal degrees, adjusts the time to Indian Standard Time (IST), and reports the data as JSON.

## Prerequisites

### Hardware

- STM32F103C8T6 microcontroller
- GPS module connected to USART3 (TX: PB10, RX: PB11)
- ST-Link programmer for programming the microcontroller
- Power source (3-5VDC)
- Ground connection

### Software

- Arduino IDE or other STM32 development environment

## Hardware Setup

1. Connect the hardware as follows:

   - GPS module: Connect the module to the USART3 of your STM32F103C8T6 microcontroller.
   - ST-Link programmer: Connect the ST-Link programmer to the appropriate programming pins on your STM32F103C8T6 microcontroller.

## Software Setup

Ensure you have the STM32 development environment set up, such as Arduino IDE, and that you can compile and upload code to your STM32F103C8T6.

## Libraries

To use this code, you'll need the following libraries:

1. **ArduinoJson**
   - **Author:** Benoit Blanchon
   - **Explanation:** ArduinoJson is a popular library for working with JSON data in Arduino-based projects. It allows you to easily create, parse, and manipulate JSON data in a memory-efficient manner. The library is widely used for serializing and deserializing data in JSON format. Benoit Blanchon is the primary author of ArduinoJson.


## ST-Link Programmer

The ST-Link programmer is used to program your STM32F103C8T6 microcontroller. Make sure to connect it to the appropriate programming pins on your microcontroller to upload the code.

## Usage

1. Upload the code to your STM32F103C8T6 microcontroller using the Arduino IDE or your preferred STM32 development environment.

2. Connect your GPS module to the USART3 interface on your microcontroller.

3. The code will parse incoming GPS data and transform it into JSON format.

4. The JSON data, including latitude, longitude,s and GPS fix information, is sent to the serial port.




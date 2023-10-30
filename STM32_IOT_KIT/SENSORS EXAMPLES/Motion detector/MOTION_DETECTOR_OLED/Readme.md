# STM32F103C8T6 - Motion Sensor and OLED Display Project

This code is designed for the STM32F103C8T6 microcontroller to interface with a motion sensor, display the motion state on an OLED screen, and report it in JSON format. This README provides an overview of the code, prerequisites, hardware setup, and how to use it.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Libraries](#libraries)
- [Usage](#usage)

## Overview

This code interfaces with a motion sensor and an OLED screen via the STM32F103C8T6 microcontroller. It monitors the motion sensor's state and displays it on the OLED screen. It also constructs a JSON document and prints it to the Serial Monitor when motion is detected.

## Prerequisites

### Hardware

- STM32F103C8T6 microcontroller
- Motion sensor
- OLED display
- ST-Link programmer
- Power source (5VDC)
- Ground connection

### Software

- Arduino IDE or STM32 development environment
- STM32 cube programmer

## Hardware Setup

1. Connect the hardware as follows:

   - Connect the motion sensor to the GPIO pin (e.g., PB5).
   - Connect the OLED display to your STM32 microcontroller.
   - Connect the power source (3-5VDC) and ground for both the motion sensor and OLED display.

2. Connect your ST-Link programmer to the STM32F103C8T6 microcontroller.

## Software Setup

Ensure you have the STM32 development environment, such as the Arduino IDE or PlatformIO, set up for STM32F103C8T6 development.

## Libraries

To use this code, you'll need the following library:

- **Adafruit_GFX and Adafruit_SSD1306**: For working with OLED displays.
- **ArduinoJson**: For easy handling and serialization of JSON data.

## Usage

1. Upload the code to your STM32F103C8T6 microcontroller using the Arduino IDE or your preferred development environment.

2. The code reads the motion sensor state and displays it on the OLED screen.

3. If motion is detected, "detected!" is displayed on the OLED screen, and the JSON data is printed to the Serial Monitor.

4. If no motion is detected, "stopped!" is displayed on the OLED screen.

5. The code reports the motion state at intervals based on the `Reporting_Interval` variable or immediately if motion is detected.

6. Monitor the Serial Monitor to see the JSON data and OLED screen for the motion state.


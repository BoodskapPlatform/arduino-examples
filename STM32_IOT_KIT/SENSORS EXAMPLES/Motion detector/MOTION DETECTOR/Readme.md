# STM32F103C8T6 - Motion Sensor Project

This code is designed for the STM32F103C8T6 microcontroller to interface with a motion sensor and report the motion state using ArduinoJson. This README provides an overview of the code, prerequisites, hardware setup, and how to use it.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Libraries](#libraries)
- [Usage](#usage)

## Overview

This code interfaces with a motion sensor via an STM32F103C8T6 microcontroller, monitors the motion sensor's state, and reports it in JSON format. It uses the ArduinoJson library for easy handling and serialization of JSON data.

## Prerequisites

### Hardware

- STM32F103C8T6 microcontroller
- Motion sensor
- ST-Link programmer
- Jumper wires
- Power source (5VDC)
- Ground connection

### Software

- Arduino IDE or STM32 development environment
- ST-Link programmer software

## Hardware Setup

1. Connect the hardware as follows:

   - Connect the motion sensor to the GPIO pin (e.g., PB5).
   - Connect the power source (5VDC) and ground.
   - Ensure the motion sensor provides digital output (HIGH/LOW).

2. Connect your ST-Link programmer to the STM32F103C8T6 microcontroller.

## Software Setup

Ensure you have the STM32 development environment (e.g., Arduino IDE or PlatformIO) set up for STM32F103C8T6 development.

## Libraries

To use this code, you'll need the following library:

- **ArduinoJson**: For easy handling and serialization of JSON data.

## Usage

1. Upload the code to your STM32F103C8T6 microcontroller using the Arduino IDE or your preferred development environment.

2. The code reads the motion sensor state and constructs a JSON document.

3. The JSON document is printed to the Serial Monitor.

4. The code reports the motion state at intervals based on the `Reporting_Interval` variable or immediately if motion is detected.

5. Monitor the Serial Monitor to see the JSON data, including the motion state (0 for no motion, 1 for motion).


# Arduino MPU6050 Orientation Sensor for STM32F103C8T6

This Arduino sketch reads data from an MPU6050 sensor and sends the orientation data in JSON format to the Serial Monitor at regular intervals on an STM32F103C8T6 microcontroller.

## Table of Contents
- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Libraries](#libraries)
- [Usage](#usage)
- [License](#license)

## Overview

This Arduino sketch interfaces with an MPU6050 sensor to obtain orientation data. It calculates the pitch, roll, and yaw angles and reports them as JSON data. The sketch is set to report the orientation data every 15 seconds.

## Prerequisites

### Hardware

- STM32F103C8T6 microcontroller
- ST-Link programmer
- MPU6050 sensor
- Appropriate wiring and connections between the STM32F103C8T6, ST-Link, and MPU6050

### Software

- Arduino IDE
- ArduinoJson library

## Hardware Setup

1. Connect the MPU6050 sensor to the STM32F103C8T6 microcontroller and set up the ST-Link programmer for uploading code to the microcontroller.

## Software Setup

1. Open the Arduino IDE.

2. Install the required library:
   - ArduinoJson library: This library is used for working with JSON data.

3. Make sure you have the STM32 development environment set up in your Arduino IDE. This includes installing the STM32 boards and selecting the correct board and programmer settings.

## Libraries


- **ArduinoJson**: Used for creating and serializing JSON data.

## Usage

1. Upload the code to your STM32F103C8T6 microcontroller using the Arduino IDE and your ST-Link programmer.

2. Open the Arduino Serial Monitor at a baud rate of 9600.

3. You will see the orientation data reported in JSON format. The format is as follows:
   ```json
   {"pos": "x:<x>,y:<y>,z:<z>"}

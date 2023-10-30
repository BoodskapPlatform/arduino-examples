# STM32F103C8T6 - TEMT6000 Light Sensor Example

This code is designed for the STM32F103C8T6 microcontroller to interface with a TEMT6000 light sensor and report light intensity readings. This README provides an in-depth guide on how to set up your development environment, configure the ST-Link programmer, Arduino IDE, and add the required ArduinoJson library. It also includes instructions on how to use the code.

## Overview

This code reads the light intensity using a TEMT6000 sensor and reports it in lux units. It utilizes the ArduinoJson library for JSON data serialization.

## Prerequisites

### Hardware

- STM32F103C8T6 microcontroller
- TEMT6000 light sensor
- Appropriate connections (VCC, GND, and your chosen ADC pin for the sensor)
- ST-Link programmer

### Software

- STM32 development environment or IDE
- Arduino IDE
- ArduinoJson library

## Setting Up the ST-Link Programmer

1. Connect your ST-Link programmer to your computer and the SWD pins on your STM32F103C8T6 microcontroller.

2. Ensure your STM32 board is powered appropriately.

## Configuring Arduino IDE

1. Install the **Arduino IDE** from the official Arduino website if you haven't already.

2. Open Arduino IDE and go to **File** -> **Preferences**.

3. In the "Additional Boards Manager URLs" field, add the URL for STM32 support:

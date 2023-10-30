# TEMT6000 Light Sensor and OLED Display Interface

This Arduino code is designed to interface with a TEMT6000 light sensor and display the light intensity on an OLED screen. This README provides an overview of the code, prerequisites, hardware setup, software setup, required libraries, and usage instructions.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Libraries](#libraries)
- [Usage](#usage)

## Overview

This code reads the light intensity using a TEMT6000 sensor and displays it on an OLED screen. It uses the BH1750 library for sensor communication and the ArduinoJson library for JSON data serialization.

## Prerequisites

### Hardware

- Arduino or compatible board
- TEMT6000 light sensor
- OLED display
- Appropriate connections (VCC, GND, SCL, SDA)

### Software

- Arduino IDE or compatible software for code compilation and upload

## Hardware Setup

1. **Connect the hardware as follows**:

   - VCC: Connect to a power source (e.g., 3.3V or 5V, depending on your sensor).
   - GND: Connect to the ground.
   - SCL: Connect to the I2C clock pin.
   - SDA: Connect to the I2C data pin.

   Ensure the connections are correct for your hardware configuration.

## Software Setup

Ensure you have the Arduino IDE or a compatible development environment installed and configured for your board. Ensure the appropriate board and port are selected in the IDE.

## Libraries

To use this code, you'll need to install the following libraries:

- **ArduinoJson**: For working with JSON data.
- **Adafruit SSD1306**: For interfacing with the OLED display.
- **Adafruit GFX**: Graphics library for use with the SSD1306 OLED display.

Make sure to install the "Adafruit SSD1306" and "Adafruit GFX" libraries for OLED screen interaction.

## Usage

1. **Upload the code** to your Arduino board using the Arduino IDE.

2. Monitor the **serial output** in the Arduino IDE to see the light intensity readings.

   - The code reads the TEMT6000 sensor and prints the lux value in a JSON format.

3. The code **reports the light intensity readings** at intervals determined by the `Reporting_Interval` variable.


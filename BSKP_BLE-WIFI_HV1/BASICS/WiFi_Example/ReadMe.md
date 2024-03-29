# ESP32 MQTT Communication using PlatformIO and Visual Studio Code

This README provides instructions and information for setting up an ESP32 device to communicate over MQTT using PlatformIO and Visual Studio Code. The code example demonstrates how to connect to a WiFi network and publish data to an MQTT server.

## Table of Contents
1. [Introduction](#1-introduction)
2. [Requirements](#2-requirements)
3. [Getting Started](#3-getting-started)
   - 3.1. [PlatformIO and Visual Studio Code Installation](#31-platformio-and-visual-studio-code-installation)
   - 3.2. [Wiring and Hardware Setup](#32-wiring-and-hardware-setup)
4. [Configuring the Code](#4-configuring-the-code)
5. [Flashing the ESP32](#5-flashing-the-esp32)
6. [Usage](#6-usage)
7. [Troubleshooting](#7-troubleshooting)
8. [References](#8-references)

## 1. Introduction
This code example is for an ESP32 microcontroller to communicate over MQTT. It publishes data to an MQTT server using the PubSubClient library. The code is designed to work with PlatformIO in Visual Studio Code. This README will guide you through setting up and flashing the ESP32 device with this code.

## 2. Requirements
- ESP32 Development Board: You will need an ESP32 development board.
- USB to TTL Converter: To program the ESP32, you'll need a USB to TTL converter.
- PlatformIO: Install PlatformIO as an extension in Visual Studio Code.
- WiFi Network: Access to a WiFi network to which the ESP32 can connect.
- MQTT Server: Access to an MQTT server (with hostname and port).

## 3. Getting Started
### 3.1. PlatformIO and Visual Studio Code Installation
- Install Visual Studio Code.
- Open Visual Studio Code and go to the Extensions panel.
- Search for "PlatformIO IDE" and install it.
- Restart Visual Studio Code.

### 3.2. Wiring and Hardware Setup
- Connect your ESP32 development board to the USB to TTL converter following the required pin connections (TX, RX, GND, VCC(3.3v)).
- Ensure the USB to TTL converter is recognized by your computer.

## 4. Configuring the Code
Edit the code according to your specific setup by modifying the following constants:
- MQTT_SERVER: Set the hostname or IP address of your MQTT server.
- MQTT_PORT: Set the MQTT server port.
- SSID and PASSWORD: Set your WiFi network credentials.
- DEVICE_TOKEN: Set your Boodskap Platform token.
- MSG_ID: Set your desired message ID.
- WIFI_LED and INTERNET_LED: Set the LED pin numbers for the WiFi and Internet status indicators.
- Serial2.begin(): Set the appropriate baud rate for Serial2.

## 5. Flashing the ESP32
- Connect your ESP32 to your computer using the USB to TTL converter.
- Open the PlatformIO project in Visual Studio Code.
- Ensure that you have the ESP32 platform installed in PlatformIO. You can do this by going to the PlatformIO Home and searching for "ESP32" in Platforms.
- Click on the "Upload" button to compile and flash the code to your ESP32 device. Ensure that the correct COM port is selected.

## 6. Usage
- After successfully flashing the code to your ESP32, it will attempt to connect to your WiFi network and the MQTT server.
- Data (JSON) received on Serial2 will be published to the MQTT server using the specified topic.
- WiFi and MQTT connection status is indicated by LEDs connected to pins WIFI_LED and INTERNET_LED.

## 7. Troubleshooting
- If you encounter any issues during the flashing process, double-check your wiring and ensure the USB to TTL converter is working correctly.
- If the ESP32 is not connecting to WiFi or MQTT, verify that your credentials and server settings are correct in the code.

## 8. References
- [PlatformIO](https://platformio.org/)
- [ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/index.html)
- [PubSubClient Library](https://pubsubclient.knolleary.net/)

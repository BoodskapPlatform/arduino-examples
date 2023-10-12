# Boodskap IoT - ESP32 Examples (Motion sensor-MH-SR602 )

## Overview

This repository contains example code for using an ESP32 with a motion sensor to detect motion events and send the data to the Boodskap Platform using MQTT. The code is written in C++ and can be developed using Visual Studio Code with PlatformIO or the Arduino IDE.

## Prerequisites

### Hardware
- ESP32 development board
- Motion sensor
- Wi-Fi network for ESP32 connection

### Software
- Arduino IDE or PlatformIO in Visual Studio Code

## 3rd Party Libraries Required

To use this code, you need to install the following 3rd-party libraries via the Arduino Library Manager:

- **PubSubClient 2.8.0** by Nick O'Leary
- **ArduinoJson 6.21.0** by Benoit Blanchon

## Configuration

Before you begin, make sure to configure the following settings in the code:

- `motion_pin`: Enter the GPIO pin connected to the motion sensor.
- `MQTT_SERVER`: Enter your MQTT server URL.
- `MQTT_PORT`: Enter the MQTT server port.
- `SSID`: Your Wi-Fi network SSID.
- `PASSWORD`: Your Wi-Fi network password.
- `MSG_ID`: Your message ID for MQTT.
- `DEVICE_TOKEN`: Your Boodskap Platform device token.

## Wiring

Wire the motion sensor to the ESP32 according to your hardware setup. Ensure the connections are correctly established.

## Code Explanation

The code initializes the ESP32, connects to Wi-Fi, detects motion events from the sensor, and sends the data to the Boodskap Platform using MQTT. Key points in the code include:

- Reading the state of the motion sensor.
- Handling Wi-Fi connection and MQTT client setup.
- Sending motion event data to the Boodskap Platform.

## Usage

1. Compile and upload the code to your ESP32.

2. Monitor the serial output for motion sensor readings.

3. The ESP32 will send motion event data to the Boodskap Platform based on the sensor readings.


## Troubleshooting

- If you encounter any issues, check the Wi-Fi and MQTT server configurations.

- Ensure the ESP32 is properly connected to the  sensor.

- Debug using the serial monitor for additional information.
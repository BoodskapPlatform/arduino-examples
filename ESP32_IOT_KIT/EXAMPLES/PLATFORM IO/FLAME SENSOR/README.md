# Boodskap IoT - ESP32 Examples (Flame sensor)

## Overview

This repository contains example code for using an ESP32 with a flame sensor to detect the presence of fire and send status information to the Boodskap Platform using MQTT. The code is written in C++ and can be developed using Visual Studio Code with PlatformIO or the Arduino IDE.

## Prerequisites

### Hardware
- ESP32 development board
- Flame sensor
- Wi-Fi network for ESP32 connection

### Software
- Arduino IDE or PlatformIO in Visual Studio Code

## 3rd Party Libraries Required

To use this code, you need to install the following 3rd-party libraries via the Arduino Library Manager:

- **ArduinoJson 6.21.0** by Benoit Blanchon
- **PubSubClient 2.8.0** by Nick O'Leary

## Configuration

Before you begin, make sure to configure the following settings in the code:

- `flame_pin`: Enter the GPIO pin to which your flame sensor is connected.
- `MQTT_SERVER`: Enter your MQTT server URL.
- `MQTT_PORT`: Enter the MQTT server port.
- `SSID`: Your Wi-Fi network SSID.
- `PASSWORD`: Your Wi-Fi network password.
- `MSG_ID`: Your message ID for MQTT.
- `DEVICE_TOKEN`: Your Boodskap Platform device token.

## Wiring

Wire the flame sensor to the ESP32 according to your hardware setup. Ensure the connections are correctly established.

## Code Explanation

The code initializes the ESP32, connects to Wi-Fi, checks the status of the flame sensor, and sends the status to the Boodskap Platform using MQTT. Here are some key points:

- The flame sensor is connected to the specified GPIO pin.

- The code checks the sensor status, and if it detects fire, it immediately sends the data to the Boodskap Platform. Otherwise, it periodically sends data every 15 seconds.

- The data is formatted as JSON and sent to the Boodskap Platform via MQTT.

- The code handles Wi-Fi connection and MQTT client setup.

## Usage

1. Compile and upload the code to your ESP32.

2. Monitor the serial output for status information (fire detected or not detected).

3. The ESP32 will send status updates to the Boodskap Platform based on the sensor readings.

## Troubleshooting

- If you encounter any issues, check the Wi-Fi and MQTT server configurations.

- Ensure the ESP32 is properly connected to the flame sensor.

- Debug using the serial monitor for additional information.



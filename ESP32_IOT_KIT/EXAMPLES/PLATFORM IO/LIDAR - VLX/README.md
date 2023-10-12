# Boodskap IoT - ESP32 Examples (VL53L0X)

## Overview

This repository contains example code for using an ESP32 with a VL53L0X LIDAR range sensor to measure distances and send the data to the Boodskap Platform using MQTT. The code is written in C++ and can be developed using Visual Studio Code with PlatformIO or the Arduino IDE.

## Prerequisites

### Hardware
- ESP32 development board
- VL53L0X LIDAR range sensor
- Wi-Fi network for ESP32 connection

### Software
- Arduino IDE or PlatformIO in Visual Studio Code

## 3rd Party Libraries Required

To use this code, you need to install the following 3rd-party libraries via the Arduino Library Manager:

- **ArduinoJson 6.21.0** by Benoit Blanchon
- **PubSubClient 2.8.0** by Nick O'Leary
- **VL53L0X Library 1.2.2** by Adafruit (for VL53L0X sensor communication)
- **Bus IO Library 1.14.1** by Adafruit

## Configuration

Before you begin, make sure to configure the following settings in the code:

- `MQTT_SERVER`: Enter your MQTT server URL.
- `MQTT_PORT`: Enter the MQTT server port.
- `SSID`: Your Wi-Fi network SSID.
- `PASSWORD`: Your Wi-Fi network password.
- `MSG_ID`: Your message ID for MQTT.
- `DEVICE_TOKEN`: Your Boodskap Platform device token.

## Wiring

Wire the VL53L0X LIDAR range sensor to the ESP32 according to your hardware setup. Ensure the connections are correctly established.

## Code Explanation

The code initializes the ESP32, connects to Wi-Fi, reads distance measurements from the VL53L0X sensor, and sends the data to the Boodskap Platform using MQTT. Here are some key points:

- The VL53L0X sensor is interfaced using the Adafruit VL53L0X library and Bus IO Library.

- The code checks if the sensor is correctly connected and initializes it for measurements.

- It reads distance measurements and sends the data to the Boodskap Platform via MQTT.

- The code handles Wi-Fi connection and MQTT client setup.

## Usage

1. Compile and upload the code to your ESP32.

2. Monitor the serial output for distance measurements.

3. The ESP32 will send distance data to the Boodskap Platform based on the sensor readings.

## Troubleshooting

- If you encounter any issues, check the Wi-Fi and MQTT server configurations.

- Ensure the ESP32 is properly connected to the VL53L0X sensor.

- Debug using the serial monitor for additional information.

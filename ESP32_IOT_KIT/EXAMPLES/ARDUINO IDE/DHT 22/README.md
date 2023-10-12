# Boodskap IoT - ESP32 Examples (DHT22)


## Overview

This repository contains example code for using an ESP32 with a DHT22 sensor to read temperature and humidity data and send it to the Boodskap Platform using MQTT. The code is written in C++ and can be developed using Visual Studio Code with PlatformIO or the Arduino IDE.

## Prerequisites

### Hardware
- ESP32 development board
- DHT22 sensor
- Wi-Fi network for ESP32 connection

### Software
- Arduino IDE or PlatformIO in Visual Studio Code

## 3rd Party Libraries Required

To use this code, you need to install the following 3rd-party libraries via the Arduino Library Manager:

- **ArduinoJson 6.21.0** by Benoit Blanchon
- **PubSubClient 2.8.0** by Nick O'Leary
- **Adafruit Unified Sensor 1.1.9** by Adafruit
- **DHT sensor library 1.1.4** by Adafruit

## Configuration

Before you begin, make sure to configure the following settings in the code:

- `DHT_PIN`: Enter the GPIO pin to which your DHT22 sensor is connected.
- `DHT_TYPE`: Specify the DHT sensor type (DHT11, DHT21, or DHT22) you are using.
- `MQTT_SERVER`: Enter your MQTT server URL.
- `MQTT_PORT`: Enter the MQTT server port.
- `SSID`: Your Wi-Fi network SSID.
- `PASSWORD`: Your Wi-Fi network password.
- `MSG_ID`: Your message ID for MQTT.
- `DEVICE_TOKEN`: Your Boodskap Platform device token.

## Wiring

Wire the DHT22 sensor to the ESP32 according to your hardware setup. Ensure the connections are correctly established.

## Code Explanation

The code initializes the ESP32, connects to Wi-Fi, reads temperature and humidity data from the DHT22 sensor, and sends it to the Boodskap Platform using MQTT. Here are some key points:

- The DHT22 sensor is connected to the specified GPIO pin.

- Temperature and humidity data is collected.

- The data is formatted as JSON and sent to the Boodskap Platform via MQTT.

- The code handles Wi-Fi connection and MQTT client setup.

## Usage

1. Compile and upload the code to your ESP32.

2. Monitor the serial output for debugging information.

3. The ESP32 will periodically (every 15 seconds) send temperature and humidity data to the Boodskap Platform.

## Troubleshooting

- If you encounter any issues, check the Wi-Fi and MQTT server configurations.

- Ensure the ESP32 is properly connected to the DHT22 sensor.

- Debug using the serial monitor for additional information.


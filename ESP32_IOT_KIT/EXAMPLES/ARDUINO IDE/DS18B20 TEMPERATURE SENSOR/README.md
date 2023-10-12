# Boodskap IoT - ESP32 Examples (DS18B20)
## Overview

This repository contains example code for using an ESP32 with a Dallas Temperature sensor to read temperature data and send it to the Boodskap Platform using MQTT. The code is written in C++ and can be developed using Visual Studio Code with PlatformIO or the Arduino IDE.

## Prerequisites

### Hardware
- ESP32 development board
- Dallas Temperature sensor
- Wi-Fi network for ESP32 connection

### Software
- Arduino IDE or PlatformIO in Visual Studio Code

## 3rd Party Libraries Required

To use this code, you need to install the following 3rd-party libraries via the Arduino Library Manager:

- **ArduinoJson 6.21.0** by Benoit Blanchon
- **PubSubClient 2.8.0** by Nick O'Leary
- **Dallas Temperature 3.9.0** by Miles Burton, Tim Newsome, Guil Barros
- **OneWire 2.3.7** by Tom Pollard, Jim Studt, Robin James

## Configuration

Before you begin, make sure to configure the following settings in the code:

- `SENSOR_PIN`: Enter the GPIO pin to which your Dallas Temperature sensor is connected.
- `MQTT_SERVER`: Enter your MQTT server URL.
- `MQTT_PORT`: Enter the MQTT server port.
- `SSID`: Your Wi-Fi network SSID.
- `PASSWORD`: Your Wi-Fi network password.
- `MSG_ID`: Your message ID for MQTT.
- `DEVICE_TOKEN`: Your Boodskap Platform device token.

## Wiring

Wire the Dallas Temperature sensor to the ESP32 according to your hardware setup. Ensure the connections are correctly established.

## Code Explanation

The code initializes the ESP32, connects to Wi-Fi, reads temperature data from the Dallas Temperature sensor, and sends it to the Boodskap Platform using MQTT. Here are some key points:

- The Dallas Temperature sensor is connected to the specified GPIO pin.

- The temperature in both Celsius and Fahrenheit is read and printed to the serial monitor.

- The temperature data is formatted as JSON and sent to the Boodskap Platform via MQTT.

- The code handles Wi-Fi connection and MQTT client setup.

## Usage

1. Compile and upload the code to your ESP32.

2. Monitor the serial output for temperature information.

3. The ESP32 will periodically (every 15 seconds) send temperature data to the Boodskap Platform.

## Troubleshooting

- If you encounter any issues, check the Wi-Fi and MQTT server configurations.

- Ensure the ESP32 is properly connected to the Dallas Temperature sensor.

- Debug using the serial monitor for additional information.


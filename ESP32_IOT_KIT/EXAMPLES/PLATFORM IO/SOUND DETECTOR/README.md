# Boodskap IoT - ESP32 Examples (sound sensor)

This repository contains example code for using an ESP32 with a sound sensor to detect sound events and send the data to the Boodskap Platform using MQTT. The code is written in C++ and utilizes 3rd-party libraries for MQTT and JSON serialization.

## Prerequisites

### Hardware
- ESP32 development board
- Sound sensor
- Wi-Fi network for ESP32 connection

### Software
- Arduino IDE or PlatformIO in Visual Studio Code

## 3rd Party Libraries Required

Before you start, make sure to install the following 3rd-party libraries via the Arduino Library Manager:

- [PubSubClient 2.8.0] by Nick O'Leary
- [ArduinoJson 6.21.0] by Benoit Blanchon

## Configuration

Before you begin, make sure to configure the following settings in the code:

- `SENSOR_PIN`: Enter the GPIO pin connected to the sound sensor.
- `MQTT_SERVER`: Enter your MQTT server URL.
- `MQTT_PORT`: Enter the MQTT server port.
- `SSID`: Your Wi-Fi network SSID.
- `PASSWORD`: Your Wi-Fi network password.
- `MSG_ID`: Your message ID for MQTT.
- `DEVICE_TOKEN`: Your Boodskap Platform device token.

## Wiring

Wire the sound sensor to the ESP32 according to your hardware setup. Ensure the connections are correctly established. 

## Code Explanation

The provided code initializes the ESP32, connects to Wi-Fi, reads the state of the sound sensor, and sends sound event data to the Boodskap Platform using MQTT. Key points in the code include:

- Initializing the ESP32 and setting up Wi-Fi.
- Reading the state of the sound sensor.
- Handling MQTT client connection and data publishing.

## Usage

1. Compile and upload the code to your ESP32 using the Arduino IDE or PlatformIO.

2. Open the serial monitor to monitor sound sensor readings and debug information.

3. The ESP32 will send sound event data to the Boodskap Platform based on sensor readings and the configured reporting interval.


## Troubleshooting

- If you encounter any issues, check the Wi-Fi and MQTT server configurations.

- Ensure the ESP32 is properly connected to the  sensor.

- Debug using the serial monitor for additional information.
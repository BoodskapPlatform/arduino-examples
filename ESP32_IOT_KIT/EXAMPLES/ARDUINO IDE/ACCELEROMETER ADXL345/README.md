# Boodskap IoT - ESP32 Examples (ADXL345 accelerometer)

This project demonstrates how to use an ESP32 to read data from an ADXL345 accelerometer and send it to the Boodskap Platform using MQTT. The code is written in C++ and can be developed using Visual Studio Code with PlatformIO or the Arduino IDE.


## Overview
This repository contains example code for using an ESP32 to read data from an ADXL345 accelerometer and send it to the Boodskap Platform using MQTT. The code is written in C++ and can be developed using Visual Studio Code with PlatformIO or the Arduino IDE.

## 3rd Party Libraries Required
- **ArduinoJson 6.21.0** by Benoit Blanchon
- **PubSubClient 2.8.0** by Nick O'Leary

## Requirements

### Hardware
- ESP32 development board
- ADXL345 accelerometer sensor
- Wi-Fi network for ESP32 connection

### Software
- Arduino IDE or PlatformIO in Visual Studio Code

## Setup

1. Ensure you have the necessary hardware components.

2. Set up the Arduino IDE or PlatformIO in Visual Studio Code.

3. Install the required libraries using the Arduino IDE or PlatformIO.

4. Open the code and update the following configurations:
   - `MQTT_SERVER`: Enter your MQTT server URL.
   - `MQTT_PORT`: Enter the MQTT server port.
   - `SSID`: Your Wi-Fi network SSID.
   - `PASSWORD`: Your Wi-Fi network password.
   - `MSG_ID`: Your message ID for MQTT.
   - `DEVICE_TOKEN`: Your Boodskap Platform device token.

### Wiring

Wire the ADXL345 accelerometer to the ESP32 according to your hardware setup. Make sure the connections are correctly established.

## Code Explanation

The code initializes the ESP32, connects to Wi-Fi, reads data from the ADXL345 accelerometer, and sends it to the Boodskap Platform using MQTT. Here are some key points:

- The ADXL345 is connected via I2C and configured for data collection.
- Sensor data (X, Y, Z) is collected and processed to determine the patient's position.
- The data is formatted as JSON and sent to the Boodskap Platform via MQTT.
- The code handles Wi-Fi connection and MQTT client setup.

## Usage

1. Compile and upload the code to your ESP32.

2. Monitor the serial output for debugging information.

3. The ESP32 will periodically (every 15 seconds) send data to the Boodskap Platform with the patient's posture information.

## Troubleshooting

- If you encounter any issues, check the Wi-Fi and MQTT server configurations.

- Ensure the ESP32 is properly connected to the ADXL345 sensor.

- Debug using the serial monitor for additional information.


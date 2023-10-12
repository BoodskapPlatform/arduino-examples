# Boodskap IoT - ESP32 Examples (Voltage sensor)

This repository contains example code for using an ESP32 with a voltage sensor to measure voltage and send the data to the Boodskap Platform using MQTT. The code is written in C++ 
## Prerequisites

### Hardware
- ESP32 development board
- Voltage sensor
- Wi-Fi network for ESP32 connection

### Software
- Arduino IDE or PlatformIO in Visual Studio Code


## 3rd Party Libraries Required

To use this code, you need to install the following 3rd-party libraries via the Arduino Library Manager:


- [PubSubClient 2.8.0] by Nick O'Leary
- [ArduinoJson 6.21.0] by Benoit Blanchon

## Configuration

Before you begin, make sure to configure the following settings in the code:

- `voltagepin`: Enter the GPIO pin connected to the voltage sensor.
- `MQTT_SERVER`: Enter your MQTT server URL.
- `MQTT_PORT`: Enter the MQTT server port.
- `SSID`: Your Wi-Fi network SSID.
- `PASSWORD`: Your Wi-Fi network password.
- `MSG_ID`: Your message ID for MQTT.
- `DEVICE_TOKEN`: Your Boodskap Platform device token.

## Code Explanation

The provided code initializes the ESP32, connects to Wi-Fi, measures the voltage using the voltage sensor, and sends it to the Boodskap Platform using MQTT. Key points in the code include:

- Reading voltage data and converting it to volts.
- Handling Wi-Fi connection and MQTT client setup.
- Sending voltage data to the Boodskap Platform.

## Usage

1. Compile and upload the code to your ESP32 using the Arduino IDE or PlatformIO.

2. Open the serial monitor to monitor voltage readings and debug information.

3. The ESP32 will send voltage data to the Boodskap Platform at the configured reporting interval.


## Troubleshooting

- If you encounter any issues, check the Wi-Fi and MQTT server configurations.

- Ensure the ESP32 is properly connected to the  sensor.

- Debug using the serial monitor for additional information.
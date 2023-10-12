
# Boodskap IoT - ESP32 Examples (TEMT6000)

This repository contains an example code for using an ESP32 with a light sensor (TEMT6000) to measure light levels and send the data to the Boodskap Platform using MQTT. The code is written in C++ .

## Prerequisites

### Hardware
- ESP32 development board
- TEMT6000 light sensor
- Wi-Fi network for ESP32 connection

### Software
- Arduino IDE or PlatformIO in Visual Studio Code


## 3rd Party Libraries Required

Before you start, make sure to install the following 3rd-party libraries via the Arduino Library Manager:

- [PubSubClient 2.8.0] by Nick O'Leary
- [ArduinoJson 6.21.0] by Benoit Blanchon

## Configuration

Before you begin, make sure to configure the following settings in the code:

- `light_pin`: Enter the GPIO pin connected to the TEMT6000 light sensor.
- `MQTT_SERVER`: Enter your MQTT server URL.
- `MQTT_PORT`: Enter the MQTT server port.
- `SSID`: Your Wi-Fi network SSID.
- `PASSWORD`: Your Wi-Fi network password.
- `MSG_ID`: Your message ID for MQTT.
- `DEVICE_TOKEN`: Your Boodskap Platform device token.

## Hardware Setup

Wire the TEMT6000 light sensor to the ESP32 according to your hardware setup. Ensure the connections are correctly established. 
## Code Explanation

The provided code initializes the ESP32, connects to Wi-Fi, reads light sensor data from the TEMT6000, and converts it to Lux (illuminance). Key points in the code include:

- Initializing the ESP32 and setting up Wi-Fi.
- Reading light sensor data and converting it to Lux.
- Handling MQTT client connection and publishing the Lux data to the Boodskap Platform.

## Usage

1. Compile and upload the code to your ESP32 using the Arduino IDE or PlatformIO.

2. Open the serial monitor to monitor Lux readings and debug information.

3. The ESP32 will send Lux data to the Boodskap Platform at the configured reporting interval.


## Troubleshooting

- If you encounter any issues, check the Wi-Fi and MQTT server configurations.

- Ensure the ESP32 is properly connected to the  sensor.

- Debug using the serial monitor for additional information.
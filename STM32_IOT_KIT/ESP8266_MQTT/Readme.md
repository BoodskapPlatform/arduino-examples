# ESP8266 MQTT Data Publisher

This Arduino sketch is designed for an ESP8266-based device to connect to an MQTT server and publish data received from the serial port.This documentation provides an overview of the sketch, its usage, and customization options.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Configuration](#configuration)
- [Usage](#usage)
- [Components](#components)


## Overview

This Arduino sketch establishes a connection to an MQTT server and publishes data from the serial port to the server using the PubSubClient library. It also includes Wi-Fi connectivity status indication with an LED. It's suitable for IoT projects where data needs to be transmitted to an MQTT broker.

## Prerequisites

Before using this sketch, you'll need the following:

### Hardware

- ESP8266 development board
- A Wi-Fi network for ESP8266 connection
- An LED connected to pin 2 for Wi-Fi connection status indication

### Software

- Arduino IDE or PlatformIO in Visual Studio Code

### 3rd Party Libraries Required

To use this code, you need to install the following 3rd-party libraries via the Arduino Library Manager:

- **ESP8266WiFi** for ESP8266 connectivity
- **PubSubClient** for MQTT communication

## Configuration

Before you begin, make sure to configure the following settings in the code:

- `MQTT_SERVER`: Set this to the address of your MQTT server.
- `MQTT_PORT`: Set this to the port number of your MQTT server.
- `ssid` and `password`: Enter the credentials of your Wi-Fi network.
- `DEVICE_TOKEN`: Specify your Boodskap Platform token.
- `MSG_ID`: Define a unique message ID.
- `WIFI_INTERNET_LED`: Set the pin number for the LED that indicates Wi-Fi connection status.
- `clientid`: You can customize the client ID. It's currently set to the device token.
- `topic`: The MQTT topic to which data will be published. It's constructed using the device token and message ID.

## Usage

1. Open the Arduino IDE and load this sketch.

2. Configure the sketch by setting the constants mentioned in the Configuration section.

3. Connect your ESP8266-based device to your computer.

4. Upload the sketch to your device.

5. Open the Serial Monitor in the Arduino IDE (Tools > Serial Monitor).

6. Send data over the serial connection. The sketch will publish this data to the configured MQTT topic when the MQTT client is connected.

7. Observe the Wi-Fi connection status using the LED indicator.

## Components

- **ESP8266**: The ESP8266 module connects to your Wi-Fi network and communicates with the MQTT server.

- **Arduino PubSubClient Library**: This library is used for MQTT communication.

- **Wi-Fi LED Indicator**: An LED connected to pin 2 is used to indicate the status of the Wi-Fi connection. It's ON when attempting to connect and OFF when connected.




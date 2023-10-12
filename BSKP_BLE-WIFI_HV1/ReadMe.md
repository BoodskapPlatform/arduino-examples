# BLE-WiFi Communication Device - User Manual

## Table of Contents

1. [Introduction](#introduction)
2. [Product Overview](#product-overview)
3. [Key Features](#key-features)
4. [Use Cases](#use-cases)
5. [Product Functionality](#product-functionality)
6. [Hardware Overview](#hardware-overview)
7. [Application Scenarios](#application-scenarios)
8. [Integration with Platforms](#integration-with-platforms)

## 1. Introduction

The BLE-WiFi Communication Device User Manual provides information about the product, its features, functionality, and various use cases. This document serves as a guide for understanding and utilizing the device.

## 2. Product Overview

### 2.1 Product Overview

The BLE-WiFi Communication Device is a versatile hardware solution designed for collecting data from BLE (Bluetooth Low Energy) servers and transmitting it via WiFi to various platforms. This device is equipped with two ESP32 modules mounted on a PCB board, with one dedicated to BLE communication and the other to WiFi communication.

## 3. Key Features

- **Dual ESP32 Modules:** Two ESP32 microcontrollers for independent BLE and WiFi communication.
- **BLE Data Collection:** Collects data from BLE servers and peripherals.
- **WiFi Data Transmission:** Transmits collected data to any platform via WiFi.
- **Serial Communication Ports:** ESP32 modules communicate with each other through Serial2.
- **Easy Programming:** Flash new programs using the available Serial0 pins on the PCB board.
- **Indicator LEDs:** Four LEDs for visual status indication.
- **Reset Buttons:** Two buttons for resetting the ESP32 modules.
- **Programming Pins:** Four pins for convenient programming and configuration.

## 4. Use Cases

- **Asset Tracking:** Track the location of assets equipped with BLE tags and send updates via WiFi.
- **Environmental Monitoring:** Collect data from BLE sensors and upload it to the cloud for analysis.
- **Home Automation:** Control and monitor BLE-enabled smart devices using a WiFi network.

## 5. Product Functionality

### 5.1 BLE Communication (ESP32-D2)

The ESP32-D2 module is responsible for BLE communication. It can connect to BLE servers and peripherals, collect data, and prepare it for transmission. Key functions include:
- Scanning for BLE devices.
- Establishing connections with BLE peripherals.
- Collecting data from connected BLE devices.
- Data processing and formatting.

### 5.2 WiFi Communication (ESP32-D1)

The ESP32-D1 module handles WiFi communication. It receives data from ESP32-D2 and transmits it to remote platforms over WiFi. Key functions include:
- Connecting to WiFi networks.
- Transmitting data to remote servers or cloud platforms.
- Managing network authentication and security.

### 5.3 Data Collection

The BLE-WiFi Communication Device can collect various types of data, including sensor readings, device status, or any data exposed by BLE servers and peripherals. Data is collected from BLE devices within the communication range of ESP32-2.

### 5.4 Data Transmission

Collected data is transmitted over a WiFi network to a specified destination. This device supports a range of data transmission methods, including HTTP, MQTT, or custom protocols, depending on your application requirements.

## 6. Hardware Overview

### 6.1 PCB Board

The PCB board provides a stable platform for mounting the ESP32 modules and connecting various components. It includes Serial0 pins for easy programming and configuration.

### 6.2 ESP32 Modules

- ESP32-2: Dedicated to BLE communication.
- ESP32-1: Dedicated to WiFi communication.

### 6.3 Serial Communication Ports

The two ESP32 modules communicate with each other using Serial2, allowing them to exchange data seamlessly.

### 6.4 Flashing New Programs

To update or reconfigure the device, use the Serial0 pins available on the PCB board for programming. This enables easy firmware updates and customization.

## 7. Application Scenarios

### 7.1 Example Use Cases

- **Asset Tracking:**
  Attach BLE tags to assets, track their location with ESP32-2, and send updates to a central server via ESP32-1 over WiFi.
  
- **Environmental Monitoring:**
  Collect data from BLE environmental sensors, such as temperature or humidity, and upload the data to a cloud platform for analysis.

- **Home Automation:**
  Control and monitor BLE-enabled smart devices in your home using a WiFi connection. Turn on lights, adjust thermostats, or monitor security sensors.

## 8. Integration with Platforms

The BLE-WiFi Communication Device can be integrated with various platforms, including:
- Cloud platforms such as AWS, Azure, Boodskap, or Google Cloud for data storage and processing.
- Mobile apps or web applications for real-time monitoring and control.

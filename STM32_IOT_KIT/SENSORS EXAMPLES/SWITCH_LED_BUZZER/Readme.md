# STM32F103C8T6 - LED and Buzzer Control with Switch

This code is designed for the STM32F103C8T6 microcontroller to control an LED and a buzzer using a switch. This README provides an overview of the code, prerequisites, hardware setup, and how to use it.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Usage](#usage)

## Overview

This code allows you to control an LED and a buzzer using a switch with the STM32F103C8T6 microcontroller. When the switch is in the LOW state, the buzzer and LED are turned on, and they are turned off when the switch is not in the LOW state.

## Prerequisites

### Hardware

- STM32F103C8T6 microcontroller
- An ST-Link programmer for programming the microcontroller
- LED
- Buzzer
- Switch


### Software

- Arduino IDE or another STM32 development environment

## Hardware Setup

1. Connect the hardware as follows:

   - Connect the LED to the `PB15` pin.
   - Connect the buzzer to the `PA8` pin.
   - Connect the switch to the `PA11` pin.
   - Provide power and ground connections for the microcontroller.

## Software Setup

Ensure you have the STM32 development environment, such as the Arduino IDE or PlatformIO, set up for STM32F103C8T6 development.

## Usage

1. Upload the code to your STM32F103C8T6 microcontroller using the Arduino IDE or your preferred STM32 development environment with the ST-Link programmer.

2. Connect the power source to the microcontroller to power it up.

3. Use the switch to control the LED and buzzer. When the switch is in the LOW state, the LED and buzzer will be turned on. When the switch is not in the LOW state, they will be turned off.


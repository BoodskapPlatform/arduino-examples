# STM32 On-Board LED Blink

This STM32 code example demonstrates how to blink the on-board LED of your STM32 microcontroller. The on-board LED will alternate between an ON and OFF state in a continuous loop with a 100-millisecond delay between each state change.

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Usage](#usage)
- [Programming with ST-Link](#programming-with-st-link)

## Overview

This STM32 code sketch showcases the basics of controlling the on-board LED of the STM32 microcontroller. The LED will blink on and off to create a simple blinking effect.

## Prerequisites

### Hardware

- STM32 microcontroller board (STM32F103C8T6)
- ST-Link programmer (e.g., ST-Link V2, ST-Link V3)

### Software

- ARDUINO IDE or STM32CubeMX (Integrated Development Environment)
- USB cable to connect the STM32 board to your computer
- ST-Link utility software (if not using STM32CubeIDE)
- STM32 Cube programmer

## Usage

1. Open STM32CubeIDE or STM32CubeMX on your computer.
2. Copy and paste the provided code into the STM32 development environment.
3. Ensure the STM32 board is connected to your computer via USB.
4. Configure the project settings in STM32CubeIDE/STM32CubeMX, including selecting the appropriate microcontroller model.
5. Build and flash the code onto your STM32 board.

## Programming with ST-Link

If you prefer to use an external ST-Link programmer:

1. Connect the ST-Link programmer to your computer using a USB cable.
2. Connect the ST-Link programmer to your STM32 board, ensuring the correct connections.
3. Open the ST-Link utility software on your computer (if not using STM32CubeIDE).
4. Select the target STM32 microcontroller and load the compiled binary onto the board.
5. The on-board LED should start blinking after programming.


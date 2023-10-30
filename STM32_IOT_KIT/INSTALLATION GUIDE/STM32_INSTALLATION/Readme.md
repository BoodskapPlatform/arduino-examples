# Setting up Arduino Environment for STM32 Microcontrollers

This guide will help you set up the Arduino environment to program STM32 microcontrollers using the Arduino IDE. It covers the installation of the STM32 package and the STM32CubeProg tool. Additionally, it provides instructions for connecting an STM32 Blue Pill to an ST-Link compatible emulator and programmer dongle.

## Installation of Arduino Environment

1. Download and install the Arduino IDE from the official Arduino website at [Arduino Software](https://www.arduino.cc/en/Main/Software).

2. Once the Arduino IDE is installed, launch it.

3. Go to "File" > "Preferences" within the Arduino IDE.

4. In the "Additional Boards Manager URLs" field, add either of the following URLs:
   - [STM32duino Package](https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json)
   - [Alternative STM32duino Package](http://dan.drown.org/stm32duino/package_STM32duino_index.json)

## Installing the STM32 Package

1. In the Arduino IDE, navigate to "Tools" > "Board" > "Boards Manager..."

2. In the Boards Manager, enter "STM32" or "stm" in the search bar.

3. You should see the STM32 package; click on it and select "Install."

## Installing STM32 Emulator and Programmer Dongle (Windows only)

- Note: Using a JLink or ST-Link dongle to program the board will erase the Arduino bootloader.

1. Install STM32CubeProg by downloading it from the official ST.com website: [STM32CubeProg Download](https://www.st.com/en/development-tools/stm32cubeprog.html).

2. Start STM32CubeProg. It should open as a separate application.

3. Close STM32CubeProg for now.

## Connecting the STM32 Blue Pill to the ST-Link Compatible Emulator and Programmer Dongle

Follow the provided wiring diagram to connect the STM32 Blue Pill to an ST-Link compatible emulator and programmer dongle. The connections are as follows:

- STM32 Blue Pill GND -> ST-Link compatible Dongle GND
- STM32 Blue Pill SCK -> ST-Link compatible Dongle SWCLK
- STM32 Blue Pill DIO -> ST-Link compatible Dongle SWDIO
- STM32 Blue Pill 3V3 -> ST-Link compatible Dongle 3.3V

## Setting Up Arduino IDE

1. Ensure you have already installed the STM32 add-on in Arduino IDE as per the earlier instructions.

2. Select "Tools" > "USB Support" and choose "None."

3. Set the Upload method to "STM32CubeProgrammer (SWD)."

These configurations should now be set in your Arduino IDE.

This README helps you set up the environment for programming STM32 microcontrollers using the Arduino IDE. You can refer to the official link provided for additional documentation and support: [Arduino Core for STM32](https://github.com/stm32duino/Arduino_Core_STM32).

## Additional Board Preference Links (Optional)

If you want to add support for more boards, follow these optional steps:

1. Open the Arduino IDE.

2. Go to **File > Preferences**.

3. In the "Additional Boards Manager URLs" field, you can add more URLs, separated by commas, for other board packages you need. For example:

https://dl.espressif.com/dl/package_esp32_index.json,http://arduino.esp8266.com/stable/package_esp8266com_index.json,https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json


4. Click the "OK" button to save the preferences.

5. Go to **Tools > Board > Boards Manager** to install the board packages associated with the URLs you added.

6. Search for and install the boards you need, such as "esp32," "esp8266," and "STM32."



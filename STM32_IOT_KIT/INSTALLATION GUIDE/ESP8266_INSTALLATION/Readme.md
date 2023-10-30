# Installing ESP8266 Support in Arduino IDE

This guide will help you install and set up ESP8266 support in the Arduino IDE, allowing you to program ESP8266-based boards.

## Installation of Arduino Environment

1. Download and install the Arduino IDE from the official Arduino website at [Arduino Software](https://www.arduino.cc/en/Main/Software).

2. Once Arduino IDE is installed, launch it.

## ESP8266 Add-on in Arduino IDE

To install the ESP8266 board in your Arduino IDE, follow these instructions:

1. In your Arduino IDE, go to "File" > "Preferences."

2. In the "Preferences" dialog, find the "Additional Boards Manager URLs" field and add the following URL:

   http://arduino.esp8266.com/stable/package_esp8266com_index.json

Then, click the "OK" button to save the changes.

3. Open the "Boards Manager" by going to "Tools" > "Board" > "Boards Manager..."

4. In the "Boards Manager," search for "ESP8266" and press the "Install" button for the "ESP8266 by ESP8266 Community."

5. Wait for a few seconds while the ESP8266 support is installed.

That's it! You have successfully installed the ESP8266 support in your Arduino IDE. You can now select ESP8266-based boards from the board manager and start programming them.

For additional documentation and support, visit the official ESP8266 Arduino Core repository: [ESP8266 Arduino Core](https://github.com/esp8266/Arduino).

## Additional Board Preference Links (Optional)

If you want to add support for more boards, follow these optional steps:

1. Open the Arduino IDE.

2. Go to **File > Preferences**.

3. In the "Additional Boards Manager URLs" field, you can add more URLs, separated by commas, for other board packages you need. For example:

https://dl.espressif.com/dl/package_esp32_index.json,http://arduino.esp8266.com/stable/package_esp8266com_index.json,https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json


4. Click the "OK" button to save the preferences.

5. Go to **Tools > Board > Boards Manager** to install the board packages associated with the URLs you added.

6. Search for and install the boards you need, such as "esp32," "esp8266," and "STM32."



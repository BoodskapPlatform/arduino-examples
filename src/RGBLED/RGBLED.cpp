/**
MIT License

Copyright (c) 2017 Boodskap Inc

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. 
 */
#ifdef IMPL_RGB_LED

#include <Arduino.h>
#include <BoodskapTransceiver.h>
#pragma message("*** LGB LED Implementation ****")

#ifdef ESP8266
const String mPrefix = "BSKP-RGBL-ESP8266-";
#elif ESP32_DEV
const String mPrefix = "BSKP-RGBL-ESP32-";
#endif

#if defined(USE_UDP)
const String deviceModel = mPrefix + String("UDP");
#elif defined(USE_MQTT)
const String deviceModel = mPrefix + String("MQTT");
#elif defined(USE_HTTP)
const String deviceModel = mPrefix + String("HTTP");
#endif

const String firmwareVersion = "1.0.0";

#define MSG_STATUS 500000300
#define CMD_100 100//set RGB value

void setValue(uint8_t red, uint8_t green, uint8_t blue);
void sendValue();

uint8_t redValue = 0;
uint8_t blueValue = 0;
uint8_t greenValue = 0;

void setupApp()
{

    DEBUG_PORT.printf("RGB Pins (%d, %d, %d)\n", RED_PIN, GREEN_PIN, BLUE_PIN);

    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    setValue(128, 128, 128);

    timer.every(60000, &sendValue);

    delay(1000);
}

void loopApp()
{
}

void setValue(uint8_t red, uint8_t green, uint8_t blue){
    DEBUG_PORT.printf("Setting RGB(%d, %d, %d)\n", red, green, blue);
    redValue = red;
    greenValue = green;
    blueValue = blue;
    analogWrite(RED_PIN, redValue);
    analogWrite(GREEN_PIN, greenValue);
    analogWrite(BLUE_PIN, blueValue);
}


void sendValue()
{

    StaticJsonBuffer<64> jsonBuffer;
    JsonObject &data = jsonBuffer.createObject();
    data["r"] = redValue;
    data["g"] = greenValue;
    data["b"] = blueValue;

    sendMessage(MSG_STATUS, data);
}

bool handleMessage(uint32_t messageId, JsonObject &header, JsonObject &data)
{
    //Messages from platform reaches here

    DEBUG_PORT.println("Handling message");

    bool acked = false;

    switch (messageId)
    {
    case CMD_100:
        acked = data.containsKey("r") && data["r"].is<uint8_t>();
        acked = acked && data.containsKey("g") && data["b"].is<uint8_t>();
        acked = acked && data.containsKey("b") && data["b"].is<uint8_t>();
        if(acked){
            setValue(data["r"], data["g"], data["b"]);
        }
        break;
    }

    return acked;
}

bool handleData(byte *data)
{
    DEBUG_PORT.println("Handling data");
    
    return true;
}

#endif //IMPL_RGB_LED
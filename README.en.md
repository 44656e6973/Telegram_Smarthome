# Smart temperature and humidity controller with Telegram bot

The project allows you to remotely control the relay and monitor the readings of temperature/humidity sensors via Telegram bot. Supports several DS18B20 and DHT22 sensors.

## Features
- Relay control via Telegram commands
- Temperature monitoring from 3 sensors:
- DHT22 (temperature + humidity)
- Two DS18B20 (thermometers)
- Automatic data sending to group chat
- Interactive control menu
- Auto reboot in case of Wi-Fi problems

## Required components
- ESP8266/ESP32 board
- Relay module
- DHT22 sensor
- DS18B20 sensors (2 pcs)
- Libraries:
- FastBot
- OneWire
- DallasTemperature
- DHT Sensor Library
- Adafruit Unified Sensor

## Connection diagram

- Component - Pin
- Relay - 14
- DHT22 - 5
- DS18B20 - (Onewire) 4

## Installation
1. Install the necessary libraries via Arduino IDE Library Manager
2. Copy the code to Arduino IDE
3. Fill in the settings in the `#define` section:
```cpp
#define WIFI_SSID "Your_SSID"
#define WIFI_PASS "Your_password"
#define BOT_TOKEN "Bot_token"
#define CHAT_ID "Chat_ID"
#define ADMIN_ID "Admin_ID"
#define GROUP_ID "Group_ID"
```
## Links to libraries
- DallasTemperature - https://github.com/milesburton/Arduino-Temperature-Control-Library
- DHT - https://github.com/adafruit/DHT-sensor-library
- FastBot - https://github.com/GyverLibs/FastBot

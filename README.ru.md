# Умный контроллер температуры и влажности с Telegram-ботом

Проект позволяет удалённо управлять реле и мониторить показания датчиков температуры/влажности через Telegram-бота. Поддерживает несколько датчиков DS18B20 и DHT22.

## Особенности
- Управление реле через Telegram-команды
- Мониторинг температуры с 3х датчиков:
  - DHT22 (температура + влажность)
  - Два DS18B20 (термометры)
- Автоматическая отправка данных в групповой чат
- Интерактивное меню управления
- Автоперезагрузка при проблемах с Wi-Fi

## Требуемые компоненты
- Плата ESP8266/ESP32
- Релейный модуль
- Датчик DHT22
- Датчики DS18B20 (2 шт)
- Библиотеки:
  - FastBot
  - OneWire
  - DallasTemperature
  - DHT Sensor Library
  - Adafruit Unified Sensor

## Схема подключения

- Компонент - Пин
  - Реле - 14
  - DHT22 - 5
  - DS18B20 - (Onewire)	4

## Установка
1. Установите необходимые библиотеки через Arduino IDE Library Manager
2. Скопируйте код в Arduino IDE
3. Заполните настройки в секции `#define`:
```cpp
#define WIFI_SSID "Ваш_SSID"
#define WIFI_PASS "Ваш_пароль"
#define BOT_TOKEN "Токен_бота"
#define CHAT_ID "ID_чата"
#define ADMIN_ID "ID_админа"
#define GROUP_ID "ID_группы"
```
## Ссылки на библиотеки
- DallasTemperature - https://github.com/milesburton/Arduino-Temperature-Control-Library
- DHT - https://github.com/adafruit/DHT-sensor-library
- FastBot - https://github.com/GyverLibs/FastBot

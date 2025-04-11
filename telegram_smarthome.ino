#include <FastBot.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE DHT22  
#define UPDATE_SENSOR_PERIOD 1000
#define RELAY_IN 14
#define WIFI_SSID "Your WiFi SSID"
#define WIFI_PASS "Your WiFi Password"
#define BOT_TOKEN "Your Bot Token"
#define CHAT_ID "Users Telegram IDs"
#define ADMIN_ID "Admin ID"
#define GROUP_ID "Group Id"
#define ONE_WIRE_BUS 4
#define DHT_PIN 5
#define TEMPERATURE_PRECISION 9
#define ASTRA_INPUT 0

int dispTemp, dispHum;
bool RFlag = false;
int32_t menuID = 0;
uint32_t tmr1, tmr2;
uint32_t startUnix;  
byte depth = 0;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
float tempC;


FastBot bot(BOT_TOKEN);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DHT_Unified dht(DHT_PIN, DHTTYPE);
DeviceAddress first_Thremometer, second_Thremometer;

void connectWiFi() {
  delay(2000);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (millis() > 15000) ESP.restart();
  }

  
}
void printData(DeviceAddress deviceAddress)
{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress);
  Serial.println();
}

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void printTemperature(DeviceAddress deviceAddress)
{
  tempC = sensors.getTempC(deviceAddress);
  if(tempC == DEVICE_DISCONNECTED_C) 
  {
    Serial.println("Error: Could not read temperature data");
    return;
  }
  Serial.print("Temp C: ");
  Serial.print(tempC);
}
  
void newMsg(FB_msg& msg) {
  Serial.println(msg.toString());
  bot.sendMessage(String(msg.toString()), GROUP_ID);
  if (msg.unix < startUnix) return;
  if (msg.data == "Enable") {
    digitalWrite(RELAY_IN, HIGH);
    RFlag = true;
    depth = 1;
  }
  if (msg.data == "Disable") {
    digitalWrite(RELAY_IN, LOW);
    RFlag = false;
    depth = 1;
  }
  if (msg.data == "TEMP1") {
    bot.sendMessage(String("Temperature:") + String(dispTemp), msg.chatID);
    bot.sendMessage(String("HUD:") + String(dispHum), msg.chatID);
    depth = 0;
  }
  if (msg.data == "Temp2") {
    tempC = sensors.getTempC(first_Thremometer);
    bot.sendMessage(String("Temperature:") + String(tempC), msg.chatID);
    depth = 0;
  } 
  if (msg.data == "Temp3") {
    tempC = sensors.getTempC(first_Thremometer);
    bot.sendMessage(String("Temperature:") + String(tempC), msg.chatID);
    depth = 0;
  } 

  if (msg.text == "/menu") {
    String menu1 = F("Enable \t Disable \t TEMP2 \n Temp ");
    bot.inlineMenu("Menu", menu1, msg.chatID);
    menuID = bot.lastBotMsg();    // запомнили ID сообщения с меню
  }

}
void Temp_And_Hum(){
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    dispTemp = event.temperature;
  }
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    dispHum = event.relative_humidity;
  }
  }
void setup() {

  if (!sensors.getAddress(first_Thremometer, 0)) Serial.println("Unable to find address for Device 0");
  if (!sensors.getAddress(second_Thremometer, 1)) Serial.println("Unable to find address for Device 1");
  connectWiFi();
  sensors.begin();
  startUnix = bot.getUnix();
  menuID = bot.lastBotMsg();
  bot.setChatID(CHAT_ID);
  bot.attach(newMsg);
  String menu1 = F("Enable \t Disable \n TEMP1 \t Temp2 \t TEMP3");
  bot.inlineMenu("Second_floor", menu1);
  dht.begin();
  sensors.setResolution(first_Thremometer, TEMPERATURE_PRECISION);
  sensors.setResolution(second_Thremometer, TEMPERATURE_PRECISION);
  Serial.print("Device 1 Address: ");
  printAddress(second_Thremometer);
  Serial.println();


  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(first_Thremometer), DEC);
  Serial.println();

  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices."); 
}
void loop() {
  if (millis() - tmr1 >= UPDATE_SENSOR_PERIOD) {
    sensors.requestTemperatures();
    Temp_And_Hum(); 
  }
    bot.tickManual();
  }

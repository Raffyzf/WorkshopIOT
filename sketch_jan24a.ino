#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
DHT dht(DHTPIN, DHTTYPE);
int M,sensor_analog;
const int sensor_pin = 34;
const char* ssid = "rifaa";
const char* password = "123456789";
#define CHAT_ID "1029670858"
#define BOTtoken "6739883042:AAEOWXgJzht65bkL7di-vPUtAwnlBb7lwEU"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
   }

  Serial.print("");
  Serial.println("WiFi connected");
  Serial.print("IP address");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Tunggu dulu...monitoring akan segera dimulai", "");

  delay(2000);
  Serial.print("Workshop Monitoring Tanaman SMKN7 Baleendah\n");
  dht.begin();
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.print("Workshop Monitoring Tanaman SMKN7 Baleendah\n");
  dht.begin();
}
void loop() {
  sensor_analog = analogRead(sensor_pin);
  M = (100 - ((sensor_analog/4095.00) * 100));
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.println("Sensor tidak terbaca!");
  if (isnan(h) || isnan(t) || isnan(M)) {
    Serial.println("Sensor tidak terbaca!");
    return;
  }
  Serial.print("========Monitoring Tanaman========\n");
  Serial.print("Humiditas gas udara: ");
  Serial.print(h);
  Serial.println(" %");
  Serial.print("Temperatur lingkungan: ");
  Serial.print(t);
  Serial.println(" °C");
  Serial.print("Kelembapan air tanah: ");
  Serial.print(M);
  Serial.println(" %");
  delay(2000);
}
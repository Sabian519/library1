#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "DHT.h"

#define DHTPIN D1

char ssid[] = "ZIBANHELM"; //nama wifi
char password[] = "10920367"; //password wifi
#define BOTtoken "6020879752:AAFDEbkLvA703-hayclpC5aPZozGCyiz6hI" //token bot telegram
#define idChat "5521674753" //idbot

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  dht.begin();
  delay(5000);
}

void loop() {
  delay(2000);
  
  float t = dht.readTemperature();
  Serial.print("Suhu saat ini : ");
  Serial.print(t);
  Serial.println(" *C");

  float h = dht.readHumidity();
  Serial.print("Kelembaban saat ini : ");
  Serial.print(h);
  Serial.println(" *%");
  
  if (t > 30.00) {
    bot.sendChatAction(idChat, "Sedang mengetik...");
    Serial.print("Suhu saat ini : ");
    Serial.println(t);
    delay(3000);

  if (h > 30.00) {
    bot.sendChatAction(idChat, "Sedang mengetik...");
    Serial.print("Kelembaban saat ini : ");
    Serial.println(h);
    delay(3000);

    String suhu = "Intensitas suhu : ";
    suhu += int(t);
    suhu += " *C\n";
    suhu += "Suhu maksimal !\n";
    bot.sendMessage(idChat, suhu, "");
    Serial.print("Mengirim data sensor ke telegram");
  }
}

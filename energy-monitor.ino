#include <Arduino.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "example.firebaseio.com"
#define FIREBASE_AUTH "token_or_secret"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"


void setup() {
  Serial.begin(115200);
  //Conexão com o WIFI
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("\n connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(250);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int power = 0;
float current = 0.1f;

void loop() {
  DynamicJsonBuffer buffer;
  JsonObject& root = buffer.createObject();
  root["place"] = "sala";
  root["hardware"] = "televisao";
  root["current"] = current;
  root["power"] = power;

  JsonObject& sensorTime = root.createNestedObject("timestamp");
  sensorTime[".sv"] = "timestamp";

  Firebase.push("sensors", root);

  power += 1;
  current += 0.1f;

  delay(10000);
}

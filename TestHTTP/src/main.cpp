#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "{your-ssid}";
const char* password = "{your-password}";
const char* serverIP = "{your-server-ip}";
const char* path = "/";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    http.begin(serverIP, 80, path);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.println("Error on HTTP request");
    }

    http.end();
  }

  delay(500);
}
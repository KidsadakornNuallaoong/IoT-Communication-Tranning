#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "{User}";
const char* password = "{Pass}";
String serverIP = "http://localhost:3000/about";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverIP);
    int httpCode = http.GET();
    if(httpCode > 0) {
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
    } else {
      Serial.println("Error on HTTP request");
    }
    http.end();
  }
  delay(500); // Wait for 5 seconds before making the next request
}

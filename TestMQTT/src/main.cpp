#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "{your-ssid}";
const char* password = "{your-password}";

const char* mqtt_server = "{mqtt-server-ip}";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");

    }
    Serial.println("Connected to WiFi");
    
    client.setServer(mqtt_server, mqtt_port);
    
    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");
        if (client.connect("ESP32Client")) {
            Serial.println("Connected to MQTT");

        } else {
            Serial.print("Failed with state ");
            Serial.print(client.state());
            delay(200);

        }
    }
}

void loop() {
    if (!client.connected()) {
        setup();
    }
    
    client.publish("esp32/output", "Hello from ESP32");
    delay(500);
}
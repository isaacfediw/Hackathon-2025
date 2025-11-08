#include <Arduino.h>
#include <ESP8266WiFi.h>
extern "C" {
#include <espnow.h>
}

#define MOSFET_PIN D1  // adjust if your MOSFET is wired to another GPIO

void onDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
    if (len < sizeof(bool)) {
        Serial.println("Received payload too small");
        return;
    }

    bool state = incomingData[0];
    Serial.print("Received: ");
    Serial.println(state);

    digitalWrite(MOSFET_PIN, state ? HIGH : LOW);
}

void setup() {
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();  // ensure station mode is not connected

    pinMode(MOSFET_PIN, OUTPUT);
    digitalWrite(MOSFET_PIN, LOW);

    if (esp_now_init() != 0) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    esp_now_register_recv_cb(onDataRecv);
}

void loop() {}

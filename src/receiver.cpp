#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#define MOSFET_PIN GPIO_NUM_26

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    if (len < sizeof(bool)) {
        Serial.println("Received payload too small");
        return;
    }

    bool state = incomingData[0];
    Serial.print("Received: ");
    Serial.println(state);

    digitalWrite(MOSFET_PIN, state ? HIGH : LOW);

    if (state) delay(2000);
}

void setup() {
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();  // ensure station mode is not connected

    pinMode(MOSFET_PIN, OUTPUT);
    digitalWrite(MOSFET_PIN, LOW);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_recv_cb(onDataRecv);
}

void loop() {}

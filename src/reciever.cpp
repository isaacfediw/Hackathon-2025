#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
    Serial.print("Received: ");
    Serial.println(*(bool *)data);
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {}
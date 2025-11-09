#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

#define BUTTON_PIN D4

bool bool_value;
uint8_t recieverAddress[] = {0x8C, 0x4F, 0x00, 0x2F, 0x6F, 0xE0};

void onDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
    Serial.print("Last Packet Send Status: ");
    Serial.println(sendStatus == 0 ? "Delivery Success" : "Delivery Fail");
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    if (esp_now_init() != 0) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_register_send_cb(onDataSent);

    if (esp_now_add_peer(recieverAddress, ESP_NOW_ROLE_SLAVE, 0, NULL, 0) != 0) {
        Serial.println("Failed to add peer");
        return;
    }
}

void loop() {
    bool_value = digitalRead(BUTTON_PIN) == LOW;
    int result = esp_now_send(recieverAddress, (uint8_t *)&bool_value, sizeof(bool));

    if (result == 0) {
        Serial.print("Sent: ");
        Serial.println(bool_value);
    } else {
        Serial.println("Error sending the data");
    }
    delay(200);
}
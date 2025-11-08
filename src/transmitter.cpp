#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#define BUTTON_PIN GPIO_NUM_26

bool bool_value;
uint8_t recieverAddress[] = {0xAC, 0x0B, 0xFB, 0xD0, 0x65, 0xD6};

esp_now_peer_info_t peerInfo;

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_send_cb([](const uint8_t *mac_addr, esp_now_send_status_t status) {
        Serial.print("Last Packet Send Status: ");
        Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
    });

    memcpy(peerInfo.peer_addr, recieverAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
}

void loop() {
    bool_value = digitalRead(BUTTON_PIN) == LOW ? true : false;
    esp_err_t result = esp_now_send(recieverAddress, (uint8_t *) &bool_value, sizeof(bool));

    if (result == ESP_OK) {
        Serial.print("Sent: ");
        Serial.println(bool_value);
    } else {
        Serial.println("Error sending the data");
    }
}
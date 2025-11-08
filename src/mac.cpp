#include "Wifi.h"

// upload and run this code on an ESP32 to get its MAC address

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_MODE_STA);
    Serial.println("MAC Adress: " + WiFi.macAddress());
}

void loop() {}
#include <WiFi.h>
#include "config.h"

WiFiClient wifi_client;

void conn_wifi(char *ssid, char *password) {
  Serial.print("Connecting to WiFi..");
  WiFi.begin(ssid, password); // 기입한 정보로 WiFi 통신 시작
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nWiFi Connected");
}

void setup() {
  Serial.begin(115200);
  conn_wifi(WIFI_SSID, WIFI_PASSWD);
  
}

void loop() {}

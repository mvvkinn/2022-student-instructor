#include <WiFi.h>
#include <PubSubClient.h>
#include <PubSubClientTools.h>
#include <ArduinoJson.h>
#include "config.h"

WiFiClient wifi_client;
PubSubClient client(wifi_client);
PubSubClientTools mqtt(client);

void conn_wifi(char *ssid, char *password) {
  Serial.print("Connecting to WiFi");

  WiFi.begin(ssid, password); // 기입한 정보로 WiFi 통신 시작
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nWiFi Connected");
}

void mqtt_conn(char *mqtt_server, int mqtt_port) {
  // Connect to MQTT when not connected
  client.setServer(mqtt_server, mqtt_port);
  Serial.print("Connecting to MQTT");
  while (!client.connected())
  {
    Serial.print(".");

    if (client.connect("wifi_client"))
    {
      Serial.println("\nConnected to MQTT");

      mqtt.subscribe("ex", message_callback);
    }
    else
    {
      Serial.print("Error > Failed with state ");
      Serial.println(client.state());

      delay(2000);
    }
  }
  mqtt.publish("ex", "Subscribed");
}

void message_callback(String topic, String message)
{
  Serial.println(topic + " : " + message);
}

void setup() {
  Serial.begin(115200);
  conn_wifi(WIFI_SSID, WIFI_PASSWD);

  mqtt_conn(MQTT_HOST, MQTT_PORT);

  String json_data;

  StaticJsonDocument<256> doc;

  doc["id"] = 1;
  doc["isTrue"] = true;

  JsonObject sensor = doc.createNestedObject("sensor");
  sensor["touch"] = touchRead(T0);

  serializeJson(doc, json_data);

  mqtt.publish("ex", json_data);

}

void loop() {
  client.loop();
}

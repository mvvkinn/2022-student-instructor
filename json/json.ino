#include <ArduinoJson.h>

void setup() {
  String json_data;

  StaticJsonDocument<256> doc;

  doc["id"] = 1;
  doc["isTrue"] = true;

  JsonObject sensor = doc.createNestedObject("sensor");
  sensor["touch"] = touchRead(T0);

  serializeJson(doc, json_data);
}

void loop() {
  // put your main code here, to run repeatedly:

}

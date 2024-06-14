#include "device.h"
#include <ArduinoJson.h>

JsonDocument jsdoc;
JsonArray Devices = jsdoc.createNestedArray("devices");

void register_device (String name, uint8_t pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  JsonObject device = Devices.createNestedObject();
  device["name"] = name;
  device["pin"] = String(pin);
  device["high"] = (digitalRead(pin) == HIGH) ? true : false;
}

void device_handler() {
  String serialized_json;
  serializeJson(jsdoc, serialized_json);
  server.send(200, "application/json", serialized_json);
}

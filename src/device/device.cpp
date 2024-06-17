#include "device.h"
#include <ArduinoJson.h>

JsonDocument jsdoc;
JsonArray Devices = jsdoc.createNestedArray("devices");


void register_device (char* name, int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  JsonObject device = Devices.createNestedObject();
  device["name"] = name;
  device["pin"] = String(pin);
  device["high"] = true;
}

void device_handler() {
  for (int i = 0; i < Devices.size(); i++) {
    JsonObject current_device = Devices[i];

    current_device["high"] = (digitalRead(atoi(current_device["pin"]))) ? true : false;
  }
  String serialized_json;
  serializeJson(jsdoc, serialized_json);
  server.send(200, "application/json", serialized_json);
}

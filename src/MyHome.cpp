#include "MyHome.h"
#include "device/device.h"
#include "server/server.h"
#include "handlers/handlers.h"


void MyHome::register_pin(char* name, int pin) {
  register_device(name, pin);
}

void MyHome::begin() {
  server.on("/", root);
  server.on("/style.css", stylesheet);
  server.on("/script.js", javascript);
  server.on("/devices", device_handler);
  server.on("/flipstatus", flip_pin_status);

  server.begin();
}


void MyHome::handle() {
  server.handleClient();
}

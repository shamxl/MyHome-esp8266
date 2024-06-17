#ifndef DEVICE_H
#define DEVICE_H

#include <ESP8266WebServer.h>

extern ESP8266WebServer server;

void device_handler();
void register_device(char* name, int pin);


#endif

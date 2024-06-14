#ifndef HANDLERS_H
#define HANDLERS_H

#include <ESP8266WebServer.h>


extern ESP8266WebServer server;

void stylesheet();
void javascript();
void root();
void flip_pin_status();

#endif

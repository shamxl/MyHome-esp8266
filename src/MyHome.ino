#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>

#include "handlers.h"
#include "device.h"

String SSID = "xxx";
String PASSWORD = "xxx";
char* APNAME = "ESP8266";
ESP8266WebServer server(80);

void setup () {
  Serial.begin(115200);
  
  delay(500);

  connect_to_wifi(SSID, PASSWORD);
  setup_ota(APNAME);
  server.on("/", root);
  server.on("/style.css", stylesheet);
  server.on("/script.js", javascript);
  server.on("/devices", device_handler);
  server.on("/flipstatus", flip_pin_status);
  register_device("built-in light 1", 2);
  register_device("built-in light 2", 16);
  

  server.begin();
}




void loop() {
  server.handleClient();
  yield();
  ArduinoOTA.handle();
}

void connect_to_wifi(String ssid, String password) {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Waiting for wifi");
    delay(500);
  }

  Serial.print("Connected to ");
  Serial.println(ssid);

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  

}

void setup_ota (char* apname) {
  ArduinoOTA.setHostname(apname);
  ArduinoOTA.begin();
}

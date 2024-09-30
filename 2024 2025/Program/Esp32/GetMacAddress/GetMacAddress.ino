#include <WiFi.h>
// #include <WiFiAP.h>
// #include <WiFiClient.h>
// #include <WiFiGeneric.h>
// #include <WiFiMulti.h>
// #include <WiFiSTA.h>
// #include <WiFiScan.h>
// #include <WiFiServer.h>
// #include <WiFiType.h>
// #include <WiFiUdp.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());

}

void loop() {
  // put your main code here, to run repeatedly:

}

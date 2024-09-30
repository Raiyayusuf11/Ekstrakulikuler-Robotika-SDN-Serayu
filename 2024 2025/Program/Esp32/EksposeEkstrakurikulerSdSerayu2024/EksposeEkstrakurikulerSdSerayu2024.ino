#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPL6KDg625lR"
#define BLYNK_TEMPLATE_NAME "Joystick SD Serayu 2024"
#define BLYNK_AUTH_TOKEN "hBTR8oAopVhzkObXWudxvXRxsu-aiYrs"

// Enter your Auth token
char auth[] = BLYNK_AUTH_TOKEN;

// Enter your WIFI SSID and password
char ssid[] = "Mama-Hotspot";
char pass[] = "mamacantik";

BLYNK_WRITE(V1) {
  if (param.asInt() == 1) {
    Serial.println("Maju");
  } else {
    Serial.println("Stop");
  }
}

BLYNK_WRITE(V2) {
  if (param.asInt() == 1) {
    Serial.println("Mundur");
  } else {
    Serial.println("Stop");
  }
}

BLYNK_WRITE(V3) {
  if (param.asInt() == 1) {
    Serial.println("Kanan");
  } else {
    Serial.println("Stop");
  }
}

BLYNK_WRITE(V4) {
  if (param.asInt() == 1) {
    Serial.println("Kiri");
  } else {
    Serial.println("Stop");
  }
}

void setup() {
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  Blynk.run();
}

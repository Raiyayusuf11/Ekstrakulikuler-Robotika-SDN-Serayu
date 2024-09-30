#define BLYNK_TEMPLATE_ID "TMPL6jRCtcpzE"
#define BLYNK_TEMPLATE_NAME "Joystick"
#define BLYNK_AUTH_TOKEN "Qvts5Eduhte-r1IAfSEDDcLak4TAPL1j"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Mama";
char pass[] = "cantikbgt";

BLYNK_WRITE(V0)
{
  int data = param.asInt(); 
  if (data == 1) {
    Serial.println("nyala");
  } else {
    Serial.println("mati");
  }
  Blynk.virtualWrite(V0, data);
} 

void setup()
{
  Serial.begin(9600);
  Serial.println("Ready");

  Blynk.begin(auth, ssid, pass);//Splash screen delay

}

void loop() 
{
  Blynk.run();
}

// coba oled

#include <Wire.h>

#include <Adafruit_SSD1306.h>
// #include <splash.h>

#include <Adafruit_GFX.h>
// #include <Adafruit_GrayOLED.h>
// #include <Adafruit_SPITFT.h>
// #include <Adafruit_SPITFT_Macros.h>
// #include <gfxfont.h>

// const int lebar = 128;
// const int tinggi = 64;
// const int reset = 4;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();

}

void loop() {
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(12, 15);
  oled.println("Halo Iyan");
  oled.display();

}

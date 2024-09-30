#include <Adafruit_SSD1306.h>
#include <splash.h>

#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>




// ------------------------------------initialization pins
// joystick (pin -> kiri|kanan)
int pinVrx[2] = {19, 4};
int pinVry[2] = {18, 16};
int pinSw[2] = {5, 17};

// button
int pinButton[8] = {12, 13, 14, 25, 26, 27, 32, 33};

// oled
int pinSda = 21, pinScl = 22;

// driver motor
int pinMotor[4] = {15, 2, 1, 23};
// int pinMotor1 = 15, pinMotor2 = 2;
// int pinMotor3 = 1, pinMotor4 = 23;

// ------------------------------------variables
// joystick
int nilaiXkiri, nilaiYkiri, nilaiSwkiri;
int nilaiXkanan, nilaiYkanan, nilaiSwkanan;

// oled
const int lebar = 128;
const int tinggi = 64;
const int reset = 4;

Adafruit_SSD1306 oled(lebar, tinggi, &Wire, reset);

void cekButton() {
  const char* buttonName[] = {"Bawah", "Kanan", "Atas", "Bulat", "Silang", "Kiri", "Segitiga", "Kotak"};

  for(int i = 0; i < 8; i++) {
    if(digitalRead(pinButton[i]) == HIGH) Serial.println(buttonName[i]);
  }
}

int test = 0;

void setup() {
  Serial.begin(9600);
  Serial.print("Ready bang!");

  for(int i = 0; i < 2; i++) {
   pinMode(pinVrx[i], INPUT); 
   pinMode(pinVry[i], INPUT);
   pinMode(pinSw[i], INPUT_PULLUP);
  }

  for(int i = 0; i < 8; i++) {
    pinMode(pinButton[i], INPUT_PULLUP);
  }

  // pinMode(pinSda, INPUT); 
  // pinMode(pinScl, INPUT);

  for(int i = 0; i < 4; i++) {
    pinMode(pinMotor[i], OUTPUT);
  }

  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();
  
}

void loop() {
  CekJoystick();
  // CekButton();
  MovementRobot();

  if (digitalRead(pinButton[0]) == LOW) {
    Serial.println("nyala");
  } else {
    Serial.println("Mati");
  }
  
  // oled.setTextSize(2);
  // oled.setTextColor(WHITE);
  // oled.setCursor(12, 15);
  // oled.println("Test");
  // oled.display();

  delay(100);
}


void CekButton() {
  if (digitalRead(pinButton[0]) == HIGH) {
    Serial.println("Bawah");
  }
  // if (digitalRead(pinButton[1]) == HIGH) {
  //   Serial.println("Kanan");
  // }
  // if (digitalRead(pinButton[2]) == HIGH) {
  //   Serial.println("Kiri");
  // }
  // if (digitalRead(pinButton[3]) == HIGH) {
  //   Serial.println("Bulat");
  // }
  // if (digitalRead(pinButton[4]) == HIGH) {
  //   Serial.println("Silang");
  // }
  // if (digitalRead(pinButton[5]) == HIGH) {
  //   Serial.println("Kotak");
  // }
  // if (digitalRead(pinButton[6]) == HIGH) {
  //   Serial.println("Segitiga");
  // }
  // if (digitalRead(pinButton[7]) == HIGH) {
  //   Serial.println("Atas");
  // }
}

void CekJoystick() {
  nilaiXkiri = map(analogRead(pinVrx[0]), 0, 1023, 0, 180);
  nilaiYkiri = map(analogRead(pinVry[0]), 0, 1023, 0, 180);
  nilaiSwkiri = digitalRead(pinSw[0]);

  nilaiXkanan = map(analogRead(pinVrx[1]), 0, 1023, 0, 180);
  nilaiYkanan = map(analogRead(pinVry[1]), 0, 1023, 0, 180);
  nilaiSwkanan = digitalRead(pinSw[1]);

  Serial.print("X2 : "); Serial.print(nilaiXkanan);
  Serial.print(" Y2 : "); Serial.print(nilaiYkanan);
  Serial.print(" SW2 : "); Serial.print(nilaiSwkanan);

  Serial.print(" X1 : "); Serial.print(nilaiXkiri);
  Serial.print(" Y1 : "); Serial.print(nilaiYkiri);
  Serial.print(" SW1 : "); Serial.print(nilaiSwkiri);

  if (nilaiXkanan == 720 && nilaiYkanan == 0) {
    Serial.print(" Kanan");
  } else if (nilaiXkanan == 0 && nilaiYkanan == 0) {
    Serial.print(" Kiri");
  }else if (nilaiSwkanan == 0) {
    Serial.print(" R3");
  }

  // if (nilaiXKiri == 720 && nilaiYkanan == 0) {
  //   Serial.print(" Kanan");
  // } else if (nilaiXkanan == 0 && nilaiYkanan == 0) {
  //   Serial.print(" Kiri");
  // }else if (nilaiSwkanan == 0) {
  //   Serial.print(" R3");
  // }

  Serial.println();
  delay(100);

}

void SetMotor(int motor1, int motor2, int motor3, int motor4) {
  digitalWrite(pinMotor[0], motor1); 
  digitalWrite(pinMotor[1], motor2);
  digitalWrite(pinMotor[2], motor4);
  digitalWrite(pinMotor[3], motor3);
}

void MovementRobot() {
  if(nilaiXkanan == 720 && nilaiYkanan == 0) {
    SetMotor(0,0,0,1);
  } else if(nilaiXkanan == 0 && nilaiYkanan == 0) {
    SetMotor(1,0,0,0);
  } else if (nilaiSwkanan == 0) {
    SetMotor(0,1,1,0);
    Serial.print("Maju");
  } else if (nilaiSwkiri == 0) {
    SetMotor(1,0,0,1);
    Serial.print("Mundur");
  }

  // if(nilaiXkanan == 720 && nilaiYkanan == 0) {
  //   SetMotor(0,0,0,1);
  // } else if(nilaiXkanan == 0 && nilaiYkanan == 0) {
  //   SetMotor(1,0,0,0);
  // } else if (nilaiSwkanan == 0) {
  //   SetMotor(0,1,1,0);
  //   Serial.print("Maju");
  // } else if (nilaiSwkiri == 0) {
  //   SetMotor(1,0,0,1);
  //   Serial.print("Mundur");
  // }
  
  // else if(nilaiXkiri == 720 && nilaiYkiri == 0) {
  //   SetMotor(1,0,0,0);
  // } else if(nilaiXkiri == 0 && nilaiYkiri == 0) {
  //   SetMotor(0,0,1,0);
  // } else if (nilaiSwkiri == 0) {
  //   SetMotor(1,0,1,0);
  // } 
  
  else {
    SetMotor(0,0,0,0);
  }
  delay(200);
}


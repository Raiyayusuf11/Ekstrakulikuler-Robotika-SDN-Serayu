#include <Servo.h>

Servo SERVO[2];
int Servo_Pin[2] = {5,3};
int sudut_ServoLengan = 0;
int sudut_ServoCapit = 0;
int status = 0;

int Pb_Pin[4] = {10, 11, 8, 9};
int PushButton[4];

bool state[4] = {1,1,1,1};

unsigned long currentMillis[4] = {0,0,0,0};
unsigned long previousMillis[4] = {0,0,0,0};
int interval[4] = {2,2,2,2};

int led_Pin = 7;
int delayLed = 150;

void setup() {
  Serial.begin(9600);
  Serial.println("Ready");

  for (int i = 0; i < 2; i++) {
    SERVO[i].attach(Servo_Pin[i]);
    SERVO[i].write(0);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(Pb_Pin[i], INPUT_PULLUP);
  }

  pinMode(led_Pin, OUTPUT);
  digitalWrite(led_Pin, HIGH); delay(delayLed);
  digitalWrite(led_Pin, LOW); delay(delayLed);
  digitalWrite(led_Pin, HIGH); delay(delayLed);
  digitalWrite(led_Pin, LOW); delay(500);
}

void loop() {
  Servo_PushButton();

  Serial.print("lengan "); 
  Serial.print(sudut_ServoLengan);
  Serial.print(" capit ");
  Serial.print(sudut_ServoCapit);
  Serial.print(" ");
  Serial.println(millis());
  digitalWrite(led_Pin, HIGH);
}

void Servo_PushButton() {
  for (int i = 0; i < 4; i++) {
    PushButton[i] = digitalRead(Pb_Pin[i]);
  }
// ------------------------------------------------------- 
// Servo Lengan
  if (PushButton[0] == 0) { 
    currentMillis[0] = millis();
    if (currentMillis[0] - previousMillis[0] >= interval[0]) {
      previousMillis[0] = currentMillis[0]; 
      SERVO[0].write(sudut_ServoLengan);
      sudut_ServoLengan++; 
      if (sudut_ServoLengan > 90) sudut_ServoLengan = 90;
    }
  } else previousMillis[0] = millis(); 
// -------------------------------------------------------
  if (PushButton[1] == 0) { 
    currentMillis[1] = millis();
    if (currentMillis[1] - previousMillis[1] >= interval[1]) {
      previousMillis[1] = currentMillis[1]; 
      SERVO[0].write(sudut_ServoLengan); 
      sudut_ServoLengan--; 
      if (sudut_ServoLengan < 0) sudut_ServoLengan = 0;
    }
  } else previousMillis[1] = millis(); 
// -------------------------------------------------------
// Servo Capit
  if (PushButton[2] == 0) { 
    currentMillis[2] = millis();
    if (currentMillis[2] - previousMillis[2] >= interval[2]) {
      previousMillis[2] = currentMillis[2]; 
      sudut_ServoCapit++; 
      SERVO[1].write(sudut_ServoCapit); 
      if (sudut_ServoCapit > 90) sudut_ServoCapit = 90; 
    }
  } else previousMillis[2] = millis(); 
// -------------------------------------------------------
  if (PushButton[3] == 0) { 
    currentMillis[3] = millis();
    if (currentMillis[3] - previousMillis[3] >= interval[3]) {
      previousMillis[3] = currentMillis[3]; 
      sudut_ServoCapit--; 
      SERVO[1].write(sudut_ServoCapit); 
      if (sudut_ServoCapit < 0) sudut_ServoCapit = 0; 
    }
  } else previousMillis[3] = millis(); 
}

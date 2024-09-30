#include <Servo.h>
Servo SERVO[2];

// ------------------------------- PINS
// joystick
#define vrx_Pin A0
#define vry_Pin A1
#define sw_Pin 12 

// push button
int pb_Pin[4] = {11, 10, 9, 8};

// driver motor
int motor_Pin[4] = {16, 17, 18, 19}; // out 1 2 3 4 

// servo
int servo_Pin[2] = {3, 5};

// led
int led_Pin = 7;

// ------------------------------- VARIABLES
// joystick
int nilaiX, nilaiY, nilaiSW;

// atur speed
int Speed = 255;
bool stateSpeed = true;
int counter = 1;

// push button
int Pb1, Pb2;
int counterPB1 = 1;
int counterPB2 = 1;
int Pb_Pin[4] = {10, 11, 8, 9};
int PushButton[4];

// servo
int sudut_ServoLengan = 0;
int sudut_ServoCapit = 0;
int status = 0;
bool state[4] = {1,1,1,1};
unsigned long currentMillis[4] = {0,0,0,0};
unsigned long previousMillis[4] = {0,0,0,0};
int interval[4] = {2,2,2,2};
int nilaiServo = 10;
int sudutKhususCapit = 80;

// led
int delayLed = 150;

void setup() {
  Serial.begin(9600);
  Serial.println("Bismillah Ready!");

  // led 
  pinMode(led_Pin, OUTPUT);

  // joystick
  pinMode(vrx_Pin, INPUT);
  pinMode(vry_Pin, INPUT);
  pinMode(sw_Pin, INPUT_PULLUP);

  // servo
  for (int i = 0; i < 2; i++) {
    SERVO[i].attach(servo_Pin[i]);
    SERVO[i].write(0);
  }
  
  // motor
  for (int i = 0; i < 6; i++) {
    pinMode(motor_Pin[i], OUTPUT);
  }

  // push button
  for (int i = 0; i < 4; i++) {
    pinMode(pb_Pin[i], INPUT_PULLUP);
  }

  Cek_Led();

}

void loop() {
  Cek_Joystick();
  Movement_Robot();
  // Gripper_Servo();
  Servo_Gripper();

  digitalWrite(led_Pin, HIGH); // set agar led nyala terus
  Serial.println();
}

void Cek_Joystick() {
  nilaiX = map(analogRead(vrx_Pin), 0, 1023, 0, 180);
  nilaiY = map(analogRead(vry_Pin), 0, 1023, 0, 180);
  nilaiSW = digitalRead(sw_Pin);

  Serial.print("X:"); Serial.print(nilaiX);
  Serial.print(" Y:"); Serial.print(nilaiY);
  Serial.print(" SW:"); Serial.print(nilaiSW);
  Serial.print(" ");

  if (nilaiX <= 90 && nilaiY == 180) Serial.print(" Kanan");
  else if (nilaiX <= 90 && nilaiY == 0) Serial.print(" Kiri");
  else if (nilaiX == 0 && nilaiY >= 90) Serial.print(" Atas");
  else if (nilaiX == 180 && nilaiY >= 90) Serial.print(" Bawah");
  else if (nilaiSW == 0) Serial.print("SW");
  
  // Serial.println();
  delay(100);
}

void Cek_Led() {
  digitalWrite(led_Pin, HIGH); delay(delayLed);
  digitalWrite(led_Pin, LOW); delay(delayLed);
  digitalWrite(led_Pin, HIGH); delay(delayLed);
  digitalWrite(led_Pin, LOW); delay(500);

  digitalWrite(led_Pin, HIGH); delay(delayLed);
  digitalWrite(led_Pin, LOW); delay(delayLed);
  digitalWrite(led_Pin, HIGH); delay(150);
  // digitalWrite(led_Pin, LOW); 
}

void Indikator_Led() {
  digitalWrite(led_Pin, LOW); delay(delayLed);
  digitalWrite(led_Pin, HIGH); delay(delayLed);
  digitalWrite(led_Pin, LOW); delay(delayLed);
  digitalWrite(led_Pin, HIGH); delay(delayLed);
}

void Atur_Speed() {
  if (nilaiSW == 0) {
    if (state) {
      stateSpeed = false;
      counter ++;
      if (counter > 3) {
        counter = 1;
      }
    }
  } else stateSpeed = true;
  
  if (counter == 1) Speed = 255;
  else if (counter == 2) Speed = 150;
  else if (counter == 3) Speed = 70;
}

void Set_Motor(int motor1, int motor2, int motor3, int motor4) { // default motor 1 2 3 4 
  Atur_Speed();
  int status_Motor[4] = {motor1, motor2, motor3, motor4};
  
  analogWrite(motor_Pin[4], Speed);
  analogWrite(motor_Pin[5], Speed);
  
  for (int i = 0; i < 4; i++) {
    digitalWrite(motor_Pin[0], status_Motor[i]);
  }
}

void Movement_Robot() {
  if (nilaiX <= 90 && nilaiY == 180) {
    Set_Motor(0, 0, 0, 1);       
    Serial.print(" Kanan");  // kanan
  }
  else if (nilaiX <= 90 && nilaiY == 0) {
    Set_Motor(0, 1, 0, 0);    
    Serial.print(" Kiri");   // kiri
  }
  else if (nilaiX == 0 && nilaiY >= 90) {
    Set_Motor(0, 1, 0, 1);    
    Serial.print(" Maju");   // maju
  }
  else if (nilaiX == 180 && nilaiY >= 90) {
    Set_Motor(1, 1, 0, 0);  
    Serial.print(" Mundur"); // mundur
  }
  else Set_Motor(0, 0, 0, 0);
  delay(100);

  // if (nilaiX <= 90 && nilaiY == 180) {
  //   Set_Motor(0, 0, 0, 1);       
  //   Serial.print(" Kanan");  // kanan
  // }
  // else if (nilaiX <= 90 && nilaiY == 0) {
  //   Set_Motor(0, 1, 0, 0);    
  //   Serial.print(" Kiri");   // kiri
  // }
  // else if (nilaiX == 0 && nilaiY >= 90) {
  //   Set_Motor(0, 1, 0, 0);    
  //   Serial.print(" Maju");   // maju
  // }
  // else if (nilaiX == 180 && nilaiY >= 90) {
  //   Set_Motor(1, 0, 0, 0);  
  //   Serial.print(" Mundur"); // mundur
  // }
  // else Set_Motor(0, 0, 0, 0);
  // delay(100);

}

void Servo_Gripper() {
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
      sudut_ServoLengan += nilaiServo; 
      if (sudut_ServoLengan > 90) sudut_ServoLengan = 90;
    }
  } else previousMillis[0] = millis(); 
// -------------------------------------------------------
  if (PushButton[1] == 0) { 
    currentMillis[1] = millis();
    if (currentMillis[1] - previousMillis[1] >= interval[1]) {
      previousMillis[1] = currentMillis[1]; 
      SERVO[0].write(sudut_ServoLengan); 
      sudut_ServoLengan -= nilaiServo;
      if (sudut_ServoLengan < 0) sudut_ServoLengan = 0;
    }
  } else previousMillis[1] = millis(); 
// -------------------------------------------------------
// Servo Capit
  if (PushButton[2] == 0) { 
    currentMillis[2] = millis();
    if (currentMillis[2] - previousMillis[2] >= interval[2]) {
      previousMillis[2] = currentMillis[2]; 
      sudut_ServoCapit += nilaiServo;
      SERVO[1].write(sudut_ServoCapit); 
      if (sudut_ServoCapit > 80) sudut_ServoCapit = 80; 
    }
  } else previousMillis[2] = millis(); 
// -------------------------------------------------------
  if (PushButton[3] == 0) { 
    currentMillis[3] = millis();
    if (currentMillis[3] - previousMillis[3] >= interval[3]) {
      previousMillis[3] = currentMillis[3]; 
      sudut_ServoCapit -= nilaiServo;
      SERVO[1].write(sudut_ServoCapit); 
      if (sudut_ServoCapit < 30) sudut_ServoCapit = 30; 
    }
  } else previousMillis[3] = millis(); 
  

  // if (PushButton[0] == 0) {
  //   if (stateSpeed) {
  //     stateSpeed = false;
  //     SERVO[0].write(90);
  //   }
  // } else stateSpeed = true;
  // if (PushButton[1] == 0) {
  //   if (stateSpeed) {
  //     stateSpeed = false;
  //     SERVO[0].write(0);
  //   }
  // } else stateSpeed = true;
  // // -------------------------------
  // if (PushButton[2] == 0) {
  //   if (stateSpeed) {
  //     stateSpeed = false;
  //     SERVO[1].write(90);
  //   }
  // } else stateSpeed = true;
  //   if (PushButton[3] == 0) {
  //   if (stateSpeed) {
  //     stateSpeed = false;
  //     SERVO[1].write(0);
  //   }
  // } else stateSpeed = true;

  Serial.print(" Capit: "); Serial.print(sudut_ServoCapit);
  Serial.print(" Lengan: "); Serial.print(sudut_ServoLengan);
}

void Gripper_Servo() {
  Pb1 = digitalRead(pb_Pin[0]);
  Pb2 = digitalRead(pb_Pin[1]);

  if (Pb1 == 0) {
    if (stateSpeed) {
      stateSpeed = false;
      counterPB1++;
      if (counterPB1 > 2) {
        counterPB1 = 1;
      }
    }
  } else stateSpeed = true;

  if (Pb2 == 0) {
    if (stateSpeed) {
      stateSpeed = false;
      counterPB2++;
      if (counterPB2 > 2) {
        counterPB2 = 1;
      }
    }
  } else stateSpeed = true;

  // if (counterPB1 == 1) SERVO[0].write(90);
  // else if (counterPB1 == 2) SERVO[0].write(0);
  // if (counterPB2 == 1) SERVO[1].write(90);
  // else if (counterPB2 == 2) SERVO[1].write(0);

  SERVO[0].write(counterPB1 == 1 ? 90 : 0);
  SERVO[1].write(counterPB2 == 1 ? 90 : 0);

}

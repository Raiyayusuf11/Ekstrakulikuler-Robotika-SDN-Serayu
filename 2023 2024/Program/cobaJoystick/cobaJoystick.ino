// int vrx = A0, vry = A1, sw = 2;
int vrx = 32, vry = 33, sw = 25;
int nilaiX, nilaiY, nilaiSW;

void setup() {
  Serial.begin(9600);
  Serial.print("Ready Bang!");
  pinMode(vrx, INPUT);
  pinMode(vry, INPUT);
  pinMode(sw, INPUT_PULLUP);
}

// Joystick Kanan
// Atas, Y < 90
// Bawah, Y > 90
// Kanan, X > 90
// Kiri, X < 90

// Joystick Kiri 
// Atas, Y > 90
// Bawah, Y < 90
// Kanan, X < 90
// Kiri, X > 90

void loop() {
  nilaiX = map(analogRead(vrx), 0, 1023, 0, 180);
  nilaiY = map(analogRead(vry), 0, 1023, 0, 180);
  // nilaiX = analogRead(vrx);
  // nilaiY = analogRead(vry);
  nilaiSW = digitalRead(sw);

  Serial.print("X : ");
  Serial.print(nilaiX);
  Serial.print(" Y : ");
  Serial.print(nilaiY);
  Serial.print(" SW : ");
  Serial.print(nilaiSW);
  
  if(nilaiY < 90){
    Serial.print(" Atas");
  // } else if(nilaiY == 720){
  //   Serial.print(" Bawah");
  }else if(nilaiX == 720){
    Serial.print(" Kanan");
  } else if(nilaiX == 0){
    Serial.print(" Kiri");
  }
  // if (nilaiX < 90) {
  //   Serial.print(" | Left");
  // } else if (nilaiX > 120) {
  //   Serial.print(" | Right");
  // }

  // if (nilaiY < 90) {
  //   Serial.print(" | Up");
  // } else if (nilaiY > 120) {
  //   Serial.print(" | Down");
  // }

  Serial.println();
  
  delay(100); // Delay untuk kestabilan
}

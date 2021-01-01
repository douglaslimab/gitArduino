//------------------------------------------------------
//  Name: Motor Controller  Date Created: 14/12/2020
//  Author: Douglas Lima    Date Modified: 28/12/2020
//  Board: Elego Arduino Mega
//------------------------------------------------------
//  Description: The board receives a package of 4 bytes
//               from the UART. The first byte indicates
//               which motor and the last 3 bytes sets
//               the motor speed.
//------------------------------------------------------
//  Devices:  Arduino Motor Shield
//            Motor dc
//            Encoder
//------------------------------------------------------
//Free Pins / A2 A3 A4 A5 / D0 D1

//Motor Shield Pins-------------------------------------
const int dirA = 12;
const int dirB = 13;
const int pwmA = 10;
const int pwmB = 11;
const int brkA = 9;
const int brkB = 8;
const int sns0 = A0;
const int sns1 = A1;

const int speaker = 4;

//Encoders----------------------------------------------
const int hallA1 = 2;
//const int hallA2 = 4;
const int hallB1 = 3;
const int hallB2 = 5;

//Motor Data--------------------------------------------
int speedSetup;
int speedA = 0;
int speedB = 0;
int instSpeedA = 0;
int instSpeedB = 0;
char dataPack[5];

//Time Control------------------------------------------
unsigned long currentMillis;
long previousMillis = 0;
long previousMillis2 = 0;
long previousMillis3 = 0;
float loopTime = 10;

//Encoder Counters--------------------------------------
volatile int cntrA = 0;
volatile int cntrB = 0;

void setup() {
  attachInterrupt(digitalPinToInterrupt (hallA1), ISR_countA, RISING);
  attachInterrupt(digitalPinToInterrupt (hallB1), ISR_countB, RISING);
  
  Serial.begin(9600);
    
  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(brkA, OUTPUT);
  pinMode(brkB, OUTPUT);
  pinMode(speaker, OUTPUT);

  pinMode(hallA1, INPUT);
  pinMode(hallB1, INPUT);

  pinMode(sns0, INPUT);
  pinMode(sns1, INPUT);

  digitalWrite(brkA, LOW);
  digitalWrite(brkB, LOW);

  buzz(2);
}

void loop() {
  currentMillis = millis();

//Receive Serial Data Package------------------------------------------------------------------------  
  if (currentMillis - previousMillis >= loopTime) {
    previousMillis = currentMillis;

    if (Serial.available()) {      
      for (int i = 0; i < 5; i++) {
        dataPack[i] = Serial.read();
        delay(5);
      }
      speedSetup = 100 * (dataPack[1] - '0') + 10 * (dataPack[2] - '0') + (dataPack[3] - '0');
    }
    
    execute();
  }
  
//Show Speed wheels status---------------------------------------------------------------------------
  if (currentMillis - previousMillis2 >= 1000){
    previousMillis2 = currentMillis;
    Serial.print("Set Speed: ");
    Serial.println(speedSetup);
    
    Serial.print("Set A: ");
    Serial.print(speedA);
    Serial.print(" | Speed A: ");
    Serial.println(instSpeedA);
    
    Serial.print("Set B: ");
    Serial.print(speedB);
    Serial.print(" | Speed B: ");
    Serial.println(instSpeedB);
  }
  
//Encoders Check-------------------------------------------------------------------------------------
  if (currentMillis - previousMillis3 >= 40){
    previousMillis3 = currentMillis;
    instSpeedA = cntrA;
    cntrA = 0;
    instSpeedB = cntrB;
    cntrB = 0;
  }
}

void  execute() {
  switch (dataPack[0]) {
    case 'a':
      digitalWrite(dirA, HIGH);
      increaseSpeedA(speedSetup);
      break;
    case 'b':
      digitalWrite(dirA, LOW);
      increaseSpeedA(speedSetup);
      break;
    case 'c':
      digitalWrite(dirB, HIGH);
      increaseSpeedB(speedSetup);
      break;
    case 'd':
      digitalWrite(dirB, LOW);
      increaseSpeedA(speedSetup);
      break;
    case 'q':
      dataPack[0] = 'Q';
      speedSetup = 0;
      speedA = 0;
      speedB = 0;
      digitalWrite(brkA, LOW);
      analogWrite(pwmA, speedSetup);
      digitalWrite(brkB, LOW);
      analogWrite(pwmB, speedSetup);
      Serial.println("STOP!!!");
      break;
  }
}

//Adjust Speed Motor A--------------------------------
void increaseSpeedA(int speedSetup()){
  if(instSpeedA < speedSetup){
    speedA++;
  } else if(instSpeedA > speedSetup){
    speedA--;
  }
  analogWrite(pwmA, speedA);
}

//Adjust Speed Motor B--------------------------------
void increaseSpeedB(int speedSetup()){
  if(instSpeedB < speedSetup){
    speedB++;
  } else if(instSpeedB > speedSetup){
    speedB--;
  }
  analogWrite(pwmB, speedB);
}

//Read Speed Sensor Motor A--------------------------
void ISR_countA(){
  cntrA++;
}

//Read Speed Sensor Motor A--------------------------
void ISR_countB(){
  cntrB++;
}

void buzz(int f){
  int i = 0;
  for(i = 0; i < 50; i++){
    digitalWrite(speaker, HIGH);
    delay(f);
    digitalWrite(speaker, LOW);
    delay(f);
  }
}

const int led1 = 9;
const int led2 = 10;
const int led3 = 11;
const int led4 = 12;
const int btn = 8;

boolean spin = false;
int aux = 1;
long int spd;
float le;

void setup() {
  Serial.begin(9600);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(btn, INPUT);
  pinMode(A0, INPUT);
}

void loop() {
  gira();
  setSpd();
  test();
}

void  gira(){
  switch(aux){
    case 1:
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    break;
    
    case 2:
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    break;
    
    case 3:
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    break;
    
    case 4:
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    break;
  }  
}

void  right(){  
  aux++;  
  if(aux == 5){
    aux = 1;
  }
}

void  left(){
  aux--;
  if (aux == 0){
    aux = 4;
  }
}

void  test(){
  if(digitalRead(btn) == HIGH){
    left();
  }else if(digitalRead(btn) == LOW){
    right();
  }
  delay(spd);
}

void  setSpd(){
  le = 10*analogRead(A0)/1023;
  spd = 35*le + 150;
  Serial.println(spd);
}

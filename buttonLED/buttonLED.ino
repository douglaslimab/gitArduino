const int led = 9;
const int btn = 8;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT);
}

void loop() {
  if(digitalRead(btn) == HIGH){
    digitalWrite(led, HIGH);
  } else if(digitalRead(btn) == LOW){
    digitalWrite(led, LOW);
  }
}

const int led = 9;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(166);
  digitalWrite(led, LOW);
  delay(166);
}

int rad=5;

void setup() {
  Serial.begin(9600);
}

void loop() {
    Serial.println(analogRead(rad)*255/1024);
    analogWrite(rad,analogRead(rad)*0.15);
}

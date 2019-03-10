#define pluie 23 //18

void setup() {
  pinMode(pluie, INPUT);
}


void loop() {
  if(!digitalRead(pluie)) {
    // Il pleut : Action à réaliser ici
  }
}

const int PIN=2;
int val=0;

void setup() {
  Serial.begin(9600);
  pinMode(PIN,INPUT);
}

void loop() {
  val=digitalRead(PIN);
  Serial.println(val);
  delay(200);
  
}

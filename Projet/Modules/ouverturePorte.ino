int porte = 2;
int val=0;
int etat=0;

void setup() {
  Serial.begin(9600);
  pinMode(porte,INPUT);
}

void loop() {
  val=digitalRead(porte);
  if(val==LOW){
    if (etat==0){
      delay(200); 
    } else {
      Serial.println("La porte a été fermée.");
      etat=0;
    }
  }
  else if(etat==0) {
    Serial.println("La porte a été ouverte !");
    etat=1;
  }
}

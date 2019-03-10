// Code ESP

#define R 5 //10
#define G 18 //11
#define B 19 //12

// Définition des constantes de ledcWrite (équivalent de analogWrite sur ESP)
const int freq = 5000;
const int ledR = 0;
const int ledG = 1;
const int ledB = 2;
const int resolution = 8;


// Définition des niveaux d'instensité des couleurs R, G, B
int rForce = 192;
int gForce = 0;
int bForce = 25;


void setup() {
  ledcSetup(ledR, freq, resolution);
  ledcSetup(ledG, freq, resolution);
  ledcSetup(ledB, freq, resolution);
  
  ledcAttachPin(R, ledR);
  ledcAttachPin(G, ledG);
  ledcAttachPin(B, ledB);
}


void loop() {
  ledcWrite(ledR, rForce);
  ledcWrite(ledG, gForce);
  ledcWrite(ledB, bForce);
}


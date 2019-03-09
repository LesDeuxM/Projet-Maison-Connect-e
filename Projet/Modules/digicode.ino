#include <Keypad.h>

const byte rows = 4; //quatre lignes
const byte cols = 4; //quatre colonnes
const String password = "7352B"; //mot de passe

//Vert=1 et Rouge=8
//8=PD37; 7=PD36 ...
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[rows] = {37,36,35,34}; //Lignes
byte colPins[cols] = {33,32,31,30}; //Colonnes

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );
  
void setup() {
  Serial.begin(9600); //Serial monitor
  Serial.println("Test de clavier 16 touches");
  
  keypad.setHoldTime(4); //Activer l'état HOLD
  keypad.setDebounceTime(4); //Anti rebond56.1
}

void loop() {
  String mdp = "";
  int i=0;
  while(i<5){
    char key = keypad.getKey();
    if (key != NO_KEY){
      Serial.println(key);
      mdp+=key;
      i++;
    }
  }
  if(mdp==password) Serial.println("Porte ouverte !");
  else Serial.println("Mauvais mot de passe");
}

#include <Keypad.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <dht11.h>


// Digicode      
const byte rows = 4; //quatre lignes
const byte cols = 4; //quatre colonnes
char password[6] = "7352B"; //mot de passe
char mdp[6] = "";
int i_digi=0;
char keys[cols][rows] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[rows] = {4, 7, 8, A4}; 
byte colPins[cols] = {10, 11, 12, 13}; 
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );


// Servo
Servo servo;


// Transmition ESP
SoftwareSerial mySerial(3, A5); // RX, TX 


// Variables
String cle="";
String oldKey="";
int contenu;
int oldContent;
String recu="";
int porteStatus = 0;


// Buzzer
#define buzzer A0 // Borne de sortie
        
        
// Chauffage
#define ledPin 6


// Température
#define dhtPin A2
dht11 DHT11;
int tempObj = 0;
int tempAct = 0;


void setup() {
  // Ports série
  Serial.begin(9600);
  mySerial.begin(9600);

  
  // Digicode
  myKeypad.setHoldTime(4); 
  myKeypad.setDebounceTime(4); 


  // Buzzer  
  pinMode(buzzer,OUTPUT);
}


      

void loop() {

  // Température
  int chk = DHT11.read(dhtPin);
  tempAct = (int)DHT11.temperature - 3;
  if ((tempObj - tempAct) <= 0){
     analogWrite(ledPin, 0);
  }
  else if ((tempObj - tempAct) <= 1) {
    analogWrite(ledPin, 100);
  }
  else if ((tempObj - tempAct) <= 2) {
    analogWrite(ledPin, 150);
  }
  else if ((tempObj - tempAct) <= 3) {
    analogWrite(ledPin, 200);
  }
  else {
    analogWrite(ledPin, 255);
  }


  // Transmition ESP
  while (mySerial.available()){   
    recu += char(mySerial.read());
  }
  delay(50); //Delay : necéssaire pour finir de lire 7 caractères.
  
  if(recu!=""){
    //Serial.println(recu);
    cle = recu[0];
    contenu = recu.substring(1,4).toInt();//
    recu = "";
  }

  // Chauffage
  if(cle=="C" && oldContent!=contenu) {
    oldKey = cle;
    oldContent = contenu;
    //Serial.println(contenu);
    tempObj = contenu;
  }

  // Porte
  if(cle=="P" && oldContent!=contenu) {
    oldKey = cle;
    oldContent = contenu;
    //Serial.println(contenu);
    porteStatus = contenu;
    servo.attach(9);
    servo.write(porteStatus);
    delay(500);
    servo.detach();
  }

  
  // Digicode
  char key = myKeypad.getKey();
  if(key != 0) {
    if (i_digi<5) {
       mdp[i_digi] = key;  
       i_digi = i_digi+1 ;
       tone(buzzer,1000,100);
     }
     if (i_digi == 5) {
      if(strcmp(mdp,password) == 0) {
        tone(buzzer,200,500);
        delay(400);
        tone(buzzer,1000,100);
        //Serial.println("Porte ouverte !");
        i_digi=0;
        if (porteStatus == 90) {
          servo.attach(9);
          servo.write(0);
          delay(500);
          servo.detach();
          delay(9000);
          servo.attach(9);
          servo.write(90);
          delay(500);
          servo.detach();
        }
      }
      else {
        tone(buzzer,400,400);
        delay(600);
        tone(buzzer,400,400);
        delay(600);
        tone(buzzer,400,400);
        //Serial.println("Mauvais mot de passe");
        i_digi=0;
      }
     }
  }

}

// Import des librairies 
#include <SoftwareSerial.h>
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <HTTPClient.h>


// Identifiants de connexion à la base de donnée
#define FIREBASE_HOST "https://smarthouse-232d7.firebaseio.com/"
#define FIREBASE_AUTH "xxx"


// Identifiants de connexion au réseau Wifi
#define WIFI_SSID "Galaxy S9"
#define WIFI_PASSWORD "motdepasse"


// Définition des Pins
#define sonette 15 //4
#define ouvPorte 0 //6
#define ouvFenetre 4 //7
#define R 5 //10
#define G 18 //11
#define B 19 //12
#define ledSonette 21 //14
#define mvt 22 //17
#define pluie 23 //18


// Définition des constantes de ledcWrite (équivalent de analogWrite sur ESP)
const int freq = 5000;
const int ledR = 0;
const int ledG = 1;
const int ledB = 2;
const int resolution = 8;


// Définition des niveaux d'instensité des couleurs R, G, B
int rForce = 0;
int gForce = 0;
int bForce = 0;


// Défintion de la température souhaitée
int tempChauff = 0;
boolean etatChauff = false;


// Définition de l'état de l'ouverture de la porte
boolean porteStatus = false;


// Définition du pattern pour l'envoie d'une notification
const String key = "key=xxxxx";
const String contentNotifDebut = "{\"to\":\"xxxxx\",\"notification\":{\"title\":\"Smart House\"\"body\":\"";
const String contentNotifFin = "\"},\"priority\":\"high\",\"sound\":\"default\"}";


// Définition des variables permettant d'enregistrer les choix de l'utilisateur concernant les notifications
boolean sonetteStatus = true;
boolean alarmeStatus = true;
boolean pluieStatus = true;
boolean mvtStatus = true;


// Ouverture des ports RX = 16, TX = 17 (RX non utilisé)
SoftwareSerial liaison(16, 17);



void setup() {

  // Démarage des ports Serial
  Serial.begin(115200);
  liaison.begin(9600);


  // Setup de la LED RGB
  ledcSetup(ledR, freq, resolution);
  ledcSetup(ledG, freq, resolution);
  ledcSetup(ledB, freq, resolution);
  ledcAttachPin(R, ledR);
  ledcAttachPin(G, ledG);
  ledcAttachPin(B, ledB);
  

  // Défintion des I/O
  pinMode(sonette, INPUT);
  pinMode(pluie, INPUT);
  pinMode(ouvPorte, INPUT);
  pinMode(ouvFenetre, INPUT);
  pinMode(ledSonette, OUTPUT);
  digitalWrite(ledSonette, LOW);
  pinMode(mvt, INPUT);


  // Démarage du Wifi et attente de la connexion
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("Connected : ");
  Serial.println(WiFi.localIP());


  // Connexion à la base de donnée Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);


  // Récupération des entiers (0-255) définissant le niveau d'intensité de chaque couleur de la RGB
  JsonObject& rgbData = Firebase.get("/rgbSalon/");
  rForce = rgbData[String("R")].as<int>();
  gForce = rgbData[String("G")].as<int>();
  bForce = rgbData[String("B")].as<int>();


  // On allume ou pas la RGB en fonction des valeurs récupérées
  if(Firebase.getBool("/ledSalon")) {
    ledcWrite(ledR, rForce);
    ledcWrite(ledG, gForce);
    ledcWrite(ledB, bForce);
  }
  else {
    ledcWrite(ledR, 0);
    ledcWrite(ledG, 0);
    ledcWrite(ledB, 0);
  }


  //Récupération de l'état du chauffage
  tempChauff = Firebase.getInt("/chauffageAuto/temp");
  etatChauff = Firebase.getBool("/chauffageAuto/status");
  if(etatChauff) {
    liaison.println("C" + String(tempChauff));
  }


  //Récupération de l'état de la porte
  porteStatus = Firebase.getBool("/porte");
  if(porteStatus) {
    liaison.println("P000");
  }
  else {
    liaison.println("P090");
  }

  
  // Récupération des préférences de notification enregistées sur la base Firebase
  JsonObject& alerts = Firebase.get("/alertes/");
  sonetteStatus = alerts[String("sonette")].as<bool>();
  alarmeStatus = alerts[String("alarme")].as<bool>();
  pluieStatus = alerts[String("pluie")].as<bool>();
  mvtStatus = alerts[String("mouvement")].as<bool>();


  // On montre que l'initialisation est OK
  clignoterLED(1000, 0, 1);

  
  // Définition du Stream : Lorsqu'un valeur change dans la base de donnéee Firebase, on execute l'action en conséquence
  Firebase.stream("", [](FirebaseStream stream) {
    if (stream.getEvent() == "put") {
      if(stream.getPath() == "/porte") {
        porteStatus = stream.getDataBool();
        if (porteStatus) {
          // On ouvre la porte
          liaison.println("P000");
        }
        else {
          // On ferme la porte
          liaison.println("P090");
        } 
      }
      else if(stream.getPath() == "/chauffageAuto/temp") {
        // Température souhaitée changée : On envoie les infos à l'Arduino UNO
        tempChauff = stream.getDataInt();
        if(etatChauff) {
          liaison.println("C" + String(tempChauff));
        }
      }
      else if(stream.getPath() == "/chauffageAuto/status") {
        // Etat du chauffage changé : On envoie les infos à l'Arduino UNO
        etatChauff = stream.getDataBool();
        if(etatChauff) {
          liaison.println("C" + String(tempChauff));
        }
        else {
          liaison.println("C" + String("000"));
        }
      }
      else if(stream.getPath() == "/ledSalon") {
        if(stream.getDataBool()) {
          // On allume la LED avec les bons niveaux d'intensité
          ledcWrite(ledR, rForce);
          ledcWrite(ledG, gForce);
          ledcWrite(ledB, bForce);
        }
        else {
          // On éteint la LED
          ledcWrite(ledR, 0);
          ledcWrite(ledG, 0);
          ledcWrite(ledB, 0);
        }
      }
      else if(stream.getPath() == "/rgbSalon/R") {
        rForce = stream.getDataInt();
        ledcWrite(ledR, rForce);
      }
      else if(stream.getPath() == "/rgbSalon/G") {
        gForce = stream.getDataInt();
        ledcWrite(ledG, gForce);
      }
      else if(stream.getPath() == "/rgbSalon/B") {
        bForce = stream.getDataInt();
        ledcWrite(ledB, bForce);
      }
      else if(stream.getPath() == "/alertes/sonette") {
        sonetteStatus = stream.getDataBool();
      }
      else if(stream.getPath() == "/alertes/alarme") {
        alarmeStatus = stream.getDataBool();
      }
      else if(stream.getPath() == "/alertes/pluie") {
        pluieStatus = stream.getDataBool();
      }
      else if(stream.getPath() == "/alertes/mouvement") {
        mvtStatus = stream.getDataBool();
      }
    }
});
}


void loop() {
  if(!digitalRead(pluie)) {
    if(pluieStatus) {
      envoyerNotif("alertes/pluie", "Il pleut !");
      pluieStatus = false;
      Firebase.setBool("/alertes/pluie", false);
    }
  }
  if(!digitalRead(sonette)) {
    clignoterLED(100, 50, 3);
    if(sonetteStatus) {
      envoyerNotif("alertes/sonette", "Quelqu'un sonne à la porte");
      Firebase.setBool("/sonette", true);
    }
    clignoterLED(200, 150, 3);
  }
  if(digitalRead(ouvFenetre) || digitalRead(ouvPorte)) {
    if(alarmeStatus) {
      envoyerNotif("alertes/alarme", "Porte / fenêtre ouverte !");
      mvtStatus = false;
      Firebase.setBool("/alertes/alarme", false);
    }
  }
  if(digitalRead(mvt)) {
    if(mvtStatus) {
      envoyerNotif("alertes/mouvement", "Mouvement detecté dans la maison !");
      mvtStatus = false;
      Firebase.setBool("/alertes/mouvement", false);
    }
  }
  
}


void envoyerNotif(String id, String message) {
  Serial.println(message);
  HTTPClient http;   
  http.begin("http://fcm.googleapis.com/fcm/send");
  http.addHeader("Content-Type", "application/json");  
  http.addHeader("Authorization", key);  
  int httpResponseCode = http.POST(contentNotifDebut + message + contentNotifFin);
  http.end();
}

void clignoterLED(int t1, int t2, int n) {
  for(int i=0; i<n; i++) {
      digitalWrite(ledSonette, HIGH);
      delay(t1);
      digitalWrite(ledSonette, LOW);
      delay(t2);
  }
}

#include <SoftwareSerial.h>
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <HTTPClient.h>

/* GND
 * 23
 * 22
 * TX 1
 * RX 3
 * 21
 * GND
 * 19
 * 18
 * 5
 * 17
 * 16
 * 4
 * 0
 * 2
 * 15
 * 8
 * 7
 * 6
 * */

#define FIREBASE_HOST "https://smarthouse-232d7.firebaseio.com/"
#define FIREBASE_AUTH "xxx"

//#define WIFI_SSID "xx S9"
//#define WIFI_PASSWORD "xx"
#define WIFI_SSID "xx"
#define WIFI_PASSWORD "xx"



#define sonette 15 //4
#define ouvPorte 0 //6
#define ouvFenetre 4 //7
#define R 5 //10
#define G 18 //11
#define B 19 //12
#define ledSonette 21 //14
#define mvt 22 //17
#define pluie 23 //18

const int freq = 5000;
const int ledR = 0;
const int ledG = 1;
const int ledB = 2;
const int resolution = 8;

int rForce = 0;
int gForce = 0;
int bForce = 0;


const String key = "key=xxxx";
const String contentNotifDebut = "{\"to\":\"xxxx",\"notification\":{\"body\":\"";
const String contentNotifFin = "\"},\"priority\":\"high\",\"sound\":\"default\"}";

boolean sonetteStatus = true;
boolean alarmeStatus = true;
boolean pluieStatus = true;
boolean mvtStatus = true;

SoftwareSerial liaison(16, 17);

void envoyerNotif(String id, String message) {
  Serial.println(message);
  HTTPClient http;   
  http.begin("http://fcm.googleapis.com/fcm/send");
  http.addHeader("Content-Type", "application/json");  
  http.addHeader("Authorization", key);  
  int httpResponseCode = http.POST(contentNotifDebut + message + contentNotifFin);
  http.end();
}

void setup() {
  ledcSetup(ledR, freq, resolution);
  ledcSetup(ledG, freq, resolution);
  ledcSetup(ledB, freq, resolution);
  ledcAttachPin(R, ledR);
  ledcAttachPin(G, ledG);
  ledcAttachPin(B, ledB);
  Serial.begin(115200);
  liaison.begin(9600);

  pinMode(sonette, INPUT);
  pinMode(pluie, INPUT);
  pinMode(ouvPorte, INPUT);
  pinMode(ouvFenetre, INPUT);
  pinMode(ledSonette, OUTPUT);
  pinMode(mvt, INPUT);
  digitalWrite(ledSonette, LOW);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("Connected : ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  JsonObject& rgbData = Firebase.get("/rgbSalon/");
  rForce = rgbData[String("R")].as<int>();
  gForce = rgbData[String("G")].as<int>();
  bForce = rgbData[String("B")].as<int>();
    
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


  JsonObject& alerts = Firebase.get("/alertes/");
  sonetteStatus = alerts[String("sonette")].as<bool>();
  alarmeStatus = alerts[String("alarme")].as<bool>();
  pluieStatus = alerts[String("pluie")].as<bool>();
  mvtStatus = alerts[String("mouvement")].as<bool>();

  
  Firebase.stream("", [](FirebaseStream stream) {
    if (stream.getEvent() == "put") {
      if(stream.getPath() == "/porte") {
        Serial.println("porte Change");
        if (stream.getDataBool()) {
          Serial.println("ok");
          liaison.println("P090");
        }
        else {
          liaison.println("P000");
        } 
      }
      else if(stream.getPath() == "/chauffageAuto/temp") {
        Serial.println("Temp Change");
        liaison.println("C" + String(29*stream.getDataInt()-477));
      }
      else if(stream.getPath() == "/ledSalon") {
        if(stream.getDataBool()) {
          ledcWrite(ledR, rForce);
          ledcWrite(ledG, gForce);
          ledcWrite(ledB, bForce);
        }
        else {
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
    if(sonetteStatus) {
      envoyerNotif("alertes/sonette", "Quelqu'un sonne à la porte");
      Firebase.setBool("/sonette", true);
    }
    for(int i=0; i<5; i++) {
      Serial.println("test");
      digitalWrite(ledSonette, HIGH);
      delay(150);
      digitalWrite(ledSonette, LOW);
      delay(100);
    }
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

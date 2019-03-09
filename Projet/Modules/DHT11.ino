#include <dht.h>

#define dataPin 2 
dht DHT; // Creats a DHT object
void setup() {
  Serial.begin(9600);
}
void loop() {
  int readData = DHT.read11(dataPin); // Reads the data from the sensor
  float t = DHT.temperature; // Gets the values of the temperature
  float h = DHT.humidity; // Gets the values of the humidity
  
  // Printing the results on the serial monitor
  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("    Humidity = ");
  Serial.print(h);
  Serial.println(" % ");
  
  delay(4000); 
}

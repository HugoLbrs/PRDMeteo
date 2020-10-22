#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial s(D6,D7,false);
StaticJsonDocument<200> doc;
String msgRecep;

void setup() {
  Serial.begin(9600); 
  s.begin(9600);
}

void loop() {
  if( s.available()>0)
  {
    Serial.println("Msg en entrée");
    Serial.println(s.readString());
  } 
}

#include <SoftwareSerial.h>

SoftwareSerial s(3, 2); //pin Rx, Tx

void setup() {
  Serial.begin(9600);
  s.begin(9600);
}

void loop() {
  s.write("ARD");
  if ( s.available() > 0)
  {
    Serial.println(s.read());
  }
  else
  {
    Serial.println("rien sur le canal - ARD");
  }
  delay(500);
}

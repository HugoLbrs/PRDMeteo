#include <SoftwareSerial.h>
#include <ArduinoJson.h>

/* SECTION ARDUINO NANO
 *  Code réalisant l'acquisition, la mise au format Json
 *  et le transfert des données a l'ESP
 */

SoftwareSerial s(3, 2); //pin Rx, Tx
const int pinPotentiometre = A0;
const int pinTemperature = A1;

int potentiometre = 0;
int temperature = 0;
String msg = " ";
char msgEnvoy[500];

const int B=4275; // B value of the thermistor
const int R0 = 100000; // R0 = 100k


void setup() {
  pinMode(3,INPUT);
  pinMode(2,OUTPUT);
  Serial.begin(9600);
  s.begin(9600);
}

void loop() {
  potentiometre = analogRead(pinPotentiometre);
  temperature = analogRead(pinTemperature);

  char slt[200];

  //Conversion de la température d'après la datasheet
  float R = 1023.0/((float)temperature)-1.0;
  R = 100000.0*R;
  //convert to temperature via datasheet ;
  float temperature=1.0/(log(R/100000.0)/B+1/298.15)-273.15;


  //Creation du doc JSON a envoyé
  StaticJsonDocument<256> doc;
  doc["potentiometreValue"] = potentiometre;
  doc["temperature"] = temperature;
  
  
  
//  serializeJson(doc,Serial);  //envoie le doc sur le port série
//  serializeJson(doc,s);


//  ////////////////TEST CRYPTAGE/////////////////////////
  serializeJson(doc,slt);
  Serial.println(slt);
//Serial.println(strlen(slt));  //Strlen = nombre de char dans la chaine
  for (int i=0; i<strlen(slt);i++)
  {
    slt[i]=slt[i]+1;
  }
  Serial.println(slt);  
  s.print(slt);
////  for (int i=0; i<sizeof(slt);i++)
////  {
////    slt[i]=slt[i]-1;
////  }
//  Serial.println(slt);
 // deserializeJson(s,slt);
 // serializeJson(doc,s);
///////////////////FIN TEST/////////////////////
//
//  
  //Serial.println(s.available());
  delay(10000);
}

#include <SoftwareSerial.h>

/* SECTION ARDUINO NANO
 *  Code réalisant l'acquisition, la mise au format Json
 *  et le transfert des données a l'ESP
 */

SoftwareSerial s(3, 2); //pin Rx, Tx
const int pinPotentiometre = A0;
const int pinTemperature = A1;
const int pinLight = A2;
const int pinMotion = A3;

long delayy2 = 30000;

int potentiometre = 0;
int temperature = 0;    //A passer en int si on ne fait pas les traitements avant le partage des données
int light = 0;
int motion = 0;

String msg = "";
String quote = ",";



void setup() {
  pinMode(3,INPUT);
  pinMode(2,OUTPUT);

  Serial.begin(9600);
  s.begin(9600);
}

void loop() {
  potentiometre = analogRead(pinPotentiometre);
  temperature = analogRead(pinTemperature);
  light = analogRead(pinLight);
  motion = analogRead(pinMotion);


  
const int B=4275; // B value of the thermistor
const int R0 = 100000; // R0 = 100k
//  //Conversion de la température d'après la datasheet
//  float R = 1023.0/((float)temperature)-1.0;
//  R = 100000.0*R;
//  //convert to temperature via datasheet ;
//  temperature=1.0/(log(R/100000.0)/B+1/298.15)-273.15;



  msg = potentiometre + quote + temperature + quote +light + quote + motion; //+ temperature + "," + light + "," + motion;
  Serial.println(msg);
  
  s.print(msg);       //Envoi du JSON s.print() OU s.write()
  
  if ( s.available() > 0)
  {
    String temp = "";
    temp += s.readString();
    delayy2 = temp.toInt()*1000;
    Serial.println(delayy2);
    Serial.println(temp);
    if (delayy2<0){
      delayy2 = 5000;
    }
    else
    {
      Serial.print("New delay : ");
      Serial.println(delayy2);
    }
  }
  delay(delayy2);
}

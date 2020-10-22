#include <ESP8266WiFi.h>

const char* ssid = "MonReseau";        //Nom de votre réseau
const char* password = "LeMDP";        //mdp

WiFiClient espClient;

void setup() {
   Serial.begin(9600);
 
  //Init connection WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)   //Attente de connection au réseau Wifi
  {
    delay(500);
    Serial.print("*");
  }
  Serial.println("");
  Serial.println("Connection wifi réussi !");
  Serial.print("Adresse IP du module ESP8266 : ");
  Serial.print(WiFi.localIP());
}

void loop() {
  
}

//--------------ESP----------------------
//-------PUBLISH & SUBSCRIBE-------------
//---------------------------------------

//librairie utilisé
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//variable
const char* ssid = "boxprd";        //showroom      -> wifi asnte
const char* password = "prdpepito";  //wt0meevfc6    -> mdp showroom
const char* mqtt_server = "192.168.1.81";
const int mqtt_port = 1883;

SoftwareSerial s(D6, D7, false);

StaticJsonDocument<512> doc;
char msgSubscribe[200];
//String msgToArduino = " ";
char msgATransmettre[200];
String msg = "";




WiFiClient espClient;
PubSubClient client(espClient);

// Fonction callback
//permet l'affichage des msg du subscribe
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Topic : ");
  Serial.println(topic);
  for (int i = 0; i < length; i++) {
    msgSubscribe[i] = payload[i];
  }
  Serial.println(msgSubscribe);

  /////COMMANDE //////////////////////
  char top[] = "frequence";
  if (strcmp(top, topic) == 0) {
    commande(msgSubscribe);
  }
  memset(msgSubscribe, 0, sizeof(msgSubscribe));
}

///////////RECONNECT/////////////////
//// loop reconnection /////////////
void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESPClient", "admin", "admin")) {
      client.publish("info", "ESPReconnecte");
      Serial.println("connecte");
      client.subscribe("frequence");
    } else {
      Serial.print("Echec, CE=");
      Serial.print(client.state());
      Serial.println(" Retest dans 5s");
      delay(5000);
    }
  }
}


///////////////Publish msg////////////////////
void publishMsg() {
  msg = s.readString();
//  Serial.println(msg);

  //decoupe du msg reçu
  //----Strtok----//
  char buf[30];
  char *string[10];
  char *ptr = NULL;  
  byte index = 0;
  msg.toCharArray(buf, 30);
  ptr = strtok(buf, ",");

  while (ptr != NULL)
  {
    string[index] = ptr;
    if (string[index] == NULL)
    {
      string[index] = 0;
    }
    index ++;
    ptr = strtok(NULL, ",");
  }

  //Création du nouveau JSON//
  doc["time"] = 1;
  doc["potentiometre"] = atoi(string[0]);
  doc["temperature"] = atoi(string[1]);
  doc["luminosite"] = atoi(string[2]);
  doc["mouvement"] = atoi(string[3]);

  serializeJson(doc, msgATransmettre);    //Passage du Json dans un String
//  Serial.println(msgATransmettre);
  //Crytpage 
  for (int i=0; i<strlen(msgATransmettre);i++)
  {
    msgATransmettre[i]=msgATransmettre[i]+1;
  }
//  Serial.println(msgATransmettre);
  //Fin crypt
  client.publish("data", msgATransmettre);
}

////////////COMMANDE//////////////////
//////////////////////////////////////
void commande(String msg) {
  Serial.println("Je suis dans la commande");
  Serial.println(msg);
  s.print(msg);
}


/////////SETUP & LOOP/////////////////
void setup() {
  Serial.begin(9600);
  s.begin(9600);

  //Init connection WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("*");
  }
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());

  //Init connection au serveur MQTT - souscrit au topic "prd"
  client.setServer(mqtt_server, 1883);

  client.setCallback(callback);
}



void loop()
{
  if (!client.connected()) {
    reconnect();//boucle de reconnection a la wifi
  }
  if ( s.available() > 0)
  {
    publishMsg();
  }

  client.loop();                                        //boucle maintenant la connection serveur & recevant les msg subscribe - lance la fct callback
  delay(500);                                          //delay pour ne pas spam la liaison et la crash
}

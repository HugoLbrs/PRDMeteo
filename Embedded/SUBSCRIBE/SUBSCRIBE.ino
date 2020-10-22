#include <PubSubClient.h>
#include <ESP8266WiFi.h>

//paramètre wifi
const char* ssid = "Hugo";
const char* password = "hugopolytech";

//paramètre MQTT
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);


//Fonction du subscribe MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Topic : ");
  Serial.println(topic);
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  delay(500);
}


// loop reconnection
void reconnect() {
  //On vérifie la connection au réseau Wifi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("tentative de reconnection au wifi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print("*");
    }
    Serial.println("");
    Serial.println("Connection wifi réussi !");
    Serial.print("Adresse IP du module ESP8266 : ");
    Serial.println(WiFi.localIP());
  }

  //On se reconnecte au serveur MQTT
  while (!client.connected()) {
    if (client.connect("ESPClient")) {
      client.subscribe("#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 1 seconds");
      delay(1000);
    }
  }
}


//Setup
void setup() {
  Serial.begin(9600);

  //Init connection WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("*");
  }
  Serial.println("");
  Serial.println("Connection wifi réussi !");
  Serial.print("Adresse IP du module ESP8266 : ");
  Serial.println(WiFi.localIP());

  //Init connection serveur MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.subscribe("#");
  client.setCallback(callback);
}

//----LA BOUCLE----
void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

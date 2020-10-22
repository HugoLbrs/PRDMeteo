#include <PubSubClient.h>
#include <ESP8266WiFi.h>

//init des variables
const char* ssid = "LeFlow";
const char* password = "genepi74";
const char* mqtt_server = "test.mosquitto.org";
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attente d'une connection MQTT");
    if (client.connect(client_name))
    {
      client.publish(msgTopic, "MQTT is connected");
      Serial.println("connected");
      client.subscribe(inTopic);

    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  //connexion au réseau wifi
  Serial.begin(9600);
  
  //Init connection WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("*");
  }
  Serial.println("");
  Serial.println("Connection wifi réussie !");
  Serial.print("Adresse IP du module ESP8266 : ");
  Serial.println(WiFi.localIP());

  //initialisation connexion mqtt
  client.setServer(mqtt_server, mqttPort);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  client.publish("prd","Je suis l'ESP");
}

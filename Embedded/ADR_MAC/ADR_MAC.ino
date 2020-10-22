#include <ESP8266WiFi.h>
 
  const char* wifiName = "LeFlow";
  const char* wifiPass = "genepi74";
 
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("ESP8266 MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Connecting to ");
  Serial.println(wifiName);
 
  WiFi.begin(wifiName, wifiPass);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
// the loop function runs over and over again forever
void loop() {
}

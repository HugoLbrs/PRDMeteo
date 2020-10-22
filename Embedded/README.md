Embedded system - WeatherStation

In this part the development of the embedded system is presented.
Constraint: 
- Several sensors
- Transfer in WIFI, with MQTT protocol
- ESP8266 card constraint (not enough digital pin), addition of an arduino nano and a serial link
- Power consumption constraint (sleep mode used, not implemented at this day)

Several pieces of code are available:
-Publish, subscribe: setting up MQTT communication
-RXTX : additional serial link (be careful with the electronics between the boards, need to adapt the voltage)
-WifiESP : setting up a WIFI connection


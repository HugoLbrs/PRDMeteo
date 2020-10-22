const int pot = A2;
int valPot =0;
String msg = " ";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  valPot = analogRead(pot);
  msg = String("slt " + String(valPot));
  Serial.println(msg);
  delay(500);
}

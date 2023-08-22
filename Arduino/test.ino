void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
delay(4000);
String stringis = Serial.readString();
Serial.println(stringis);

}

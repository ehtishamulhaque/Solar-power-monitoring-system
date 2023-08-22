#include <dht.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
const int voltageSensor = A0;
SoftwareSerial s(3,1);

float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int currentPin = A1;
int sensitivity = 66;
int adcValue= 0;
int offsetVoltage = 2500;
double adcVoltage = 0;
double currentValue = 0;

dht DHT;
const int ldr_pin = 8;
const int led_pin = 13;

#define DHT11_PIN A2

void setup(){
    pinMode(ldr_pin,INPUT);
    pinMode(led_pin,OUTPUT);
    Serial.begin(9600);
    s.begin(9600);
  lcd.begin(16, 2);
  //Serial.begin(9600);
delay(5000);
 Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print(" Solar Power ");
  lcd.setCursor(0,1);
  lcd.print("  monitoring SYS  ");
  delay(3000);
}

void serialDoubleWrite(double d) {
  
  String stringData =  String(d, 1); 
  for (int i = 0; i < stringData.length(); i++)
  {
    Serial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
  }
}

void loop(){
  int chk = DHT.read11(DHT11_PIN);
  lcd.setCursor(0,0); 
  lcd.print("Temperature: ");
  lcd.print(DHT.temperature);

lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(1,1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  //delay(2000);

  char format_result_end[] = "]#";
  char format_result_start[] = "#S|TEMPFIX|[";
  Serial.print(" Temperature ");
  serialDoubleWrite(DHT.temperature);
  Serial.println("      ");
  Serial.print("  Humidity    ");
    serialDoubleWrite(DHT.humidity);
  
  
  
  

//  ldr sensor code
if( digitalRead( ldr_pin ) == 1){
      digitalWrite( led_pin,HIGH);
   }
   else{
      digitalWrite( led_pin , LOW);
   }
   
Serial.println( digitalRead( ldr_pin ));

  delay(3000);

  //voltage sensor
  value = analogRead(voltageSensor);
  vOUT = (value * 5.0) / 1024.0;
  vIN = vOUT / (R2/(R1+R2));
  //Serial.print("Input = ");
  //Serial.println(vIN);
  lcd.setCursor(0,0);
  
  //lcd.setCursor(9,0);
 // lcd.print(vIN);
  //delay(5000);

  
  adcValue = analogRead(currentPin);
  adcVoltage = (adcValue / 1024.0) * 5000;
  currentValue = ((adcVoltage - offsetVoltage) / sensitivity);
  
  Serial.print("Light Intensity = ");
  Serial.print(adcValue);
  delay(5000);
  //lcd.display();
  lcd.setCursor(0,0);
  lcd.print("Light Intens= ");
  lcd.setCursor(13,0);
  lcd.print(adcValue);

  delay(3000);

  Serial.print("\t Voltage(mV) = ");
  Serial.print(adcVoltage,3);
  
  lcd.setCursor(0,0);
  lcd.print("V in mV = ");
  lcd.setCursor(12,0);
  lcd.print(adcVoltage,1);

  delay(3000);
 
  Serial.print("\t Current = ");
  Serial.println(currentValue,3);
 
  lcd.setCursor(0,0);
  lcd.print("Current =       ");
  lcd.setCursor(10,0);
  lcd.print(currentValue,2);
  //lcd.setCursor(14,0);
  //lcd.print("A");
  //delay(3000);
}

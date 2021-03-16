// include the library code:
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define ONE_WIRE_BUS 13

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int RS = 2, EN = 4, d4 = 5, d5 = 18, d6 = 19, d7 = 21;

const int buttonPin1 = 12;     // the number of the pushbutton pin
const int buttonPin2 = 14;     // the number of the pushbutton pin
const int ledPin1 = 27;

int buttonState1 = 0;
int buttonState2 = 0;
int Counter = 18;
int Temp = 0;

LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);
OneWire oneWire(ONE_WIRE_BUS);
float temp=0.0;
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(ledPin1, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temp=");
  lcd.setCursor(0, 1);
  lcd.print("Man=");
  ;sensors.begin();
}

void loop() {
  
 sensors.requestTemperatures(); 
  Serial.print("Temperature: ");
  Serial.println(sensors.getTempCByIndex(0)); 
  lcd.setCursor(6, 0);
  lcd.print(sensors.getTempCByIndex(0));
  Temp = (sensors.getTempCByIndex(0));
  

  buttonState1 = digitalRead(12);
 if (buttonState1 == 1){
   Counter = Counter + 1;
    Serial.println(Counter);
    lcd.setCursor(5, 1);
    lcd.print(Counter);
  }
  buttonState2 = digitalRead(14);
 if (buttonState2 == 1){
   Counter = Counter - 1;
    Serial.println(Counter);
    lcd.setCursor(5, 1);
    lcd.print(Counter);
 }

 if (Counter < Temp){
  digitalWrite(ledPin1, HIGH);
 }
 if (Counter > Temp){
  digitalWrite(ledPin1, LOW);
 }
 
  delay(1000);
}

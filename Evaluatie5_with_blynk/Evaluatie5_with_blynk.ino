// include the library code:
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "K40rFyqcPMu6dGihL5QOiAeXBFKyqyke";

WidgetLED led1(V2);


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

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "telenet-32924";
char pass[] = "********";





void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");  

  Blynk.begin("K40rFyqcPMu6dGihL5QOiAeXBFKyqyke", ssid, pass, "server.wyns.it", 8081);

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
     Blynk.run();
  Blynk.virtualWrite(V1 , Temp);
  

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
  led1.off();
 }
 if (Counter > Temp){
  digitalWrite(ledPin1, LOW);
  led1.on();
 }

  delay(1000);
}

BLYNK_WRITE(V3)
{

int pinValue = param.asInt();

Serial.println("The value is:");

Serial.println(pinValue);

 if (pinValue < Temp){
  digitalWrite(ledPin1, HIGH);
  led1.off();
 }
 if (pinValue > Temp){
  digitalWrite(ledPin1, LOW);
  led1.on();
 }
  

 
}

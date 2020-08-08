
#include <Arduino.h>
unsigned int soil1;
unsigned int soil2;
unsigned int soil3;
bool watering=0;
int maxwateringSessions=1;
int numWatering=0;
unsigned long fiveMin=300000; //in seconds
unsigned long fifteenMin=900000; //in seconds
unsigned long thirtyMin=1800000; //
unsigned long day=86400000;// divided by ten
unsigned long checkTime;
unsigned long checkDay;
volatile int startWatering;
//2019-05-31 Gab: removed sensors 2 and 3 to reduce complexity, sensor 1 on A0 input
//2019-05-31 Gab: introduced interrupt routine on pin D3 to connect a switch, the objective is to force watering=1 and numwatering=0 to start at the next check


#define D2 7
#define D3 3
#define A0 14
#define A1 15
#define A2 16

void setup() {
    // put your setup code here, to run once:
    pinMode(LED_BUILTIN,OUTPUT);
    pinMode(A0,INPUT);
    pinMode(A1,INPUT);
    pinMode(A2,INPUT);
    pinMode(D2,OUTPUT);
    pinMode(D3,INPUT_PULLUP);
    digitalWrite(D2,HIGH);
    Serial.begin(9600);
    Serial.println("Hello Moritz! ver.2.0 interrupt enabled");
    numWatering=0;
    checkDay=0;
    checkTime=0;
    attachInterrupt(digitalPinToInterrupt(D3), water_button_pressed, CHANGE);
    startWatering=0;
}
void water_button_pressed() {
  if (digitalRead(D3)==0) {
     startWatering=1;
     digitalWrite(LED_BUILTIN,1);
    }
}

void loop() {
 
  if ((millis()-checkDay)>day) {
    checkDay=millis();
    numWatering=0;
    watering=0;
    Serial.println("It's a new day in Wolkenheim...");
  }
 
  if ((millis()-checkTime)>thirtyMin) {
      Serial.println("check");
      //soil1=analogRead(A0);
      //soil3=analogRead(A1);
      //soil2=analogRead(A2);
      //int hum1=1024-soil1;
      //Serial.println(hum1);
      //int hum2=1024-soil2;
      //int hum3=1024-soil3;
      //if ((hum1<450)or(hum2<450)or(hum3<450)) {
      //if (hum1<135) {
      //  Serial.println("dry soil found:");
      //  Serial.println(hum1);        
      watering=1;
      //}
      //Serial.print(hum1);
      //Serial.print("--");
      //Serial.print(hum2);
      //Serial.print("--");
      //Serial.println(hum3);
      checkTime=millis();
    }
    if((watering && (numWatering<maxwateringSessions))||startWatering) {

      if (startWatering>0) {
       Serial.println("button pressed...");
       Serial.println(startWatering);
       startWatering=0;
       delay(2000);
       digitalWrite(LED_BUILTIN,0);
       }
      //turn on the TAP
      digitalWrite(D2,LOW);
      Serial.println("Watering ACTIVE!");
      //delay for 5 mins
      delay(fiveMin);
      digitalWrite(D2,HIGH);
      numWatering++;  //increase watering session counter
      watering=0; //reset watering
      startWatering=0; //reset interrupt variable once again :(
    }
}
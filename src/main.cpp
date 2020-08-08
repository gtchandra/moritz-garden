
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
    //start watering immediately once turned on setting D2 to low
    digitalWrite(D2,LOW);
    Serial.begin(9600);
    Serial.println("Hello Moritz! Watering is active...");
    numWatering=0;
    checkDay=0;
    checkTime=0;
    startWatering=0;
}

void loop() {
  if ((millis()-fifteenMin)>0) {
    digitalWrite(D2,HIGH);
    Serial.println("Stop watering after 15 min");
    delay(900000);
  }

}
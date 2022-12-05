#include "AudioAnalyzer.h"

const short waterSPin = 0;
const short yellowLEDPin = 2;
const short redLEDPin = 3;

const int waterShort1 = 580;
const int waterShort2 = 480;

Analyzer Audio = Analyzer(4,5,5);
int freqVal[7];
int pumpsVal[6];


void setup() {
  
  Serial.begin(9600);
  Audio.Init();
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

}
short checkWater(); //return an indicator of the one of the 3 cases: (0) if Water is enough, (1) if water level is low , and (2) water level is critically low
void updatePumps(int F[], bool stopPumps = false); //send PWM value to each water pump

void loop() {
  
  switch(checkWater()) {
    case 0:
    digitalWrite(redLEDPin, LOW);
    digitalWrite(yellowLEDPin, LOW);

    
    break;

    case 1:
    digitalWrite(redLEDPin, LOW);
    digitalWrite(yellowLEDPin, HIGH);

    break;

    case 2:
    updatePumps(freqVal, true);
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(yellowLEDPin, HIGH);
    while(checkWater()); // hold until water level is appropraite

    break;
  }

  Audio.ReadFreq(freqVal);
  for(int i = 0; i < 6; i++) //Displays frequncy values on serial monitor    
  {
    //Serial.print(max(freqVal[i] - 100, 0));
    if (i < 5)  
      Serial.print(",");
    else 
      Serial.println();
  }  
  delay(50);

  updatePumps(freqVal);
}

short checkWater() {

  
  int waterLevel = analogRead(waterSPin);
  Serial.println(waterLevel);
  if (waterLevel < waterShort2) {
    return 2;
  }
  else if (waterLevel < waterShort1) {
    return 1;


 }
 return 0;
}

void updatePumps(int F[], bool stopPumps) {
  if (!stopPumps)
    for (short i = 0; i < 6; i++) {
      pumpsVal[i] = map(F[i], 0, 924, 0, 255); //scaling the frequency values
      pumpsVal[i] = (int)(pumpsVal[i] / 63.75) * 63.75; // limits pumps output to 4 bands of operation
      analogWrite(i+6, pumpsVal[i]);


    }
  else
    for (short i = 0; i < 6; i++) 
        analogWrite(i+6, pumpsVal[i]);
}



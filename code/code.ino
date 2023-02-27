#include "AudioAnalyzer.h"



Analyzer Audio = Analyzer(4,5,5);
int freqVal[7];
int pumpsVal[7];


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
  pinMode(12, OUTPUT);

}

void updatePumps(int F[], bool stopPumps = false); //send PWM value to each water pump

void loop() {
  
  
  Audio.ReadFreq(freqVal);
  for(int i = 0; i < 7; i++) //Displays frequncy values on serial monitor    
  {
    Serial.print(max(freqVal[i] - 100, 0));
    if (i < 6)  
      Serial.print(",");
    else 
      Serial.println();
  }  
  delay(50);

  updatePumps(freqVal);
}


void updatePumps(int F[], bool stopPumps) {

  for (short i = 0; i < 7; i++) {
    pumpsVal[i] = map(F[i], 0, 924, 0, 255); //scaling the frequency values
    pumpsVal[i] = (int)(pumpsVal[i] / 63.75) * 63.75; // limits pumps output to 4 bands of operation
    analogWrite(i+6, pumpsVal[i]);


  }

}



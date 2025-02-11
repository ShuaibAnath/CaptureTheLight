#include "Arduino.h" 
#include "leds.h"
#include "button.h"


Leds::Leds()
{
  // Setting up buttons as inputs
  for(int i = 2; i < 17; i++) pinMode(i, OUTPUT);
}// constructor


void Leds::beginLevel()
{
   // LED connected to pin 19 lit to indicate a level will begin.
   pinMode(A5, OUTPUT);
   digitalWrite(A5, HIGH);
   delay(5000);
   digitalWrite(A5, LOW);
   delay(2000);// wait 2 seconds before starting level
}// begin level for lighting LEDS


void Leds::lightLeds(int &level, int &targetLed, Button &buttonObj)
{
  int lightingDuration = 1000;// 1 second at level 1
  if(level == 1)
  {// level 1
  executeLevelLedLighting(targetLed, buttonObj, 3, lightingDuration);
  }// level 1

  if(level == 2)
  {// level 2
    lightingDuration-=250;
    executeLevelLedLighting(targetLed, buttonObj, 7, lightingDuration);
  }// level 2

  if(level == 3)
  {// level 3
   lightingDuration-=350;
   executeLevelLedLighting(targetLed, buttonObj, 11, lightingDuration);
  }// level 3

  if(level == 4)
  {//level 4
    lightingDuration-=500;
    executeLevelLedLighting(targetLed, buttonObj, 14, lightingDuration);
  }//level 4

}//lightLeds


void Leds::randomiseLedLighting (int &level)
{ 
  int arrayMembersLeft = 15;
  int i = 0;
  for(int j = 0; j < 15; j++)  ledArray[j] = 0;// for loop to reset led array
  int arrPins[15] =  {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2};
  populateLedArray(arrayMembersLeft, 0, arrPins, i, 0, 15);

}//randomiseLedLighting


void Leds::populateLedArray(int &arrayMembersLeft, int numberOfMembersToInsert, int arrayPins[], int &i, int minRandNumber, int maxRandNumber)
{
  randomSeed(analogRead(A4));
  int randomIndex = random(minRandNumber, maxRandNumber);
  while(arrayMembersLeft > numberOfMembersToInsert)
  {// place pin numbers in random positions of ledSequenceArray
      if(ledArray[randomIndex] == 0)
      {
        ledArray[randomIndex] = arrayPins[i];
        i++;
        arrayMembersLeft--;
      }
   randomIndex = random(minRandNumber, maxRandNumber);
  }
}//populate ledSequenceArray


void Leds::finishedLevel()
{
  // Turn off all LEDs
  for(int i = 2; i < 17; i++) digitalWrite(i, LOW);// write LOW to all pins 

  for(int i = 2; i < 17; i++){
    digitalWrite(i, HIGH);
    delay(200);
   }// write HIGH to all pins

  for(int i = 2; i < 17; i++) digitalWrite(i, LOW);// write LOW to all pins 
  
  delay(2000);
}//Finished level


void Leds::resetGame()
{
  Serial.println("GAME OVER :(");
    while(1)
  {
   for(int i = 2; i < 17; i++) digitalWrite(i, HIGH); // write to digital pins
   delay(500);

   for(int i = 2; i < 17; i++) digitalWrite(i, LOW);// write to digital pins 
   delay(500);
  }
}// reset Game


void Leds::executeLevelLedLighting(int &targetLed, Button &buttonObj, int maxIndex, int lightingDuration)
{
  unsigned long  timeSnapshot;// millis() return type
  int i = 0;
  randomSeed(analogRead(A4));
  int randomTargetLedInsertIndex = random(0,(maxIndex+1));
  for(int k = 0; k < 15; k++)
  {// for loop to insert target LED at random index
    if(ledArray[k] == targetLed)
    {// if target led index is found
      int temp = ledArray[randomTargetLedInsertIndex]; // store randomTargetLedInsertIndex element
      ledArray[randomTargetLedInsertIndex] = targetLed; // place target led in randomTargetLedInsertIndex position
      ledArray[k] = temp; // place element that was at rarandomTargetLedInsertIndexndomIndex in targetLed former position
    }
  }
   timeSnapshot = millis();
    while(!buttonObj.isButtonPressed)
    {// while button is not pressed
        digitalWrite(ledArray[i], HIGH);
        buttonObj.pollButton();// check if button is pressed
       
        if(buttonObj.isButtonPressed) break;// if button is pressed come out of loop

        if ((millis() - timeSnapshot) >= lightingDuration)
        { // if lighting duration has elapsed
          timeSnapshot = millis();// reset snapshot
          digitalWrite(ledArray[i], LOW);
            if(i < maxIndex)
              {// if else to iterate through first 4 elements of array
                i++;
              }
              else{
                i = 0;
              }// if else to iterate through first 4 elements of array
        }//if lighting duration has elapsed
      
      if(buttonObj.isButtonPressed) break; // if the button has been pressed exit loop
    }//while button is not pressed
}// execute led lighting

void Leds::gameFinished()
{
  Serial.println("Congratulations, You WIN!!");
  while(1){
    // Turn off all LEDs
  for(int i = 2; i < 17; i++) digitalWrite(i, LOW);// write LOW to all pins 

  for(int i = 2; i < 17; i++){
    digitalWrite(i, HIGH);
    delay(200);
   }// write HIGH to all pins

  for(int i = 2; i < 17; i++){
    digitalWrite(i, LOW);// write LOW to all pins 
    delay(200);
  }
  //delay(1000);
  }
}
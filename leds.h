#include "button.h"
#ifndef leds_h
#define leds_h

class Leds
{
  private:

  public:

     int ledArray [15] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2};// array of pins connected to LEDs
  
     Leds();// constructor

     void beginLevel();//LED lighting arrangement for the beginning of a level 

     void randomiseLedLighting (int &level);//randomises ledArray elements

    // Populates ledArray with pin numbers connected to the LEDs (randomly, by index)
     void populateLedArray(int &arrayMembersLeft, int numberOfMembersToInsert, int arrayPins[], int &i, int minRandNumber, int maxRandNumber);

     void lightLeds(int &level, int &targetLed, Button &buttonObj);// Calls executeLevelLedLighting 
     // and determines how executeLevelLedLighting performs the led lighting by dictating the speed of lighting, 
     //how many LEDs are lit in the level and the randomness of the lighting 

     void finishedLevel();

     void resetGame();

     void executeLevelLedLighting(int &targetLed, Button &buttonObj, int maxIndex, int lightingDuration);// executeLevelLedLighting Performs the lighting of the leds 
     // based on how many must be lit and 
     // the random order they must be lit in,
     // specified by the parameters of the function

     void gameFinished();
    
}; // end of class Leds

#endif
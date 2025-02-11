#include "leds.h"
#include "button.h"

Leds leds = Leds();
int level = 1;
int targetLed = 0;
Button button = Button();
bool targetLedCaught = false; // indicates if button was pressed while targetLed was lit
void setup() 
{
  Serial.begin(9600);
  leds.beginLevel();
  Serial.println("LEVEL: 1");
  delay(1000); 
  leds.randomiseLedLighting(level);
}

void loop() 
{
  randomSeed(analogRead(A4));
  targetLed = random(2, 17);
  digitalWrite(targetLed, HIGH);// light the target LED
  delay(4000);// allow enough time for the player to see it.
  digitalWrite(targetLed, LOW);
  delay(1000);
  leds.lightLeds(level, targetLed, button);

  if(button.isButtonPressed)
  {// if the button was pressed 
    for(int i = 0; i < 15; i++)
    {// check each LED pin
       int ledPinRead = digitalRead(leds.ledArray[i]);
       if(ledPinRead == HIGH )
       {// if the pin read is HIGH
          if(leds.ledArray[i] ==  targetLed){
             targetLedCaught = true ;
             break;// if a pin is high and it is the targetLed, stop checking
             }
             else
             {
               break;// if a pin is high and it is NOT the targetLed, stop checking
             }
       }// if the pin read is HIGH
    }// for loop check each LED pin
  }// if the button was pressed

  if(targetLedCaught){
     leds.finishedLevel();
  } else{
    leds.resetGame();
  }

  if(level == 4 && button.isButtonPressed) leds.gameFinished();
  targetLedCaught = false;// reset for next level
  button.isButtonPressed = false;// reset for next level
  level++;// next level
  leds.beginLevel();
  Serial.print("LEVEL: ");
  Serial.println(level);
  delay(1000); 
  leds.randomiseLedLighting(level);
}

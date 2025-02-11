#include "Arduino.h"
#include "button.h"

Button::Button()
{// Setting up button as input
  pinMode(A3, INPUT);
}// Button constructor


void Button::pollButton()
{
  int buttonRead = digitalRead(buttonPin);
    if (buttonRead != lastButtonState) 
    {// if button Press is bouncing
      lastDebounceTime = millis();
    }// if button Press is bouncing
    if ((millis() - lastDebounceTime) > debounceDelay) 
    {// if debounce delay time has elapsed
      if (buttonRead != buttonState) 
      {// if the state of the button that has been read differs from the current button state
       buttonState = buttonRead;
        if (buttonState == HIGH)
        {// if buttonState is HIGH after debouncing
          isButtonPressed = true;
        }// if buttonState is HIGH after debouncing

      }// if the state of the button that has been read differs from the current button state

    }// if debounce delay time has elapsed
  lastButtonState = buttonRead;// store button state read for next iteration of main loop

}// pollButton function
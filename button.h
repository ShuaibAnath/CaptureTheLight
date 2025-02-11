#ifndef button_h
#define button_h

class Button
{
  private:
    int buttonPin = 17;// Pin to read the button

    int buttonState; // checks current button state

    int lastButtonState = LOW ;// for button debouncing

    unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled

    unsigned long debounceDelay = 50;    // the debounce time in milliseconds 
  
  public:
    // Constructor
    Button();

    void pollButton();// checks if button is pressed

    bool isButtonPressed = false;// variable to check if button is pressed
}; // end of class Button

#endif
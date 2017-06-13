// include the library code:
#include <LiquidCrystal.h>
#include <Bounce2.h>

const int nbButtons=3;

//button pins
int buttonPins[nbButtons]={16,15,17};

// Instantiate a Bounce object
Bounce debouncer[nbButtons];

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(8, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");

  for(int i=0; i<nbButtons; i++) {
    debouncer[i]=Bounce();
    
      // Setup the button with an internal pull-up :
    pinMode(buttonPins[i],INPUT_PULLUP);
  
    // After setting up the button, setup the Bounce instance :
    debouncer[i].attach(buttonPins[i]);
    debouncer[i].interval(5); // interval in ms
  }
}

void loop() {
  lcd.clear();
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  
  for(int i=0; i<nbButtons; i++) {
        // Update the Bounce instance :
      debouncer[i].update();
    
      // Get the updated value :
      int value = debouncer[i].read();
      // Turn on or off the LED as determined by the state :
      if ( value == HIGH ) {
      } else {
        lcd.print(buttonPins[i]);
      }
  }
  delay(100);
}

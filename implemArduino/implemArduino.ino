#include <LiquidCrystal.h>
#include <Bounce2.h>
#include "model.h"
#include "datetime.h"
#include "menu.h"
#include "charmanagement.h"

#define ROWS 2
#define COLS 8
#define NBBUTTONS 3
#define PBP0 16
#define PBP1 15
#define PBPEN 17
#define BBP0 0
#define BBP1 1
#define BBPEN 2
#define INIT 0
#define ENG 1
#define WAIT 2
#define SWX 0
#define SW1 1
#define SW2 2
#define SW3 3
#define SW4 4

void testsCharMngmt ()
{
    Serial.begin(9600);
  char cases[16]="";
  strupdate(cases,0,"test",5);
  char intTest[5];
  int2TabChar(intTest, 5, 27050);
  char floatTest[6];
  float2TabChar(floatTest, 2, 3, 43.01757);
//  Serial.println(cases);
//  Serial.println(intTest);
  Serial.println(floatTest[5]);
  Serial.println(floatTest);
}

void showMenu(LiquidCrystal* lcd, Menu* menu, bool configBlink)
{
  for (int  thisRow = 0; thisRow < ROWS; thisRow++) {
      // loop over the rows:
      for (int thisCol = 0; thisCol < COLS; thisCol++) {
        // set the cursor position:
        lcd->setCursor(thisCol, thisRow);
        // print the letter:
        lcd->write(menu->cases[thisCol+8*thisRow]);
      }
    }
  if(configBlink) {
    for(int i=0; i<16; i++) {
      if(menu->selectionIDGroupCases[i] == menu->selectedIDGroup) {
        int thisCol = i % 8;
        int thisRow = i / 8;
        // set the cursor position:
        lcd->setCursor(thisCol, thisRow);
        // print the letter:
        lcd->write(' ');
      }
    }
  }
}

void testShowMenu(LiquidCrystal* lcd, Menu** menus)
{
  delay(3000);
  showMenu(lcd, menus[ACCUEIL], false);
  delay(3000);
  showMenu(lcd, menus[DATE], false);
  delay(3000);
  showMenu(lcd, menus[PARCOURS], false);
  delay(3000);
  showMenu(lcd, menus[INTERVAL], false);
  delay(3000);
  showMenu(lcd, menus[COORDS1], false);
  delay(3000);
  showMenu(lcd, menus[COORDS2], false);
  delay(3000);
  showMenu(lcd, menus[COORDS3], false);
  delay(3000);
  showMenu(lcd, menus[COORDS4], false);
  delay(3000);
  showMenu(lcd, menus[ENR1], false);
  delay(3000);
  showMenu(lcd, menus[ENR2], false);
}

//3 states : 0 init, 1 engaged, 2 waiting to desengaged
//2 values : HIGH or LOW
void readBoutons(Bounce* debouncer , int* buttonStates, int* buttonValues)
{
    for(int i=0; i<NBBUTTONS; i++) {
      //Wait mode
      if(buttonStates[i] == 1) {
         buttonStates[i] = 2;
      }
        // Update the Bounce instance :
      debouncer[i].update();
      int value = debouncer[i].read();
      if ( value != buttonValues[i]) {
        buttonValues[i] = value;
        buttonStates[i] = (buttonStates[i] + 1)%3; //buttonStates is either 0 or 2
      }
  }
}

//return switchActivated
int buttonStatesToSwitchActivated(int* buttonStates)
{
  if(buttonStates[BBP0]!=ENG && buttonStates[BBP1]!=ENG && buttonStates[BBPEN]==ENG) {
    return SW1;
  } else if (buttonStates[BBP0]==ENG && buttonStates[BBP1]!=ENG && buttonStates[BBPEN]==ENG) {
    return SW2;
  } else if (buttonStates[BBP0]!=ENG && buttonStates[BBP1]==ENG && buttonStates[BBPEN]==ENG) {
    return SW3;
  } else if (buttonStates[BBP0]==ENG && buttonStates[BBP1]==ENG && buttonStates[BBPEN]==ENG) {
    return SW4;
  } else {
    return SWX;
  }
}



// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

//button pins
int buttonPins[NBBUTTONS]={PBP0,PBP1,PBPEN};

// Instantiate a Bounce object
Bounce debouncer[NBBUTTONS];
int buttonValues[NBBUTTONS]={HIGH,HIGH,HIGH};
int buttonStates[NBBUTTONS]={INIT,INIT,INIT};

Model momo;
ShowModel showMomo;
Menu menus[10];
Menu* currentMenu;

void testButtons()
{
  readBoutons(debouncer , buttonStates, buttonValues);
  int switchActivated = buttonStatesToSwitchActivated(buttonStates);
  switch(switchActivated) {
    case SW1 :
      Serial.println("SW1");
      break;
    case SW2 :
      Serial.println("SW2");
      break;
    case SW3 :
      Serial.println("SW3");
      break;
    case SW4 :
      Serial.println("SW4");
      break;
    default :
      break;
  }
  for(int i=0; i<NBBUTTONS; i++) {
    Serial.print("Button ");
    Serial.print(i);
//    Serial.print("the value : ");Serial.println(buttonValues[i]);
//    Serial.print("the state : ");Serial.println(buttonStates[i]);
    Serial.print("  ");
    Serial.print(buttonValues[i]);
    Serial.print("  ");
  }
  Serial.print("\n");
}

void setup()
{
  Serial.begin(9600);

  // init menus and model
  initModel(&momo);
  initShowModel(&showMomo);
  modelToShowModel(&momo, &showMomo);
  generateMenu(&menus[ACCUEIL], &showMomo, ACCUEIL);
  generateMenu(&menus[DATE], &showMomo, DATE);
  generateMenu(&menus[PARCOURS], &showMomo, PARCOURS);
  generateMenu(&menus[INTERVAL], &showMomo, INTERVAL);
  generateMenu(&menus[COORDS1], &showMomo, COORDS1);
  generateMenu(&menus[COORDS2], &showMomo, COORDS2);
  generateMenu(&menus[COORDS3], &showMomo, COORDS3);
  generateMenu(&menus[COORDS4], &showMomo, COORDS4);
  generateMenu(&menus[ENR1], &showMomo, ENR1);
  generateMenu(&menus[ENR2], &showMomo, ENR2);
  interconnexions(menus);

  currentMenu = &menus[ACCUEIL];

  // set up the LCD's number of columns and rows:
  lcd.begin(8, 2);
  showMenu(&lcd, currentMenu, false);
  

  // Setup for BUTTONS
  for(int i=0; i<NBBUTTONS; i++) {
    debouncer[i]=Bounce();
    
      // Setup the button with an internal pull-up :
    pinMode(buttonPins[i],INPUT_PULLUP);
  
    // After setting up the button, setup the Bounce instance :
    debouncer[i].attach(buttonPins[i]);
    debouncer[i].interval(20); // interval in ms
    debouncer[i].update();
    buttonValues[i]=debouncer[i].read();
  }
}

void loop()
{
  readBoutons(debouncer , buttonStates, buttonValues);
  int switchActivated = buttonStatesToSwitchActivated(buttonStates);
  switch(switchActivated) {
    case SW1 :
      Serial.println("SW1");
      currentMenu = currentMenu -> sw1Connection;
      break;
    case SW2 :
      Serial.println("SW2");
      currentMenu = currentMenu -> sw2Connection;
      break;
    case SW3 :
      Serial.println("SW3");
      break;
    case SW4 :
      Serial.println("SW4");
      break;
    default :
      break;
  }
  for(int i=0; i<NBBUTTONS; i++) {
    Serial.print("Button ");
    Serial.print(i);
//    Serial.print("the value : ");Serial.println(buttonValues[i]);
//    Serial.print("the state : ");Serial.println(buttonStates[i]);
    Serial.print("  ");
    Serial.print(buttonValues[i]);
    Serial.print("  ");
  }
  Serial.print("\n");

  showMenu(&lcd, currentMenu, false);
  delay(50);
}



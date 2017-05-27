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

//int readBoutons(Bounce* debouncer ...)


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

//button pins
int buttonPins[NBBUTTONS]={PBP0,PBP1,PBPEN};

// Instantiate a Bounce object
Bounce debouncer[NBBUTTONS];
bool buttonValues[NBBUTTONS]={HIGH,HIGH,HIGH};

Model momo;
ShowModel showMomo;
Menu menus[10];
Menu* currentMenu;

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
  

  for(int i=0; i<NBBUTTONS; i++) {
    debouncer[i]=Bounce();
    
      // Setup the button with an internal pull-up :
    pinMode(buttonPins[i],INPUT_PULLUP);
  
    // After setting up the button, setup the Bounce instance :
    debouncer[i].attach(buttonPins[i]);
    debouncer[i].interval(5); // interval in ms
    debouncer[i].update();
    buttonValues[i]=debouncer[i].read();
  }
}

void loop()
{
  for(int i=0; i<NBBUTTONS; i++) {
        // Update the Bounce instance :
      debouncer[i].update();
      int value = debouncer[i].read();
      if ( value != buttonValues[i]) {
        buttonValues[i] = value;
        Serial.println("test");
        Serial.println(i);
        if(i==BBPEN) {
          currentMenu = currentMenu->sw1Connection;
          showMenu(&lcd, currentMenu, false); 
        }
      } 
  }
  delay(100);
}



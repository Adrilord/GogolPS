#include <TinyGPS.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
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
#define GPSRX 2
#define GPSTX 3

void testsCharMngmt ();

void showMenu(LiquidCrystal* lcd, Menu* menu, int configBlink);

void testShowMenu(LiquidCrystal* lcd, Menu** menus);

//3 states : 0 init, 1 engaged, 2 waiting to desengaged
//2 values : HIGH or LOW
void readBoutons(Bounce* debouncer , int* buttonStates, int* buttonValues);

//return switchActivated
int buttonStatesToSwitchActivated(int* buttonStates);

void testButtons();

//FOR THE GPS
static void smartdelay(unsigned long ms);
static void print_float(float val, float invalid, int len, int prec);
static void print_int(unsigned long val, unsigned long invalid, int len);
static void print_date(TinyGPS &gps);
static void print_str(const char *str, int len);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

//GPS
TinyGPS gps;
SoftwareSerial ss(GPSRX, GPSTX);

//button pins
int buttonPins[NBBUTTONS]={PBP0,PBP1,PBPEN};

// Instantiate a Bounce object
Bounce debouncer[NBBUTTONS];
int buttonValues[NBBUTTONS]={HIGH,HIGH,HIGH};
int buttonStates[NBBUTTONS]={INIT,INIT,INIT};

Model momo;
Menu menus[10];
Menu* currentMenu;

int configBlinking=FALSE;

void setup()
{
  Serial.begin(9600);

  // init menus and model
  initModel(&momo);
  generateMenu(&menus[ACCUEIL], &momo, ACCUEIL);
  generateMenu(&menus[DATE], &momo, DATE);
  generateMenu(&menus[PARCOURS], &momo, PARCOURS);
  generateMenu(&menus[INTERVAL], &momo, INTERVAL);
  generateMenu(&menus[COORDS1], &momo, COORDS1);
  generateMenu(&menus[COORDS2], &momo, COORDS2);
  generateMenu(&menus[COORDS3], &momo, COORDS3);
  generateMenu(&menus[COORDS4], &momo, COORDS4);
  generateMenu(&menus[ENR1], &momo, ENR1);
  generateMenu(&menus[ENR2], &momo, ENR2);
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
    debouncer[i].interval(5); // interval in ms
    debouncer[i].update();
    buttonValues[i]=debouncer[i].read();
  }

  //SoftwareSerial setup for the gps
   ss.begin(4800);
}

void loop()
{
  readBoutons(debouncer , buttonStates, buttonValues);
  int switchActivated = buttonStatesToSwitchActivated(buttonStates);
  switch(switchActivated) {
    case SW1 :
      Serial.println("SW1");
      if(currentMenu->configureMode == FALSE) {
        currentMenu = currentMenu -> sw1Connection;
      }
      break;
    case SW2 :
      Serial.println("SW2");
      if(currentMenu->configureMode == FALSE) {
        currentMenu = currentMenu -> sw2Connection;
      } else {
        increaseSelectedConfigValue(currentMenu,&momo);
      }
      break;
    case SW3 :
      Serial.println("SW3");
      if(currentMenu->configureMode==TRUE) {
        increaseSelection(currentMenu);
      }
      break;
    case SW4 :
      Serial.println("SW4");
      if(currentMenu->isConfigurable == TRUE && currentMenu->configureMode==FALSE) {
        currentMenu->configureMode=TRUE;
      } else {
        currentMenu->configureMode=FALSE;
      }
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

  //Model refreshing
  updateModelGPSdata(&momo, &gps);
  //Menu refreshing
  showMenu(&lcd, currentMenu, configBlinking);
  updateMenuCases(currentMenu, &momo);
  //Config blinking
  if(currentMenu->isConfigurable == TRUE && currentMenu->configureMode==TRUE) {
      configBlinking=(configBlinking + 1) %2; 
  } else {
      configBlinking=FALSE;
  }
  delay(50);
}

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

void showMenu(LiquidCrystal* lcd, Menu* menu, int configBlink)
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
  if(configBlink==TRUE) {
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


static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void print_float(float val, float invalid, int len, int prec)
{
  if (val == invalid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartdelay(0);
}

static void print_int(unsigned long val, unsigned long invalid, int len)
{
  char sz[32];
  if (val == invalid)
    strcpy(sz, "*******");
  else
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartdelay(0);
}

static void print_date(TinyGPS &gps)
{
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE)
    Serial.print("********** ******** ");
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d ",
        month, day, year, hour, minute, second);
    Serial.print(sz);
  }
  print_int(age, TinyGPS::GPS_INVALID_AGE, 5);
  smartdelay(0);
}

static void print_str(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartdelay(0);
}



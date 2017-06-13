#include <TinyGPS.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include <Bounce2.h>
#include "model.h"
#include "datetime.h"
#include "menu.h"
#include "charmanagement.h"
#include "iomanagement.h"

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
#define PSD 10

//tests des fonctions du module charmanagement
void testsCharMngmt ();

//affiche un menu sur le lcd en indiquant si on veut que le curseur
//clignote dans le cas du mode configuration
void showMenu(LiquidCrystal* lcd, Menu* menu, int configBlink);

//test l'affichage de menu
void testShowMenu(LiquidCrystal* lcd, Menu** menus);

//3 states : 0 init, 1 engaged, 2 waiting to desengaged
//2 values : HIGH or LOW
//En fonction des modifications de valeurs des boutons, on change leur état
void readBoutons(Bounce* debouncer , int* buttonStates, int* buttonValues);

//Indique le switch en cours d'activation en fonction des états des boutons
int buttonStatesToSwitchActivated(int* buttonStates);

//pour vérifier le bon fonctionnement des boutons
void testButtons();

//FOR THE GPS
static void smartdelay(unsigned long ms);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

//objets nécessaires pour lire les données transmises par le gps
TinyGPS gps;
SoftwareSerial ss(GPSTX, GPSRX);

//pins des boutons
int buttonPins[NBBUTTONS]={PBP0,PBP1,PBPEN};

//objets nécessairesp pour lire les valeurs et déterminer les états
//des boutons
Bounce debouncer[NBBUTTONS];
int buttonValues[NBBUTTONS]={HIGH,HIGH,HIGH};
int buttonStates[NBBUTTONS]={INIT,INIT,INIT};

Model momo; //model
Menu currentMenu; //menu actuel affiché sur le lcd

//indique si on doit faire clignoter le curseur pour le mode configuration
int configBlinking=FALSE;

RecordConf recordConf; //paramètres d'enregistrement
char isSDOK[2]; //indique (en char) si la carte SD est bien connectée

void setup()
{
  Serial.begin(9600);
  
  // init menu and model
  initModel(&momo);
  generateMenu(&currentMenu, &momo, ACCUEIL);

  //init SD
  momo.isSDOK=FALSE;
  if (SD.begin(PSD)) { //Port 10
    momo.isSDOK=TRUE;
  }
  initRecordConf(&recordConf, &momo);

  // set up the LCD's number of columns and rows:
  lcd.begin(8, 2);
  showMenu(&lcd, &currentMenu, false);
  

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
  readBoutons(debouncer , buttonStates, buttonValues); // lecture des boutons
  //on détermine quel switch est activé
  int switchActivated = buttonStatesToSwitchActivated(buttonStates);
  //en fonction du switch activé, on effectue une action
  switch(switchActivated) {
    case SW1 :
      Serial.println("SW1");
      //changement de menu
      if(currentMenu.configureMode == FALSE) {
        generateMenu(&currentMenu, &momo, currentMenu.sw1Connection);
      }
      break;
    case SW2 :
      Serial.println("SW2");
      //changement de sous-menu
      if(currentMenu.configureMode == FALSE) {
        generateMenu(&currentMenu, &momo, currentMenu.sw2Connection);
      } else {
		 //ou changement du paramètre sélectionné en mode configuration
        increaseSelectedConfigValue(&currentMenu,&momo);
      }
      break;
    case SW3 :
      Serial.println("SW3");
      if(currentMenu.configureMode==TRUE && currentMenu.menu_type != ENR1) {
        increaseSelection(&currentMenu);
      } else if (currentMenu.menu_type == ENR1) {
		  //ici on aurait du avoir la partie enregistrement desdonnées
	  }
      break;
    case SW4 :
      Serial.println("SW4");
      //on passe en mode configuration ou on le quitte
      if(currentMenu.isConfigurable == TRUE && currentMenu.configureMode==FALSE) {
        currentMenu.configureMode=TRUE;
      } else {
        currentMenu.configureMode=FALSE;
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
  updateModelLocaldata(&momo);
  //Menu refreshing
  showMenu(&lcd, &currentMenu, configBlinking);
  updateMenuCases(&currentMenu, &momo);
  //Config blinking
  if(currentMenu.isConfigurable == TRUE && currentMenu.configureMode==TRUE) {
      configBlinking=(configBlinking + 1) %2; 
  } else {
      configBlinking=FALSE;
  }
  smartdelay(50);
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
      if(buttonStates[i] == ENG) {
         buttonStates[i] = WAIT;
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

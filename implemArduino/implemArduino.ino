#include <LiquidCrystal.h>
#include "model.h"
#include "datetime.h"
#include "menu.h"
#include "charmanagement.h"

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


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);


void setup()
{
  Serial.begin(9600);
  
  Model momo;
  ShowModel showMomo;
  Menu menus[10];
  initModel(&momo);
  //initShowModel(&showMomo);
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

  // set up the LCD's number of columns and rows:
  lcd.begin(8, 2);
  lcd.print(menus[PARCOURS].cases);
  Serial.println("test");
  Serial.println(showMomo.autonomy);
  strupdate(menus[ACCUEIL].cases,0,"?",1);
  Serial.println(menus[ACCUEIL].cases[0]);
}

void loop()
{
}



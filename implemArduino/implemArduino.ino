//#include "model.h"
//#include "datetime.h"
#include "menu.h"
#include "charmanagement.h"

void toto()
{
//    Model momo;
//  ShowModel showMomo;
//  Menu menus[10];
//  initModel(&momo);
//  initShowModel(&showMomo);
//  showMomo = modelToShowModel(&momo);
//  generateMenu(&menus[ACCUEIL], &showMomo, ACCUEIL);
//  generateMenu(&menus[DATE], &showMomo, DATE);
//  generateMenu(&menus[PARCOURS], &showMomo, PARCOURS);
//  generateMenu(&menus[INTERVAL], &showMomo, INTERVAL);
//  generateMenu(&menus[COORDS1], &showMomo, COORDS1);
//  generateMenu(&menus[COORDS2], &showMomo, COORDS2);
//  generateMenu(&menus[COORDS3], &showMomo, COORDS3);
//  generateMenu(&menus[COORDS4], &showMomo, COORDS4);
//  generateMenu(&menus[ENR1], &showMomo, ENR1);
//  generateMenu(&menus[ENR2], &showMomo, ENR2);
//  interconnexions(menus);
//  Menu* currentMenu = &menus[ACCUEIL];
//  showMenu(*currentMenu);
//  printf("\n\n\n\n\n\n");
//
//    while(1) {
//    char resp[4];
//    scanf("%s",resp);
//    //~ fgets(resp,4,stdin);
//    if(strcmp(resp,"sw1") == 0) {
//      currentMenu = currentMenu->sw1Connection;
//      showMenu(*currentMenu);
//      printf("\n\n\n\n\n\n");
//    } else if(strcmp(resp,"sw1") == 1) {
//      currentMenu = currentMenu->sw2Connection;
//      showMenu(*currentMenu);
//      printf("\n\n\n\n\n\n");
//    }
//  }
//
//
//  
}





void setup()
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

void loop()
{
}



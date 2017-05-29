#ifndef MENU
#define MENU

#include "charmanagement.h"
#include "model.h"

#define NUMBER_OF_CASES 16
enum MENU_TYPE {ACCUEIL, DATE, PARCOURS ,INTERVAL, COORDS1, COORDS2, 
	COORDS3, COORDS4, ENR1, ENR2};
typedef enum MENU_TYPE MENU_TYPE;
#define TRUE 0
#define FALSE 1

typedef struct Menu{
	char cases[16];
	int selectionIDGroupCases[16];
	int selectedIDGroup;
	int maxSelectionGroupId;
	int isConfigurable; //0 (TRUE)
	int configureMode; // avec BPEN+BP1+BP0 (sw4), 0->normal, 1->config
	struct Menu* sw1Connection; //BPEN
	struct Menu* sw2Connection; //BPEN+BP0
  MENU_TYPE menu_type;
}Menu;

void showMenu(Menu menu);

void generateMenu(Menu* menu, Model* model, MENU_TYPE menu_type);

void interconnexions(Menu menus[10]);

void increaseSelection(Menu* menu);

void increaseSelectedConfigValue(Menu* menu, Model* model);

void updateMenuCases(Menu* menu, Model* model);

#endif

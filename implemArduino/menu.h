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

//Représentation
typedef struct Menu{
	char cases[16]; //contenu du menu
	//variables pour la gestion de la configuration
	int selectionIDGroupCases[16];
	int selectedIDGroup;
	int maxSelectionGroupId;
	int isConfigurable; //0 (TRUE)
	int configureMode; // avec BPEN+BP1+BP0 (sw4), 0->normal, 1->config
	//Variables de connection à d'autres menus
	MENU_TYPE sw1Connection; //BPEN
	MENU_TYPE sw2Connection; //BPEN+BP0
	
	MENU_TYPE menu_type; //indique le type de menu
}Menu;

//Affiche un menu sur lcd
void showMenu(Menu menu);

//Permet de générer un menu (sans type initial) à l'aide du type de menu
// menu_type désiré
void generateMenu(Menu* menu, Model* model, MENU_TYPE menu_type);

//Changement de sélection (de paramètre) pour la configuration
void increaseSelection(Menu* menu);

//Changement de la valeur du paramètre sélectionné pour la configuration
void increaseSelectedConfigValue(Menu* menu, Model* model);

//Met à jours les valeurs de cases en fonction du model
void updateMenuCases(Menu* menu, Model* model);

#endif

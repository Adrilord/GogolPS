#ifndef MENU
#define MENU

//~ #define ACCUEIL 0
//~ #define DATE 1
//~ #define PARCOURS 2
//~ #define INTERVAL 3
//~ #define COORDS1 4
//~ #define COORDS2 4
//~ #define COORDS3 4
//~ #define COORDS4 4
//~ #define COORDS5 4

enum MENU_TYPE {ACCUEIL, DATE, PARCOURS ,INTERVAL, COORDS1, COORDS2, COORDS3, COORDS4, COORDS5, ENR1, ENR2};

class Menu 
{
	private:
		char cases[16];
		int guidCases[16];
		bool guidSelected;
		bool isConfigurable;
		bool configureMode;
		Menu* sw1Connection;
		Menu* sw2Connection;
		Menu* sw3Connection;
	
	public:
		Menu(MENU_TYPE);
		void setCaseValue(int numero, char value);
		char getCasValue(int numero);
		void changeSelection();
};

#endif

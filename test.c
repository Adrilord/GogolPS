#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//~ #include "/home/adi/Arduino/libraries/TinyGPS-13/TinyGPS.h"

#define NUMBER_OF_CASES 17 //16
typedef enum MENU_TYPE MENU_TYPE;
enum MENU_TYPE {ACCUEIL, DATE, PARCOURS ,INTERVAL, COORDS1, COORDS2, 
	COORDS3, COORDS4, COORDS5, ENR1, ENR2};

typedef struct Datetime {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int hundredths;
}Datetime;

typedef struct Showdatetime {
	char year[5];
	char month[3];
	char day[3];
	char hour[3];
	char minute[3];
	char second[3];
	char hundredths[3];
}Showdatetime;

Showdatetime datetime2Showdatetime(Datetime datetime)
{
	Showdatetime showdatetime;
	sprintf(showdatetime.year, "%d", datetime.year);
	sprintf(showdatetime.month, "%d", datetime.month);
	sprintf(showdatetime.day, "%d", datetime.day);
	sprintf(showdatetime.minute, "%d", datetime.minute);
	sprintf(showdatetime.second, "%d", datetime.second);
	sprintf(showdatetime.hundredths, "%d", datetime.hundredths);
	return showdatetime;
}

typedef struct Model {
	//local prog data
	int autonomy;
	Datetime localDateTime;
	int durationParcours; //in seconds
	int durationInterval; //in milliseconds
	//GPS data
	float latitude, longitude; //in degrees
	float altitude; //in meters
	float course; //in degrees
	float speed; //in m/sec
	Datetime GPSDateTime;
	short satellites;
	long hdop;
}Model;

//~ updateModelGPSdata(Model model, TinyGPS gps)
//~ {
	//~ // returns +/- latitude/longitude in degrees (NULL is where we could have the encoding time)
	//~ gps.f_get_position(&model.latitude, &model.longitude, NULL);
	//~ model.altitude = gps.f_altitude();
	//~ model.speed = gps.f_speed_mps();
	//~ gps.crack_datetime(&model.GPSDateTime.year, &model.GPSDateTime.month, &model.GPSDateTime.day,
	//~ &model.GPSDateTime.hour, &model.GPSDateTime.minute, &model.GPSDateTime.second, &model.GPSDateTime.hundredths, NULL);
	//~ model.satellites = gps.satellites();
	//~ model.hdop = gps.hdop();
//~ }

typedef struct Menu{
	char cases[17];
	int selectionIDGroupCases[16];
	int selectedIDGroup;
	int maxSelectionGroupId;
	int isConfigurable; //0 (TRUE)
	int configureMode; // avec BPEN+BP1+BP0 (sw4)
	struct Menu* sw1Connection; //BPEN
	struct Menu* sw2Connection; //BPEN+BP0
	struct Menu* sw3Connection; //BPEN+BP1
}Menu;

void showMenu(Menu menu)
{
	for(int i=0; i<NUMBER_OF_CASES/2; i++) {
		printf("%c",menu.cases[i]);
	}
	printf("\n");
	for(int i=NUMBER_OF_CASES/2+1; i<NUMBER_OF_CASES; i++) {
		printf("%c",menu.cases[i]);
	}
	printf("\n");
}

void generateMenu(Menu* menu, Model* model, MENU_TYPE menu_type)
{
	Showdatetime localShowdatetime = datetime2Showdatetime(model->localDateTime);
	Showdatetime GPSShowdatetime = datetime2Showdatetime(model->GPSDateTime);
	char* result;
	switch(menu_type) {
		case ACCUEIL :
			//~ strcat(result,localShowdatetime.hour);
			//~ strcpy(menu.cases,);
		break;
		case DATE :
		break;
		PARCOURS :
		break; 
		INTERVAL :
		break;
		COORDS1 :
		break; 
		COORDS2 :
		break;
		COORDS3 :
		break;
		COORDS4 :
		break;
		COORDS5 :
		break;
		ENR1: 
		break;
		ENR2:
		break;
		default :
		break;
	}
}

int main()
{
	//~ Menu accueil;
	//~ strcpy(accueil.cases, "BonjourLOL10rorr");
	//~ showMenu(accueil);
	char* lol1 = "LOL?   ";
	char* lol2 = "WTF?";
	//~ strcat(lol1,lol2);
	printf(lol1);
}

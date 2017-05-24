#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//~ #include "/home/adi/Arduino/libraries/TinyGPS-13/TinyGPS.h"

#define NUMBER_OF_CASES 17 //16
typedef enum MENU_TYPE MENU_TYPE;
enum MENU_TYPE {ACCUEIL, DATE, PARCOURS ,INTERVAL, COORDS1, COORDS2, 
	COORDS3, COORDS4, COORDS5, ENR1, ENR2};
#define TRUE 0
#define FALSE 1
#define NORMAL 0
#define CONFIG 1

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

Showdatetime datetime2Showdatetime(Datetime* datetime)
{
	Showdatetime showdatetime;
	snprintf(showdatetime.year, sizeof showdatetime.year, "%d", datetime->year);
	snprintf(showdatetime.month, sizeof showdatetime.month, "%d", datetime->month);
	snprintf(showdatetime.day, sizeof showdatetime.day, "%d", datetime->day);
	snprintf(showdatetime.hour, sizeof showdatetime.hour, "%d", datetime->hour);
	snprintf(showdatetime.minute, sizeof showdatetime.minute, "%d", datetime->minute);
	snprintf(showdatetime.second, sizeof showdatetime.second, "%d", datetime->second);
	snprintf(showdatetime.hundredths, sizeof showdatetime.hundredths, "%d", datetime->hundredths);
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

typedef struct ShowModel {
	//local prog data
	char autonomy[3];
	Showdatetime localShowDateTime;
	char durationParcours[7]; // HH:MM:SS
	char durationInterval[7]; //MM:SS:hShS
	//GPS data
	char latitude[7], longitude[7], altitude[7]; // xx.xxx
	char course[7];
	char speed[7];
	Showdatetime GPSShowDateTime;
	char satellites[3];
	char hdop[7];
}ShowModel;

ShowModel modelToShowModel(Model* model)
{
	ShowModel showModel;
	snprintf(showModel.autonomy, sizeof showModel.autonomy, "%d", model->autonomy);
	showModel.localShowDateTime = datetime2Showdatetime(&model->localDateTime);
	snprintf(showModel.durationParcours, sizeof showModel.durationParcours, "%d:%d:%d", (model->durationParcours/3600),
		(model->durationParcours%3600)/60,(model->durationParcours%3600)%60);
	snprintf(showModel.durationInterval, sizeof showModel.durationInterval,"%d:%d:%d", (model->durationParcours/6000),
		(model->durationParcours%6000)/100,(model->durationParcours%6000)%100);
	snprintf(showModel.latitude, sizeof showModel.latitude, "%f", model->latitude);
    snprintf(showModel.longitude, sizeof showModel.longitude, "%f", model->longitude);
    snprintf(showModel.altitude, sizeof showModel.altitude, "%f", model->altitude);
    snprintf(showModel.course, sizeof showModel.course, "%f", model->course);
    snprintf(showModel.speed, sizeof showModel.speed, "%f", model->speed);
    showModel.GPSShowDateTime = datetime2Showdatetime(&model->GPSDateTime);
    snprintf(showModel.longitude, sizeof showModel.longitude, "%f", model->longitude);
    snprintf(showModel.satellites, sizeof showModel.satellites, "%d", model->satellites);
    snprintf(showModel.hdop, sizeof showModel.hdop, "%ld", model->hdop);
    
    return showModel;
}

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
	int configureMode; // avec BPEN+BP1+BP0 (sw4), 0->normal, 1->config
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
	for(int i=NUMBER_OF_CASES/2; i<NUMBER_OF_CASES; i++) {
		printf("%c",menu.cases[i]);
	}
	printf("\n");
}

void generateMenu(Menu* menu, ShowModel* showModel, MENU_TYPE menu_type)
{
	char cases[17]="";
	menu->selectionIDGroupCases[0]=-1;
	menu->selectionIDGroupCases[1]=-1;
	menu->selectionIDGroupCases[2]=-1;
	menu->selectionIDGroupCases[3]=-1;
	menu->selectionIDGroupCases[4]=-1;
	menu->selectionIDGroupCases[5]=-1;
	menu->selectionIDGroupCases[6]=-1;
	menu->selectionIDGroupCases[7]=-1;
	menu->selectionIDGroupCases[8]=-1;
	menu->selectionIDGroupCases[9]=-1;
	menu->selectionIDGroupCases[10]=-1;
	menu->selectionIDGroupCases[11]=-1;
	menu->selectionIDGroupCases[12]=-1;
	menu->selectionIDGroupCases[13]=-1;
	menu->selectionIDGroupCases[14]=-1;
	menu->selectionIDGroupCases[15]=-1;
	menu->configureMode=NORMAL;
	switch(menu_type) {
		case ACCUEIL :
			strcat(cases,showModel->localShowDateTime.hour);
			strcat(cases,":");
			strcat(cases,showModel->localShowDateTime.minute);
			strcat(cases,":");
			strcat(cases,showModel->localShowDateTime.second);
			strcat(cases,"BAT");
			strcat(cases,":");
			strcat(cases,showModel->autonomy);
			strcat(cases,"%");
			menu->isConfigurable=TRUE;
		break;
		case DATE :
			strcat(cases,"   ");
			strcat(cases,showModel->localShowDateTime.day);
			strcat(cases," ");
			strcat(cases,showModel->localShowDateTime.month);
			strcat(cases,"    ");
			strcat(cases,showModel->localShowDateTime.year);
		break;
		PARCOURS :
			strcat(cases,"PARCOURS");
			//~ strcat(cases,showModel->localShowDateTime.hour);
			//~ strcat(cases,":");
			//~ strcat(cases,showModel->localShowDateTime.minute);
			//~ strcat(cases,":");
			//~ strcat(cases,showModel->localShowDateTime.second);
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
	strcpy(menu->cases,cases);
}

void connectMenus()
{
	
}

void initModel(Model* model)
{
	model->autonomy=100;
	model->localDateTime.year=2017;
	model->localDateTime.month=1;
	model->localDateTime.day=1;
	model->localDateTime.hour=10;
	model->localDateTime.minute=10;
	model->localDateTime.second=10;
	model->localDateTime.hundredths=0;
	model->durationParcours=100; model->durationInterval=10;
	model->latitude=50; model->longitude=40; model->altitude=30;
	model->course=10;
	model->speed=20;
	model->GPSDateTime.year=2017;
	model->GPSDateTime.month=1;
	model->GPSDateTime.day=1;
	model->GPSDateTime.hour=10;
	model->GPSDateTime.minute=10;
	model->GPSDateTime.second=10;
	model->GPSDateTime.hundredths=0;
	model->satellites=0;
	model->hdop=0;
}

void initShowDateTime(Showdatetime* showdatetime)
{
	strcpy(showdatetime->year,"");
	strcpy(showdatetime->month,"");
	strcpy(showdatetime->day,"");
	strcpy(showdatetime->hour,"");
	strcpy(showdatetime->minute,"");
	strcpy(showdatetime->second,"");
	strcpy(showdatetime->hundredths,"");
}

void initShowModel(ShowModel* showModel)
{
	//local prog data
	strcpy(showModel->autonomy,"");
	initShowDateTime(&showModel->localShowDateTime);
	strcpy(showModel->durationParcours,"");
	strcpy(showModel->durationInterval,"");
	//GPS data
	strcpy(showModel->latitude,"");strcpy(showModel->longitude,"");
	strcpy(showModel->altitude,"");strcpy(showModel->course,"");
	strcpy(showModel->speed,"");
	initShowDateTime(&showModel->GPSShowDateTime);
	strcpy(showModel->satellites,"");
	strcpy(showModel->hdop,"");
}

int main()
{
	Model momo;
	ShowModel showMomo;
	Menu accueil;
	initModel(&momo);
	initShowModel(&showMomo);
	showMomo = modelToShowModel(&momo);
	generateMenu(&accueil, &showMomo, ACCUEIL);
	showMenu(accueil);
	
	//~ char buffer[6];
	//~ float myFloat=4.00179115;
	//~ snprintf(buffer, sizeof buffer, "%f", myFloat);
	//~ printf(buffer);
}

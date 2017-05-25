#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//~ #include "/home/adi/Arduino/libraries/TinyGPS-13/TinyGPS.h"

#define NUMBER_OF_CASES 17 //16
typedef enum MENU_TYPE MENU_TYPE;
enum MENU_TYPE {ACCUEIL, DATE, PARCOURS ,INTERVAL, COORDS1, COORDS2, 
	COORDS3, COORDS4, ENR1, ENR2};
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
	snprintf(showdatetime.year, sizeof showdatetime.year, "%04d", datetime->year);
	snprintf(showdatetime.month, sizeof showdatetime.month, "%02d", datetime->month);
	snprintf(showdatetime.day, sizeof showdatetime.day, "%02d", datetime->day);
	snprintf(showdatetime.hour, sizeof showdatetime.hour, "%02d", datetime->hour);
	snprintf(showdatetime.minute, sizeof showdatetime.minute, "%02d", datetime->minute);
	snprintf(showdatetime.second, sizeof showdatetime.second, "%02d", datetime->second);
	snprintf(showdatetime.hundredths, sizeof showdatetime.hundredths, "%02d", datetime->hundredths);

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
	char autonomy[4];
	Showdatetime localShowDateTime;
	char durationParcours[9]; // HH:MM:SS
	char durationInterval[9]; //MM:SS:hShS
	//GPS data
	char latitude[7], longitude[7], altitude[7]; // xx.xxx
	char course[7];
	char speed[7];
	Showdatetime GPSShowDateTime;
	char satellites[3];
	char hdop[7];
	//filename for recording
	char recordFilename[17];
}ShowModel;

ShowModel modelToShowModel(Model* model)
{
	ShowModel showModel;
	snprintf(showModel.autonomy, sizeof showModel.autonomy, "%03d", model->autonomy);
	showModel.localShowDateTime = datetime2Showdatetime(&model->localDateTime);
	snprintf(showModel.durationParcours, sizeof showModel.durationParcours, "%02d:%02d:%02d", (model->durationParcours/3600),
		(model->durationParcours%3600)/60,(model->durationParcours%3600)%60);
	snprintf(showModel.durationInterval, sizeof showModel.durationInterval,"%02d:%02d:%02d", (model->durationParcours/6000),
		(model->durationParcours%6000)/100,(model->durationParcours%6000)%100);
	snprintf(showModel.latitude, sizeof showModel.latitude, "%02.3f", model->latitude);
    snprintf(showModel.longitude, sizeof showModel.longitude, "%02.3f", model->longitude);
    snprintf(showModel.altitude, sizeof showModel.altitude, "%02.3f", model->altitude);
    snprintf(showModel.course, sizeof showModel.course, "%02.3f", model->course);
    snprintf(showModel.speed, sizeof showModel.speed, "%02.3f", model->speed);
    showModel.GPSShowDateTime = datetime2Showdatetime(&model->GPSDateTime);
    snprintf(showModel.longitude, sizeof showModel.longitude, "%02.3f", model->longitude);
    snprintf(showModel.satellites, sizeof showModel.satellites, "%02d", model->satellites);
    snprintf(showModel.hdop, sizeof showModel.hdop, "%06ld", model->hdop);
    snprintf(showModel.recordFilename,sizeof showModel.recordFilename,"EN%s%s%s%s%s%s",
		showModel.localShowDateTime.year,showModel.localShowDateTime.month,showModel.localShowDateTime.day
		,showModel.localShowDateTime.hour,showModel.localShowDateTime.minute,showModel.localShowDateTime.second);
    
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
	char cases[17]="\0";
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
	menu->maxSelectionGroupId=-1;
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
			strcat(cases,"%%");
			menu->isConfigurable=FALSE;
		break;
		case DATE :
			strcat(cases,"   ");
			strcat(cases,showModel->localShowDateTime.day);
			strcat(cases," ");
			strcat(cases,showModel->localShowDateTime.month);
			strcat(cases,"    ");
			strcat(cases,showModel->localShowDateTime.year);
			menu->isConfigurable=TRUE;
			menu->selectionIDGroupCases[3]=0;
			menu->selectionIDGroupCases[4]=0;
			menu->selectionIDGroupCases[6]=1;
			menu->selectionIDGroupCases[7]=1;
			menu->selectionIDGroupCases[12]=2;
			menu->selectionIDGroupCases[13]=2;
			menu->selectionIDGroupCases[14]=2;
			menu->selectionIDGroupCases[15]=2;
			menu->maxSelectionGroupId=2;
		break;
		case PARCOURS :
			strcat(cases,"PARCOURS");
			strcat(cases,showModel->durationParcours);
			menu->isConfigurable=TRUE;
			menu->selectionIDGroupCases[8]=0;
			menu->selectionIDGroupCases[9]=0;
			menu->selectionIDGroupCases[11]=1;
			menu->selectionIDGroupCases[12]=1;
			menu->selectionIDGroupCases[14]=2;
			menu->selectionIDGroupCases[15]=2;
			menu->maxSelectionGroupId=2;
		break; 
		case INTERVAL :
			strcat(cases,"INTERVms");
			strcat(cases,showModel->durationInterval);
			menu->isConfigurable=TRUE;
			menu->selectionIDGroupCases[8]=0;
			menu->selectionIDGroupCases[9]=0;
			menu->selectionIDGroupCases[11]=1;
			menu->selectionIDGroupCases[12]=1;
			menu->selectionIDGroupCases[14]=2;
			menu->selectionIDGroupCases[15]=2;
			menu->maxSelectionGroupId=2;
		break;
		case COORDS1 :
			strcat(cases,"LA");
			strcat(cases,showModel->latitude);
			strcat(cases,"LO");
			strcat(cases,showModel->longitude);
			menu->isConfigurable=FALSE;
		break; 
		case COORDS2 :
			strcat(cases,"AL");
			strcat(cases,showModel->altitude);
			strcat(cases,"CO");
			strcat(cases,showModel->course);
			menu->isConfigurable=FALSE;
		break;
		case COORDS3 :
			strcat(cases,"SP");
			strcat(cases,showModel->speed);
			strcat(cases,"SATT  ");
			strcat(cases,showModel->satellites);
			menu->isConfigurable=FALSE;
		break;
		case COORDS4 :
			strcat(cases,"HD");
			strcat(cases,showModel->hdop);
			strcat(cases,"        ");
			menu->isConfigurable=FALSE;
		break;
		case ENR1:
			strcat(cases,"START   ");
			strcat(cases,"STOP    ");
			menu->isConfigurable=TRUE;
			menu->selectionIDGroupCases[0]=0;
			menu->selectionIDGroupCases[1]=0;
			menu->selectionIDGroupCases[2]=0;
			menu->selectionIDGroupCases[3]=0;
			menu->selectionIDGroupCases[4]=0;
			menu->selectionIDGroupCases[8]=1;
			menu->selectionIDGroupCases[9]=1;
			menu->selectionIDGroupCases[10]=1;
			menu->selectionIDGroupCases[11]=1;
			menu->maxSelectionGroupId=1;
		break;
		case ENR2:
			strcat(cases,showModel->recordFilename);
			menu->isConfigurable=FALSE;
		break;
		default :
			strcat(cases,"SECRET  MENU");
			menu->isConfigurable=FALSE;
		break;
	}
	//~ printf("TEST1 \n");
	//~ printf(cases);
	//~ printf("\n");
	strcpy(menu->cases,"              ");
	snprintf(menu->cases,17,cases);
	//~ printf("TEST2 \n");
	//~ printf(menu->cases);
	//~ printf("\n");
}

void initModel(Model* model)
{
	model->autonomy=10;
	model->localDateTime.year=2017;
	model->localDateTime.month=1;
	model->localDateTime.day=1;
	model->localDateTime.hour=1;
	model->localDateTime.minute=1;
	model->localDateTime.second=1;
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
	//record filename
	strcpy(showModel->recordFilename,"");
}

void interconnexions(Menu menus[10])
{
	menus[ACCUEIL].sw1Connection = &menus[PARCOURS];
	menus[ACCUEIL].sw2Connection = &menus[DATE];
	menus[DATE].sw1Connection = &menus[PARCOURS];
	menus[DATE].sw2Connection = &menus[ACCUEIL];
	menus[PARCOURS].sw1Connection = &menus[COORDS1];
	menus[PARCOURS].sw2Connection = &menus[INTERVAL];
	menus[INTERVAL].sw1Connection = &menus[COORDS1];
	menus[INTERVAL].sw2Connection = &menus[PARCOURS];
	menus[COORDS1].sw1Connection = &menus[ENR1];
	menus[COORDS1].sw2Connection = &menus[COORDS2];
	menus[COORDS2].sw1Connection = &menus[ENR1];
	menus[COORDS2].sw2Connection = &menus[COORDS3];
	menus[COORDS3].sw1Connection = &menus[ENR1];
	menus[COORDS3].sw2Connection = &menus[COORDS4];
	menus[COORDS4].sw1Connection = &menus[ENR1];
	menus[COORDS4].sw2Connection = &menus[COORDS1];
	menus[ENR1].sw1Connection = &menus[ACCUEIL];
	menus[ENR1].sw2Connection = &menus[ENR2];
	menus[ENR2].sw1Connection = &menus[ACCUEIL];
	menus[ENR2].sw2Connection = &menus[ENR1];
}

int main()
{
	Model momo;
	ShowModel showMomo;
	Menu menus[10];
	initModel(&momo);
	initShowModel(&showMomo);
	showMomo = modelToShowModel(&momo);
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
	Menu* currentMenu = &menus[ACCUEIL];
	showMenu(*currentMenu);
	printf("\n\n\n\n\n\n");
	while(1) {
		char resp[4];
		scanf("%s",resp);
		//~ fgets(resp,4,stdin);
		if(strcmp(resp,"sw1") == 0) {
			currentMenu = currentMenu->sw1Connection;
			showMenu(*currentMenu);
			printf("\n\n\n\n\n\n");
		} else if(strcmp(resp,"sw1") == 1) {
			currentMenu = currentMenu->sw2Connection;
			showMenu(*currentMenu);
			printf("\n\n\n\n\n\n");
		}
	}
}

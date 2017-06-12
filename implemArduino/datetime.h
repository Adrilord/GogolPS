#ifndef DATETIME
#define DATETIME

#include "charmanagement.h"

//Représentation du temps sous format de nombres
typedef struct Datetime {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int hundredths;
}Datetime;

//Représentation du temps sous format de caractères
typedef struct Showdatetime {
	char year[4];
	char month[2];
	char day[2];
	char hour[2];
	char minute[2];
	char second[2];
	char hundredths[2];
}Showdatetime;

//Fonctions de transformation de format
Showdatetime datetime2Showdatetime(Datetime* datetime);

//Initialisation
void initShowDateTime(Showdatetime* showdatetime);

#endif

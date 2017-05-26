#ifndef DATETIME
#define DATETIME

#include "charmanagement.h"

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
	char year[4];
	char month[2];
	char day[2];
	char hour[2];
	char minute[2];
	char second[2];
	char hundredths[2];
}Showdatetime;

Showdatetime datetime2Showdatetime(Datetime* datetime);

void initShowDateTime(Showdatetime* showdatetime);

#endif

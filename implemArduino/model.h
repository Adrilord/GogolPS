#ifndef MODEL
#define MODEL

#include "datetime.h"

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
	char durationParcours[8]; // HH:MM:SS
	char durationInterval[8]; //MM:SS:hShS
	//GPS data
	char latitude[6], longitude[6], altitude[6]; // xx.xxx
	char course[6];
	char speed[6];
	Showdatetime GPSShowDateTime;
	char satellites[2];
	char hdop[6];
	//filename for recording
	char recordFilename[16];
}ShowModel;

ShowModel modelToShowModel(Model* model);

//updateModelGPSdata(Model model, TinyGPS gps);

void initModel(Model* model);

void initShowModel(ShowModel* showModel);


#endif

#ifndef MODEL
#define MODEL

#include "datetime.h"
#include "charmanagement.h"
#include <TinyGPS.h>
#include <Arduino.h>

#define PBATT 0
#define TRUE 0
#define FALSE 1

//Le modèle contient toutes les données importantes du programme au
//format "brut" (nombres)
typedef struct Model {
	//local prog data
	int autonomy;
	Datetime localDateTime;
	long durationParcours; //in seconds
	long durationInterval; //in milliseconds
  int isSDOK;
	//GPS data
	float latitude, longitude; //in degrees
	float altitude; //in meters
	float course; //in degrees
	float speed; //in m/sec
	Datetime GPSDateTime;
	short satellites;
	long hdop;
}Model;

//Cette structure permet de faciliter l'affichage en donnant le modèle
//sous forme de chaînes de caractères 
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
	//recording
	char recordFilename[16];
  char isSDOK[2];
}ShowModel;

//Fonction de transformation de Model à ShowModel
void modelToShowModel(Model* model, ShowModel* showModel);

//Fonctions de mise à jour du modèle

void updateModelGPSdata(Model* model, TinyGPS* gps);

void updateModelLocaldata(Model* model);

void initModel(Model* model);

void initShowModel(ShowModel* showModel);


#endif

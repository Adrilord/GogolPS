#ifndef IOMANAGEMENT
#define IOMANAGEMENT

#include "model.h"
#include <SD.h>

#define START 0
#define STOP 1
#define CONTINUE 2

//Informations nécessaires pour l'enregistrement des données de modèle
//dans un fichier de la carte SD (configuration d'enregistrement)
typedef struct RecordConf{
  int mode; // START, STOP ou CONTINUE
  char recordingFilename[16]; // Nom de fichier pour l'enregistrement
  Model* model; // modèle
}RecordConf;

//Initialise la configuration d'enregistrement
void initRecordConf(RecordConf* recordConf, Model* model);

//Ouvre le fichier d'enregistrement si on est en mode START
//ou Ecrit les informations du modèle si on est en mode CONTINUE (ou START)
//Ne fait rien en mode STOP
void updateRecordConf(RecordConf* recordConf, int Mode);

//Enregistre les données de modèle pour un parcours
void recordData(RecordConf* recordConf);

//enregistre les paramètres de temps d'intervalle et de parcours
void recordParams(RecordConf* recordConf);

//Lit les paramètres (on s'en sert en début de programme)
void readParams(Model* model);

#endif

#ifndef IOMANAGEMENT
#define IOMANAGEMENT

#include "model.h"
#include <SD.h>

#define START 0
#define STOP 1
#define CONTINUE 0

typedef struct RecordConf{
  int mode;
  char recordingFilename[16];
  Model* model;
}RecordConf;

void initRecordConf(RecordConf* recordConf, Model* model);

void updateRecordConf(RecordConf* recordConf, int Mode);

void recordData(RecordConf* recordConf);

void recordParams(RecordConf* recordConf);

void readParams(Model* model);

#endif

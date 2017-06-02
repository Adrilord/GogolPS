#include "iomanagement.h"

void initRecordConf(RecordConf* recordConf, Model* model)
{
  recordConf->mode=STOP;
  recordConf->model=model;
  ShowModel showModel;
  initShowModel(&showModel);
  modelToShowModel(model, &showModel);
  strupdate(recordConf->recordingFilename,0,showModel.recordFilename,16);
}

void updateRecordConf(RecordConf* recordConf, int mode)
{
  recordConf->mode=mode;
  ShowModel showModel;
  initShowModel(&showModel);
  modelToShowModel(recordConf->model, &showModel);
  strupdate(recordConf->recordingFilename,0,showModel.recordFilename,16);
}

void recordData(RecordConf* recordConf)
{
//  switch (recordConf->mode)
//  {
//    case START :
//      SD.open(recordConf->recordingFilename, FILE_WRITE);
//    break;
//    case CONTINUE :
//    break;
//    case STOP :
//    break;
//  }
}

void recordParams(RecordConf* recordConf)
{
  SD.remove("params.info");
  File myFile;
  // if the file opened okay, write to it:
  myFile = SD.open("params.info", FILE_WRITE);
  if (myFile) {
    Serial.print("Writing to params.info...");
    myFile.println(recordConf->model->durationParcours);
    myFile.println(recordConf->model->durationInterval);
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening params.info");
  }
  myFile.close();
}

void readParams(Model* model)
{
  File myFile;
// re-open the file for reading:
  myFile = SD.open("params.info");
  if (myFile) {
    Serial.println("reading params.info");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening params.info");
  }
}


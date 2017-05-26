#include "model.h"

void modelToShowModel(Model* model, ShowModel* showModel)
{
  int2TabChar(showModel->autonomy, 3, model->autonomy);
	showModel->localShowDateTime = datetime2Showdatetime(&model->localDateTime);
  char temp2[2];
  char temp4[4];
  // !! VALEUR LIMITE DE PRECISION SUR 8BITs !!
  long2TabChar(temp2, 2, (model->durationParcours/3600));
  strupdate(showModel->durationParcours,0,temp2,2);
  strupdate(showModel->durationParcours,2,":",1);
  long2TabChar(temp2, 2, (model->durationParcours%3600)/60);
  strupdate(showModel->durationParcours,3,temp2,2);
  strupdate(showModel->durationParcours,5,":",1);
  long2TabChar(temp2, 2, (model->durationParcours%3600)%60);
  strupdate(showModel->durationParcours,6,temp2,2);

  int2TabChar(temp2, 2, (model->durationInterval/6000));
  strupdate(showModel->durationInterval,0,temp2,2);
  strupdate(showModel->durationInterval,2,":",1);
  int2TabChar(temp2, 2, (model->durationInterval%6000)/100);
  strupdate(showModel->durationInterval,3,temp2,2);
  strupdate(showModel->durationInterval,5,":",1);
  int2TabChar(temp2, 2, (model->durationInterval%6000)%100);
  strupdate(showModel->durationInterval,6,temp2,2);

  float2TabChar(showModel->latitude, 2, 3, model->latitude);
  float2TabChar(showModel->longitude, 2, 3, model->longitude);
  float2TabChar(showModel->altitude, 2, 3, model->altitude);
  float2TabChar(showModel->course, 2, 3, model->course);
  float2TabChar(showModel->speed, 2, 3, model->speed);
  showModel->GPSShowDateTime = datetime2Showdatetime(&model->GPSDateTime);

  int2TabChar(showModel->satellites, 2, model->satellites);
  long2TabChar(showModel->hdop, 6, model->hdop);
  strupdate(showModel->recordFilename,0,"EN",2);
  strupdate(showModel->recordFilename,2,showModel->localShowDateTime.year,4);
  strupdate(showModel->recordFilename,6,showModel->localShowDateTime.month,2);
  strupdate(showModel->recordFilename,8,showModel->localShowDateTime.day,2);
  strupdate(showModel->recordFilename,10,showModel->localShowDateTime.hour,2);
  strupdate(showModel->recordFilename,12,showModel->localShowDateTime.minute,2);
  strupdate(showModel->recordFilename,14,showModel->localShowDateTime.second,2);
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

void initShowModel(ShowModel* showModel)
{
	//local prog data
	strupdate(showModel->autonomy,0,"0",1);
	initShowDateTime(&showModel->localShowDateTime);
	strupdate(showModel->durationParcours,0,"0",1);
	strupdate(showModel->durationInterval,0,"0",1);
	//GPS data
	strupdate(showModel->latitude,0,"0",1);strupdate(showModel->longitude,0,"0",1);
	strupdate(showModel->altitude,0,"0",1);strupdate(showModel->course,0,"0",1);
	strupdate(showModel->speed,0,"0",1);
	initShowDateTime(&showModel->GPSShowDateTime);
	strupdate(showModel->satellites,0,"0",1);
	strupdate(showModel->hdop,0,"0",1);
	//recording
	strupdate(showModel->recordFilename,0,"0",1);
  strupdate(showModel->isSDOK,0,"NO",2);
}



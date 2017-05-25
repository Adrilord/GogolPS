#include "model.h"

ShowModel modelToShowModel(Model* model)
{
	ShowModel showModel;
	//~ snprintf(showModel.autonomy, sizeof showModel.autonomy, "%03d", model->autonomy);
	//~ showModel.localShowDateTime = datetime2Showdatetime(&model->localDateTime);
	//~ snprintf(showModel.durationParcours, sizeof showModel.durationParcours, "%02d:%02d:%02d", (model->durationParcours/3600),
		//~ (model->durationParcours%3600)/60,(model->durationParcours%3600)%60);
	//~ snprintf(showModel.durationInterval, sizeof showModel.durationInterval,"%02d:%02d:%02d", (model->durationParcours/6000),
		//~ (model->durationParcours%6000)/100,(model->durationParcours%6000)%100);
	//~ snprintf(showModel.latitude, sizeof showModel.latitude, "%02.3f", model->latitude);
    //~ snprintf(showModel.longitude, sizeof showModel.longitude, "%02.3f", model->longitude);
    //~ snprintf(showModel.altitude, sizeof showModel.altitude, "%02.3f", model->altitude);
    //~ snprintf(showModel.course, sizeof showModel.course, "%02.3f", model->course);
    //~ snprintf(showModel.speed, sizeof showModel.speed, "%02.3f", model->speed);
    //~ showModel.GPSShowDateTime = datetime2Showdatetime(&model->GPSDateTime);
    //~ snprintf(showModel.longitude, sizeof showModel.longitude, "%02.3f", model->longitude);
    //~ snprintf(showModel.satellites, sizeof showModel.satellites, "%02d", model->satellites);
    //~ snprintf(showModel.hdop, sizeof showModel.hdop, "%06ld", model->hdop);
    //~ snprintf(showModel.recordFilename,sizeof showModel.recordFilename,"EN%s%s%s%s%s%s",
		//~ showModel.localShowDateTime.year,showModel.localShowDateTime.month,showModel.localShowDateTime.day
		//~ ,showModel.localShowDateTime.hour,showModel.localShowDateTime.minute,showModel.localShowDateTime.second);
    
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
//	//local prog data
//	strcpy(showModel->autonomy,"");
//	initShowDateTime(&showModel->localShowDateTime);
//	strcpy(showModel->durationParcours,"");
//	strcpy(showModel->durationInterval,"");
//	//GPS data
//	strcpy(showModel->latitude,"");strcpy(showModel->longitude,"");
//	strcpy(showModel->altitude,"");strcpy(showModel->course,"");
//	strcpy(showModel->speed,"");
//	initShowDateTime(&showModel->GPSShowDateTime);
//	strcpy(showModel->satellites,"");
//	strcpy(showModel->hdop,"");
//	//record filename
//	strcpy(showModel->recordFilename,"");
}



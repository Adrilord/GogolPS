#ifndef MODEL
#define MODEL

class Model
{
	private:
		//données prog
		int autonomie; // un % à calculer avec le votage
		DateTime localDateTime;
		int dureeParcours; //en secondes
		int dureeInterval; //en millisecondes
		//données GPS
		double latitude;
		double longitude;
		double altitude;
		int satellites;
		double hdop;
		DateTime GPSdate;
		double speed;
		double course;
}

#include <TinyGPS.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include <Arduino.h>
#include <Bounce2.h>

#define ROWS 2
#define COLS 8
#define NBBUTTONS 3
#define PBP0 16
#define PBP1 15
#define PBPEN 17
#define BBP0 0
#define BBP1 1
#define BBPEN 2
#define INIT 0
#define ENG 1
#define WAIT 2
#define SWX 0
#define SW1 1
#define SW2 2
#define SW3 3
#define SW4 4
#define GPSRX 2
#define GPSTX 3
#define PSD 10
#define ACCUEIL 0
#define COORDS1 1
#define COORDS2 2
#define ENR 3
#define TEMPS_INTERV 5000 // en millis


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

//objets nécessaires pour lire les données transmises par le gps
TinyGPS gps;
SoftwareSerial ss(GPSTX, GPSRX);

//pins des boutons
int buttonPins[NBBUTTONS]={PBP0,PBP1,PBPEN};

//objets nécessairesp pour lire les valeurs et déterminer les états
//des boutons
Bounce debouncer[NBBUTTONS];
int buttonValues[NBBUTTONS]={HIGH,HIGH,HIGH};
int buttonStates[NBBUTTONS]={INIT,INIT,INIT};

//3 states : 0 init, 1 engaged, 2 waiting to desengaged
//2 values : HIGH or LOW
//En fonction des modifications de valeurs des boutons, on change leur état
void readBoutons(Bounce* debouncer , int* buttonStates, int* buttonValues);

//Indique le switch en cours d'activation en fonction des états des boutons
int buttonStatesToSwitchActivated(int* buttonStates);

//Indique le menu actuel
int currentMenu=ACCUEIL;

//pour vérifier le bon fonctionnement des boutons
void testButtons();

//pour ouvrir le fichier d'enregistrement
void initPath();

//pour fermer le fichier d'enregistrement
void closePath();

//pour lire le fichier d'enregistrement
void readPath();

bool isSDOK; //indique si la carte est bien connectée

//informations de model
double batterieVolt=0;
float latitude;
float longitude;
float altitude;
int nb_satellites;
bool started;
byte heure;
byte minute;
byte secondes;

//Paramètres pour le fichier d'enregistrment
char filename[18];
File pathFile;
bool fileOpened;

//timer pour enregistrer de manière périodique les données de model
long timerInterv = millis();

void setup() {
    
    //initialise le lcd
    lcd.begin(COLS,ROWS);

	//initialisation des boutons
    for(int i=0; i<NBBUTTONS; i++) {
    debouncer[i]=Bounce();
    
      // Setup the button with an internal pull-up :
    pinMode(buttonPins[i],INPUT_PULLUP);
  
    // After setting up the button, setup the Bounce instance :
    debouncer[i].attach(buttonPins[i]);
    debouncer[i].interval(5); // interval in ms
    debouncer[i].update();
    buttonValues[i]=debouncer[i].read();
  }
  
  //initialisation de la carte SD
  isSDOK=false;
  if (SD.begin(PSD)){
    isSDOK=true;
  }
  
  //initialisation de l'interface  série Ordinateur/Arduino
  Serial.begin(9600);
  
  //SoftwareSerial setup for the gps
   ss.begin(4800);
  

}

void loop() {

  // récupération des données GPS
  gps.f_get_position(&latitude,&longitude, NULL);
  altitude=gps.f_altitude();
  gps.crack_datetime(NULL,NULL,NULL,&heure,&minute,&secondes,NULL,NULL);
  
  readBoutons(debouncer , buttonStates, buttonValues); // lecture des boutons
  //on détermine quel switch est activé
  int switchActivated = buttonStatesToSwitchActivated(buttonStates);
  //en fonction du switch activé, on effectue une action
  lcd.setCursor(0,0);
  switch(switchActivated) {
    case SW1 :
	   //changement de menu
      Serial.println("SW1");
       currentMenu=(currentMenu+1)%4;
       lcd.clear();
      break;
    case SW2 :
		//début/fin d'enregistrment de parcours (si on est dans le bon menu)
      Serial.println("SW2");
      if(currentMenu==ENR){
        started=!started;
        if(started){
        initPath();
        }else{
        closePath();
       }
      }
      lcd.clear();
      
      break;
    case SW3 :
		//lecture du fichier d'enregistrement sur le moniteur série
       Serial.println("SW3");
       if(currentMenu==ENR){
          readPath();
       }
       lcd.clear();
       break;
     case SW4 :
        //lecture d'informations GPS sur le moniteur série
        Serial.print(longitude);
        Serial.print(",");
        Serial.print(latitude);
        Serial.print(",");
        Serial.println(altitude);
        break;
    default :
      break;
      
  }

  //affiche du menu actuel sur le LCD en fonction de son type
  switch(currentMenu) {
      case ACCUEIL :
        lcd.print("BAT");
        batterieVolt = ((analogRead(0)*6.2)/1023.f)*20;
        lcd.setCursor(4,0);
        lcd.print(batterieVolt,3);
        lcd.setCursor(7,0);
        lcd.print("%");
        lcd.setCursor(0,1);
        lcd.print("SD");
        lcd.setCursor(4,1);
        if(isSDOK){
           lcd.print("OK");
        }else{
          lcd.print("NO");
        }
       
      break;
     case COORDS1 :
        lcd.print(latitude,8);
        lcd.setCursor(0,1);
        lcd.print(longitude,8);

     break;
     case COORDS2:
          lcd.print(altitude,8);
          lcd.setCursor(0,1);
          lcd.print(gps.satellites());
     break;
     case ENR :
        lcd.print((int) heure,2);
        lcd.setCursor(2,0);
        lcd.print(":");
        lcd.setCursor(3,0);
        lcd.print((int) minute,2);
        lcd.setCursor(5,0);
        lcd.print(":");
        lcd.setCursor(6,0);
        lcd.print((int) secondes,2);
        lcd.setCursor(0,1);
        if(started){
          lcd.print("STOP");
        }else{
          lcd.print("START");
        }
          
     break;
  default:
  break; 
  }
  
  //écriture d'une ligne de donénes GPS
  //dans le fichier d'enregistrement si celui si est ouvert et si
  //si le temps est venu (> TEMPS_INTERV)
  if(fileOpened){
    if(millis() - timerInterv > TEMPS_INTERV){
      pathFile.print(longitude,10);
      pathFile.print(",");
      pathFile.print(latitude,10);
      pathFile.print(",");
      pathFile.print(altitude,10);
      pathFile.print(",");
      pathFile.print(gps.satellites());
      pathFile.print(",");
      pathFile.print(heure);
      pathFile.print(",");
      pathFile.print(minute);
      pathFile.print(",");
      pathFile.print(secondes);
      pathFile.print(",");
      pathFile.println(gps.hdop());
      Serial.println("Printing data");
      timerInterv = millis();
    }
  }
 smartdelay(50);  
}

void readBoutons(Bounce* debouncer , int* buttonStates, int* buttonValues)
{
    for(int i=0; i<NBBUTTONS; i++) {
      //Wait mode
      if(buttonStates[i] == 1) {
         buttonStates[i] = 2;
      }
        // Update the Bounce instance :
      debouncer[i].update();
      int value = debouncer[i].read();
      if ( value != buttonValues[i]) {
        buttonValues[i] = value;
        buttonStates[i] = (buttonStates[i] + 1)%3; //buttonStates is either 0 or 2
      }
  }
}

int buttonStatesToSwitchActivated(int* buttonStates)
{
  if(buttonStates[BBP0]!=ENG && buttonStates[BBP1]!=ENG && buttonStates[BBPEN]==ENG) {
    return SW1;
  } else if (buttonStates[BBP0]==ENG && buttonStates[BBP1]!=ENG && buttonStates[BBPEN]==ENG) {
    return SW2;
  } else if (buttonStates[BBP0]!=ENG && buttonStates[BBP1]==ENG && buttonStates[BBPEN]==ENG) {
    return SW3;
  } else if (buttonStates[BBP0]==ENG && buttonStates[BBP1]==ENG && buttonStates[BBPEN]==ENG) {
    return SW4;
  } else {
    return SWX;
  }
}


static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}


void initPath()
{
  fileOpened=1;
  SD.remove("pathFile.txt");
  pathFile=SD.open("pathFile.txt",FILE_WRITE); //pas de caractères spéciaux dans le nom du fichier!
  Serial.println("File created");
}

void closePath(){

    pathFile.close();
    fileOpened=0;
    Serial.println("File closed");
  
}

void readPath(){
  pathFile = SD.open("pathFile.txt",FILE_READ);
  if (pathFile) 
  {
    while (pathFile.available())
    {
      Serial.write(pathFile.read());
    }
    pathFile.close();
  }  
  else {
    Serial.println("error opening the pathFile");
  } 

}


  



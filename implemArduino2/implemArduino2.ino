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



// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

//GPS
TinyGPS gps;
SoftwareSerial ss(GPSTX, GPSRX);

//button pins
int buttonPins[NBBUTTONS]={PBP0,PBP1,PBPEN};

// Instantiate a Bounce object
Bounce debouncer[NBBUTTONS];
int buttonValues[NBBUTTONS]={HIGH,HIGH,HIGH};
int buttonStates[NBBUTTONS]={INIT,INIT,INIT};

void readBoutons(Bounce* debouncer , int* buttonStates, int* buttonValues);

//return switchActivated
int buttonStatesToSwitchActivated(int* buttonStates);

int currentMenu=ACCUEIL;

void testButtons();

void savePath();

void closePath();

void readPath();

bool isSDOK;
double batterieVolt=0;
float latitude;
float longitude;
float altitude;
int nb_satellites;
bool started;
byte heure;
byte minute;
byte secondes;

//quand on passe de stopped a started on cree un fichier horodaté dans la fonction recordParam
//d'abord reussir a creer un fichier enregistrer les données et le lire, puis horodatage, puis eventuellment rajouter un menu pour la selection des fichiers,
//pour l'envoi des fichiers,et peut etre la suppression
char filename[18];
int compteur=0;

File pathFile;
bool fileOpened;

void setup() {
    
    lcd.begin(COLS,ROWS);

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
  
  isSDOK=false;
  if (SD.begin(PSD)){
    isSDOK=true;
  }
  
  
  Serial.begin(9600);
  
  //SoftwareSerial setup for the gps
   ss.begin(4800);
  

}

void loop() {

  gps.f_get_position(&latitude,&longitude, NULL);
  altitude=gps.f_altitude();
  gps.crack_datetime(NULL,NULL,NULL,&heure,&minute,&secondes,NULL,NULL);
  
  readBoutons(debouncer , buttonStates, buttonValues);
  int switchActivated = buttonStatesToSwitchActivated(buttonStates);
  lcd.setCursor(0,0);
  switch(switchActivated) {
    case SW1 :
      Serial.println("SW1");
       currentMenu=(currentMenu+1)%4;
       lcd.clear();
       
      break;
    case SW2 :
      Serial.println("SW2");
      if(currentMenu==ENR){

        started=!started;
        if(started){
        savePath();
        }else{
        closePath();
       }
                }
      lcd.clear();
      
      break;
    case SW3 :
       Serial.println("SW3");
       if(currentMenu==ENR){
          readPath();
       }
       lcd.clear();
       break;
     case SW4 :
        Serial.print(longitude);
        Serial.print(",");
        Serial.print(latitude);
        Serial.print(",");
        Serial.println(altitude);
        break;
    default :
      break;
      
  }

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
        lcd.print(heure,2);
        lcd.setCursor(2,0);
        lcd.print(":");
        lcd.setCursor(3,0);
        lcd.print(minute,2);
        lcd.setCursor(5,0);
        lcd.print(":");
        lcd.setCursor(6,0);
        lcd.print(secondes,2);
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

  if(fileOpened){
    if(compteur%21==0){
      pathFile.print(longitude);
      pathFile.print(",");
      pathFile.print(latitude);
      pathFile.print(",");
      pathFile.println(altitude);
    }
  }
 
 compteur=(compteur+1)%21;
 Serial.println(compteur);
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


void savePath()
{
  fileOpened=1;
  pathFile=SD.open("pathFile.txt",FILE_WRITE); //pas de caractères spéciaux dans le nom du fichier!
  Serial.println("File created");
}

void closePath(){

    pathFile.close();
    fileOpened=0;
    Serial.println("File closed");
  
}

void readPath(){
  SD.open("pathFile.txt",FILE_READ);
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


  



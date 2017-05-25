//trouver une structure pour assigner plusieurs fonctions a un bouton (par exemple en en maintenant deux en meme temps) si possible

#include <LiquidCrystal.h>
#include <Bounce2.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

const int nbButtons=3;
const double lat_scd = 48.26893;
const double lng_scd = 4.066073;

int buttonPins[nbButtons]={16,15,17};

Bounce debouncer[nbButtons];

LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

TinyGPSPlus gps;
static const uint32_t GPSBaud = 4800;

//declaration des pins du gps
SoftwareSerial ss(3, 2);

void setup() {
  lcd.begin(8, 2);

  Serial.begin(115200);
  ss.begin(GPSBaud);

  for(int i=0; i<nbButtons; i++) {
    debouncer[i]=Bounce();
    pinMode(buttonPins[i],INPUT_PULLUP);
    debouncer[i].attach(buttonPins[i]);
    debouncer[i].interval(5); // interval in ms
  }
}

void loop() {
  lcd.clear();
  
  while (ss.available() >0){
   gps.encode(ss.read());
   }
  

  for(int i=0; i<nbButtons; i++) {
        // Update the Bounce instance :
      debouncer[i].update();
    
      // Get the updated value :
      int value = debouncer[i].read();
      
//au scd ca donne lat=48.26893 et long=4.066073 ; date=2032(?); alt environ 122 metres ->correct

      if ( value == HIGH ) {
      } else {
        if(digitalRead(17)==HIGH){
          lcd.setCursor(0, 0);
          if(digitalRead(15)==LOW && digitalRead(16)==LOW ){
              lcd.print("Latitude:");
              lcd.setCursor(0, 1);
              lcd.print(gps.location.lat(), 6);
          }else if(digitalRead(15)==LOW && digitalRead(16)==HIGH ){
            lcd.print("Longitude:");
            lcd.setCursor(0, 1);
            lcd.print(gps.location.lng(), 6);
          }else if(digitalRead(15)==HIGH && digitalRead(16)==LOW ){
            lcd.print("Alt:");
            lcd.setCursor(0, 1);
            lcd.print(gps.altitude.meters());
          }else if(digitalRead(15)==HIGH && digitalRead(16)==HIGH ){
            //distance jusqu'au scd
            lcd.print("Distance");
            lcd.setCursor(0, 1);
            lcd.print(gps.distanceBetween(gps.location.lat(),gps.location.lng(),lat_scd,lng_scd));
          }
      
        }else{
        
        }
      }
 
  }
  delay(100);
}

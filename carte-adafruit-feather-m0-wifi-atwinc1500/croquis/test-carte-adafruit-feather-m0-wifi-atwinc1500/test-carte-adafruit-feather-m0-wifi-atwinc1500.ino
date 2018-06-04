#include <LiquidCrystal.h>
#include "MMA_7455.h"

LiquidCrystal lcd (18, 17, 16, 15, 14, 19) ; // Feather M0 Wifi
MMA_7455 accelerometer ;
 
void setup() {
  pinMode (LED_BUILTIN, OUTPUT);
  digitalWrite (LED_BUILTIN, HIGH) ;
  Serial.begin (9600) ;
  Serial1.begin (19200) ;
  lcd.begin (20, 4); // Utilisation d'un écran 20 colonnes et 4 lignes
  accelerometer.begin () ;
 //--- Set the g force sensitivity: 2=2g, 4=4g, 8-8g
  accelerometer.initSensitivity (2) ;
 //--- Update the numbers with your own values from the MMA7455_CalibrateOffset sketch.
//  accelerometer.calibrateOffset (0, 0, 0) ;
}

byte etatEntrees = 0 ;
static unsigned dateLectureAccelerometre ;
byte valeurEncodeur = 0 ;

void loop () {
  if (dateLectureAccelerometre < millis ()) {
    dateLectureAccelerometre += 500 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  //--- Get the X, Y, and Z axis values from the device
    const int8_t xVal = accelerometer.readXAxis ();   // Read X Axis
    const int8_t yVal = accelerometer.readYAxis ();   // Read Y Axis
    const int8_t zVal = accelerometer.readZAxis ();   // Read Z Axis
    lcd.setCursor (0, 0) ;
    for (int i=0 ; i<20 ; i++) {
      lcd.print (" ") ;
    }
    lcd.setCursor (0, 0) ;
    lcd.print ("X=") ;
    lcd.print (xVal) ;
    lcd.print (", Y=") ;
    lcd.print (yVal) ;
    lcd.print (", Z=") ;
    lcd.print (zVal) ;
  }
  if (Serial1.available () > 0) {
    const byte nouvelEtat = Serial1.read () ;
    Serial.println (nouvelEtat) ;
    const byte leds = nouvelEtat & 0x0F ;
    if (etatEntrees != leds) {
      etatEntrees = leds ;
//      Serial1.write (6) ;
      Serial1.write (((etatEntrees & 1) != 0) ? 4 : 0) ;
      Serial1.write (((etatEntrees & 2) != 0) ? 5 : 1) ;
      Serial1.write (((etatEntrees & 4) != 0) ? 6 : 2) ;
      Serial1.write (((etatEntrees & 8) != 0) ? 7 : 3) ;
 //     Serial1.flush () ;
    }
    if ((nouvelEtat & 0x30) != 0) { // Modification encodeur
      bool afficherEncodeur = false ;
      if (((nouvelEtat & 0x10) != 0) && (valeurEncodeur < 255)) {
        valeurEncodeur += 1 ;
        afficherEncodeur = true ;
      }else if (((nouvelEtat & 0x20) != 0) && (valeurEncodeur > 0)) {
        valeurEncodeur -= 1 ;
        afficherEncodeur = true ;
      }
      if (afficherEncodeur) {
        lcd.setCursor (0, 1) ;
        lcd.print ("Encodeur : ") ;
        lcd.print (valeurEncodeur) ;
        lcd.print ("  ") ;
      }
    }
  }
//  Serial1.print (x) ;
//  x ++ ;
//  if (x == '8') {
//    x = '0' ;
//  }
}


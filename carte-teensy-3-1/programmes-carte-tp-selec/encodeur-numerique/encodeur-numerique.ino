#include "LiquidCrystal.h"

LiquidCrystal lcd (18, 17, 16, 15, 14, 19); //liaison 4 bits de données

void setup() {
  pinMode (3, OUTPUT) ;
  pinMode (4, OUTPUT) ;
  pinMode (5, OUTPUT) ;
  pinMode (6, OUTPUT) ;
  pinMode (7, OUTPUT) ;
  pinMode (13, OUTPUT) ;
  pinMode (0, INPUT_PULLUP) ;
  pinMode (1, INPUT_PULLUP) ;
  lcd.begin(20,4); //utilisation d'un écran 20 colonnes et 4 lignes
  lcd.write ("Hello World!"); //petit test pour vérifier que tout marche
}

volatile int gEncodeur = 0 ;
int gEncodeurCache = 0 ;
bool gEncoderA = false ;

void encoderHandler (void) {
  const bool encoderA = digitalRead (0) ;
  if (encoderA && !gEncoderA) {
    if ((gEncodeur < 63) && !digitalRead (1)) {
      gEncodeur ++ ;
    }else if ((gEncodeur > 0) && digitalRead (1)) {
      gEncodeur -- ;
    }
  }
  gEncoderA = encoderA ;
}

void loop() {
  delay (1) ;
  encoderHandler () ;
  if (gEncodeurCache != gEncodeur) {
    gEncodeurCache = gEncodeur ;
    lcd.setCursor (0, 0) ;
    lcd.print ("  ") ;
    lcd.setCursor (0, 0) ;
    lcd.print (gEncodeurCache) ;
  }
  digitalWrite (13, !digitalRead (13)) ;
}


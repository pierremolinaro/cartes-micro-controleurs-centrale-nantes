#include "LiquidCrystal.h"
#include "TimerOne.h"

LiquidCrystal lcd (18, 17, 16, 15, 14, 19); //liaison 4 bits de données

void setup() {
  pinMode (13, OUTPUT) ;
  pinMode (0, INPUT_PULLUP) ;
  pinMode (1, INPUT_PULLUP) ;
  lcd.begin(20,4); //utilisation d'un écran 20 colonnes et 4 lignes
  lcd.write ("Hello World!"); //petit test pour vérifier que tout marche
  Timer1.initialize (1000) ; // 1000 micro s.
  Timer1.attachInterrupt (encoderHandler);
}

volatile int gEncodeur = 0 ;
int gEncodeurCache = 0 ;
bool gEncoderA = false ;
int gClignotement = 0 ;

void encoderHandler (void) {
  const bool encoderA = digitalRead (0) ;
  if (encoderA && !gEncoderA) {
    const bool encoderB = digitalRead (1) ;
    if ((gEncodeur < 63) && !encoderB) {
      gEncodeur ++ ;
    }else if ((gEncodeur > 0) && encoderB) {
      gEncodeur -- ;
    }
  }
  gEncoderA = encoderA ;
  gClignotement ++ ;
  if (gClignotement == 500) {
    gClignotement = 0 ;
    digitalWrite (13, !digitalRead (13)) ;
  }
}

void loop() {
  delay (100) ;
  if (gEncodeurCache != gEncodeur) {
    gEncodeurCache = gEncodeur ;
    lcd.setCursor (0, 0) ;
    lcd.print ("  ") ;
    lcd.setCursor (0, 0) ;
    lcd.print (gEncodeurCache) ;
  }
}


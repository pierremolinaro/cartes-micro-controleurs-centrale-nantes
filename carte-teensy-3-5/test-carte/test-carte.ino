//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
//  Programme de test de la carte Teensy 3.5 pour vérifier que tout marche
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#ifndef __MK64FX512__
  #error "Ce sketch doit être compilé pour la Teensy 3.5"
#endif

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <LiquidCrystal.h>
#include <TimerOne.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

LiquidCrystal lcd (18, 17, 16, 15, 14, 19); //liaison 4 bits de données

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void setup() {
  pinMode (3, OUTPUT) ;
  pinMode (4, OUTPUT) ;
  pinMode (5, OUTPUT) ;
  pinMode (6, OUTPUT) ;
  pinMode (7, OUTPUT) ;
  pinMode (13, OUTPUT) ;
  pinMode (8, INPUT_PULLUP) ;
  pinMode (9, INPUT_PULLUP) ;
  pinMode (10, INPUT_PULLUP) ;
  pinMode (11, INPUT_PULLUP) ;
  pinMode (12, INPUT_PULLUP) ;
  pinMode (2, INPUT_PULLUP) ; // ENCODER CLIC
  pinMode (25, INPUT_PULLUP) ; // ENCODER B
  pinMode (24, INPUT_PULLUP) ; // ENCODER A
  lcd.begin (20,4) ; //utilisation d'un écran 20 colonnes et 4 lignes
  lcd.write ("Programme de test"); //petit test pour vérifier que tout marche
  Timer1.initialize (1000) ; // 1000 micro s.
  Timer1.attachInterrupt (encoderHandlerISR);
}

volatile int gEncodeur = 0 ;
int gEncodeurCache = 0 ;
bool gEncoderA = false ;
int gClignotement = 0 ;

void encoderHandlerISR (void) {
  const bool encoderA = digitalRead (24) ;
  if (encoderA && !gEncoderA) {
    if ((gEncodeur < 63) && !digitalRead (25)) {
      gEncodeur ++ ;
    }else if ((gEncodeur > 0) && digitalRead (25)) {
      gEncodeur -- ;
    }
  }
  gEncoderA = encoderA ;
  gClignotement ++ ;
  if (gClignotement == 250) {
    gClignotement = 0 ;
    digitalWrite (13, !digitalRead (13)) ;
  }
}


void loop() {
  delay (100) ;
  digitalWrite (3, ! digitalRead (8)) ;
  digitalWrite (4, ! digitalRead (9)) ;
  digitalWrite (5, ! digitalRead (10)) ;
  digitalWrite (6, ! digitalRead (11)) ;
  digitalWrite (7, ! digitalRead (12)) ;
  lcd.setCursor (0, 3) ;
  if (!digitalRead (2)) {
    lcd.print ("CLIC") ;
  }else{
    lcd.print ("    ") ;
  }
  if (gEncodeurCache != gEncodeur) {
    gEncodeurCache = gEncodeur ;
    lcd.setCursor (0, 1) ;
    lcd.print ("  ") ;
    lcd.setCursor (0, 1) ;
    lcd.print (gEncodeurCache) ;
  }
}

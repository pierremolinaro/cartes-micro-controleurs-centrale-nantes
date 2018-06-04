#include "LiquidCrystal.h"
#include "TimerOne.h"
#include "MsTimer2.h"

// https://www.pjrc.com/teensy/td_pulse.html

LiquidCrystal lcd (18, 17, 16, 15, 14, 19); //liaison 4 bits de données

void setup() {
//  pinMode (3, OUTPUT) ;
//  pinMode (4, OUTPUT) ;
  pinMode (5, OUTPUT) ;
  pinMode (6, OUTPUT) ;
  pinMode (7, OUTPUT) ;
  pinMode (13, OUTPUT) ;
  pinMode (0, INPUT_PULLUP) ;
  pinMode (1, INPUT_PULLUP) ;
  lcd.begin(20,4); //utilisation d'un écran 20 colonnes et 4 lignes
  lcd.write ("Hello World!"); //petit test pour vérifier que tout marche
  MsTimer2::set (1, encoderHandler) ; // 1ms
  MsTimer2::start () ;
//  Timer1.initialize (1000) ; // 1000 micro s.
//  Timer1.attachInterrupt (encoderHandler);
  analogWriteFrequency (23, 25000); // PWM Frequency 25 kHz
  analogWriteResolution (6);  // analogWrite value 0 to 63
  analogWriteFrequency (4, 25); // PWM Frequency 50Hz
}

volatile int gEncodeur = 0 ;
int gEncodeurCache = 0 ;
bool gEncoderA = false ;
int gClignotement = 0 ;

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
  gClignotement ++ ;
  if (gClignotement == 500) {
    gClignotement = 0 ;
    digitalWrite (13, !digitalRead (13)) ;
  }
}

void loop() {
  delay (100) ;
  if (gEncodeurCache != gEncodeur) {
    analogWrite (23, gEncodeur) ;
    gEncodeurCache = gEncodeur ;
    lcd.setCursor (0, 0) ;
    lcd.print ("  ") ;
    lcd.setCursor (0, 0) ;
    lcd.print (gEncodeurCache) ;
  }
}


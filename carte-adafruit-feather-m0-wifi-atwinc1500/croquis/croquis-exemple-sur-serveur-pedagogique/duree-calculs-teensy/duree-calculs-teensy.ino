#include "fonctionVide.h"
#include "division-entiere.h"
#include "division-flottante.h"
#include "division-double.h"
#include "LiquidCrystal.h"

LiquidCrystal lcd (18, 17, 16, 15, 14, 19); // Liaison 4 bits de données

static const uint32_t NOMBRE_ITERATIONS = 100000 ;

void setup() {
  pinMode (LED_BUILTIN, OUTPUT);
  digitalWrite (LED_BUILTIN, HIGH) ;
  lcd.begin (20, 4); // Utilisation d'un écran 20 colonnes et 4 lignes
  Serial.println ("C'est parti") ;
//---  Fonction vide
  delay (100) ;
  const uint32_t t0 = millis () ;
  for (uint32_t i = 0 ; i < NOMBRE_ITERATIONS ; i++) {
    fonctionVide () ;
  }
  const uint32_t dureeAppelsFonctionVide = millis () - t0 ;
  lcd.print (dureeAppelsFonctionVide) ;
//--- Division entière 32 bits
  delay (100) ;
  const uint32_t t1 = millis () ;
  uint32_t cumul = 0 ;
  for (uint32_t i = 0 ; i < NOMBRE_ITERATIONS ; i++) {
    cumul += divisionEntiere32bits (i) ;
  }
  const uint32_t dureeAppelsDivisionEntiere = millis () - t1 ;
  lcd.setCursor (0, 1) ;
  lcd.print (dureeAppelsDivisionEntiere) ;
  //--- Division flottante 32 bits
  delay (100) ;
  const uint32_t t2 = millis () ;
  float fcumul = 0.0 ;
  for (uint32_t i = 0 ; i < NOMBRE_ITERATIONS ; i++) {
    fcumul += divisionFlottante ((float) i) ;
  }
  const uint32_t dureeAppelsDivisionFlottante = millis () - t2 ;
  lcd.setCursor (0, 2) ;
  lcd.print (dureeAppelsDivisionFlottante) ;
  //--- Division flottante 64 bits
  delay (100) ;
  const uint32_t t3 = millis () ;
  double dcumul = 0.0 ;
  for (uint32_t i = 0 ; i < NOMBRE_ITERATIONS ; i++) {
    dcumul += divisionDouble ((double) i) ;
  }
  const uint32_t dureeAppelsDivisionDouble = millis () - t3 ;
  lcd.setCursor (0, 3) ;
  lcd.print (dureeAppelsDivisionDouble) ;
}


void loop () {
  delay (500) ;
  digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
}


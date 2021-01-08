#include <LiquidCrystal.h>
#include "sram-externe.h"

//--------------------------------------------------------------------------------------------------

LiquidCrystal lcd (PD6, PD7, PG6, PC0, PD2, PD3) ;

//--------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin (38400) ;
  while (!Serial) {}
  pinMode (PE1, OUTPUT) ;
  configurerAccesRamExterne () ;
  lcd.begin (20, 4) ;
  lcd.print ("Test Ram externe") ;
  lcd.setCursor (0, 1) ;
  lcd.print ("Duree test ") ;
  lcd.setCursor (0, 2) ;
  lcd.print ("Nombre tests ") ;
  lcd.setCursor (0, 3) ;
  lcd.print ("Erreurs ") ;
}

//--------------------------------------------------------------------------------------------------

static uint32_t gEcheance = 0 ;
static uint8_t gValue = 0 ;
static uint32_t gErreurs = 0 ;
static uint32_t gNombreTests = 0 ;

//--------------------------------------------------------------------------------------------------

void loop() {
  if (gEcheance < millis ()) {
    gEcheance += 1000 ;
    digitalWrite (PE1, !digitalRead (PE1)) ;
    const uint32_t instantDebut = millis () ;
    const uint32_t nbErreurs = testRamExterne () ;
    gErreurs += nbErreurs ;
    gNombreTests += 1 ;
    const uint32_t duree = millis () - instantDebut ;
    lcd.setCursor (13, 1) ; lcd.print (duree) ; lcd.print (" ms") ;
    lcd.setCursor (13, 2) ; lcd.print (gNombreTests) ;
    lcd.setCursor (8, 3) ; lcd.print (gErreurs) ;
  }
}

//--------------------------------------------------------------------------------------------------

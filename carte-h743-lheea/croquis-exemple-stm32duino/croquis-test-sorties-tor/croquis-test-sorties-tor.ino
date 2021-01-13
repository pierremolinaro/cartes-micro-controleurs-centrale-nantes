#include "STM32H743-configuration-lheea.h"

//--------------------------------------------------------------------------------------------------

void setup() {
  configurerCarteH743LHEEA () ;
  fixerGammeEncodeur (-10, 10) ;
  lcd.print ("Test TOR") ;
  lcd.setCursor (17, 0) ;
  lcd.print (NUM_DIGITAL_PINS) ; // DOIT AFFICHER 100
  lcd.setCursor (0, 1) ;
  lcd.print ("Sortie active :") ;
}

//--------------------------------------------------------------------------------------------------

static uint32_t gEcheance = 1000 ;
static uint32_t gSortieTOR = 0 ;

//--------------------------------------------------------------------------------------------------

void loop() {
  if (gEcheance < millis ()) {
    gEcheance += 1000 ;
    digitalWrite (NUCLEO_LD3_ROUGE, !digitalRead (NUCLEO_LD3_ROUGE)) ;
  //--- Sortie TOR
    const uint32_t idx = (gSortieTOR + 10 - 1) % 10 ;
    activerSortieTOR (idx, false) ;
    activerSortieTOR (gSortieTOR, true) ;
    lcd.setCursor (16, 1) ;
    lcd.print (gSortieTOR) ;
    gSortieTOR = (gSortieTOR + 1) % 10 ;
  }
}

//--------------------------------------------------------------------------------------------------

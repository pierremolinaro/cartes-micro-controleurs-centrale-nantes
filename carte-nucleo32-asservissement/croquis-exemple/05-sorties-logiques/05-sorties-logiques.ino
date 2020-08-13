
#include "carte-asservissement.h"

//--------------------------------------------------------

void setup () {
  configurerCarteAsservissement () ;
  fixerGammeEncodeur (-10, 10) ;
  lcd.print ("Sorties logiques") ;
  lcd.setCursor (0, 1) ;
  lcd.print ("Appuyer sur les") ;
  lcd.setCursor (0, 2) ;
  lcd.print ("poussoirs P0 a P3") ;
}

//--------------------------------------------------------

static uint32_t gInstantClignotement = 0 ;

//--------------------------------------------------------

void loop () {
//--- Première action : clignotement led
  if (gInstantClignotement <= millis ()) {
  //--- Calcul de la prochaine échéance
    gInstantClignotement += 1000 ;
  //--- Faire clignoter LED_BUILTIN
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
//--- Deuxième action
  actionSortieLogique (SORTIE_LOGIQUE::S1, etatClic ()) ;
}

//--------------------------------------------------------

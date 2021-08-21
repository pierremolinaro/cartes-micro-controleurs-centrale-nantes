
#include "carte-asservissement.h"

//--------------------------------------------------------

void setup () {
  configurerCarteAsservissement () ;
//--- Après la configuration, le curseur est au début (à gauche) de la première ligne
  lcd.print ("Test leds/poussoirs") ;
  lcd.setCursor (0, 1) ;
  lcd.print ("Appuyer") ;
  lcd.setCursor (0, 2) ;
  lcd.print ("sur les poussoirs") ;
}

//--------------------------------------------------------

static uint32_t gInstantClignotement = 0 ;
static uint32_t gInstantAffichage = 0 ;

//--------------------------------------------------------

void loop () {
//--- Première action : clignotement led
  if (gInstantClignotement <= millis ()) {
  //--- Calcul de la prochaine échéance
    gInstantClignotement += 500 ;
  //--- Faire clignoter LED_BUILTIN
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
//--- Deuxième action : affichage
  if (gInstantAffichage <= millis ()) {
  //--- Calcul de la prochaine échéance
    gInstantAffichage += 1000 ;
  //--- Affichage au début de la 2e ligne
    lcd.setCursor (0, 3) ;
    lcd.print (millis ()) ;
  }
  actionLed (LED::L0, etatPoussoir (POUSSOIR::P0)) ;
  actionLed (LED::L1, etatPoussoir (POUSSOIR::P1)) ;
  actionLed (LED::L2, etatPoussoir (POUSSOIR::P2)) ;
  actionLed (LED::L3, etatPoussoir (POUSSOIR::P3)) ;
  actionLed (LED::L4, etatPoussoir (POUSSOIR::P4)) ;
}

//--------------------------------------------------------


#include "carte-asservissement.h"

//--------------------------------------------------------

void setup () {
  configurerCarteAsservissement () ;
//--- Après la configuration, le curseur est au début (à gauche) de la première ligne
  lcd.print ("Hello") ;
}

//--------------------------------------------------------

static uint32_t gInstantClignotement = 0 ;
static uint32_t gInstantAffichage = 0 ;

//--------------------------------------------------------

void loop () {
//--- Première action : clignotement led
  if (gInstantClignotement <= millis ()) {
  //--- Calcul de la prochaine échéance
    gInstantClignotement += 100 ;
  //--- Faire clignoter LED_BUILTIN
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
//--- Deuxième action : affichage
  if (gInstantAffichage <= millis ()) {
  //--- Calcul de la prochaine échéance
    gInstantAffichage += 1000 ;
  //--- Affichage au début de la 2e ligne
    lcd.setCursor (0, 1) ;
    lcd.print (millis ()) ;
  }
}

//--------------------------------------------------------

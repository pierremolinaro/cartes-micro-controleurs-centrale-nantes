
#include "carte-asservissement.h"

//--------------------------------------------------------

void setup () {
  configurerCarteAsservissement () ;
//--- Après la configuration, le curseur est au début (à gauche) de la première ligne
  lcd.print ("Hello") ;
}

//--------------------------------------------------------

void loop () {
//--- Affichage au début de la 2e ligne
  lcd.setCursor (0, 1) ;
  lcd.print (millis ()) ;
//--- Faire clignoter LED_BUILTIN
  digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
//--- Attendre
  delay (1000) ;
}

//--------------------------------------------------------

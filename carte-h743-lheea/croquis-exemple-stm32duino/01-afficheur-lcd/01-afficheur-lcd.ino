#include "STM32H743-configuration-lheea.h"

//--------------------------------------------------------

void setup () {
  configurerCarteH743LHEEA () ;
//--- Après la configuration, le curseur est au début (à gauche) de la première ligne
  lcd.print ("Test afficheur LCD") ;
}

//--------------------------------------------------------

void loop () {
//--- Affichage au début de la 2e ligne
  lcd.setCursor (0, 1) ;
  lcd.print (millis ()) ;
//--- Faire clignoter LED_BUILTIN
  digitalWrite (NUCLEO_LD2_JAUNE, !digitalRead (NUCLEO_LD2_JAUNE)) ;
//--- Attendre
  delay (1000) ;
}

//--------------------------------------------------------

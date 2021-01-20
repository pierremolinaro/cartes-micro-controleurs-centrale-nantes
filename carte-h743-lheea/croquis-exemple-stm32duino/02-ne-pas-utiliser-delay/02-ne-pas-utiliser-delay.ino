#include "STM32H743-configuration-lheea.h"

//--------------------------------------------------------

void setup () {
  configurerCarteH743LHEEA () ;
//--- Après la configuration, le curseur est au début (à gauche) de la première ligne
  lcd.print ("Actions periodiques") ;
}

//--------------------------------------------------------

static uint32_t gInstantClignotementLedNucleoVerte = 0 ;
static uint32_t gInstantClignotementLedNucleoJaune = 0 ;
static uint32_t gInstantClignotementLedNucleoRouge = 0 ;
static uint32_t gInstantAffichage = 0 ;

//--------------------------------------------------------

void loop () {
//--- Première action : clignotement led Nucleo verte
  if (gInstantClignotementLedNucleoVerte <= millis ()) {
  //--- Calcul de la prochaine échéance
    gInstantClignotementLedNucleoVerte += 100 ;
  //--- Faire clignoter la led
    digitalWrite (NUCLEO_LD1_VERTE, !digitalRead (NUCLEO_LD1_VERTE)) ;
  }
//--- Deuxième action : clignotement led Nucleo jaune
  if (gInstantClignotementLedNucleoJaune <= millis ()) {
  //--- Calcul de la prochaine échéance
    gInstantClignotementLedNucleoJaune += 123 ;
  //--- Faire clignoter la led
    digitalWrite (NUCLEO_LD2_JAUNE, !digitalRead (NUCLEO_LD2_JAUNE)) ;
  }
//--- Troisième action : clignotement led Nucleo rouge
  if (gInstantClignotementLedNucleoRouge <= millis ()) {
  //--- Calcul de la prochaine échéance
    gInstantClignotementLedNucleoRouge += 133 ;
  //--- Faire clignoter la led
    digitalWrite (NUCLEO_LD3_ROUGE, !digitalRead (NUCLEO_LD3_ROUGE)) ;
  }
//--- Quatrième action : affichage
  if (gInstantAffichage <= millis ()) {
  //--- Calcul de la prochaine échéance
    gInstantAffichage += 1000 ;
  //--- Affichage au début de la 2e ligne
    lcd.setCursor (0, 1) ;
    lcd.print (millis ()) ;
  }
}

//--------------------------------------------------------

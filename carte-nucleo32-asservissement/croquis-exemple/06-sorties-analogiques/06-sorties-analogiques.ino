
#include "carte-asservissement.h"

//--------------------------------------------------------

void setup () {
  configurerCarteAsservissement () ;
  fixerGammeEncodeur (0, 63) ;
  lcd.print ("E/S analogiques") ;
  lcd.setCursor (0, 1) ;
  lcd.print ("Sorties :") ;
  lcd.setCursor (0, 2) ;
  lcd.print ("Entree 0 :") ;
  lcd.setCursor (0, 3) ;
  lcd.print ("Entree 1 :") ;
}

//--------------------------------------------------------

static uint32_t gInstantClignotement = 0 ;
static uint32_t gInstantLectureAnalogique = 0 ;
static int32_t  gValeurEncodeur = -1 ;
static uint16_t gEntreeAnalogique0 = 0 ;
static uint16_t gEntreeAnalogique1 = 0 ;

//--------------------------------------------------------

void loop () {
//--- Première action : clignotement led
  if (gInstantClignotement <= millis ()) {
  //--- Calcul de la prochaine échéance
    gInstantClignotement += 1000 ;
  //--- Faire clignoter LED_BUILTIN
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
//--- Deuxième action : lire l'encodeur pour fixer les sorties analogiques
  const int32_t encodeur = valeurEncodeur () ;
  if (gValeurEncodeur != encodeur) {
    gValeurEncodeur = encodeur ;
    const uint8_t commande = (uint8_t (encodeur) << 2) | (uint8_t (encodeur) >> 4) ;
    actionSortieAnalogique (SORTIE_ANALOGIQUE::S0, commande) ;
    actionSortieAnalogique (SORTIE_ANALOGIQUE::S1, 255 - commande) ;
    lcd.setCursor (10, 1) ;
    lcd.print ("   ") ;
    lcd.setCursor (10, 1) ;
    lcd.print (commande) ;
  }
//--- Troisième action : lire les entrées analogiques
  if (gInstantLectureAnalogique <= millis ()) {
    gInstantLectureAnalogique += 100 ;
    const uint16_t entree0 = lireEntreeAnalogique (ENTREE_ANALOGIQUE::E0) ;
    if (gEntreeAnalogique0 != entree0) {
      gEntreeAnalogique0 = entree0 ;
      lcd.setCursor (11, 2) ;
      lcd.print ("    ") ;
      lcd.setCursor (11, 2) ;
      lcd.print (entree0) ;
    }
    const uint16_t entree1 = lireEntreeAnalogique (ENTREE_ANALOGIQUE::E1) ;
    if (gEntreeAnalogique1 != entree1) {
      gEntreeAnalogique1 = entree1 ;
      lcd.setCursor (11, 3) ;
      lcd.print ("    ") ;
      lcd.setCursor (11, 3) ;
      lcd.print (entree1) ;
    }
  }
}

//--------------------------------------------------------

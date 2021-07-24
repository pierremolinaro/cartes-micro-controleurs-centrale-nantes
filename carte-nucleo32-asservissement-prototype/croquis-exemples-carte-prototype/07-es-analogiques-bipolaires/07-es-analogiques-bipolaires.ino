
#include "carte-asservissement.h"

//--------------------------------------------------------

void setup () {
  configurerCarteAsservissement () ;
  fixerGammeEncodeur (0, 63) ;
  lcd.print ("E/S analog. -10V:10V") ;
  lcd.setCursor (0, 1) ;
  lcd.print ("S0,S1:") ;
  lcd.setCursor (0, 2) ;
  lcd.print ("E0:") ;
  lcd.setCursor (0, 3) ;
  lcd.print ("E1:") ;
}

//--------------------------------------------------------

static uint32_t gInstantClignotement = 0 ;
static uint32_t gInstantLectureAnalogique = 0 ;
static int32_t  gValeurEncodeur = -1 ;
static uint16_t gEntreeAnalogique0 = UINT16_MAX ;
static uint16_t gEntreeAnalogique1 = UINT16_MAX ;

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
    actionSortieAnalogique (SORTIE_ANALOGIQUE::S1, commande) ;
    lcd.setCursor (7, 1) ;
    lcd.print ("             ") ;
    lcd.setCursor (7, 1) ;
    lcd.print (commande) ;
    lcd.print (" -> ") ;
    lcd.print (float (commande) * 0.082824 - 10.56) ;
    lcd.print ("V") ;
  }
//--- Troisième action : lire les entrées analogiques
  if (gInstantLectureAnalogique <= millis ()) {
    gInstantLectureAnalogique += 500 ;
    const uint16_t entree0 = lireEntreeAnalogique (ENTREE_ANALOGIQUE::E0) ;
    if (gEntreeAnalogique0 != entree0) {
      gEntreeAnalogique0 = entree0 ;
      lcd.setCursor (4, 2) ;
      lcd.print ("               ") ;
      lcd.setCursor (4, 2) ;
      lcd.print (entree0) ;
      lcd.print (" -> ") ;
      lcd.print ((float (entree0) - 511.5) * 0.0206452) ;
      lcd.print ("V") ;
    }
    const uint16_t entree1 = lireEntreeAnalogique (ENTREE_ANALOGIQUE::E1) ;
    if (gEntreeAnalogique1 != entree1) {
      gEntreeAnalogique1 = entree1 ;
      lcd.setCursor (4, 3) ;
      lcd.print ("               ") ;
      lcd.setCursor (4, 3) ;
      lcd.print (entree1) ;
      lcd.print (" -> ") ;
      lcd.print ((float (entree1) - 511.5) * 0.0206452) ;
      lcd.print ("V") ;
    }
  }
//--- Quatrième action : action des poussoirs sur les sorties logiques
  actionSortieLogique (SORTIE_LOGIQUE::S0, etatPoussoir (POUSSOIR::P0)) ;
  actionSortieLogique (SORTIE_LOGIQUE::S1, etatPoussoir (POUSSOIR::P1)) ;
  actionSortieLogique (SORTIE_LOGIQUE::S2, etatPoussoir (POUSSOIR::P2)) ;
  actionSortieLogique (SORTIE_LOGIQUE::S3, etatPoussoir (POUSSOIR::P3)) ;
}

//--------------------------------------------------------

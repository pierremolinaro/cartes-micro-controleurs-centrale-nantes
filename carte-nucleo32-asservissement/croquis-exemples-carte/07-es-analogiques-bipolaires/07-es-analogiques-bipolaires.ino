
#include "carte-asservissement.h"

//--------------------------------------------------------

void setup () {
  configurerCarteAsservissement () ;
  fixerGammeEncodeur (-128, 127) ;
  lcd.print ("E/S analog. -10V:10V") ;
  lcd.setCursor (0, 1) ;
  lcd.print ("SB0,1:") ;
  lcd.setCursor (0, 2) ;
  lcd.print ("EB0:") ;
  lcd.setCursor (0, 3) ;
  lcd.print ("EB1:") ;
}

//--------------------------------------------------------

static uint32_t gInstantClignotement = 0 ;
static uint32_t gInstantLectureAnalogique = 0 ;
static int32_t  gValeurEncodeur = -1 ;
static int32_t gEntreeAnalogique0 = INT32_MAX ;
static int32_t gEntreeAnalogique1 = INT32_MAX ;

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
    actionSortieAnalogiqueBipolaire (SORTIE_ANALOGIQUE_BIPOLAIRE::SB0, gValeurEncodeur) ;
    actionSortieAnalogiqueBipolaire (SORTIE_ANALOGIQUE_BIPOLAIRE::SB1, gValeurEncodeur) ;
    lcd.setCursor (6, 1) ;
    lcd.print ("              ") ;
    lcd.setCursor (6, 1) ;
    lcd.print (gValeurEncodeur) ;
    lcd.print ("->") ;
    lcd.print (float (gValeurEncodeur) * 0.082824) ;
    lcd.print ("V") ;
  }
//--- Troisième action : lire les entrées analogiques
  if (gInstantLectureAnalogique <= millis ()) {
    gInstantLectureAnalogique += 500 ;
    const int32_t entree0 = lireEntreeAnalogiqueBipolaire (ENTREE_ANALOGIQUE_BIPOLAIRE::EB0) ;
    if (gEntreeAnalogique0 != entree0) {
      gEntreeAnalogique0 = entree0 ;
      lcd.setCursor (5, 2) ;
      lcd.print ("              ") ;
      lcd.setCursor (5, 2) ;
      lcd.print (entree0) ;
      lcd.print (" -> ") ;
      lcd.print (float (entree0) * 0.0206452) ;
      lcd.print ("V") ;
    }
    const int32_t entree1 = lireEntreeAnalogiqueBipolaire (ENTREE_ANALOGIQUE_BIPOLAIRE::EB1) ;
    if (gEntreeAnalogique1 != entree1) {
      gEntreeAnalogique1 = entree1 ;
      lcd.setCursor (5, 3) ;
      lcd.print ("              ") ;
      lcd.setCursor (5, 3) ;
      lcd.print (entree1) ;
      lcd.print (" -> ") ;
      lcd.print (float (entree1) * 0.0206452) ;
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

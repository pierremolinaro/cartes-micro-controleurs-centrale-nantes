 
#include "carte-asservissement.h"

//--------------------------------------------------------

void setup () {
  configurerCarteAsservissement () ;
  fixerGammeEncodeur (0, 255) ;
  lcd.print ("Test sorties 4/20 mA") ;
  lcd.setCursor (0, 1) ;
  lcd.print ("SU0 :") ;
  lcd.setCursor (0, 2) ;
  lcd.print ("Courant :") ;
}

//--------------------------------------------------------

static uint32_t gInstantClignotement = 0 ;
static uint32_t gInstantLectureAnalogique = 0 ;
static int32_t  gValeurEncodeur = -1 ;
static uint32_t gEntreeAnalogique0 = UINT32_MAX ;
static uint32_t gEntreeAnalogique1 = UINT32_MAX ;

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
    actionSortieAnalogiqueUnipolaire (SORTIE_ANALOGIQUE_UNIPOLAIRE::SU0, uint32_t (gValeurEncodeur)) ;
    lcd.setCursor (6, 1) ;
    lcd.print ("             ") ;
    lcd.setCursor (6, 1) ;
    lcd.print (gValeurEncodeur) ;
    lcd.print (" -> ") ;
    const float tension = float (gValeurEncodeur) * 0.041412 ;
    lcd.print (tension) ;
    lcd.print ("V") ;
    lcd.setCursor (10, 2) ;
    lcd.print ("          ") ;
    lcd.setCursor (10, 2) ;
    const float courant = tension * 20.0 / 3.0 ; // 0,6 V --> 4 mA, 3 V ---> 20 mA
    lcd.print (courant) ;
    lcd.print ("mA") ;
  }
//--- Troisième action : lire les entrées analogiques
}

//--------------------------------------------------------

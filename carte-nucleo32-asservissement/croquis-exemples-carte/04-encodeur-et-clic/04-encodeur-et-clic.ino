
#include "carte-asservissement.h"

//--------------------------------------------------------

void setup () {
  configurerCarteAsservissement () ;
  fixerGammeEncodeur (-10, 10) ;
  lcd.print ("Test encodeur") ;
  lcd.setCursor (0, 1) ;
  lcd.print ("Clic :") ;
  lcd.setCursor (0, 2) ;
  lcd.print ("Valeur :") ;
}

//--------------------------------------------------------

static uint32_t gInstantClignotement = 0 ;
static bool gEtatClic = true ;
static int32_t gValeurEncodeur = 1 ;

//--------------------------------------------------------

void loop () {
//--- Première action : clignotement led
  if (gInstantClignotement <= millis ()) {
  //--- Calcul de la prochaine échéance
    gInstantClignotement += 1000 ;
  //--- Faire clignoter LED_BUILTIN
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
//--- Deuxième action : affichage de l'état de CLIC
  const bool clic = etatClic () ;
  if (gEtatClic != clic) {
    gEtatClic = clic ;
    lcd.setCursor (7, 1) ;
    lcd.print (clic ? "appuye " : "relache") ;
  }
//--- Troisième action : affichage de la valeur de l'encodeur
  const int32_t encodeur = valeurEncodeur () ;
  if (gValeurEncodeur != encodeur) {
    gValeurEncodeur = encodeur ;
    lcd.setCursor (9, 2) ;
    lcd.print ("    ") ;
    lcd.setCursor (9, 2) ;
    lcd.print (encodeur) ;   
  }
}

//--------------------------------------------------------

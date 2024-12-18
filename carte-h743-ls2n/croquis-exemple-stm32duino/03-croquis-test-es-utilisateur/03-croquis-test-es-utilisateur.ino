#include "STM32H743-configuration-ls2n.h"

//--------------------------------------------------------------------------------------------------

void setup() {
  configurerCarteH743LS2N () ;
  fixerGammeEncodeur (-10, 10) ;
  lcd.print ("Test ES utilisateur") ;
  lcd.setCursor (0, 1) ;
  lcd.print ("Inter DIL :") ;
  lcd.setCursor (0, 2) ;
  lcd.print ("Poussoirs :") ;
  lcd.setCursor (0, 3) ;
  lcd.print ("Encodeur  :") ;
}

//--------------------------------------------------------------------------------------------------

static uint32_t gEcheance = 0 ;
static uint32_t gAffichageLeds = 0 ;

//--------------------------------------------------------------------------------------------------

void loop() {
  if (gEcheance < millis ()) {
    gEcheance += 1000 ;
    digitalWrite (NUCLEO_LD2_JAUNE, !digitalRead (NUCLEO_LD2_JAUNE)) ;
    gAffichageLeds = (gAffichageLeds + 1) % 3 ;
    switch (gAffichageLeds) {
    case 0 :
      digitalWrite (LED_2_ROUGE, LOW) ;
      digitalWrite (LED_0_VERTE, HIGH) ;
      break ;
    case 1 :
      digitalWrite (LED_0_VERTE, LOW) ;
      digitalWrite (LED_1_JAUNE, HIGH) ;
      break ;
    default :
      digitalWrite (LED_1_JAUNE, LOW) ;
      digitalWrite (LED_2_ROUGE, HIGH) ;
      break ;
    }
  //--- Interrupteurs DIL
    lcd.setCursor (12, 1) ;
    lcd.print (digitalRead (INTER_DIL_1)) ;
    lcd.print (digitalRead (INTER_DIL_2)) ;
    lcd.print (digitalRead (INTER_DIL_3)) ;
    lcd.print (digitalRead (INTER_DIL_4)) ;
  //--- Poussoirs
    lcd.setCursor (12, 2) ;
    lcd.print (digitalRead (POUSSOIR_P0_BLANC)) ;
    lcd.print (digitalRead (POUSSOIR_P1_ROSE)) ;
    lcd.print (digitalRead (POUSSOIR_P2_JAUNE)) ;
    lcd.print (digitalRead (POUSSOIR_P3_ROUGE)) ;
    lcd.print (" ") ;
    lcd.print (digitalRead (POUSSOIR_NUCLEO_BLEU)) ;
  //--- Encodeur
    lcd.setCursor (12, 3) ;
    lcd.print ("    ") ;
    lcd.setCursor (12, 3) ;
    lcd.print (valeurEncodeur ()) ;
    lcd.setCursor (19, 3) ;
    lcd.print (digitalRead (ENCODEUR_CLIC)) ;
  }
}

//--------------------------------------------------------------------------------------------------

#include "STM32H743-configuration-ls2n.h"

//--------------------------------------------------------------------------------------------------

void setup() {
  configurerCarteH743LS2N () ;
  fixerGammeEncodeur (0, 15) ;
  lcd.print ("Test EA0 a EA15") ;
}

//--------------------------------------------------------------------------------------------------

static uint32_t gEcheance = 500 ;
static uint32_t gClignotement = 0 ;
static int32_t gValeurEncodeur = -1 ;
static uint16_t gEntreeAnalogique_9bits = 512 ;
static uint16_t gEntreeAnalogique_10bits = 1024 ;

//--------------------------------------------------------------------------------------------------

void loop() {
  if (gClignotement < millis ()) {
    gClignotement += 1000 ;
    digitalWrite (NUCLEO_LD2_JAUNE, !digitalRead (NUCLEO_LD2_JAUNE)) ;
  }
  if (gEcheance < millis ()) {
    gEcheance += 50 ;
    const int encodeur = valeurEncodeur () ;
    if (gValeurEncodeur != encodeur) {
      gValeurEncodeur = encodeur ;
      lcd.setCursor (0, 1) ;
      lcd.print ("Encodeur : EA") ;
      lcd.print (gValeurEncodeur) ;
      lcd.print (" ") ;
    }
    const uint16_t ea_9bits = lireEntreeAnalogique_9bits (uint8_t (gValeurEncodeur)) ;
    if (gEntreeAnalogique_9bits != ea_9bits) {
      gEntreeAnalogique_9bits = ea_9bits ;
      lcd.setCursor (0, 2) ;
      lcd.print ("                    ") ;
      lcd.setCursor (0, 2) ;
      lcd.print (" 9bits ") ;
      lcd.print (ea_9bits) ;
      lcd.print (" -> ") ;
      const float tension = float (ea_9bits) * (5.0 / 511.0) ;
      lcd.print (tension) ;
      lcd.print ("V") ;
    }
    delay (10) ;
    const uint16_t ea_10bits = lireEntreeAnalogique_10bits (uint8_t (gValeurEncodeur)) ;
    if (gEntreeAnalogique_10bits != ea_10bits) {
      gEntreeAnalogique_10bits = ea_10bits ;
      lcd.setCursor (0, 3) ;
      lcd.print ("                    ") ;
      lcd.setCursor (0, 3) ;
      lcd.print ("10bits ") ;
      lcd.print (ea_10bits) ;
      lcd.print (" -> ") ;
      const float tension = float (ea_10bits) * (5.0 / 1024.0) ;
      lcd.print (tension) ;
      lcd.print ("V") ;
    }
  }
}

//--------------------------------------------------------------------------------------------------

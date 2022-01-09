#include "STM32H743-configuration-ls2n.h"

//--------------------------------------------------------------------------------------------------

void setup() {
  configurerCarteH743LS2N () ;
  fixerGammeEncodeur (0, 255) ;
  lcd.print ("Test EL11 a EL0") ;
}

//--------------------------------------------------------------------------------------------------

static uint32_t gEcheance = 0 ;
static int32_t gValeurEncodeur = -1 ;

//--------------------------------------------------------------------------------------------------

void loop() {
  if (gEcheance < millis ()) {
    gEcheance += 1000 ;
    digitalWrite (NUCLEO_LD2_JAUNE, !digitalRead (NUCLEO_LD2_JAUNE)) ;
    lcd.setCursor (0, 2) ;
    uint16_t el = lireToutesEntreesLogiques () ;
    for (uint32_t i=0 ; i<12 ; i++) {
      const bool b = (el & 0x800) != 0 ;
      lcd.print (b ? "1" : "0") ;
      el <<= 1 ;
    }
  }
}

//--------------------------------------------------------------------------------------------------

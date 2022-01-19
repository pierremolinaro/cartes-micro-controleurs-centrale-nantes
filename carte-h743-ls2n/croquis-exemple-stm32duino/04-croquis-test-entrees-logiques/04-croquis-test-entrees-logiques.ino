#include "STM32H743-configuration-ls2n.h"

//--------------------------------------------------------------------------------------------------

void setup() {
  configurerCarteH743LS2N () ;
  fixerGammeEncodeur (0, 255) ;
  lcd.print ("Test EL11 a EL0") ;
}

//--------------------------------------------------------------------------------------------------

static uint32_t gEcheanceClignotement = 0 ;
static uint16_t gEntreesLogiques = 1 << 12 ;
static int32_t gValeurEncodeur = -1 ;

//--------------------------------------------------------------------------------------------------

void loop() {
  if (gEcheanceClignotement < millis ()) {
    gEcheanceClignotement += 500 ;
    digitalWrite (NUCLEO_LD2_JAUNE, !digitalRead (NUCLEO_LD2_JAUNE)) ;
  }
  const uint16_t entreesLogiques = lireToutesEntreesLogiques () ;
  if (gEntreesLogiques != entreesLogiques) {
    gEntreesLogiques = entreesLogiques ;
    lcd.setCursor (0, 2) ;
    uint16_t el = entreesLogiques ;
    for (uint32_t i=0 ; i<12 ; i++) {
      const bool b = (el & 0x800) != 0 ;
      lcd.print (b ? "1" : "0") ;
      el <<= 1 ;
    }
  }
}

//--------------------------------------------------------------------------------------------------

#include "STM32H743-configuration-ls2n.h"

//--------------------------------------------------------------------------------------------------

void setup() {
  configurerCarteH743LS2N () ;
  fixerGammeEncodeur (0, 3) ;
  lcd.print ("Test vannes (DIL4  )") ;
}

//--------------------------------------------------------------------------------------------------

static uint32_t gEcheance = 500 ;
static uint32_t gClignotement = 0 ;
static int32_t gValeurEncodeur = -1 ;
static uint16_t gPotentiometre = 256 ;
static uint16_t gRetourCommande = 512 ;
static bool gPage = false ;
static uint16_t gEntreeAnalogiqueCapteurVanne = 512 ;

//--------------------------------------------------------------------------------------------------

void loop () {
  if (gClignotement < millis ()) {
    gClignotement += 1000 ;
    digitalWrite (NUCLEO_LD2_JAUNE, !digitalRead (NUCLEO_LD2_JAUNE)) ;
  }
  if (gEcheance < millis ()) {
    gEcheance += 50 ;
    bool rafraichir = false ;
    const int encodeur = valeurEncodeur () ;
    if (gValeurEncodeur != encodeur) {
      gValeurEncodeur = encodeur ;
      rafraichir = true ;
      lcd.setCursor (0, 1) ;
      lcd.print ("Encodeur : vanne ") ;
      lcd.print (gValeurEncodeur) ;
    }
    digitalWrite (LED_0_VERTE, retourLogiqueVanne (uint8_t (gValeurEncodeur))) ;
    const bool page = digitalRead (INTER_DIL_4) == LOW ;
    if (rafraichir || (gPage != page)) {
      gPage = page ;
      rafraichir = true ;
      lcd.setCursor (18, 0) ;
      lcd.print (page) ;
    }
    const uint16_t potentiometre = lireEntreeAnalogique_9bits (15) / 2 ; // Lire le potentiomètre EA15 (sur 8 bits)
    if (rafraichir || (gPotentiometre != potentiometre)) {
      gPotentiometre = potentiometre ;
      rafraichir = true ;
      lcd.setCursor (0, 2) ;
      lcd.print ("                    ") ;
      lcd.setCursor (0, 2) ;
      lcd.print ("Pot. ") ;
      lcd.print (potentiometre) ;
      lcd.print (" -> ") ;
      if (page) {
        const float tension = float (potentiometre) * 0.04406 ;
        lcd.print (tension) ;
        lcd.print ("V") ;
      }else{
        const float courant = float (potentiometre) * (1000.0 * 5.0) / (255.0 * 150.0) ;
        lcd.print (courant) ;
        lcd.print ("mA") ;
      }
    }
    if (page) {
      if (rafraichir) {
        fixerValeurTestRetourAnalogique (potentiometre) ;
      }
      const uint16_t entreeAnalogique = retourAnalogiqueVanne (uint8_t (gValeurEncodeur)) ;
      if (rafraichir || (gEntreeAnalogiqueCapteurVanne != entreeAnalogique)) {
        gEntreeAnalogiqueCapteurVanne = entreeAnalogique ;
        rafraichir = true ;
        lcd.setCursor (0, 3) ;
        lcd.print ("                    ") ;
        lcd.setCursor (0, 3) ;
        lcd.print ("Ret. ") ;
        lcd.print (entreeAnalogique) ;
        lcd.print (" -> ") ;
        const float tension = float (entreeAnalogique) * (5.0 / 511.0) * 2.0 ;
        lcd.print (tension) ;
        lcd.print ("V") ;
      }
     
    }else{
      if (rafraichir) {
        commandeVanne (uint8_t (gValeurEncodeur), potentiometre) ;
      }
      const uint16_t retourCommande = testCommandeVanne () ;
      if (rafraichir || (gRetourCommande != retourCommande)) {
        gRetourCommande = retourCommande ;
        lcd.setCursor (0, 3) ;
        lcd.print ("                    ") ;
        lcd.setCursor (0, 3) ;
        lcd.print ("Ret. ") ;
        lcd.print (retourCommande) ;
        lcd.print (" -> ") ;
        const float R2 =  9'100.0 ; // 9,1 kΩ
        const float R1 = 10'000.0 ; // 10 kΩ
        const float R0 = 250.74 ; // 250,74 Ω = (15 kΩ // 255Ω)
        const float courant = float (retourCommande) * (5.0 / 511.0) * R1 * 1000.0 / (R0 * R2) ;
        lcd.print (courant) ;
        lcd.print ("mA") ;
      }
    }
  }
}

//--------------------------------------------------------------------------------------------------

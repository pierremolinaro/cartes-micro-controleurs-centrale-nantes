#include "STM32H743-configuration-lheea.h"

//--------------------------------------------------------------------------------------------------

static SPIEEPROM mySPIEEPROM (MySPI::spi1, SPI_EEPROM_TYPE::MCP25LC256) ;

//--------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin (38400) ;
  configurerCarteH743LHEEA () ;
  mySPIEEPROM.begin () ; // Appeler après la configuration de la carte 
  lcd.print ("Test EEPROM externe") ;
}

//--------------------------------------------------------------------------------------------------

static uint32_t gEcheance = 0 ;
static uint32_t gCompteur = 0 ;
static bool gPoussoirP0Appuye = false ;
static uint32_t ADRESSE_EN_EEPROM = 125 ;

//--------------------------------------------------------------------------------------------------

void loop () {
  if (gEcheance < millis ()) {
    gEcheance += 1000 ;
    digitalWrite (PE1, !digitalRead (PE1)) ;
    lcd.setCursor (0, 1) ;
    lcd.print (gCompteur) ;
    gCompteur += 1 ;
  //--- Lecture
    uint8_t buffer [6] ;
    mySPIEEPROM.eepromRead (ADRESSE_EN_EEPROM, buffer, 6) ;
    lcd.setCursor (0, 2) ;
    lcd.print ("                    ") ;
    lcd.setCursor (0, 2) ;
    for (uint32_t i=0 ; i<6 ; i++) {
      lcd.print (buffer [i], HEX) ;
      lcd.print (" ") ;
    }
  //--- Écriture ?
    digitalWrite (LED_0_VERTE, LOW) ;
    const bool p0 = !digitalRead (POUSSOIR_P0_BLANC) ;
    if (p0 && !gPoussoirP0Appuye) {
      digitalWrite (LED_0_VERTE, HIGH) ;
      uint8_t b = uint8_t (gCompteur) ;
      for (uint32_t i=0 ; i<6 ; i++) {
        buffer [i] = b ;
        b += 1 ;     
      }
      const uint32_t debutEcriture = millis () ;
      mySPIEEPROM.eepromWrite (ADRESSE_EN_EEPROM, buffer, 6) ;
      while (mySPIEEPROM.eepromIsBusy ()) {
        delay (1) ;
      }
      const uint32_t dureeEcriture = millis () - debutEcriture ;
      lcd.setCursor (0, 3) ;
      lcd.print ("Duree ") ; lcd.print (dureeEcriture) ; lcd.print ("ms") ;
    }
    gPoussoirP0Appuye = p0 ;
  }
}

//--------------------------------------------------------------------------------------------------

#include "STM32H743-configuration-lheea.h"

//--------------------------------------------------------------------------------------------------

static SPIFLASH myFlash (MySPI::spi2, SPI_FLASH_TYPE::SST26VF064B) ;

//--------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin (38400) ;
  configurerCarteH743LHEEA () ;
  myFlash.begin () ; // Appeler après la configuration de la carte 
  lcd.print ("Test FLASH externe") ;
}

//--------------------------------------------------------------------------------------------------

static uint32_t gEcheance = 0 ;
static uint32_t gCompteur = 0 ;
static bool gPoussoirP0Appuye = false ;
static bool gPoussoirP1Appuye = false ;
static bool gPoussoirP2Appuye = false ;

static uint32_t ADRESSE_EN_FLASH = 217055 ;
static uint32_t LONGUEUR_DONNEES = 6 ;

//--------------------------------------------------------------------------------------------------

void loop () {
  if (gEcheance < millis ()) {
    gEcheance += 1000 ;
    digitalWrite (PE1, !digitalRead (PE1)) ;
    lcd.setCursor (0, 1) ;
    lcd.print (gCompteur) ;
    gCompteur += 1 ;
  //--- Lecture
    uint8_t buffer [LONGUEUR_DONNEES] ;
    myFlash.flashRead (ADRESSE_EN_FLASH, buffer, LONGUEUR_DONNEES) ;
    lcd.setCursor (0, 2) ;
    lcd.print ("                    ") ;
    lcd.setCursor (0, 2) ;
    for (uint32_t i=0 ; i<LONGUEUR_DONNEES ; i++) {
      lcd.print (buffer [i], HEX) ;
      lcd.print (" ") ;
    }
  //--- Écriture ?
    digitalWrite (LED_0_VERTE, LOW) ;
    const bool p0 = !digitalRead (POUSSOIR_P0_BLANC) ;
    if (p0 && !gPoussoirP0Appuye) {
      digitalWrite (LED_0_VERTE, HIGH) ;
      uint8_t b = uint8_t (gCompteur) ;
      for (uint32_t i=0 ; i<LONGUEUR_DONNEES ; i++) {
        buffer [i] = b ;
        b += 1 ;     
      }
      const uint32_t debutEcriture = millis () ;
      myFlash.flashWrite (ADRESSE_EN_FLASH, buffer, LONGUEUR_DONNEES) ;
      while (myFlash.flashIsBusy ()) {
        delay (1) ;
      }
      const uint32_t dureeEcriture = millis () - debutEcriture ;
      lcd.setCursor (0, 3) ;
      lcd.print ("                    ") ;
      lcd.setCursor (0, 3) ;
      lcd.print ("Ecriture ") ; lcd.print (dureeEcriture) ; lcd.print (" ms") ;
    }
    gPoussoirP0Appuye = p0 ;
  //--- Effacement Secteur 0 ?
    digitalWrite (LED_1_JAUNE, LOW) ;
    const bool p1 = !digitalRead (POUSSOIR_P1_ROSE) ;
    if (p1 && !gPoussoirP1Appuye) {
      digitalWrite (LED_1_JAUNE, HIGH) ;
      const uint32_t premierSecteur = ADRESSE_EN_FLASH / myFlash.flashSectorSize () ;
      const uint32_t dernierSecteur = (ADRESSE_EN_FLASH + LONGUEUR_DONNEES - 1) / myFlash.flashSectorSize () ;
      const uint32_t debutEcriture = millis () ;
      for (uint32_t secteur = premierSecteur ; secteur <= dernierSecteur ; secteur ++) {
        myFlash.flashEraseSector (secteur) ;
      }
      while (myFlash.flashIsBusy ()) {
        delay (1) ;
      }
      const uint32_t dureeEcriture = millis () - debutEcriture ;
      lcd.setCursor (0, 3) ;
      lcd.print ("                    ") ;
      lcd.setCursor (0, 3) ;
      lcd.print ("Secteur ") ; lcd.print (dureeEcriture) ; lcd.print (" ms") ;
    }
    gPoussoirP1Appuye = p1 ;
  //--- Effacement complet ?
    digitalWrite (LED_2_ROUGE, LOW) ;
    const bool p2 = !digitalRead (POUSSOIR_P2_JAUNE) ;
    if (p2 && !gPoussoirP2Appuye) {
      digitalWrite (LED_2_ROUGE, HIGH) ;
      const uint32_t debutEcriture = millis () ;
      myFlash.flashEraseChip () ;
      while (myFlash.flashIsBusy ()) {
        delay (1) ;
      }
      const uint32_t dureeEcriture = millis () - debutEcriture ;
      lcd.setCursor (0, 3) ;
      lcd.print ("                    ") ;
      lcd.setCursor (0, 3) ;
      lcd.print ("Chip ") ; lcd.print (dureeEcriture) ; lcd.print (" ms") ;
    }
    gPoussoirP2Appuye = p2 ;
  }
}

//--------------------------------------------------------------------------------------------------

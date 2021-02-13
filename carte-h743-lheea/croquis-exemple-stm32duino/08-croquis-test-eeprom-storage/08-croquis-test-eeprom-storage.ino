#include "STM32H743-configuration-lheea.h"

//--------------------------------------------------------------------------------------------------

static SPIEEPROM mySPIEEPROM (MySPI::spi1, SPI_EEPROM_TYPE::MCP25LC256) ;

static VarInEEPROM <uint32_t> gVar0 (mySPIEEPROM, 0) ;
static VarInEEPROM <uint32_t> gVar1 (mySPIEEPROM, 4) ;
static VarInEEPROM <uint32_t> gVar2 (mySPIEEPROM, 8) ;
static VarInEEPROM <uint32_t> gVar3 (mySPIEEPROM, 126) ;

//--------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin (38400) ;
  configurerCarteH743LHEEA () ;
  mySPIEEPROM.begin () ;
  lcd.print ("Test EEPROM storage") ;
}

//--------------------------------------------------------------------------------------------------

static uint32_t gEcheance = 0 ;
static uint32_t gCompteur = 0 ;
static bool gPoussoirP0Appuye = false ;
static bool gPoussoirP1Appuye = false ;
static bool gPoussoirP2Appuye = false ;
static bool gPoussoirP3Appuye = false ;

//--------------------------------------------------------------------------------------------------

void loop () {
  if (gEcheance < millis ()) {
    gEcheance += 1000 ;
    digitalWrite (PE1, !digitalRead (PE1)) ;
    lcd.setCursor (0, 1) ;
    lcd.print (gCompteur) ;
    gCompteur += 1 ;
  //--- Lecture des variables
    lcd.setCursor (0, 2) ;
    lcd.print ("                    ") ;
    lcd.setCursor (0, 2) ;
    lcd.print (gVar0.get ()) ;
    lcd.setCursor (10, 2) ;
    lcd.print (gVar1.get ()) ;
    lcd.setCursor (0, 3) ;
    lcd.print ("                    ") ;
    lcd.setCursor (0, 3) ;
    lcd.print (gVar2.get ()) ;
    lcd.setCursor (10, 3) ;
    lcd.print (gVar3.get ()) ;
  //--- Écriture gVar0 ?
    digitalWrite (LED_0_VERTE, LOW) ;
    const bool p0 = !digitalRead (POUSSOIR_P0_BLANC) ;
    if (p0 && !gPoussoirP0Appuye) {
      digitalWrite (LED_0_VERTE, HIGH) ;
      gVar0.set (gCompteur) ;
    }
    gPoussoirP0Appuye = p0 ;
  //--- Écriture gVar1 ?
    digitalWrite (LED_1_JAUNE, LOW) ;
    const bool p1 = !digitalRead (POUSSOIR_P1_ROSE) ;
    if (p1 && !gPoussoirP1Appuye) {
      digitalWrite (LED_1_JAUNE, HIGH) ;
      gVar1.set (gCompteur) ;
    }
    gPoussoirP1Appuye = p1 ;
  //--- Écriture gVar2 ?
    digitalWrite (LED_2_ROUGE, LOW) ;
    const bool p2 = !digitalRead (POUSSOIR_P2_JAUNE) ;
    if (p2 && !gPoussoirP2Appuye) {
      digitalWrite (LED_2_ROUGE, HIGH) ;
      gVar2.set (gCompteur) ;
    }
    gPoussoirP2Appuye = p2 ;
  //--- Écriture gVar3 ?
    const bool p3 = !digitalRead (POUSSOIR_P3_ROUGE) ;
    if (p3 && !gPoussoirP3Appuye) {
      digitalWrite (LED_0_VERTE, HIGH) ;
      digitalWrite (LED_1_JAUNE, HIGH) ;
      gVar3.set (gCompteur) ;
    }
    gPoussoirP3Appuye = p3 ;
  }
}

//--------------------------------------------------------------------------------------------------

#include "STM32H743-configuration-lheea.h"

//--------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin (38400) ;
  while (!Serial) {}
  pinMode (PE1, OUTPUT) ;
  configurerCarteH743LHEEA () ;
  lcd.print ("Test RAM externe") ;
  lcd.setCursor (0, 1) ;
  lcd.print ("Duree test ") ;
  lcd.setCursor (0, 2) ;
  lcd.print ("Nombre tests ") ;
  lcd.setCursor (0, 3) ;
  lcd.print ("Erreurs ") ;
}

//--------------------------------------------------------------------------------------------------

static uint32_t gEcheance = 0 ;
static uint32_t gErreurs = 0 ;
static uint32_t gNombreTests = 0 ;

//--------------------------------------------------------------------------------------------------

void loop() {
  if (gEcheance < millis ()) {
    gEcheance += 1000 ;
    digitalWrite (PE1, !digitalRead (PE1)) ;
    const uint32_t instantDebut = millis () ;
    const uint32_t nbErreurs = testRamExterne () ;
    gErreurs += nbErreurs ;
    gNombreTests += 1 ;
    const uint32_t duree = millis () - instantDebut ;
    lcd.setCursor (13, 1) ; lcd.print (duree) ; lcd.print (" ms") ;
    lcd.setCursor (13, 2) ; lcd.print (gNombreTests) ;
    lcd.setCursor (8, 3) ; lcd.print (gErreurs) ;
  }
}

//--------------------------------------------------------------------------------------------------

static const uint32_t TAILLE_RAM_EXTERNE = 4 * 512 * 1024 ;
static uint8_t gIncrement = 1 ;

//--------------------------------------------------------------------------------------------------

static uint32_t testRamExterne (void) {
  gIncrement += 2 ;
  uint8_t valeur = gIncrement ;
  for (uint32_t i = 0 ; i<TAILLE_RAM_EXTERNE ; i++) {
    uint8_t * addresse = (uint8_t *) (0x6000'0000 + i) ;
    *addresse = valeur ;
    valeur += gIncrement ;
  }
  valeur = gIncrement ;
  uint32_t nombreErreurs = 0 ;
  for (uint32_t i = 0 ; i<TAILLE_RAM_EXTERNE ; i++) {
    uint8_t * addresse = (uint8_t *) (0x6000'0000 + i) ;
    const uint8_t valeurLue = *addresse ;
    if (valeurLue != valeur) {
       nombreErreurs += 1 ;
    }
    valeur += gIncrement ;
  }
  return nombreErreurs ;
}

//--------------------------------------------------------------------------------------------------

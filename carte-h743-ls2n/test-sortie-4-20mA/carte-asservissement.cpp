//-------------------------------------------------------------------------------------------------
// CONFIGURATION DE LA CARTE ASSERVISSEMENT
//-------------------------------------------------------------------------------------------------

#include <SPI.h>

#include "carte-asservissement.h"

//-------------------------------------------------------------------------------------------------
// Documentation de l'API de STM32DUINO
//-------------------------------------------------------------------------------------------------

// https://github.com/stm32duino/wiki/wiki

//-------------------------------------------------------------------------------------------------
// Afficheur LCD
//-------------------------------------------------------------------------------------------------

static const uint8_t LCD_E  = D5 ;
static const uint8_t LCD_RS = D4 ;
static const uint8_t LCD_D4 = D9 ;
static const uint8_t LCD_D5 = D10 ;
static const uint8_t LCD_D6 = D11 ;
static const uint8_t LCD_D7 = D12 ;

LiquidCrystal lcd (LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7) ;

//-------------------------------------------------------------------------------------------------
// SPI
//-------------------------------------------------------------------------------------------------
// La configuration du SPI sous stm32duino est TRÈS particulière.
// Voir https://github.com/stm32duino/wiki/wiki/API#spi
//
// Par défaut, pour compatibilité avec Arduino, utiliser le nom SPI configure les signaux MOSI,
// MISO, et SCK de façon à avoir la disposition que l'Arduino nano.
//  #include <SPI.h>
//  ...
//  void setup () {
//    SPI.begin () ;
//    ....
//
// Pour changer les broches par défaut, il faut appeler setMISO, setMOSI, setSCLK, avant
// d'appeler SPI.begin (). C'est ce qui est fait ici. Évidemment, il faut choisir pour les broches
// en fonction de ce que permet le micro-contrôleur.
//
// Si l'on veut des liaisons SPI supplémentaires, il faut créer des nouvelles instances de SPIClass
// avec en arguments MOSI, MISO et SCK :
//  SPIClass mySPI (myMOSI, myMISO, mySCK);
//
// Et c'est là l'approche particulière : alors que la plupart des systèmes de type Arduino
// définissent SPI2, SPI3, … en stm32duino la fonction begin devine le module qui sera
// effectivement utilisé grâce au choix des broches MOSI, MISO et SCK.
//
//-------------------------------------------------------------------------------------------------

static const uint8_t myMOSI = A6 ; // Attention, noté A6 sur la STM32
static const uint8_t myMISO = A5 ; // Attention, noté A5 sur la STM32
static const uint8_t mySCLK = A4 ; // Attention, noté A4 sur la STM32

static const uint8_t CS_SPI_23S17 = D3 ;
static const uint8_t CS_DAC_UNIPOLAIRE = D6 ;
static const uint8_t CS_DAC_BIPOLAIRE = A7 ; // A7 sur la carte STM32

//-------------------------------------------------------------------------------------------------
// MCP23S17 sur bus SPI
//-------------------------------------------------------------------------------------------------
// Le MCP23S17 présente deux ports de 8 bits dont l'affectation des masques est :

static const uint8_t MASQUE_GPA_PUSH_0 = 1 << 0 ; // GPA0, en entrée
static const uint8_t MASQUE_GPA_PUSH_1 = 1 << 1 ; // GPA1, en entrée
static const uint8_t MASQUE_GPA_PUSH_2 = 1 << 2 ; // GPA2, en entrée
static const uint8_t MASQUE_GPA_PUSH_3 = 1 << 3 ; // GPA3, en entrée
static const uint8_t MASQUE_GPA_PUSH_4 = 1 << 4 ; // GPA4, en entrée
static const uint8_t MASQUE_GPA_SORTIE_LOGIQUE_0 = 1 << 5 ; // GPA5, en sortie
static const uint8_t MASQUE_GPA_SORTIE_LOGIQUE_1 = 1 << 6 ; // GPA6, en sortie
static const uint8_t MASQUE_GPA_LDAC_DAC_UNIPOLAIRE = 1 << 7 ; // GPA7, en sortie

static const uint8_t MASQUE_GPB_LED_0 = 1 << 0 ; // GPB0, en sortie
static const uint8_t MASQUE_GPB_LED_1 = 1 << 1 ; // GPB1, en sortie
static const uint8_t MASQUE_GPB_LED_2 = 1 << 2 ; // GPB2, en sortie
static const uint8_t MASQUE_GPB_LED_3 = 1 << 3 ; // GPB3, en sortie
static const uint8_t MASQUE_GPB_LED_4 = 1 << 4 ; // GPB4, en sortie
static const uint8_t MASQUE_GPB_SORTIE_LOGIQUE_2 = 1 << 5 ; // GPB5, en sortie
static const uint8_t MASQUE_GPB_SORTIE_LOGIQUE_3 = 1 << 6 ; // GPB6, en sortie
static const uint8_t MASQUE_GPB_LDAC_DAC_BIPOLAIRE = 1 << 7 ; // GPB7, en sortie

//--- Initialement, IOCON.BANK est à zéro, et n'est pas modifié par la configuration.
// Les adresses des registres du MCP23S17 sont donc :
static const uint8_t IODIRA_MCP23S17 = 0x00 ;
static const uint8_t IODIRB_MCP23S17 = 0x01 ;
static const uint8_t IPOLA_MCP23S17  = 0x02 ;
static const uint8_t IPOLB_MCP23S17  = 0x03 ;
static const uint8_t GPPUA_MCP23S17  = 0x0C ;
static const uint8_t GPPUB_MCP23S17  = 0x0D ;
static const uint8_t GPIOA_MCP23S17  = 0x12 ;
static const uint8_t GPIOB_MCP23S17  = 0x13 ;

//--- Ordres de lecture et d'écriture
static const uint8_t LECTURE_MCP23S17  = 0x41 ;
static const uint8_t ECRITURE_MCP23S17 = 0x40 ;

//--- Débits SPI
static const uint32_t DEBIT_SPI_MCP23S17 = 10 * 1000 * 1000 ; // En bit/s, maximum 10 Mbit/s
const SPISettings SPI_SETTINGS_MCP23S17 (DEBIT_SPI_MCP23S17, MSBFIRST, SPI_MODE0) ;

static const uint32_t DEBIT_SPI_MCP49x2 = 20 * 1000 * 1000 ; // En bit/s, maximum 20 Mbit/s
const SPISettings SPI_SETTINGS_MCP49x2 (DEBIT_SPI_MCP49x2, MSBFIRST, SPI_MODE0) ;

//-------------------------------------------------------------------------------------------------
// ENCODEUR NUMÉRIQUE
//-------------------------------------------------------------------------------------------------

static const uint8_t ENCODEUR_A    = D0 ;
static const uint8_t ENCODEUR_B    = D1 ;
static const uint8_t ENCODEUR_CLIC = D2 ;

//--- La gestion de la valeur de l'encodeur numérique est faite par la routine d'interruption
//    appuiEncodeur, déclenchée sur front descendant du port ENCODEUR_A.
static void appuiEncodeur (void) ;

//-------------------------------------------------------------------------------------------------
//  CONFIGURER CARTE ASSERVISSEMENT
//-------------------------------------------------------------------------------------------------

void configurerCarteAsservissement () {
//--- Configurer en sortie la led BUILTIN et l'allumer
  pinMode (LED_BUILTIN, OUTPUT) ;
  digitalWrite (LED_BUILTIN, HIGH) ;
//--- Configurer les ports reliés à l'encodeur numérique
  pinMode (ENCODEUR_A, INPUT_PULLUP) ;
  pinMode (ENCODEUR_B, INPUT_PULLUP) ;
  pinMode (ENCODEUR_CLIC, INPUT_PULLUP) ;
  attachInterrupt (digitalPinToInterrupt (ENCODEUR_A), appuiEncodeur, FALLING) ;
//--- Configurer l'afficheur LCD
  lcd.begin (20, 4) ; // 20 colonnes, 4 lignes
//--- Configurer le SPI
  pinMode (CS_SPI_23S17, OUTPUT) ;
  digitalWrite (CS_SPI_23S17, HIGH) ;
  pinMode (CS_DAC_UNIPOLAIRE, OUTPUT) ;
  digitalWrite (CS_DAC_UNIPOLAIRE, HIGH) ;
  pinMode (CS_DAC_BIPOLAIRE, OUTPUT) ;
  digitalWrite (CS_DAC_BIPOLAIRE, HIGH) ;
  SPI.setSCLK (mySCLK) ;
  SPI.setMOSI (myMOSI) ;
  SPI.setMISO (myMISO) ;
  SPI.begin () ;
//--- Configurer le MCP23S17 : GPA
  SPI.beginTransaction (SPI_SETTINGS_MCP23S17) ;
  digitalWrite (CS_SPI_23S17, LOW);
  SPI.transfer (ECRITURE_MCP23S17) ;
  SPI.transfer (IODIRA_MCP23S17) ;
  SPI.transfer (0x1F) ; // GPA0 à GPA4 en entrée, GPA5 à GPA7 en sortie
  digitalWrite (CS_SPI_23S17, HIGH);
  SPI.endTransaction () ;
//--- Configurer le MCP23S17 : activer les pullup sur GPA0 à GPA4
  SPI.beginTransaction (SPI_SETTINGS_MCP23S17) ;
  digitalWrite (CS_SPI_23S17, LOW);
  SPI.transfer (ECRITURE_MCP23S17) ;
  SPI.transfer (GPPUA_MCP23S17) ;
  SPI.transfer (0x1F) ; // pullup sur GPA0 à GPA4
  digitalWrite (CS_SPI_23S17, HIGH);
  SPI.endTransaction () ;
//--- Configurer le MCP23S17 : GPB
  SPI.beginTransaction (SPI_SETTINGS_MCP23S17) ;
  digitalWrite (CS_SPI_23S17, LOW);
  SPI.transfer (ECRITURE_MCP23S17) ;
  SPI.transfer (IODIRB_MCP23S17) ;
  SPI.transfer (0x00) ; // GPB0 à GPB7 en sortie
  digitalWrite (CS_SPI_23S17, HIGH);
  SPI.endTransaction () ;
}

//-------------------------------------------------------------------------------------------------
//  CACHE DES PORTS DU MCP23S17
//-------------------------------------------------------------------------------------------------

static uint8_t gCachePortA = 0 ;
static uint8_t gCachePortB = 0 ;

//-------------------------------------------------------------------------------------------------
//  ACTIVATION GPA
//-------------------------------------------------------------------------------------------------

static void activationGPA (const uint8_t inValue) {
//--- Mettre à jour le cache du port A
  const uint8_t cachePortA = gCachePortA ;
  gCachePortA |= inValue ;
//--- Si changement, écrire le registre GPIOA du MCP23S17
  if (cachePortA != gCachePortA) {
    SPI.beginTransaction (SPI_SETTINGS_MCP23S17) ;
    digitalWrite (CS_SPI_23S17, LOW);
    SPI.transfer (ECRITURE_MCP23S17) ;
    SPI.transfer (GPIOA_MCP23S17) ;
    SPI.transfer (gCachePortA) ;
    digitalWrite (CS_SPI_23S17, HIGH);
    SPI.endTransaction () ;
  }
}

//-------------------------------------------------------------------------------------------------
//  DESACTIVATION GPA
//-------------------------------------------------------------------------------------------------

static void desactivationGPA (const uint8_t inValue) {
//--- Mettre à jour le cache du port A
  const uint8_t cachePortA = gCachePortA ;
  gCachePortA &= ~ inValue ;
//--- Si changement, écrire le registre GPIOA du MCP23S17
  if (cachePortA != gCachePortA) {
    SPI.beginTransaction (SPI_SETTINGS_MCP23S17) ;
    digitalWrite (CS_SPI_23S17, LOW);
    SPI.transfer (ECRITURE_MCP23S17) ;
    SPI.transfer (GPIOA_MCP23S17) ;
    SPI.transfer (gCachePortA) ;
    digitalWrite (CS_SPI_23S17, HIGH);
    SPI.endTransaction () ;
  }
}

//-------------------------------------------------------------------------------------------------
//  ACTIVATION GPB
//-------------------------------------------------------------------------------------------------

static void activationGPB (const uint8_t inValue) {
//--- Mettre à jour le cache du port B
  const uint8_t cachePortB = gCachePortB ;
  gCachePortB |= inValue ;
//--- Si changement, écrire le registre GPIOB du MCP23S17
  if (cachePortB != gCachePortB) {
    SPI.beginTransaction (SPI_SETTINGS_MCP23S17) ;
    digitalWrite (CS_SPI_23S17, LOW);
    SPI.transfer (ECRITURE_MCP23S17) ;
    SPI.transfer (GPIOB_MCP23S17) ;
    SPI.transfer (gCachePortB) ;
    digitalWrite (CS_SPI_23S17, HIGH);
    SPI.endTransaction () ;
  }
}

//-------------------------------------------------------------------------------------------------
//  DESACTIVATION GPB
//-------------------------------------------------------------------------------------------------

static void desactivationGPB (const uint8_t inValue) {
//--- Mettre à jour le cache du port B
  const uint8_t cachePortB = gCachePortB ;
  gCachePortB &= ~ inValue ;
//--- Si changement, écrire le registre GPIOB du MCP23S17
  if (cachePortB != gCachePortB) {
    SPI.beginTransaction (SPI_SETTINGS_MCP23S17) ;
    digitalWrite (CS_SPI_23S17, LOW);
    SPI.transfer (ECRITURE_MCP23S17) ;
    SPI.transfer (GPIOB_MCP23S17) ;
    SPI.transfer (gCachePortB) ;
    digitalWrite (CS_SPI_23S17, HIGH);
    SPI.endTransaction () ;
  }
}

//-------------------------------------------------------------------------------------------------
//  ACTION LED
//-------------------------------------------------------------------------------------------------

void actionLed (const LED inLed, const bool inValue) {
  if (inValue) {
    activationGPB (uint8_t (inLed)) ;
  }else{
    desactivationGPB (uint8_t (inLed)) ;
  }
}

//-------------------------------------------------------------------------------------------------
//  ÉTAT POUSSOIR
//-------------------------------------------------------------------------------------------------

bool etatPoussoir (const POUSSOIR inPoussoir) {
//--- Lire le port A
  SPI.beginTransaction (SPI_SETTINGS_MCP23S17) ;
  digitalWrite (CS_SPI_23S17, LOW);
  SPI.transfer (LECTURE_MCP23S17) ;
  SPI.transfer (GPIOA_MCP23S17) ;
  const uint8_t portA = SPI.transfer (0) ;
  digitalWrite (CS_SPI_23S17, HIGH);
  SPI.endTransaction () ;
  return (portA & uint8_t (inPoussoir)) == 0 ;
}

//-------------------------------------------------------------------------------------------------
// ENCODEUR NUMÉRIQUE
//-------------------------------------------------------------------------------------------------

//--- Clic relâché -> retourne false, appuyé -> retourne true
bool etatClic (void) {
  return digitalRead (ENCODEUR_CLIC) == LOW ;
}

//-------------------------------------------------------------------------------------------------

static int32_t gBorneInfEncodeur = 0 ;
static int32_t gBorneSupEncodeur = 0 ;
static int32_t gValeurEncodeur = 0 ;

//-------------------------------------------------------------------------------------------------

void fixerGammeEncodeur (const int32_t inBorneInf, const int32_t inBorneSup) {
  gBorneInfEncodeur = inBorneInf ;
  gBorneSupEncodeur = inBorneSup ;
  if (gValeurEncodeur > gBorneSupEncodeur) {
    gValeurEncodeur = gBorneSupEncodeur ;
  }
  if (gValeurEncodeur < gBorneInfEncodeur) {
    gValeurEncodeur = gBorneInfEncodeur ;
  }
}

//-------------------------------------------------------------------------------------------------

static void appuiEncodeur (void) {
  const bool encodeurB = digitalRead (ENCODEUR_B) ;
  if (encodeurB && (gValeurEncodeur > gBorneInfEncodeur)) {
    gValeurEncodeur -= 1 ;
  }else if (!encodeurB && (gValeurEncodeur < gBorneSupEncodeur)) {
    gValeurEncodeur += 1 ;
  }
}

//-------------------------------------------------------------------------------------------------

int32_t valeurEncodeur (void) {
  return gValeurEncodeur ;
}

//-------------------------------------------------------------------------------------------------
// SORTIES LOGIQUES
//-------------------------------------------------------------------------------------------------

void actionSortieLogique (const SORTIE_LOGIQUE inSortieLogique, const bool inValue) {
  switch (inSortieLogique) {
  case SORTIE_LOGIQUE::S0 :
    if (inValue) {
      activationGPA (MASQUE_GPA_SORTIE_LOGIQUE_0) ;
    }else{
      desactivationGPA (MASQUE_GPA_SORTIE_LOGIQUE_0) ;
    }
    break ;
  case SORTIE_LOGIQUE::S1 :
    if (inValue) {
      activationGPA (MASQUE_GPA_SORTIE_LOGIQUE_1) ;
    }else{
      desactivationGPA (MASQUE_GPA_SORTIE_LOGIQUE_1) ;
    }
    break ;
  case SORTIE_LOGIQUE::S2 :
    if (inValue) {
      activationGPB (MASQUE_GPB_SORTIE_LOGIQUE_2) ;
    }else{
      desactivationGPB (MASQUE_GPB_SORTIE_LOGIQUE_2) ;
    }
    break ;
  case SORTIE_LOGIQUE::S3 :
    if (inValue) {
      activationGPB (MASQUE_GPB_SORTIE_LOGIQUE_3) ;
    }else{
      desactivationGPB (MASQUE_GPB_SORTIE_LOGIQUE_3) ;
    }
    break ;
  }
}

//-------------------------------------------------------------------------------------------------
// SORTIES ANALOGIQUES UNIPOLAIRES
//-------------------------------------------------------------------------------------------------

void actionSortieAnalogiqueUnipolaire (const SORTIE_ANALOGIQUE_UNIPOLAIRE inSortieAnalogique,
                                       const uint32_t inValue) {
  uint16_t v = uint16_t (inValue) ;
  if (inValue > 255) {
    v = 255 ;
  }
  v <<= 4 ; // MCP4902 : 8 bit DAC, LSB is bit 4
  v |= (1 << 12) ; // Active mode operation. Vout is available
  v |= (1 << 13) ; // Gain 1
  v |= (1 << 14) ;
  switch (inSortieAnalogique) {
  case SORTIE_ANALOGIQUE_UNIPOLAIRE::SU0 :
    SPI.beginTransaction (SPI_SETTINGS_MCP49x2) ;
    digitalWrite (CS_DAC_UNIPOLAIRE, LOW);
    SPI.transfer (uint8_t (v >> 8)) ;
    SPI.transfer (uint8_t (v)) ;
    digitalWrite (CS_DAC_UNIPOLAIRE, HIGH);
    SPI.endTransaction () ;
    break ;
  case SORTIE_ANALOGIQUE_UNIPOLAIRE::SU1 :
    v |= (1 << 15) ; // Write to DAC1
    SPI.beginTransaction (SPI_SETTINGS_MCP49x2) ;
    digitalWrite (CS_DAC_UNIPOLAIRE, LOW);
    SPI.transfer (uint8_t (v >> 8)) ;
    SPI.transfer (uint8_t (v)) ;
    digitalWrite (CS_DAC_UNIPOLAIRE, HIGH);
    SPI.endTransaction () ;
    break ;
  }
}

//-------------------------------------------------------------------------------------------------
// SORTIES ANALOGIQUES BIPOLAIRES
//-------------------------------------------------------------------------------------------------

void actionSortieAnalogiqueBipolaire (const SORTIE_ANALOGIQUE_BIPOLAIRE inSortieAnalogique,
                                      const int32_t inValue) {
  int16_t value = int16_t (inValue) ;
  if (inValue > 127) {
    value = 127 ;
  }else if (inValue < -128) {
    value = -128 ;
  }
  value += 128 ;
  uint16_t v = uint16_t (value) ;
  v <<= 4 ; // MCP4902 : 8 bit DAC, LSB is bit 4
  v |= (1 << 12) ; // Active mode operation. Vout is available
  v |= (1 << 13) ; // Gain 1
  v |= (1 << 14) ;
  switch (inSortieAnalogique) {
  case SORTIE_ANALOGIQUE_BIPOLAIRE::SB0 :
    SPI.beginTransaction (SPI_SETTINGS_MCP49x2) ;
    digitalWrite (CS_DAC_BIPOLAIRE, LOW);
    SPI.transfer (uint8_t (v >> 8)) ;
    SPI.transfer (uint8_t (v)) ;
    digitalWrite (CS_DAC_BIPOLAIRE, HIGH);
    SPI.endTransaction () ;
    break ;
  case SORTIE_ANALOGIQUE_BIPOLAIRE::SB1 :
    v |= (1 << 15) ; // Write to DAC1
    SPI.beginTransaction (SPI_SETTINGS_MCP49x2) ;
    digitalWrite (CS_DAC_BIPOLAIRE, LOW);
    SPI.transfer (uint8_t (v >> 8)) ;
    SPI.transfer (uint8_t (v)) ;
    digitalWrite (CS_DAC_BIPOLAIRE, HIGH);
    SPI.endTransaction () ;
    break ;
  }
}

//-------------------------------------------------------------------------------------------------
// ENTRÉES ANALOGIQUES UNIPOLAIRES
//-------------------------------------------------------------------------------------------------

uint32_t lireEntreeAnalogiqueUnipolaire (const ENTREE_ANALOGIQUE_UNIPOLAIRE inEntreeAnalogique) {
  uint32_t result = 0 ;
  switch (inEntreeAnalogique) {
  case ENTREE_ANALOGIQUE_UNIPOLAIRE::EU0 :
    result = analogRead (PA0) ;
    break ;
  case ENTREE_ANALOGIQUE_UNIPOLAIRE::EU1 :
    result = analogRead (PA1) ;
    break ;
  }
  return result ;
}

//-------------------------------------------------------------------------------------------------
// ENTRÉES ANALOGIQUES UNIPOLAIRES
//-------------------------------------------------------------------------------------------------

int32_t lireEntreeAnalogiqueBipolaire (const ENTREE_ANALOGIQUE_BIPOLAIRE inEntreeAnalogique) {
  uint32_t rawValue = 0 ;
  switch (inEntreeAnalogique) {
  case ENTREE_ANALOGIQUE_BIPOLAIRE::EB0 :
    rawValue = analogRead (PA3) ;
    break ;
  case ENTREE_ANALOGIQUE_BIPOLAIRE::EB1 :
    rawValue = analogRead (PA4) ;
    break ;
  }
  int32_t result = int32_t (rawValue) ;
  result -= 512 ;
  return result ;
}

//-------------------------------------------------------------------------------------------------

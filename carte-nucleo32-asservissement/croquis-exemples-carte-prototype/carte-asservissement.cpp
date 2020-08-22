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

static const uint8_t myMOSI = PA7 ;
static const uint8_t myMISO = PA6 ;
static const uint8_t mySCLK = PA1 ;
static const uint8_t myCS   = D3 ;

//-------------------------------------------------------------------------------------------------
// MCP23S17 sur bus SPI
//-------------------------------------------------------------------------------------------------
// Le MCP23S17 présente deux ports de 8 bits dont l'affectation des masques est :

static const uint8_t MASQUE_PUSH_0 = 1 << 0 ; // GPA0, en entrée
static const uint8_t MASQUE_PUSH_1 = 1 << 1 ; // GPA1, en entrée
static const uint8_t MASQUE_PUSH_2 = 1 << 2 ; // GPA2, en entrée
static const uint8_t MASQUE_PUSH_3 = 1 << 3 ; // GPA3, en entrée
static const uint8_t MASQUE_PUSH_4 = 1 << 4 ; // GPA4, en entrée
static const uint8_t MASQUE_SORTIE_LOGIQUE_2 = 1 << 5 ; // GPA5, en sortie
static const uint8_t MASQUE_GAMME_ENTREE_ANALOGIQUE_0 = 1 << 6 ; // GPA6, en sortie
static const uint8_t MASQUE_GAMME_SORTIE_ANALOGIQUE_0 = 1 << 7 ; // GPA7, en sortie

static const uint8_t MASQUE_LED_0 = 1 << 0 ; // GPB0, en sortie
static const uint8_t MASQUE_LED_1 = 1 << 1 ; // GPB1, en sortie
static const uint8_t MASQUE_LED_2 = 1 << 2 ; // GPB2, en sortie
static const uint8_t MASQUE_LED_3 = 1 << 3 ; // GPB3, en sortie
static const uint8_t MASQUE_LED_4 = 1 << 4 ; // GPB4, en sortie
static const uint8_t MASQUE_SORTIE_LOGIQUE_3 = 1 << 5 ; // GPB5, en sortie
static const uint8_t MASQUE_GAMME_ENTREE_ANALOGIQUE_1 = 1 << 6 ; // GPB6, en sortie
static const uint8_t MASQUE_GAMME_SORTIE_ANALOGIQUE_1 = 1 << 7 ; // GPB7, en sortie

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

//--- Débit SPI (en bit/s, maximum 10 Mbit/s)
static const uint32_t DEBIT_SPI = 10 * 1000 * 1000 ;

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
// SORTIES LOGIQUES
//-------------------------------------------------------------------------------------------------

//--- Les sorties logiques 0 et 1 sont directement conduites par le STM32
//    les sorties logiques 2 et 3 sont conduites par le MCP23S17
static const uint8_t COMMANDE_LOGIQUE_0 = D6 ;
static const uint8_t COMMANDE_LOGIQUE_1 = PA2 ;

//-------------------------------------------------------------------------------------------------
//  CONFIGURER CARTE ASSERVISSEMENT
//-------------------------------------------------------------------------------------------------

void configurerCarteAsservissement () {
//--- Configurer en sortie la led BUILTIN et l'allumer
  pinMode (LED_BUILTIN, OUTPUT) ;
  digitalWrite (LED_BUILTIN, HIGH) ;
//--- Configurer les ports reliés aux sorties logiques
  pinMode (COMMANDE_LOGIQUE_0, OUTPUT) ;
  pinMode (COMMANDE_LOGIQUE_1, OUTPUT) ;
//--- Configurer les ports reliés à l'encodeur numérique
  pinMode (ENCODEUR_A, INPUT_PULLUP) ;
  pinMode (ENCODEUR_B, INPUT_PULLUP) ;
  pinMode (ENCODEUR_CLIC, INPUT_PULLUP) ;
  attachInterrupt (digitalPinToInterrupt (ENCODEUR_A), appuiEncodeur, FALLING) ;
//--- Configurer l'afficheur LCD
  lcd.begin (20, 4) ; // 20 colonnes, 4 lignes
//--- Configurer le SPI
  pinMode (myCS, OUTPUT);
  digitalWrite (myCS, HIGH);
  SPI.setMOSI (myMOSI) ;
  SPI.setMISO (myMISO) ;
  SPI.setSCLK (mySCLK) ;
  SPI.begin () ;
  SPISettings settings (DEBIT_SPI, MSBFIRST, SPI_MODE0) ;
  SPI.beginTransaction (settings) ;
//--- Configurer le MCP23S17 : GPA
  digitalWrite (myCS, LOW);
  SPI.transfer (ECRITURE_MCP23S17) ;
  SPI.transfer (IODIRA_MCP23S17) ;
  SPI.transfer (0x1F) ; // GPA0 à GPA4 en entrée, GPA5 à GPA7 en sortie
  digitalWrite (myCS, HIGH);
//--- Configurer le MCP23S17 : activer les pullup sur GPA0 à GPA4
  digitalWrite (myCS, LOW);
  SPI.transfer (ECRITURE_MCP23S17) ;
  SPI.transfer (GPPUA_MCP23S17) ;
  SPI.transfer (0x1F) ; // puluup sur GPA0 à GPA4
  digitalWrite (myCS, HIGH);
//--- Configurer le MCP23S17 : GPB
  digitalWrite (myCS, LOW);
  SPI.transfer (ECRITURE_MCP23S17) ;
  SPI.transfer (IODIRB_MCP23S17) ;
  SPI.transfer (0x00) ; // GPB0 à GPB7 en sortie
  digitalWrite (myCS, HIGH);
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
    digitalWrite (myCS, LOW);
    SPI.transfer (ECRITURE_MCP23S17) ;
    SPI.transfer (GPIOA_MCP23S17) ;
    SPI.transfer (gCachePortA) ;
    digitalWrite (myCS, HIGH);
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
    digitalWrite (myCS, LOW);
    SPI.transfer (ECRITURE_MCP23S17) ;
    SPI.transfer (GPIOA_MCP23S17) ;
    SPI.transfer (gCachePortA) ;
    digitalWrite (myCS, HIGH);
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
    digitalWrite (myCS, LOW);
    SPI.transfer (ECRITURE_MCP23S17) ;
    SPI.transfer (GPIOB_MCP23S17) ;
    SPI.transfer (gCachePortB) ;
    digitalWrite (myCS, HIGH);
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
    digitalWrite (myCS, LOW);
    SPI.transfer (ECRITURE_MCP23S17) ;
    SPI.transfer (GPIOB_MCP23S17) ;
    SPI.transfer (gCachePortB) ;
    digitalWrite (myCS, HIGH);
  }
}

//-------------------------------------------------------------------------------------------------
//  ACTION LED
//-------------------------------------------------------------------------------------------------

void actionLed (const LED inLed, const  bool inValue) {
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
  digitalWrite (myCS, LOW);
  SPI.transfer (LECTURE_MCP23S17) ;
  SPI.transfer (GPIOA_MCP23S17) ;
  const uint8_t portA = SPI.transfer (0) ;
  digitalWrite (myCS, HIGH);
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
  if (!encodeurB && (gValeurEncodeur > gBorneInfEncodeur)) {
    gValeurEncodeur -= 1 ;
  }else if (encodeurB && (gValeurEncodeur < gBorneSupEncodeur)) {
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
    digitalWrite (COMMANDE_LOGIQUE_0, inValue) ;
    break ;
  case SORTIE_LOGIQUE::S1 :
    digitalWrite (COMMANDE_LOGIQUE_1, inValue) ;
    break ;
  case SORTIE_LOGIQUE::S2 :
    if (inValue) {
      activationGPA (1 << 5) ;
    }else{
      desactivationGPA (1 << 5) ;
    }
    break ;
  case SORTIE_LOGIQUE::S3 :
    if (inValue) {
      activationGPB (1 << 5) ;
    }else{
      desactivationGPB (1 << 5) ;
    }
    break ;
  }
}

//-------------------------------------------------------------------------------------------------
// SORTIES ANALOGIQUES
//-------------------------------------------------------------------------------------------------

void actionSortieAnalogique (const SORTIE_ANALOGIQUE inSortieAnalogique, const uint8_t inValue) {
  switch (inSortieAnalogique) {
  case SORTIE_ANALOGIQUE::S0 :
    analogWrite (PA4, inValue);
    break ;
  case SORTIE_ANALOGIQUE::S1 :
    analogWrite (PA5, inValue);
    break ;
  }
}

//-------------------------------------------------------------------------------------------------
// ENTRÉES ANALOGIQUES
//-------------------------------------------------------------------------------------------------

uint16_t lireEntreeAnalogique (const ENTREE_ANALOGIQUE inEntreeAnalogique) {
  uint16_t result = 0 ;
  switch (inEntreeAnalogique) {
  case ENTREE_ANALOGIQUE::E0 :
    result = analogRead (PA0) ;
    break ;
  case ENTREE_ANALOGIQUE::E1 :
    result = analogRead (PA3) ;
    break ;
  }
  return result ;
}

//-------------------------------------------------------------------------------------------------

#include "STM32H743-configuration-ls2n.h"

//--------------------------------------------------------------------------------------------------
// ATTENTION : il faut straper SB14 et SB15 au dos de la carte Nucleo (voir UM2407)
// https://community.st.com/s/question/0D53W000000YhiISAS/nucleo-h743zi2-pc8-not-connected-to-cn12the-user-manual-for-the-nucleo-h7-devices-says-that-pc8-is-connected-to-connector-8-pin-2-and-connector-12-pin-2-pages-39-and-42-however-on-my-boards-it-doesnt-seem-to-be-connected-to-connector-12-pin-2
// https://community.st.com/s/question/0D53W00000NBaWlSAL/why-are-pc8-and-pc9-not-connected-on-the-morpho-connector-of-my-nucleoh743zi2
//--------------------------------------------------------------------------------------------------
// ATTENTION : il y a un bug dans STM32Duino 1.9.0, qui rend inopérant la lecture de l'entrée analogique sur PA6
// Il faut modifier ~/Library/Arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_H743ZI/PeripheralPins.c
// en décommentant la ligne 57 :
//   {PA_6,  ADC1,  STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 3, 0)}, // ADC1_INP3
//  https://github.com/stm32duino/Arduino_Core_STM32/issues/1277
//--------------------------------------------------------------------------------------------------
// ATTENTION : il y a un bug dans STM32Duino 1.9.0, qui rend inopérant PG9 en sortie logique
// Il faut modifier ~/Library/Arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_H743ZI/variant.h
// Changer la ligne 174 :
//       #define NUM_DIGITAL_PINS        99
// En
//       #define NUM_DIGITAL_PINS        100
//  https://github.com/stm32duino/Arduino_Core_STM32/issues/1276
//--------------------------------------------------------------------------------------------------

LiquidCrystal lcd (PD6, PD7, PG6, PC0, PD2, PD3) ;

//--------------------------------------------------------------------------------------------------
//   ENCODEUR
//--------------------------------------------------------------------------------------------------

static const uint8_t ENCODEUR_A = PC8 ;
static const uint8_t ENCODEUR_B = PC9 ;

//--- La gestion de la valeur de l'encodeur numérique est faite par la routine d'interruption
//    appuiEncodeur, déclenchée sur front descendant du port ENCODEUR_A.
static void appuiEncodeur (void) ;

//--------------------------------------------------------------------------------------------------
//   CONFIGURATION DES PORTS D'ENTRÉES SORTIES
//--------------------------------------------------------------------------------------------------

static void configurerEntreesSortiesLogiques () {
  pinMode (LED_0_VERTE, OUTPUT) ;
  pinMode (LED_1_JAUNE, OUTPUT) ;
  pinMode (LED_2_ROUGE, OUTPUT) ;
  pinMode (NUCLEO_LD1_VERTE, OUTPUT) ;
  pinMode (NUCLEO_LD2_JAUNE, OUTPUT) ;
  pinMode (NUCLEO_LD3_ROUGE, OUTPUT) ;
  pinMode (INTER_DIL_1, INPUT_PULLUP) ;
  pinMode (INTER_DIL_2, INPUT_PULLUP) ;
  pinMode (INTER_DIL_3, INPUT_PULLUP) ;
  pinMode (INTER_DIL_4, INPUT_PULLUP) ;
  pinMode (POUSSOIR_P0_BLANC, INPUT_PULLUP) ;
  pinMode (POUSSOIR_P1_ROSE, INPUT_PULLUP) ;
  pinMode (POUSSOIR_P2_JAUNE, INPUT_PULLUP) ;
  pinMode (POUSSOIR_P3_ROUGE, INPUT_PULLUP) ;
  pinMode (POUSSOIR_NUCLEO_BLEU, INPUT) ;
  pinMode (ENCODEUR_A, INPUT_PULLUP) ;
  pinMode (ENCODEUR_B, INPUT_PULLUP) ;
  pinMode (ENCODEUR_CLIC, INPUT_PULLUP) ;
  attachInterrupt (digitalPinToInterrupt (ENCODEUR_A), appuiEncodeur, FALLING) ;
}

//-------------------------------------------------------------------------------------------------
// ENCODEUR NUMÉRIQUE
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
// ENTREES LOGIQUES EL0 à EL11
//-------------------------------------------------------------------------------------------------

static void configurerPortsEntreesLogiques (void) {
  pinMode (PORT_EL0,  INPUT_PULLUP) ;
  pinMode (PORT_EL1,  INPUT_PULLUP) ;
  pinMode (PORT_EL2,  INPUT_PULLUP) ;
  pinMode (PORT_EL3,  INPUT_PULLUP) ;
  pinMode (PORT_EL4,  INPUT_PULLUP) ;
  pinMode (PORT_EL5,  INPUT_PULLUP) ;
  pinMode (PORT_EL6,  INPUT_PULLUP) ;
  pinMode (PORT_EL7,  INPUT_PULLUP) ;
  pinMode (PORT_EL8,  INPUT_PULLUP) ;
  pinMode (PORT_EL9,  INPUT_PULLUP) ;
  pinMode (PORT_EL10, INPUT_PULLUP) ;
  pinMode (PORT_EL11, INPUT_PULLUP) ;
  pinMode (PA15, OUTPUT) ;
  digitalWrite (PA15, HIGH) ;
  pinMode (PORT_ENTREE_LOGIQUE_CAPTEUR_VANNE_0, INPUT_PULLUP) ;
  pinMode (PORT_ENTREE_LOGIQUE_CAPTEUR_VANNE_1, INPUT_PULLUP) ;
  pinMode (PORT_ENTREE_LOGIQUE_CAPTEUR_VANNE_2, INPUT_PULLUP) ;
  pinMode (PORT_ENTREE_LOGIQUE_CAPTEUR_VANNE_3, INPUT_PULLUP) ;
}

//-------------------------------------------------------------------------------------------------

uint16_t lireToutesEntreesLogiques (void) {
//--- Lire le port F
  const uint16_t portF = GPIOF->IDR ;
//--- Isoler les ports 0 à 5 : EL0 à EL5
  const uint16_t el0_el5 = portF & 0x3F ;
//--- Isoler les ports 10 à 15 : EL6 à EL11
  const uint16_t el6_el11 = (portF >> 4) & (0x3F << 6) ;
//--- Retour
  return el0_el5 | el6_el11 ;
}

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
// Pour changer les broches par défaut, il faut appeler setMISO, setMOSI, setSCLK, setSSEL, avant
// d'appeler SPI.begin (). C'est ce qui est fait ici. Évidemment, il faut choisir pour les broches
// en fonction de ce que permet le micro-contrôleur.
//
// Si l'on veut des liaisons SPI supplémentaires, il faut créer des nouvelles instances de SPIClass
// avec en arguments MOSI, MISO, SCK et SS :
//  SPIClass mySPI (myMOSI, myMISO, mySCK, mySS) ;
//
// Et c'est là l'approche particulière : alors que la plupart des systèmes de type Arduino
// définissent SPI2, SPI3, … en stm32duino la fonction begin devine le module qui sera
// effectivement utilisé grâce au choix des broches MOSI, MISO, SCK et SS.
//
//-------------------------------------------------------------------------------------------------

static const PinName SPI1_MOSI = PB_5 ;
static const PinName SPI1_MISO = PB_4 ;
static const PinName SPI1_CS   = PG_10 ;
static const PinName SPI1_SCK  = PA_5 ;

static const uint8_t SPI2_MOSI = PB15 ;
static const uint8_t SPI2_MISO = PC2_C ;
static const uint8_t SPI2_CS   = PB12 ;
static const uint8_t SPI2_SCK  = PB10 ;

static const uint8_t SPI3_MOSI = PC12 ;
static const uint8_t SPI3_MISO = PC11 ;
static const uint8_t SPI3_CS   = PA15 ;
static const uint8_t SPI3_SCK  = PC10 ;

static const uint8_t SPI4_MOSI = PE14 ;
static const uint8_t SPI4_MISO = PE13 ;
static const uint8_t SPI4_CS   = PE11 ;
static const uint8_t SPI4_SCK  = PE12 ;


static const uint8_t SPI5_MOSI = PF9 ;
static const uint8_t SPI5_MISO = PF8 ;
static const uint8_t SPI5_CS   = PF6 ;
static const uint8_t SPI5_SCK  = PF7 ;

//-------------------------------------------------------------------------------------------------

static SPIClass mySPI2 (SPI2_MOSI, SPI2_MISO, SPI2_SCK, SPI2_CS) ;
static SPIClass mySPI3 (SPI3_MOSI, SPI3_MISO, SPI3_SCK) ;
static SPIClass mySPI4 (SPI4_MOSI, SPI4_MISO, SPI4_SCK, SPI4_CS) ;
static SPIClass mySPI5 (SPI5_MOSI, SPI5_MISO, SPI5_SCK, SPI5_CS) ;

static const SPISettings spiSettings_MCP3008 (1'000'000, MSBFIRST, SPI_MODE0) ;
static const SPISettings spiSettings_MCP4902 (1'000'000, MSBFIRST, SPI_MODE0) ;

//-------------------------------------------------------------------------------------------------

static void configurerSPI (void) {
//--- Configurer SPI1
  SPI.setMOSI (SPI1_MOSI) ;
  SPI.setMISO (SPI1_MISO) ;
  SPI.setSCLK (SPI1_SCK) ;
  SPI.setSSEL (SPI1_CS) ;
  SPI.begin () ;
//--- Configurer SPI2
  mySPI2.begin () ;
//--- Configurer SPI3
  mySPI3.begin () ;
//--- Configurer SPI4
  mySPI4.begin () ;
//--- Configurer SPI5
  mySPI5.begin () ;
}

//-------------------------------------------------------------------------------------------------
// ENTREES ANALOGIQUES EA0 à EA15
//
// EA0 à EA7  : SPI1, canal 0 à 7
// EA8 à EA15 : SPI2, canal 0 à 7
// La fréquence maximum du SPI est 3,6 MHz (les MCP3008 sont alimentés sous 5V)
//
// Le mot de 17 bits (oui, 17) à envoyer au MCP3008 est le suivant :
//   - bit 16 (START) : 1 pour lancer la conversion
//   - bit 15 (SINGLE) : 1 pour signifier que l'on veut une conversion d'un seul canal
//   - bits 14 à 12 : l'indice du canal
//   - bits 11 à 0 : valeurs quelconques.
// Le MCP3008 renvoie :
//   - bits 16 à 10 : valeurs non significatives
//   - bits 9 à 0 : les 10 bits résultat de la conversion.
//
//-------------------------------------------------------------------------------------------------
// On fait un échange 16 bits, qui perdra le LSB (l'acquisition est donc sur 9 bits) :
//   - bit 15 (START) : 1 pour lancer la conversion
//   - bit 14 (SINGLE) : 1 pour signifier que l'on veut une conversion d'un seul canal
//   - bits 13 à 11 : l'indice du canal
//   - bits 10 à 0 : valeurs quelconques.
// Le MCP3008 renvoie :
//   - bits 15 à 9 : valeurs non significatives
//   - bits 8 à 0 : les 9 bits résultat de la conversion.

uint16_t lireEntreeAnalogique_9bits (const uint8_t inIndiceEntree) {
  uint16_t resultat = 0 ;
  if (inIndiceEntree < 16) {
  //--- Construction du mot à envoyer au MCP3008
    uint16_t w = inIndiceEntree << 11 ;
    w |= 1 << 15 ; // Bit START
    w |= 1 << 14 ; // Bit SINGLE
    if (inIndiceEntree < 8) {
      SPI.beginTransaction (spiSettings_MCP3008) ;
      resultat = SPI.transfer16 (w) ;
      SPI.endTransaction () ;
    }else{
      mySPI2.beginTransaction (spiSettings_MCP3008) ;
      resultat = mySPI2.transfer16 (w) ;
      mySPI2.endTransaction () ;
    }
    resultat &= 0x1FF ;
  }
 //---
  return resultat ;
}

//-------------------------------------------------------------------------------------------------
// On fait un échange 24 bits, l'acquisition est sur 10 bits :
//   - octet 0 :
//       - bits 7 à 1 : 0, ce qui ne lance pas l'acquiisition
//       - bit 0 : 1, c'est START qui lance la conversion
//   - octet 1 :
//       - bit 7 (SINGLE) : 1 pour signifier que l'on veut une conversion d'un seul canal
//       - bits 6 à 4 : l'indice du canal
//       - bits 3 à 0 : valeurs quelconques ;
//   - octet 2 : 8 bits quelconques
// Le MCP3008 renvoie :
//   - octet 0 : rien d'intéressant
//   - octet 1 : les bits 1 et 0 contiennent les bits 9 et 8 de l'acquisition
//   - octet 2 : les bits 7 à 0 de l'acquisition

uint16_t lireEntreeAnalogique_10bits (const uint8_t inIndiceEntree) {
  uint16_t resultat = 0 ;
  if (inIndiceEntree < 16) {
  //--- Construction du mot à envoyer au MCP3008
    uint8_t localBuffer [3] ;
    localBuffer [0] = 0x01 ; // Seul le bit START est à 1
    localBuffer [1] = inIndiceEntree << 4 ;
    localBuffer [1] |= 1 << 7 ; // Bit SINGLE
    localBuffer [2] = 0 ;
    if (inIndiceEntree < 8) {
      SPI.beginTransaction (spiSettings_MCP3008) ;
      SPI.transfer (localBuffer, 3) ;
      SPI.endTransaction () ;
    }else{
      mySPI2.beginTransaction (spiSettings_MCP3008) ;
      mySPI2.transfer (localBuffer, 3) ;
      mySPI2.endTransaction () ;
    }
    resultat = uint16_t (localBuffer [1]) ;
    resultat <<= 8 ;
    resultat |= uint16_t (localBuffer [2]) ;
    resultat &= 0x3FF ;
  }
 //---
  return resultat ;
}

//-------------------------------------------------------------------------------------------------
// CONTRÔLE DES VANNES 0 à 3
// Vanne
//    0 : SPI3, canal 0
//    1 : SPI3, canal 1
//    2 : SPI5, canal 0
//    3 : SPI5, canal 1
//-------------------------------------------------------------------------------------------------

void commandeVanne (const uint32_t inNumeroVanne, // 0 à 3
                    const uint8_t inCommande) {
  uint16_t w = uint16_t (inCommande) << 4 ;
  w |= 1 << 12 ; // bit SHDN: 1 -> la sortie est active
  w |= 1 << 13 ; // bit GA: 1 -> le gain est 1
  w |= 1 << 14 ; // bit BUF: 1 -> bufferisé
  w |= (inNumeroVanne & 1) << 15 ; // Sélection du canal
  if (inNumeroVanne < 2) {
    digitalWrite (SPI3_CS, LOW) ;
    mySPI3.beginTransaction (spiSettings_MCP4902) ;
    mySPI3.transfer16 (w) ;
    mySPI3.endTransaction () ;
    digitalWrite (SPI3_CS, HIGH) ;
  }else{
    mySPI5.beginTransaction (spiSettings_MCP4902) ;
    mySPI5.transfer16 (w) ;
    mySPI5.endTransaction () ;
  }
}

//-------------------------------------------------------------------------------------------------

bool retourLogiqueVanne (const uint32_t inNumeroVanne) { // 0 à 3
  bool r = false ;
  switch (inNumeroVanne) {
  case 0 :
    r = digitalRead (PORT_ENTREE_LOGIQUE_CAPTEUR_VANNE_0) ;
    break ;
  case 1 :
    r = digitalRead (PORT_ENTREE_LOGIQUE_CAPTEUR_VANNE_1) ;
    break ;
  case 2 :
    r = digitalRead (PORT_ENTREE_LOGIQUE_CAPTEUR_VANNE_2) ;
    break ;
  case 3 :
    r = digitalRead (PORT_ENTREE_LOGIQUE_CAPTEUR_VANNE_3) ;
    break ;
  default :
    break ;
  }
  return r ;
}

//--------------------------------------------------------------------------------------------------

uint16_t retourAnalogiqueVanne (const uint32_t inNumeroVanne) { // 0 à 3
  uint16_t r = 0 ;
  if (inNumeroVanne < 4) {
    uint16_t w = uint16_t (inNumeroVanne) << 11 ;
    w |= 1 << 15 ; // Bit START
    w |= 1 << 14 ; // Bit SINGLE
    mySPI4.beginTransaction (spiSettings_MCP3008) ;
    r = mySPI4.transfer16 (w) ;
    mySPI4.endTransaction () ;
    r &= 0x1FF ;
  }
  return r ;
}

//-------------------------------------------------------------------------------------------------
//  TEST CONNEXION VANNE
//-------------------------------------------------------------------------------------------------

uint16_t testCommandeVanne (void) {
  uint16_t w = 4 << 11 ;
  w |= 1 << 15 ; // Bit START
  w |= 1 << 14 ; // Bit SINGLE
  mySPI4.beginTransaction (spiSettings_MCP3008) ;
  uint16_t r = mySPI4.transfer16 (w) ;
  mySPI4.endTransaction () ;
  r &= 0x1FF ;
  return r ;
}

//-------------------------------------------------------------------------------------------------

void fixerValeurTestRetourAnalogique (const uint16_t inValeur) {
  analogWrite (PA4, (inValeur > 255) ? 255 : uint8_t (inValeur)) ;
}

//--------------------------------------------------------------------------------------------------
//   CONFIGURATION CARTE H743 LS2N
//--------------------------------------------------------------------------------------------------

void configurerCarteH743LS2N (void) {
  lcd.begin (20, 4) ;
  configurerEntreesSortiesLogiques () ;
  configurerPortsEntreesLogiques () ;
  configurerSPI () ;
}

//--------------------------------------------------------------------------------------------------

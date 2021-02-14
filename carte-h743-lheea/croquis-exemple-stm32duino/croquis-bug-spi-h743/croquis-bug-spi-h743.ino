#include <SPI.h>

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

static const uint8_t SPI3_MOSI = PC12 ;
static const uint8_t SPI3_MISO = PC11 ;
static const uint8_t SPI3_SSEL  = PA15 ;
static const uint8_t SPI3_SCLK = PC10 ;

//--------------------------------------------------------------------------------------------------

void setup() {
  SPI.setMOSI (SPI3_MOSI) ;
  SPI.setMISO (SPI3_MISO) ;
  SPI.setSCLK (SPI3_SCLK) ;
  SPI.setSSEL (SPI3_SSEL) ;
  SPI.begin () ;
}

//--------------------------------------------------------------------------------------------------

void loop () {
  delay (100) ;
  SPI.beginTransaction (SPISettings (1000 * 1000, MSBFIRST, SPI_MODE0)) ;
  SPI.transfer (0x12, SPI_CONTINUE) ;
  SPI.transfer (0x34, SPI_CONTINUE) ;
  SPI.transfer16 (0x5678, SPI_CONTINUE) ;
  SPI.transfer16 (0xABCD, SPI_LAST) ;
  SPI.endTransaction () ;
}

//--------------------------------------------------------------------------------------------------

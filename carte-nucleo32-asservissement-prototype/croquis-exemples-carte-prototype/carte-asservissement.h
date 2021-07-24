//-------------------------------------------------------------------------------------------------
// CONFIGURATION DE LA CARTE ASSERVISSEMENT
//-------------------------------------------------------------------------------------------------

#pragma once

#include <LiquidCrystal.h>

//-------------------------------------------------------------------------------------------------
// Configuration : cette fonction  est à appeler une et une seule fois, dans le setup.
//-------------------------------------------------------------------------------------------------

void configurerCarteAsservissement () ;

//-------------------------------------------------------------------------------------------------
// Afficheur LCD
// Les fonctions appelables sont décrites à l'URL :
//     https://www.arduino.cc/en/Reference/LiquidCrystal
//-------------------------------------------------------------------------------------------------

extern LiquidCrystal lcd ;

//-------------------------------------------------------------------------------------------------
// LEDS
//-------------------------------------------------------------------------------------------------

enum class LED : uint8_t {
  L0 = 1 << 0,
  L1 = 1 << 1,
  L2 = 1 << 2,
  L3 = 1 << 3,
  L4 = 1 << 4
} ;

//--- inValue à true -> led allumée, inValue à false -> led éteinte
void actionLed (const LED inLed, const  bool inValue) ;

//-------------------------------------------------------------------------------------------------
// POUSSOIRS
//-------------------------------------------------------------------------------------------------

enum class POUSSOIR : uint8_t {
  P0 = 1 << 0,
  P1 = 1 << 1,
  P2 = 1 << 2,
  P3 = 1 << 3,
  P4 = 1 << 4
} ;

//--- Poussoir relâché -> retourne false, appuyé -> retourne true
bool etatPoussoir (const POUSSOIR inPoussoir) ;

//-------------------------------------------------------------------------------------------------
// ENCODEUR NUMÉRIQUE
//-------------------------------------------------------------------------------------------------

//--- Clic relâché -> retourne false, appuyé -> retourne true
bool etatClic (void) ; 

void fixerGammeEncodeur (const int32_t inBorneInf, const int32_t inBorneSup) ;

int32_t valeurEncodeur (void) ;

//-------------------------------------------------------------------------------------------------
// SORTIES LOGIQUES
//-------------------------------------------------------------------------------------------------

enum class SORTIE_LOGIQUE : uint8_t {S0, S1, S2, S3} ;

void actionSortieLogique (const SORTIE_LOGIQUE inSortieLogique, const bool inValue) ;

//-------------------------------------------------------------------------------------------------
// SORTIES ANALOGIQUES
//-------------------------------------------------------------------------------------------------

//enum class SORTIE_ANALOGIQUE {
//  SU0, // Sortie analogique unipolaire 0
//  SU1, // Sortie analogique unipolaire 1
//  SB0, // Sortie analogique bipolaire 0
//  SB1  // Sortie analogique bipolaire 1
//} ;


enum class SORTIE_ANALOGIQUE {
  S0, // Sortie analogique 0
  S1  // Sortie analogique 1
} ;

void actionSortieAnalogique (const SORTIE_ANALOGIQUE inSortieAnalogique, const uint8_t inValue) ;

//-------------------------------------------------------------------------------------------------
// ENTRÉES ANALOGIQUES
//-------------------------------------------------------------------------------------------------

//enum class ENTREE_ANALOGIQUE {
//  EU0, // Entrée analogique unipolaire 0
//  EU1, // Entrée analogique unipolaire 1
//  EB0, // Entrée analogique bipolaire 0
//  EB1  // Entrée analogique bipolaire 1
//} ;


enum class ENTREE_ANALOGIQUE {
  E0, // Entrée analogique 0
  E1  // Entrée analogique 1
} ;

uint16_t lireEntreeAnalogique (const ENTREE_ANALOGIQUE inEntreeAnalogique) ;

//-------------------------------------------------------------------------------------------------

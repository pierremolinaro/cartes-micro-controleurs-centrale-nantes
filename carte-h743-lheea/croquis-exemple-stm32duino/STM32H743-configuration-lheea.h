#pragma once
#include <LiquidCrystal.h>

//#define REQUIRED_BOARD ("NUCLEO_H743ZI2")
//#ifndef BOARD_NAME
//  #error "Carte inconnue, sélectionner 'Nucleo H743ZI2'"
//#elif BOARD_NAME == REQUIRED_BOARD
//  #error "Mauvaise sélection de carte, sélectionner 'Nucleo H743ZI2'"
//#endif

//--------------------------------------------------------------------------------------------------

extern LiquidCrystal lcd ;

//--------------------------------------------------------------------------------------------------

void configurerCarteH743LHEEA (void) ;

//--------------------------------------------------------------------------------------------------
//   LEDS
//--------------------------------------------------------------------------------------------------

static const uint8_t LED_0_VERTE = PA0 ;
static const uint8_t LED_1_JAUNE = PA3 ;
static const uint8_t LED_2_ROUGE = PB2 ;
static const uint8_t NUCLEO_LD1_VERTE = PB0 ;
static const uint8_t NUCLEO_LD2_JAUNE = PE1 ;
static const uint8_t NUCLEO_LD3_ROUGE = PB14 ;

//--------------------------------------------------------------------------------------------------
//   INTERRUPTEURS DIL
//--------------------------------------------------------------------------------------------------

static const uint8_t INTER_DIL_1 = PG14 ;
static const uint8_t INTER_DIL_2 = PB11 ;
static const uint8_t INTER_DIL_3 = PB9 ;
static const uint8_t INTER_DIL_4 = PB8 ;

//--------------------------------------------------------------------------------------------------
//   POUSSOIRS
//--------------------------------------------------------------------------------------------------

static const uint8_t POUSSOIR_P0_BLANC = PE0 ;
static const uint8_t POUSSOIR_P1_ROSE  = PE2 ;
static const uint8_t POUSSOIR_P2_JAUNE = PE5 ;
static const uint8_t POUSSOIR_P3_ROUGE = PE6 ;
static const uint8_t POUSSOIR_NUCLEO_BLEU = PC13 ;

//-------------------------------------------------------------------------------------------------
// ENCODEUR NUMÉRIQUE
//-------------------------------------------------------------------------------------------------

static const uint8_t ENCODEUR_CLIC = PC6 ;

void fixerGammeEncodeur (const int32_t inBorneInf, const int32_t inBorneSup) ;

int32_t valeurEncodeur (void) ;

//--------------------------------------------------------------------------------------------------

void activerSortieTOR (const uint32_t inIndex, const bool inValue) ;

//--------------------------------------------------------------------------------------------------

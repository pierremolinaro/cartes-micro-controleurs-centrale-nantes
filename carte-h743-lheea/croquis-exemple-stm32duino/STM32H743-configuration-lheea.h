#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>

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

//-------------------------------------------------------------------------------------------------
// SORTIES TOR
//-------------------------------------------------------------------------------------------------

void activerSortieTOR (const uint32_t inIndex, const bool inValue) ;

//-------------------------------------------------------------------------------------------------
// SORTIE ANALOGIQUE
// Sortie directe :
//   0 -> 0V
//   255 -> 3,3V
//   inValue -> 3,3V *  inValue / 255
// Sortie amplifiée : dépend du réglage du potentiomètre
//-------------------------------------------------------------------------------------------------

void commanderSortieAnalogique (const uint8_t inValue) ;

//-------------------------------------------------------------------------------------------------
// ENTRÉES ANALOGIQUES
// Attention, la tension qui parvient au micro-contrôleur est réglage par potentiomètre :
//   0V -> 0
//   3,3V -> 4095
//-------------------------------------------------------------------------------------------------

uint16_t lireEntreeAnalogique (const uint32_t inNumeroEntree) ; // 0 ... 3

//--------------------------------------------------------------------------------------------------

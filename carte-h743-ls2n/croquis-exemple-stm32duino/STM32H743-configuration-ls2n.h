#pragma once

//--------------------------------------------------------------------------------------------------

#ifndef ARDUINO_NUCLEO_H743ZI2
  #error "Sélection de carte invalide: sélectionner Board Part Number : Nucleo H743ZI2".
#endif

//--------------------------------------------------------------------------------------------------

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SPI.h>

//--------------------------------------------------------------------------------------------------

extern LiquidCrystal lcd ;

//--------------------------------------------------------------------------------------------------

void configurerCarteH743LS2N (void) ;

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
// ENTREES LOGIQUES EL0 à EL11
//-------------------------------------------------------------------------------------------------

static const uint8_t PORT_EL0  = PF0 ;
static const uint8_t PORT_EL1  = PF1 ;
static const uint8_t PORT_EL2  = PF2 ;
static const uint8_t PORT_EL3  = PF3 ;
static const uint8_t PORT_EL4  = PF4 ;
static const uint8_t PORT_EL5  = PF5 ;
static const uint8_t PORT_EL6  = PF10 ;
static const uint8_t PORT_EL7  = PF11 ;
static const uint8_t PORT_EL8  = PF12 ;
static const uint8_t PORT_EL9  = PF13 ;
static const uint8_t PORT_EL10 = PF14 ;
static const uint8_t PORT_EL11 = PF15 ;

//-------------------------------------------------------------------------------------------------
// Cette fonction renvoie un entier non signé de 16 bits :
//   - le bit i (0 ≤ i ≤ 11) est à 1 si l'entrée est non connectée, 0 si elle est activée ;
//   - les bits 12 à 15 sont à 0.

uint16_t lireToutesEntreesLogiques (void) ;

//-------------------------------------------------------------------------------------------------
// ENTREES ANALOGIQUES EA0 à EA15
//-------------------------------------------------------------------------------------------------

uint16_t lireEntreeAnalogique_9bits (const uint8_t inIndiceEntree) ; // Résultat : 0 -> 511

//-------------------------------------------------------------------------------------------------

uint16_t lireEntreeAnalogique_10bits (const uint8_t inIndiceEntree) ; // Résultat : 0 -> 1023

//-------------------------------------------------------------------------------------------------
// CONTRÔLE DES VANNES 0 à 3
//-------------------------------------------------------------------------------------------------

void commandeVanne (const uint32_t inNumeroVanne, // 0 à 3
                    const uint8_t inCommande) ;

//-------------------------------------------------------------------------------------------------

bool retourLogiqueVanne (const uint32_t inNumeroVanne) ; // 0 à 3

static const uint8_t PORT_ENTREE_LOGIQUE_CAPTEUR_VANNE_0 = PG2 ;
static const uint8_t PORT_ENTREE_LOGIQUE_CAPTEUR_VANNE_1 = PG3 ;
static const uint8_t PORT_ENTREE_LOGIQUE_CAPTEUR_VANNE_2 = PG0 ;
static const uint8_t PORT_ENTREE_LOGIQUE_CAPTEUR_VANNE_3 = PG9 ;

//-------------------------------------------------------------------------------------------------

uint16_t retourAnalogiqueVanne (const uint32_t inNumeroVanne) ; // 0 à 3

//-------------------------------------------------------------------------------------------------
// TEST CONNEXION VANNE
//-------------------------------------------------------------------------------------------------

uint16_t retourCommandeVanne (void) ;

//-------------------------------------------------------------------------------------------------

void fixerValeurCapteurAnalogique (const uint16_t inValeur) ;

//--------------------------------------------------------------------------------------------------

#include "STM32H743.h"
#include "io-ports.h"
#include "sram-externe.h"

//#include "stm32h7xx_hal_gpio.h"
//#include "stm32h7xx_ll_gpio.h"
//#include "stm32h7xx_hal_nor.h"

#include <Arduino.h>

static void MPU_Config (void) {
  MPU_Region_InitTypeDef MPU_InitStruct ;

  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU as Normal Non Cacheable for the SRAM1 and SRAM2 */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE ;
  MPU_InitStruct.BaseAddress = 0x6000'0000 ; // FMC base
  MPU_InitStruct.Size = MPU_REGION_SIZE_2MB ;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS ;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE ;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE ;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE ;
  MPU_InitStruct.Number = MPU_REGION_NUMBER1 ;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0 ;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE ;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
  __DSB () ;
  __ISB () ;
}

// https://community.st.com/s/question/0D50X0000C9hD8DSQU/stm32f746-fmc-configured-for-8bit-parallel-interface-extra-bytes-sent
//--------------------------------------------------------------------------------------------------

void configurerAccesRamExterne () {
//--- Activer le module FMC
  RCC_AHB3ENR |= RCC_AHB3ENR_FMCEN ;
  RCC_AHB3ENR ;
 //--- Reset le module FMC
 RCC_AHB3RSTR |= RCC_AHB3RSTR_FMCRST ;
  RCC_AHB3RSTR &= ~ RCC_AHB3RSTR_FMCRST ;
//--- Activer les GPIO
  RCC_AHB4ENR |= RCC_AHB4ENR_GPIOAEN | RCC_AHB4ENR_GPIOBEN | RCC_AHB4ENR_GPIOCEN | RCC_AHB4ENR_GPIODEN | RCC_AHB4ENR_GPIOEEN | RCC_AHB4ENR_GPIOFEN | RCC_AHB4ENR_GPIOGEN ;
  RCC_AHB4ENR ;
//---
  RCC_D1CCIPR &= ~3 ;
 // RCC_D1CCIPR |= 3 ;
//--- Configurer les ports
  pinMode (IOPin::PinC7, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinC7, APF::af9) ; // NE1
  pinMode (IOPin::PinD4, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinD4, APF::af12) ; // NOE
  pinMode (IOPin::PinD5, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinD5, APF::af12) ; // NWE
  pinMode (IOPin::PinF0, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinF0, APF::af12) ; // A0
  pinMode (IOPin::PinF1, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinF1, APF::af12) ; // A1
  pinMode (IOPin::PinF2, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinF2, APF::af12) ; // A2
  pinMode (IOPin::PinF3, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinF3, APF::af12) ; // A3
  pinMode (IOPin::PinF4, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinF4, APF::af12) ; // A4
  pinMode (IOPin::PinF5, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinF5, APF::af12) ; // A5
  pinMode (IOPin::PinF12, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinF12, APF::af12) ; // A6
  pinMode (IOPin::PinF13, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinF13, APF::af12) ; // A7
  pinMode (IOPin::PinF14, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinF14, APF::af12) ; // A8
  pinMode (IOPin::PinF15, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinF15, APF::af12) ; // A9
  pinMode (IOPin::PinG0, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinG0, APF::af12) ; // A10
  pinMode (IOPin::PinG1, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinG1, APF::af12) ; // A11
  pinMode (IOPin::PinG2, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinG2, APF::af12) ; // A12
  pinMode (IOPin::PinG3, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinG3, APF::af12) ; // A13
  pinMode (IOPin::PinG4, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinG4, APF::af12) ; // A14
  pinMode (IOPin::PinG5, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinG5, APF::af12) ; // A15
  pinMode (IOPin::PinD11, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinD11, APF::af12) ; // A16
  pinMode (IOPin::PinD12, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinD12, APF::af12) ; // A17
  pinMode (IOPin::PinD13, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinD13, APF::af12) ; // A18
  pinMode (IOPin::PinE3, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinE3, APF::af12) ; // A19
  pinMode (IOPin::PinE4, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinE4, APF::af12) ; // A20
  pinMode (IOPin::PinD14, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinD14, APF::af12) ; // D0
  pinMode (IOPin::PinD15, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinD15, APF::af12) ; // D1
  pinMode (IOPin::PinD0, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinD0, APF::af12) ; // D2
  pinMode (IOPin::PinD1, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinD1, APF::af12) ; // D3
  pinMode (IOPin::PinE7, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinE7, APF::af12) ; // D4
  pinMode (IOPin::PinE8, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinE8, APF::af12) ; // D5
  pinMode (IOPin::PinE9, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinE9, APF::af12) ; // D6
  pinMode (IOPin::PinE10, IOMode::ALTERNATE) ; setAlternateFunction (IOPin::PinE10, APF::af12) ; // D7
//--- Table 164 page 806 et §21.7.6 page 833
  FMC_BTR1 = FMC_BTR1_BUSTURN (1) | FMC_BTR1_DATAST (9) | FMC_BTR1_ADDSET (7) ;
//--- Table 163, page 805 et §21.7.6 page 829
  FMC_BCR1 = FMC_BCR1_FMCEN // Activer le contrôleur FMC1
    | (1 << 7)
    | FMC_BCR1_WFDIS // Désactiver la FIFO d'écriture
    | FMC_BCR1_WREN // Autoriser les écritures
    | FMC_BCR1_MBKEN // Autoriser les accès
  ;
 // SCB_DisableDCache () ;
  MPU_Config () ;
}

//--------------------------------------------------------------------------------------------------

static const uint32_t TAILLE_RAM_EXTERNE = 4 * 512 * 1024 ;
//static uint32_t gErreursCumulees = 0 ;

//--------------------------------------------------------------------------------------------------

uint32_t testRamExterne (void) {
  const uint8_t valeurInitiale = uint8_t (millis ()) ;
  uint8_t valeur = valeurInitiale ;
  for (uint32_t i = 0 ; i<TAILLE_RAM_EXTERNE ; i++) {
    uint8_t * addresse = (uint8_t *) (0x6000'0000 + i) ;
    *addresse = valeur ;
    valeur += 3 ;
  }
  valeur = valeurInitiale ;
  uint32_t nombreErreurs = 0 ;
  for (uint32_t i = 0 ; i<TAILLE_RAM_EXTERNE ; i++) {
    uint8_t * addresse = (uint8_t *) (0x6000'0000 + i) ;
    const uint8_t valeurLue = *addresse ;
    if (valeurLue != valeur) {
       nombreErreurs += 1 ;
    }
    valeur += 3 ;
  }
//  gErreursCumulees += nombreErreurs ;
//  Serial.print ("Nombre d'erreurs : ") ;
//  Serial.print (nombreErreurs) ;
//  Serial.print (", cumul ") ;
//  Serial.print (gErreursCumulees) ;
//  Serial.print (", duree ") ;
//  Serial.print (duree) ;
//  Serial.println (" ms") ;
  return nombreErreurs ;
}

//--------------------------------------------------------------------------------------------------

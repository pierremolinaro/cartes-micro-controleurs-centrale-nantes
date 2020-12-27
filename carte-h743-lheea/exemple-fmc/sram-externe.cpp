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
  RCC_AHB3RSTR |= RCC_AHB3RSTR_FMCRST ;
  RCC_AHB3RSTR &= ~ RCC_AHB3RSTR_FMCRST ;
  RCC_AHB4ENR |= RCC_AHB4ENR_GPIOAEN | RCC_AHB4ENR_GPIOBEN | RCC_AHB4ENR_GPIOCEN | RCC_AHB4ENR_GPIODEN | RCC_AHB4ENR_GPIOEEN | RCC_AHB4ENR_GPIOFEN | RCC_AHB4ENR_GPIOGEN ;
  RCC_AHB4ENR ;
  RCC_D1CCIPR &= ~3 ;
  RCC_D1CCIPR |= 3 ;
//--- Configurer les ports
 // pinMode (IOPin::PinE1, IOMode::OUTPUT_MODE) ;
  pinMode (IOPin::PinC7, IOMode::ALTERNATE) ;
  setAlternateFunction (IOPin::PinC7, APF::af9) ;
  pinMode (IOPin::PinD4, IOMode::ALTERNATE) ;
  setAlternateFunction (IOPin::PinD4, APF::af12) ;
  pinMode (IOPin::PinD5, IOMode::ALTERNATE) ;
  setAlternateFunction (IOPin::PinD5, APF::af12) ;
  pinMode (IOPin::PinF0, IOMode::ALTERNATE) ;
  setAlternateFunction (IOPin::PinF0, APF::af12) ;
  pinMode (IOPin::PinF1, IOMode::ALTERNATE) ;
  setAlternateFunction (IOPin::PinF1, APF::af12) ;
  pinMode (IOPin::PinD14, IOMode::ALTERNATE) ;
  setAlternateFunction (IOPin::PinD14, APF::af12) ;
//--- Table 164 page 806 et §21.7.6 page 833
  FMC_BTR1 = FMC_BTR1_BUSTURN (7) | FMC_BTR1_DATAST (128) | FMC_BTR1_ADDSET (7) ;
 // FMC_BWTR1 = FMC_BTR1_BUSTURN (15) | FMC_BTR1_DATAST (255) | FMC_BTR1_ADDSET (15) ;
//--- Table 163, page 805 et §21.7.6 page 829
  FMC_BCR1 = FMC_BCR1_FMCEN // Activer le contrôleur FMC1
    | (1 << 7)
    | FMC_BCR1_WFDIS // Désactiver la FIFO d'écriture
    | FMC_BCR1_WREN // Autoriser les écritures
    | FMC_BCR1_MBKEN // Autoriser les accès
  ;
  SCB_DisableDCache () ;
  MPU_Config () ;
}

//--------------------------------------------------------------------------------------------------

void ecritureRamExterne (const uint8_t inValue) {
  #define ADDR (*((volatile uint16_t *) 0x6000'0000))
  ADDR = inValue ;
  __DSB () ;
  ADDR ;
  __DSB () ;
  ADDR = inValue ;
  __DSB () ;
  ADDR ;
  __DSB () ;
}

//--------------------------------------------------------------------------------------------------

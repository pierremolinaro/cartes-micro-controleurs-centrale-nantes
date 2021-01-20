#include "STM32H743-pin-modes.h"
#include "STM32H743-control-registers.h"
#include "STM32H743-configuration-lheea.h"

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

  HAL_MPU_ConfigRegion (&MPU_InitStruct) ;

  /* Enable the MPU */
  HAL_MPU_Enable (MPU_PRIVILEGED_DEFAULT);
  __DSB () ;
  __ISB () ;
}

// https://community.st.com/s/question/0D50X0000C9hD8DSQU/stm32f746-fmc-configured-for-8bit-parallel-interface-extra-bytes-sent
//--------------------------------------------------------------------------------------------------

static void configurerAccessRAMExterne (void) {
//--- Activer le module FMC
  REG_RCC_AHB3ENR |= REG_RCC_AHB3ENR_FMCEN ;
  const auto unused1 __attribute__((unused)) = REG_RCC_AHB3ENR ;
 //--- Reset le module FMC
  REG_RCC_AHB3RSTR |= REG_RCC_AHB3RSTR_FMCRST ;
  REG_RCC_AHB3RSTR &= ~ REG_RCC_AHB3RSTR_FMCRST ;
//--- Activer les GPIO
  REG_RCC_AHB4ENR |=
    REG_RCC_AHB4ENR_GPIOAEN |
    REG_RCC_AHB4ENR_GPIOBEN |
    REG_RCC_AHB4ENR_GPIOCEN |
    REG_RCC_AHB4ENR_GPIODEN |
    REG_RCC_AHB4ENR_GPIOEEN |
    REG_RCC_AHB4ENR_GPIOFEN |
    REG_RCC_AHB4ENR_GPIOGEN
  ;
  const auto unused2 __attribute__((unused)) = REG_RCC_AHB4ENR ;
//---
  REG_RCC_D1CCIPR &= ~3 ;
//--- Configurer les ports
  setAlternateFunctionMode (AlternateFunction::PC7_FMC_NE1) ;
  setAlternateFunctionMode (AlternateFunction::PD4_FMC_NOE) ;
  setAlternateFunctionMode (AlternateFunction::PD5_FMC_NWE) ;
  setAlternateFunctionMode (AlternateFunction::PF0_FMC_A0) ;
  setAlternateFunctionMode (AlternateFunction::PF1_FMC_A1) ;
  setAlternateFunctionMode (AlternateFunction::PF2_FMC_A2) ;
  setAlternateFunctionMode (AlternateFunction::PF3_FMC_A3) ;
  setAlternateFunctionMode (AlternateFunction::PF4_FMC_A4) ;
  setAlternateFunctionMode (AlternateFunction::PF5_FMC_A5) ;
  setAlternateFunctionMode (AlternateFunction::PF12_FMC_A6) ;
  setAlternateFunctionMode (AlternateFunction::PF13_FMC_A7) ;
  setAlternateFunctionMode (AlternateFunction::PF14_FMC_A8) ;
  setAlternateFunctionMode (AlternateFunction::PF15_FMC_A9) ;
  setAlternateFunctionMode (AlternateFunction::PG0_FMC_A10) ;
  setAlternateFunctionMode (AlternateFunction::PG1_FMC_A11) ;
  setAlternateFunctionMode (AlternateFunction::PG2_FMC_A12) ;
  setAlternateFunctionMode (AlternateFunction::PG3_FMC_A13) ;
  setAlternateFunctionMode (AlternateFunction::PG4_FMC_A14) ;
  setAlternateFunctionMode (AlternateFunction::PG5_FMC_A15) ;
  setAlternateFunctionMode (AlternateFunction::PD11_FMC_A16) ;
  setAlternateFunctionMode (AlternateFunction::PD12_FMC_A17) ;
  setAlternateFunctionMode (AlternateFunction::PD13_FMC_A18) ;
  setAlternateFunctionMode (AlternateFunction::PE3_FMC_A19) ;
  setAlternateFunctionMode (AlternateFunction::PE4_FMC_A20) ;
  setAlternateFunctionMode (AlternateFunction::PD14_FMC_D0) ;
  setAlternateFunctionMode (AlternateFunction::PD15_FMC_D1) ;
  setAlternateFunctionMode (AlternateFunction::PD0_FMC_D2) ;
  setAlternateFunctionMode (AlternateFunction::PD1_FMC_D3) ;
  setAlternateFunctionMode (AlternateFunction::PE7_FMC_D4) ;
  setAlternateFunctionMode (AlternateFunction::PE8_FMC_D5) ;
  setAlternateFunctionMode (AlternateFunction::PE9_FMC_D6) ;
  setAlternateFunctionMode (AlternateFunction::PE10_FMC_D7) ;
//--- Table 164 page 806 et §21.7.6 page 833
  REG_FMC_BTR1 = REG_FMC_BTR1_BUSTURN (1) | REG_FMC_BTR1_DATAST (10) | REG_FMC_BTR1_ADDSET (7) ;
//--- Table 163, page 805 et §21.7.6 page 829
  REG_FMC_BCR1 = REG_FMC_BCR1_FMCEN // Activer le contrôleur FMC1
    | (1 << 7)
    | REG_FMC_BCR1_WFDIS // Désactiver la FIFO d'écriture
    | REG_FMC_BCR1_WREN // Autoriser les écritures
    | REG_FMC_BCR1_MBKEN // Autoriser les accès
  ;
 // SCB_DisableDCache () ;
  MPU_Config () ;
}

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
 // pinMode (PA6, ANALOG_INPUT
  Serial.println (PC8) ;
  Serial.println (ENCODEUR_A) ;
  Serial.println (digitalPinToInterrupt (ENCODEUR_A)) ;
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

//--------------------------------------------------------------------------------------------------
//   SORTIES TOUT-OU-RIEN (TOR)
//--------------------------------------------------------------------------------------------------

static const byte SORTIES_TOR [10] = {
  PE11, // TOR 0
  PE12, // TOR 1
  PE13, // TOR 2
  PE14, // TOR 3
  PE15, // TOR 4
  PF10, // TOR 5
  PG8, // TOR 6
  PG9, // TOR 7
  PG12, // TOR 8
  PG15  // TOR 9
} ;

//--------------------------------------------------------------------------------------------------

static void configurerSortiesTOR (void) {
  for (uint32_t i=0 ; i<10 ; i++) {
    pinMode (SORTIES_TOR [i], OUTPUT) ;
  }
}

//--------------------------------------------------------------------------------------------------

void activerSortieTOR (const uint32_t inIndex, const bool inValue) {
  if (inIndex < 10) {
    digitalWrite (SORTIES_TOR [inIndex], inValue) ;
  }
}

//-------------------------------------------------------------------------------------------------
// SORTIE ANALOGIQUE
// Sortie directe :
//   0 -> 0V
//   255 -> 3,3V
//   inValue -> 3,3V *  inValue / 255
// Sortie amplifiée : dépend du réglage du potentiomètre
//-------------------------------------------------------------------------------------------------

void commanderSortieAnalogique (const uint8_t inValue) {
  analogWrite (PA4, inValue) ;   
}

//-------------------------------------------------------------------------------------------------
// ENTRÉES ANALOGIQUES
// Attention, la tension qui parvient au micro-contrôleur est réglage par potentiomètre :
//   0V -> 0
//   3,3V -> 4095
//-------------------------------------------------------------------------------------------------

uint16_t lireEntreeAnalogique (const uint32_t inNumeroEntree) { // 0 ... 3
  uint16_t resultat = 0 ;
  switch (inNumeroEntree) {
  case 0 :
    resultat = adc_read_value (PA_6, 12) ;
    break ;
  case 1 :
    //resultat = analogRead (PB1) ;
    resultat = adc_read_value (PB_1, 12) ;
    break ;
  case 2 :
    // resultat= analogRead (PC3) ;
    resultat = adc_read_value (PC_3, 12) ;
    break ;
  case 3 :
    // resultat = analogRead (PF11) ;
    resultat = adc_read_value (PF_11, 12) ;
    break ;
  default :
    break ;
  }
  return resultat ;
}

//--------------------------------------------------------------------------------------------------
//   CONFIGURATION CARTE H743 LHEEA
//--------------------------------------------------------------------------------------------------

void configurerCarteH743LHEEA (void) {
  lcd.begin (20, 4) ;
  configurerEntreesSortiesLogiques () ;
  configurerSortiesTOR () ;
  analogReadResolution (12) ;
  configurerAccessRAMExterne () ;
}

//--------------------------------------------------------------------------------------------------

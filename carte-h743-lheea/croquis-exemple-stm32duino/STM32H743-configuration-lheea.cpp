//#include "STM32H743-pin-modes.h"
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

//------------------------------------------------------------------------------
// ALTERNATE FUNCTIONS MODE
//------------------------------------------------------------------------------
// AlternateFunction encoding:
// Bit 15: unused (zero)
// Bits 14-13: 0 -> no pull, 1 -> pullup, 2 -> pulldown
// Bit 12: 0 -> push-pull output, 1 -> open collector output
// Bits 11-4: pin index (PA0 -> 0, PA1 -> 1, ..., PA15 -> 15, PB0 -> 16, ...)
// Bits 3-0: alternate function code (AF0 -> 0, AF1 -> 12, ...)
//------------------------------------------------------------------------------

enum class AlternateFunction : uint16_t {
  PC7_FMC_NE1  = (0 << 13) | (0 << 12) | (39 << 4) | 9,
  PD0_FMC_D2   = (0 << 13) | (0 << 12) | (48 << 4) | 12,
  PD1_FMC_D3   = (0 << 13) | (0 << 12) | (49 << 4) | 12,
  PD4_FMC_NOE  = (0 << 13) | (0 << 12) | (52 << 4) | 12,
  PD5_FMC_NWE  = (0 << 13) | (0 << 12) | (53 << 4) | 12,
  PD11_FMC_A16 = (0 << 13) | (0 << 12) | (59 << 4) | 12,
  PD12_FMC_A17 = (0 << 13) | (0 << 12) | (60 << 4) | 12,
  PD13_FMC_A18 = (0 << 13) | (0 << 12) | (61 << 4) | 12,
  PD14_FMC_D0  = (0 << 13) | (0 << 12) | (62 << 4) | 12,
  PD15_FMC_D1  = (0 << 13) | (0 << 12) | (63 << 4) | 12,
  PE3_FMC_A19  = (0 << 13) | (0 << 12) | (67 << 4) | 12,
  PE4_FMC_A20  = (0 << 13) | (0 << 12) | (68 << 4) | 12,
  PE7_FMC_D4   = (0 << 13) | (0 << 12) | (71 << 4) | 12,
  PE8_FMC_D5   = (0 << 13) | (0 << 12) | (72 << 4) | 12,
  PE9_FMC_D6   = (0 << 13) | (0 << 12) | (73 << 4) | 12,
  PE10_FMC_D7  = (0 << 13) | (0 << 12) | (74 << 4) | 12,
  PF0_FMC_A0   = (0 << 13) | (0 << 12) | (80 << 4) | 12,
  PF1_FMC_A1   = (0 << 13) | (0 << 12) | (81 << 4) | 12,
  PF2_FMC_A2   = (0 << 13) | (0 << 12) | (82 << 4) | 12,
  PF3_FMC_A3   = (0 << 13) | (0 << 12) | (83 << 4) | 12,
  PF4_FMC_A4   = (0 << 13) | (0 << 12) | (84 << 4) | 12,
  PF5_FMC_A5   = (0 << 13) | (0 << 12) | (85 << 4) | 12,
  PF12_FMC_A6  = (0 << 13) | (0 << 12) | (92 << 4) | 12,
  PF13_FMC_A7  = (0 << 13) | (0 << 12) | (93 << 4) | 12,
  PF14_FMC_A8  = (0 << 13) | (0 << 12) | (94 << 4) | 12,
  PF15_FMC_A9  = (0 << 13) | (0 << 12) | (95 << 4) | 12,
  PG0_FMC_A10  = (0 << 13) | (0 << 12) | (96 << 4) | 12,
  PG1_FMC_A11  = (0 << 13) | (0 << 12) | (97 << 4) | 12,
  PG2_FMC_A12  = (0 << 13) | (0 << 12) | (98 << 4) | 12,
  PG3_FMC_A13  = (0 << 13) | (0 << 12) | (99 << 4) | 12,
  PG4_FMC_A14  = (0 << 13) | (0 << 12) | (100 << 4) | 12,
  PG5_FMC_A15  = (0 << 13) | (0 << 12) | (101 << 4) | 12
} ;

//------------------------------------------------------------------------------
// GPIOA BASE ADDRESS
//------------------------------------------------------------------------------

static const uint32_t GPIO_BASE_ADDRESS = 0x58020000 ; // Addresse de GPIOA_MODER

//------------------------------------------------------------------------------

static void setAlternateFunctionMode (const AlternateFunction inPin) {
  const uint32_t pinIndex = (uint32_t (inPin) >> 4) & 0xFF ;
  const uint32_t gpioIndex = pinIndex / 16 ; // 0 -> PORTA, 1 -> PORTB, ...
  const uint32_t portIndex = pinIndex % 16 ; // portIndex: 0, ..., 15
//--- gpioAddress
  const uint32_t gpioAddress = GPIO_BASE_ADDRESS + gpioIndex * 0x400 ;
//--- OPTYPER register has offset 0x04
  const bool openCollector = (uint16_t (inPin) & (1 << 12)) != 0 ;
  volatile uint32_t & OTYPER = *((volatile uint32_t *) (gpioAddress + 0x04)) ;
  uint32_t registerValue = OTYPER ;
  if (openCollector) { // Open collector output
    registerValue |=   (uint32_t (1) << portIndex) ;
  }else{ // Push-pull output
    registerValue &= ~ (uint32_t (1) << portIndex) ;
  }
  OTYPER = registerValue ;
//--- PUPDR register has offset 0x0C
  const uint32_t pupd = uint32_t (inPin) >> 13 ;
  volatile uint32_t & PUPDR = *((volatile uint32_t *) (gpioAddress + 0x0C)) ;
  registerValue = PUPDR ;
  registerValue &= ~ (uint32_t (3) << (portIndex * 2)) ;
  registerValue |=    pupd << (portIndex * 2) ;
  PUPDR = registerValue ;
//--- OSPEEDR register has offset 0x08
  volatile uint32_t & OSPEEDR = *((volatile uint32_t *) (gpioAddress + 0x08)) ;
  const uint32_t speed = 3 ; // Very high speed
  OSPEEDR |= speed << (portIndex * 2) ;
//--- MODER register has offset 0x0
// Alternate : set bit (portIndex * 2 + 1), reset bit (portIndex * 2)
  volatile uint32_t & MODER = *((volatile uint32_t *) (gpioAddress + 0x00)) ;
  registerValue = MODER ;
  registerValue |= uint32_t (1) << ((portIndex * 2) + 1) ;
  registerValue &= ~ (uint32_t (1) << (portIndex * 2)) ;
  MODER = registerValue ;
//--- AFRL register has offset 0x20, AFRH -> 0x24
//--- We use byte access
//    At offset 0 : AFR1[3:0], AFR0[3:0]
//    At offset 1 : AFR3[3:0], AFR2[3:0]
//    At offset 2 : AFR5[3:0], AFR4[3:0]
//    ....
//    At offset 7 : AFR15[3:0], AFR14[3:0]
  const uint8_t alternationFunction = uint8_t (inPin) & 0x0F ;
  const uint32_t AFR_address = gpioAddress + 0x20 + (portIndex / 2) ;
  volatile uint8_t & AFR_BYTE = *((volatile uint8_t *) AFR_address) ;
  const uint8_t mask = ((portIndex & 1) == 0) ? 0xF0 : 0x0F ;
  const uint8_t shiftedAltFunc = ((portIndex & 1) == 0)
    ? alternationFunction
    : (alternationFunction << 4)
  ;
  uint8_t reg = AFR_BYTE ;
  reg &= mask ;
  reg |= shiftedAltFunc ;
  AFR_BYTE = reg ;
}

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

//------------------------------------------------------------------------------
// Peripheral FMC: FMC
//------------------------------------------------------------------------------

//--- Register BCR1: This register contains the control information of each memory bank, used for SRAMs, PSRAM and NOR Flash memories.
static volatile uint32_t & REG_FMC_BCR1 __attribute__((unused)) = * ((volatile uint32_t *) (0x52004000 + 0)) ;

  // Field MBKEN:  Memory bank enable bit This bit enables the memory bank. After reset Bank1 is enabled, all others are disabled. Accessing a disabled bank causes an ERROR on AXI bus.
  const uint32_t REG_FMC_BCR1_MBKEN = 1U << 0 ;

  // Field WREN:  Write enable bit This bit indicates whether write operations are enabled/disabled in the bank by the FMC:
  const uint32_t REG_FMC_BCR1_WREN = 1U << 12 ;

  // Field WFDIS:  Write FIFO Disable This bit disables the Write FIFO used by the FMC controller. Note: The WFDIS bit of the FMC_BCR2..4 registers is dont care. It is only enabled through the FMC_BCR1 register.
  const uint32_t REG_FMC_BCR1_WFDIS = 1U << 21 ;

  // Field FMCEN:  FMC controller Enable This bit enables/disables the FMC controller. Note: The FMCEN bit of the FMC_BCR2..4 registers is dont care. It is only enabled through the FMC_BCR1 register.
  const uint32_t REG_FMC_BCR1_FMCEN = 1U << 31 ;

//------------------------------------------------------------------------------

//--- Register BTR1: This register contains the control information of each memory bank, used for SRAMs, PSRAM and NOR Flash memories.If the EXTMOD bit is set in the FMC_BCRx register, then this register is partitioned for write and read access, that is, 2 registers are available: one to configure read accesses (this register) and one to configure write accesses (FMC_BWTRx registers).
static volatile uint32_t & REG_FMC_BTR1 __attribute__((unused)) = * ((volatile uint32_t *) (0x52004000 + 4)) ;

  // Field ADDSET:  Address setup phase duration These bits are written by software to define the duration of the address setup phase (refer to Figure81 to Figure93), used in SRAMs, ROMs and asynchronous NOR Flash: For each access mode address setup phase duration, please refer to the respective figure (refer to Figure81 to Figure93). Note: In synchronous accesses, this value is dont care. In Muxed mode or Mode D, the minimum value for ADDSET is 1.
  inline uint32_t REG_FMC_BTR1_ADDSET (const uint32_t inValue) { return (inValue & 0xFU) << 0 ; }

  // Field DATAST:  Data-phase duration These bits are written by software to define the duration of the data phase (refer to Figure81 to Figure93), used in asynchronous accesses: For each memory type and access mode data-phase duration, please refer to the respective figure (Figure81 to Figure93). Example: Mode1, write access, DATAST=1: Data-phase duration= DATAST+1 = 2 KCK_FMC clock cycles. Note: In synchronous accesses, this value is dont care.
  inline uint32_t REG_FMC_BTR1_DATAST (const uint32_t inValue) { return (inValue & 0xFFU) << 8 ; }

  // Field BUSTURN:  Bus turnaround phase duration These bits are written by software to add a delay at the end of a write-to-read or read-to write transaction. The programmed bus turnaround delay is inserted between an asynchronous read (in muxed or mode D) or write transaction and any other asynchronous /synchronous read/write from/to a static bank. If a read operation is performed, the bank can be the same or a different one, whereas it must be different in case of write operation to the bank, except in muxed mode or mode D. In some cases, whatever the programmed BUSTRUN values, the bus turnaround delay is fixed as follows: The bus turnaround delay is not inserted between two consecutive asynchronous write transfers to the same static memory bank except in muxed mode and mode D. There is a bus turnaround delay of 1 FMC clock cycle between: Two consecutive asynchronous read transfers to the same static memory bank except for modes muxed and D. An asynchronous read to an asynchronous or synchronous write to any static bank or dynamic bank except in modes muxed and D mode. There is a bus turnaround delay of 2 FMC clock cycle between: Two consecutive synchronous write operations (in Burst or Single mode) to the same bank. A synchronous write (burst or single) access and an asynchronous write or read transfer to or from static memory bank (the bank can be the same or a different one in case of a read operation. Two consecutive synchronous read operations (in Burst or Single mode) followed by any synchronous/asynchronous read or write from/to another static memory bank. There is a bus turnaround delay of 3 FMC clock cycle between: Two consecutive synchronous write operations (in Burst or Single mode) to different static banks. A synchronous write access (in Burst or Single mode) and a synchronous read from the same or a different bank. The bus turnaround delay allows to match the minimum time between consecutive transactions (tEHEL from NEx high to NEx low) and the maximum time required by the memory to free the data bus after a read access (tEHQZ): (BUSTRUN + 1) KCK_FMC period &#8805; tEHELmin and (BUSTRUN + 2)KCK_FMC period &#8805; tEHQZmax if EXTMOD = 0 (BUSTRUN + 2)KCK_FMC period &#8805; max (tEHELmin, tEHQZmax) if EXTMOD = 126. ...
  inline uint32_t REG_FMC_BTR1_BUSTURN (const uint32_t inValue) { return (inValue & 0xFU) << 16 ; }

//--------------------------------------------------------------------------------------------------

static void configurerAccessRAMExterne (void) {
//--- Activer le module FMC
  RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN ;
  const auto unused1 __attribute__((unused)) = RCC->AHB3ENR ;
 //--- Reset le module FMC
  RCC->AHB3RSTR |= RCC_AHB3RSTR_FMCRST ;
  RCC->AHB3RSTR &= ~ RCC_AHB3RSTR_FMCRST ;
//--- Activer les GPIO
  RCC->AHB4ENR |=
    RCC_AHB4ENR_GPIOAEN |
    RCC_AHB4ENR_GPIOBEN |
    RCC_AHB4ENR_GPIOCEN |
    RCC_AHB4ENR_GPIODEN |
    RCC_AHB4ENR_GPIOEEN |
    RCC_AHB4ENR_GPIOFEN |
    RCC_AHB4ENR_GPIOGEN
  ;
  const auto unused2 __attribute__((unused)) = RCC->AHB4ENR ;
//---
  RCC->D1CCIPR &= ~3 ;
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
//  Serial.println (PC8) ;
//  Serial.println (ENCODEUR_A) ;
//  Serial.println (digitalPinToInterrupt (ENCODEUR_A)) ;
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

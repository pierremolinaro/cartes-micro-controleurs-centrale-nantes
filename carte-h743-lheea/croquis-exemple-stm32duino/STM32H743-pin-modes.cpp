#include "STM32H743-pin-modes.h"
#include "STM32H743-control-registers.h"

//------------------------------------------------------------------------------
// STM32H743
//------------------------------------------------------------------------------
// PA0
// Possible signals: ADC1_INP16, ETH_CRS, GPIO, PWR_WKUP0, SAI2_SD_B, SDMMC2_CMD, TIM15_BKIN, TIM2_CH1, TIM2_ETR, TIM5_CH1, TIM8_ETR, UART4_TX, USART2_CTS, USART2_NSS
//------------------------------------------------------------------------------

// PA0: digital input
// PA0: digital output
// PA0: analog
// PA0: EXTI
// PA0: EVENTOUT
// PA0_TIM2_CH1 // AF1
// PA0_TIM2_ETR // AF1
// PA0_TIM5_CH1 // AF2
// PA0_TIM8_ETR // AF3
// PA0_TIM15_BKIN // AF4
// PA0_USART2_CTS // AF7
// PA0_USART2_NSS // AF7
// PA0_UART4_TX // AF8
// PA0_SDMMC2_CMD // AF9
// PA0_SAI2_SD_B // AF10
// PA0_ETH_CRS // AF11

//------------------------------------------------------------------------------
// PA1
// Possible signals: ADC1_INN16, ADC1_INP17, ETH_REF_CLK, ETH_RX_CLK, GPIO, LPTIM3_OUT, LTDC_R2, QUADSPI_BK1_IO3, SAI2_MCLK_B, TIM15_CH1N, TIM2_CH2, TIM5_CH2, UART4_RX, USART2_DE, USART2_RTS
//------------------------------------------------------------------------------

// PA1: digital input
// PA1: digital output
// PA1: analog
// PA1: EXTI
// PA1: EVENTOUT
// PA1_TIM2_CH2 // AF1
// PA1_TIM5_CH2 // AF2
// PA1_LPTIM3_OUT // AF3
// PA1_TIM15_CH1N // AF4
// PA1_USART2_DE // AF7
// PA1_USART2_RTS // AF7
// PA1_UART4_RX // AF8
// PA1_QUADSPI_BK1_IO3 // AF9
// PA1_SAI2_MCLK_B // AF10
// PA1_ETH_REF_CLK // AF11
// PA1_ETH_RX_CLK // AF11
// PA1_LTDC_R2 // AF14

//------------------------------------------------------------------------------
// PA2
// Possible signals: ADC1_INP14, ADC2_INP14, ETH_MDIO, GPIO, LPTIM4_OUT, LTDC_R1, MDIOS_MDIO, PWR_WKUP1, SAI2_SCK_B, TIM15_CH1, TIM2_CH3, TIM5_CH3, USART2_TX
//------------------------------------------------------------------------------

// PA2: digital input
// PA2: digital output
// PA2: analog
// PA2: EXTI
// PA2: EVENTOUT
// PA2_TIM2_CH3 // AF1
// PA2_TIM5_CH3 // AF2
// PA2_LPTIM4_OUT // AF3
// PA2_TIM15_CH1 // AF4
// PA2_USART2_TX // AF7
// PA2_SAI2_SCK_B // AF8
// PA2_ETH_MDIO // AF11
// PA2_MDIOS_MDIO // AF12
// PA2_LTDC_R1 // AF14

//------------------------------------------------------------------------------
// PA3
// Possible signals: ADC1_INP15, ADC2_INP15, ETH_COL, GPIO, LPTIM5_OUT, LTDC_B2, LTDC_B5, TIM15_CH2, TIM2_CH4, TIM5_CH4, USART2_RX, USB_OTG_HS_ULPI_D0
//------------------------------------------------------------------------------

// PA3: digital input
// PA3: digital output
// PA3: analog
// PA3: EXTI
// PA3: EVENTOUT
// PA3_TIM2_CH4 // AF1
// PA3_TIM5_CH4 // AF2
// PA3_LPTIM5_OUT // AF3
// PA3_TIM15_CH2 // AF4
// PA3_USART2_RX // AF7
// PA3_LTDC_B2 // AF9
// PA3_USB_OTG_HS_ULPI_D0 // AF10
// PA3_ETH_COL // AF11
// PA3_LTDC_B5 // AF14

//------------------------------------------------------------------------------
// PA4
// Possible signals: ADC1_INP18, ADC2_INP18, DAC1_OUT1, DCMI_HSYNC, GPIO, I2S1_WS, I2S3_WS, LTDC_VSYNC, SPI1_NSS, SPI3_NSS, SPI6_NSS, TIM5_ETR, USART2_CK, USB_OTG_HS_SOF
//------------------------------------------------------------------------------

// PA4: digital input
// PA4: digital output
// PA4: analog
// PA4: EXTI
// PA4: EVENTOUT
// PA4_TIM5_ETR // AF2
// PA4_I2S1_WS // AF5
// PA4_SPI1_NSS // AF5
// PA4_I2S3_WS // AF6
// PA4_SPI3_NSS // AF6
// PA4_USART2_CK // AF7
// PA4_SPI6_NSS // AF8
// PA4_USB_OTG_HS_SOF // AF12
// PA4_DCMI_HSYNC // AF13
// PA4_LTDC_VSYNC // AF14

//------------------------------------------------------------------------------
// PA5
// Possible signals: ADC1_INN18, ADC1_INP19, ADC2_INN18, ADC2_INP19, DAC1_OUT2, GPIO, I2S1_CK, LTDC_R4, SPI1_SCK, SPI6_SCK, TIM2_CH1, TIM2_ETR, TIM8_CH1N, USB_OTG_HS_ULPI_CK
//------------------------------------------------------------------------------

// PA5: digital input
// PA5: digital output
// PA5: analog
// PA5: EXTI
// PA5: EVENTOUT
// PA5_TIM2_CH1 // AF1
// PA5_TIM2_ETR // AF1
// PA5_TIM8_CH1N // AF3
// PA5_I2S1_CK // AF5
// PA5_SPI1_SCK // AF5
// PA5_SPI6_SCK // AF8
// PA5_USB_OTG_HS_ULPI_CK // AF10
// PA5_LTDC_R4 // AF14

//------------------------------------------------------------------------------
// PA6
// Possible signals: ADC1_INP3, ADC2_INP3, DCMI_PIXCLK, GPIO, I2S1_SDI, LTDC_G2, MDIOS_MDC, SPI1_MISO, SPI6_MISO, TIM13_CH1, TIM1_BKIN, TIM1_BKIN_COMP1, TIM1_BKIN_COMP2, TIM3_CH1, TIM8_BKIN, TIM8_BKIN_COMP1, TIM8_BKIN_COMP2
//------------------------------------------------------------------------------

// PA6: digital input
// PA6: digital output
// PA6: analog
// PA6: EXTI
// PA6: EVENTOUT
// PA6_TIM1_BKIN // AF1
// PA6_TIM3_CH1 // AF2
// PA6_TIM8_BKIN // AF3
// PA6_I2S1_SDI // AF5
// PA6_SPI1_MISO // AF5
// PA6_SPI6_MISO // AF8
// PA6_TIM13_CH1 // AF9
// PA6_TIM8_BKIN_COMP1 // AF10
// PA6_TIM8_BKIN_COMP2 // AF10
// PA6_MDIOS_MDC // AF11
// PA6_TIM1_BKIN_COMP1 // AF12
// PA6_TIM1_BKIN_COMP2 // AF12
// PA6_DCMI_PIXCLK // AF13
// PA6_LTDC_G2 // AF14

//------------------------------------------------------------------------------
// PA7
// Possible signals: ADC1_INN3, ADC1_INP7, ADC2_INN3, ADC2_INP7, ETH_CRS_DV, ETH_RX_DV, FMC_SDNWE, GPIO, I2S1_SDO, OPAMP1_VINM, OPAMP1_VINM1, SPI1_MOSI, SPI6_MOSI, TIM14_CH1, TIM1_CH1N, TIM3_CH2, TIM8_CH1N
//------------------------------------------------------------------------------

// PA7: digital input
// PA7: digital output
// PA7: analog
// PA7: EXTI
// PA7: EVENTOUT
// PA7_TIM1_CH1N // AF1
// PA7_TIM3_CH2 // AF2
// PA7_TIM8_CH1N // AF3
// PA7_I2S1_SDO // AF5
// PA7_SPI1_MOSI // AF5
// PA7_SPI6_MOSI // AF8
// PA7_TIM14_CH1 // AF9
// PA7_ETH_CRS_DV // AF11
// PA7_ETH_RX_DV // AF11
// PA7_FMC_SDNWE // AF12

//------------------------------------------------------------------------------
// PA8
// Possible signals: GPIO, HRTIM_CHB2, I2C3_SCL, LTDC_B3, LTDC_R6, RCC_MCO_1, TIM1_CH1, TIM8_BKIN2, TIM8_BKIN2_COMP1, TIM8_BKIN2_COMP2, UART7_RX, USART1_CK, USB_OTG_FS_SOF
//------------------------------------------------------------------------------

// PA8: digital input
// PA8: digital output
// PA8: analog
// PA8: EXTI
// PA8: EVENTOUT
// PA8_RCC_MCO_1 // AF0
// PA8_TIM1_CH1 // AF1
// PA8_HRTIM_CHB2 // AF2
// PA8_TIM8_BKIN2 // AF3
// PA8_I2C3_SCL // AF4
// PA8_USART1_CK // AF7
// PA8_USB_OTG_FS_SOF // AF10
// PA8_UART7_RX // AF11
// PA8_TIM8_BKIN2_COMP1 // AF12
// PA8_TIM8_BKIN2_COMP2 // AF12
// PA8_LTDC_B3 // AF13
// PA8_LTDC_R6 // AF14

//------------------------------------------------------------------------------
// PA9
// Possible signals: DAC1_EXTI9, DCMI_D0, GPIO, HRTIM_CHC1, I2C3_SMBA, I2S2_CK, LPUART1_TX, LTDC_R5, SPI2_SCK, TIM1_CH2, USART1_TX, USB_OTG_FS_VBUS
//------------------------------------------------------------------------------

// PA9: digital input
// PA9: digital output
// PA9: analog
// PA9: EXTI
// PA9: EVENTOUT
// PA9_TIM1_CH2 // AF1
// PA9_HRTIM_CHC1 // AF2
// PA9_LPUART1_TX // AF3
// PA9_I2C3_SMBA // AF4
// PA9_I2S2_CK // AF5
// PA9_SPI2_SCK // AF5
// PA9_USART1_TX // AF7
// PA9_DCMI_D0 // AF13
// PA9_LTDC_R5 // AF14

//------------------------------------------------------------------------------
// PA10
// Possible signals: DCMI_D1, GPIO, HRTIM_CHC2, LPUART1_RX, LTDC_B1, LTDC_B4, MDIOS_MDIO, TIM1_CH3, USART1_RX, USB_OTG_FS_ID
//------------------------------------------------------------------------------

// PA10: digital input
// PA10: digital output
// PA10: analog
// PA10: EXTI
// PA10: EVENTOUT
// PA10_TIM1_CH3 // AF1
// PA10_HRTIM_CHC2 // AF2
// PA10_LPUART1_RX // AF3
// PA10_USART1_RX // AF7
// PA10_USB_OTG_FS_ID // AF10
// PA10_MDIOS_MDIO // AF11
// PA10_LTDC_B4 // AF12
// PA10_DCMI_D1 // AF13
// PA10_LTDC_B1 // AF14

//------------------------------------------------------------------------------
// PA11
// Possible signals: ADC1_EXTI11, ADC2_EXTI11, ADC3_EXTI11, FDCAN1_RX, GPIO, HRTIM_CHD1, I2S2_WS, LPUART1_CTS, LTDC_R4, SPI2_NSS, TIM1_CH4, UART4_RX, USART1_CTS, USART1_NSS, USB_OTG_FS_DM
//------------------------------------------------------------------------------

// PA11: digital input
// PA11: digital output
// PA11: analog
// PA11: EXTI
// PA11: EVENTOUT
// PA11_TIM1_CH4 // AF1
// PA11_HRTIM_CHD1 // AF2
// PA11_LPUART1_CTS // AF3
// PA11_I2S2_WS // AF5
// PA11_SPI2_NSS // AF5
// PA11_UART4_RX // AF6
// PA11_USART1_CTS // AF7
// PA11_USART1_NSS // AF7
// PA11_FDCAN1_RX // AF9
// PA11_USB_OTG_FS_DM // AF10
// PA11_LTDC_R4 // AF14

//------------------------------------------------------------------------------
// PA12
// Possible signals: FDCAN1_TX, GPIO, HRTIM_CHD2, I2S2_CK, LPUART1_DE, LPUART1_RTS, LTDC_R5, SAI2_FS_B, SPI2_SCK, TIM1_ETR, UART4_TX, USART1_DE, USART1_RTS, USB_OTG_FS_DP
//------------------------------------------------------------------------------

// PA12: digital input
// PA12: digital output
// PA12: analog
// PA12: EXTI
// PA12: EVENTOUT
// PA12_TIM1_ETR // AF1
// PA12_HRTIM_CHD2 // AF2
// PA12_LPUART1_DE // AF3
// PA12_LPUART1_RTS // AF3
// PA12_I2S2_CK // AF5
// PA12_SPI2_SCK // AF5
// PA12_UART4_TX // AF6
// PA12_USART1_DE // AF7
// PA12_USART1_RTS // AF7
// PA12_SAI2_FS_B // AF8
// PA12_FDCAN1_TX // AF9
// PA12_USB_OTG_FS_DP // AF10
// PA12_LTDC_R5 // AF14

//------------------------------------------------------------------------------
// PA13
// Possible signals: DEBUG_JTMS-SWDIO, GPIO
//------------------------------------------------------------------------------

// PA13: digital input
// PA13: digital output
// PA13: analog
// PA13: EXTI
// PA13: EVENTOUT
// PA13_DEBUG_JTMS-SWDIO // AF0

//------------------------------------------------------------------------------
// PA14
// Possible signals: DEBUG_JTCK-SWCLK, GPIO
//------------------------------------------------------------------------------

// PA14: digital input
// PA14: digital output
// PA14: analog
// PA14: EXTI
// PA14: EVENTOUT
// PA14_DEBUG_JTCK-SWCLK // AF0

//------------------------------------------------------------------------------
// PA15
// Possible signals: ADC1_EXTI15, ADC2_EXTI15, ADC3_EXTI15, CEC, DEBUG_JTDI, GPIO, HRTIM_FLT1, I2S1_WS, I2S3_WS, SPI1_NSS, SPI3_NSS, SPI6_NSS, TIM2_CH1, TIM2_ETR, UART4_DE, UART4_RTS, UART7_TX
//------------------------------------------------------------------------------

// PA15: digital input
// PA15: digital output
// PA15: analog
// PA15: EXTI
// PA15: EVENTOUT
// PA15_DEBUG_JTDI // AF0
// PA15_TIM2_CH1 // AF1
// PA15_TIM2_ETR // AF1
// PA15_HRTIM_FLT1 // AF2
// PA15_CEC // AF4
// PA15_I2S1_WS // AF5
// PA15_SPI1_NSS // AF5
// PA15_I2S3_WS // AF6
// PA15_SPI3_NSS // AF6
// PA15_SPI6_NSS // AF7
// PA15_UART4_DE // AF8
// PA15_UART4_RTS // AF8
// PA15_UART7_TX // AF11
// PA15_DSIHOST_TE // AF13

//------------------------------------------------------------------------------
// PB0
// Possible signals: ADC1_INN5, ADC1_INP9, ADC2_INN5, ADC2_INP9, COMP1_INP, DFSDM1_CKOUT, ETH_RXD2, GPIO, LTDC_G1, LTDC_R3, OPAMP1_VINP, TIM1_CH2N, TIM3_CH3, TIM8_CH2N, UART4_CTS, USB_OTG_HS_ULPI_D1
//------------------------------------------------------------------------------

// PB0: digital input
// PB0: digital output
// PB0: analog
// PB0: EXTI
// PB0: EVENTOUT
// PB0_TIM1_CH2N // AF1
// PB0_TIM3_CH3 // AF2
// PB0_TIM8_CH2N // AF3
// PB0_DFSDM1_CKOUT // AF6
// PB0_UART4_CTS // AF8
// PB0_LTDC_R3 // AF9
// PB0_USB_OTG_HS_ULPI_D1 // AF10
// PB0_ETH_RXD2 // AF11
// PB0_LTDC_G1 // AF14

//------------------------------------------------------------------------------
// PB1
// Possible signals: ADC1_INP5, ADC2_INP5, COMP1_INM, DFSDM1_DATIN1, ETH_RXD3, GPIO, LTDC_G0, LTDC_R6, TIM1_CH3N, TIM3_CH4, TIM8_CH3N, USB_OTG_HS_ULPI_D2
//------------------------------------------------------------------------------

// PB1: digital input
// PB1: digital output
// PB1: analog
// PB1: EXTI
// PB1: EVENTOUT
// PB1_TIM1_CH3N // AF1
// PB1_TIM3_CH4 // AF2
// PB1_TIM8_CH3N // AF3
// PB1_DFSDM1_DATIN1 // AF6
// PB1_LTDC_R6 // AF9
// PB1_USB_OTG_HS_ULPI_D2 // AF10
// PB1_ETH_RXD3 // AF11
// PB1_LTDC_G0 // AF14

//------------------------------------------------------------------------------
// PB2
// Possible signals: COMP1_INP, DFSDM1_CKIN1, GPIO, I2S3_SDO, QUADSPI_CLK, RTC_OUT_ALARM, RTC_OUT_CALIB, SAI1_D1, SAI1_SD_A, SAI4_D1, SAI4_SD_A, SPI3_MOSI
//------------------------------------------------------------------------------

// PB2: digital input
// PB2: digital output
// PB2: analog
// PB2: EXTI
// PB2: EVENTOUT
// PB2_RTC_OUT_ALARM // AF0
// PB2_RTC_OUT_CALIB // AF0
// PB2_SAI1_D1 // AF2
// PB2_DFSDM1_CKIN1 // AF4
// PB2_SAI1_SD_A // AF6
// PB2_I2S3_SDO // AF7
// PB2_SPI3_MOSI // AF7
// PB2_SAI4_SD_A // AF8
// PB2_QUADSPI_CLK // AF9
// PB2_SAI4_D1 // AF10

//------------------------------------------------------------------------------
// PB3
// Possible signals: CRS_SYNC, DEBUG_JTDO-SWO, GPIO, HRTIM_FLT4, I2S1_CK, I2S3_CK, SDMMC2_D2, SPI1_SCK, SPI3_SCK, SPI6_SCK, TIM2_CH2, UART7_RX
//------------------------------------------------------------------------------

// PB3: digital input
// PB3: digital output
// PB3: analog
// PB3: EXTI
// PB3: EVENTOUT
// PB3_DEBUG_JTDO-SWO // AF0
// PB3_TIM2_CH2 // AF1
// PB3_HRTIM_FLT4 // AF2
// PB3_I2S1_CK // AF5
// PB3_SPI1_SCK // AF5
// PB3_I2S3_CK // AF6
// PB3_SPI3_SCK // AF6
// PB3_SPI6_SCK // AF8
// PB3_SDMMC2_D2 // AF9
// PB3_CRS_SYNC // AF10
// PB3_UART7_RX // AF11

//------------------------------------------------------------------------------
// PB4
// Possible signals: DEBUG_JTRST, GPIO, HRTIM_EEV6, I2S1_SDI, I2S2_WS, I2S3_SDI, SDMMC2_D3, SPI1_MISO, SPI2_NSS, SPI3_MISO, SPI6_MISO, TIM16_BKIN, TIM3_CH1, UART7_TX
//------------------------------------------------------------------------------

// PB4: digital input
// PB4: digital output
// PB4: analog
// PB4: EXTI
// PB4: EVENTOUT
// PB4_SYS_JTRST // AF0
// PB4_TIM16_BKIN // AF1
// PB4_TIM3_CH1 // AF2
// PB4_HRTIM_EEV6 // AF3
// PB4_I2S1_SDI // AF5
// PB4_SPI1_MISO // AF5
// PB4_I2S3_SDI // AF6
// PB4_SPI3_MISO // AF6
// PB4_I2S2_WS // AF7
// PB4_SPI2_NSS // AF7
// PB4_SPI6_MISO // AF8
// PB4_SDMMC2_D3 // AF9
// PB4_UART7_TX // AF11

//------------------------------------------------------------------------------
// PB5
// Possible signals: DCMI_D10, ETH_PPS_OUT, FDCAN2_RX, FMC_SDCKE1, GPIO, HRTIM_EEV7, I2C1_SMBA, I2C4_SMBA, I2S1_SDO, I2S3_SDO, SPI1_MOSI, SPI3_MOSI, SPI6_MOSI, TIM17_BKIN, TIM3_CH2, UART5_RX, USB_OTG_HS_ULPI_D7
//------------------------------------------------------------------------------

// PB5: digital input
// PB5: digital output
// PB5: analog
// PB5: EXTI
// PB5: EVENTOUT
// PB5_TIM17_BKIN // AF1
// PB5_TIM3_CH2 // AF2
// PB5_HRTIM_EEV7 // AF3
// PB5_I2C1_SMBA // AF4
// PB5_I2S1_SDO // AF5
// PB5_SPI1_MOSI // AF5
// PB5_I2C4_SMBA // AF6
// PB5_I2S3_SDO // AF7
// PB5_SPI3_MOSI // AF7
// PB5_SPI6_MOSI // AF8
// PB5_FDCAN2_RX // AF9
// PB5_USB_OTG_HS_ULPI_D7 // AF10
// PB5_ETH_PPS_OUT // AF11
// PB5_FMC_SDCKE1 // AF12
// PB5_DCMI_D10 // AF13
// PB5_UART5_RX // AF14

//------------------------------------------------------------------------------
// PB6
// Possible signals: CEC, DCMI_D5, DFSDM1_DATIN5, FDCAN2_TX, FMC_SDNE1, GPIO, HRTIM_EEV8, I2C1_SCL, I2C4_SCL, LPUART1_TX, QUADSPI_BK1_NCS, TIM16_CH1N, TIM4_CH1, UART5_TX, USART1_TX
//------------------------------------------------------------------------------

// PB6: digital input
// PB6: digital output
// PB6: analog
// PB6: EXTI
// PB6: EVENTOUT
// PB6_TIM16_CH1N // AF1
// PB6_TIM4_CH1 // AF2
// PB6_HRTIM_EEV8 // AF3
// PB6_I2C1_SCL // AF4
// PB6_CEC // AF5
// PB6_I2C4_SCL // AF6
// PB6_USART1_TX // AF7
// PB6_LPUART1_TX // AF8
// PB6_FDCAN2_TX // AF9
// PB6_QUADSPI_BK1_NCS // AF10
// PB6_DFSDM1_DATIN5 // AF11
// PB6_FMC_SDNE1 // AF12
// PB6_DCMI_D5 // AF13
// PB6_UART5_TX // AF14

//------------------------------------------------------------------------------
// PB7
// Possible signals: DCMI_VSYNC, DFSDM1_CKIN5, FMC_NL, GPIO, HRTIM_EEV9, I2C1_SDA, I2C4_SDA, LPUART1_RX, PWR_PVD_IN, TIM17_CH1N, TIM4_CH2, USART1_RX
//------------------------------------------------------------------------------

// PB7: digital input
// PB7: digital output
// PB7: analog
// PB7: EXTI
// PB7: EVENTOUT
// PB7_TIM17_CH1N // AF1
// PB7_TIM4_CH2 // AF2
// PB7_HRTIM_EEV9 // AF3
// PB7_I2C1_SDA // AF4
// PB7_I2C4_SDA // AF6
// PB7_USART1_RX // AF7
// PB7_LPUART1_RX // AF8
// PB7_DFSDM1_CKIN5 // AF11
// PB7_FMC_NL // AF12
// PB7_DCMI_VSYNC // AF13

//------------------------------------------------------------------------------
// PB8
// Possible signals: DCMI_D6, DFSDM1_CKIN7, ETH_TXD3, FDCAN1_RX, GPIO, I2C1_SCL, I2C4_SCL, LTDC_B6, SDMMC1_CKIN, SDMMC1_D4, SDMMC2_D4, TIM16_CH1, TIM4_CH3, UART4_RX
//------------------------------------------------------------------------------

// PB8: digital input
// PB8: digital output
// PB8: analog
// PB8: EXTI
// PB8: EVENTOUT
// PB8_TIM16_CH1 // AF1
// PB8_TIM4_CH3 // AF2
// PB8_DFSDM1_CKIN7 // AF3
// PB8_I2C1_SCL // AF4
// PB8_I2C4_SCL // AF6
// PB8_SDMMC1_CKIN // AF7
// PB8_UART4_RX // AF8
// PB8_FDCAN1_RX // AF9
// PB8_SDMMC2_D4 // AF10
// PB8_ETH_TXD3 // AF11
// PB8_SDMMC1_D4 // AF12
// PB8_DCMI_D6 // AF13
// PB8_LTDC_B6 // AF14

//------------------------------------------------------------------------------
// PB9
// Possible signals: DAC1_EXTI9, DCMI_D7, DFSDM1_DATIN7, FDCAN1_TX, GPIO, I2C1_SDA, I2C4_SDA, I2C4_SMBA, I2S2_WS, LTDC_B7, SDMMC1_CDIR, SDMMC1_D5, SDMMC2_D5, SPI2_NSS, TIM17_CH1, TIM4_CH4, UART4_TX
//------------------------------------------------------------------------------

// PB9: digital input
// PB9: digital output
// PB9: analog
// PB9: EXTI
// PB9: EVENTOUT
// PB9_TIM17_CH1 // AF1
// PB9_TIM4_CH4 // AF2
// PB9_DFSDM1_DATIN7 // AF3
// PB9_I2C1_SDA // AF4
// PB9_I2S2_WS // AF5
// PB9_SPI2_NSS // AF5
// PB9_I2C4_SDA // AF6
// PB9_SDMMC1_CDIR // AF7
// PB9_UART4_TX // AF8
// PB9_FDCAN1_TX // AF9
// PB9_SDMMC2_D5 // AF10
// PB9_I2C4_SMBA // AF11
// PB9_SDMMC1_D5 // AF12
// PB9_DCMI_D7 // AF13
// PB9_LTDC_B7 // AF14

//------------------------------------------------------------------------------
// PB10
// Possible signals: DFSDM1_DATIN7, ETH_RX_ER, GPIO, HRTIM_SCOUT, I2C2_SCL, I2S2_CK, LPTIM2_IN1, LTDC_G4, QUADSPI_BK1_NCS, SPI2_SCK, TIM2_CH3, USART3_TX, USB_OTG_HS_ULPI_D3
//------------------------------------------------------------------------------

// PB10: digital input
// PB10: digital output
// PB10: analog
// PB10: EXTI
// PB10: EVENTOUT
// PB10_TIM2_CH3 // AF1
// PB10_HRTIM_SCOUT // AF2
// PB10_LPTIM2_IN1 // AF3
// PB10_I2C2_SCL // AF4
// PB10_I2S2_CK // AF5
// PB10_SPI2_SCK // AF5
// PB10_DFSDM1_DATIN7 // AF6
// PB10_USART3_TX // AF7
// PB10_QUADSPI_BK1_NCS // AF9
// PB10_USB_OTG_HS_ULPI_D3 // AF10
// PB10_ETH_RX_ER // AF11
// PB10_LTDC_G4 // AF14

//------------------------------------------------------------------------------
// PB11
// Possible signals: ADC1_EXTI11, ADC2_EXTI11, ADC3_EXTI11, DFSDM1_CKIN7, ETH_TX_EN, GPIO, HRTIM_SCIN, I2C2_SDA, LPTIM2_ETR, LTDC_G5, TIM2_CH4, USART3_RX, USB_OTG_HS_ULPI_D4
//------------------------------------------------------------------------------

// PB11: digital input
// PB11: digital output
// PB11: analog
// PB11: EXTI
// PB11: EVENTOUT
// PB11_TIM2_CH4 // AF1
// PB11_HRTIM_SCIN // AF2
// PB11_LPTIM2_ETR // AF3
// PB11_I2C2_SDA // AF4
// PB11_DFSDM1_CKIN7 // AF6
// PB11_USART3_RX // AF7
// PB11_USB_OTG_HS_ULPI_D4 // AF10
// PB11_ETH_TX_EN // AF11
// PB11_DSIHOST_TE // AF13
// PB11_LTDC_G5 // AF14

//------------------------------------------------------------------------------
// PB12
// Possible signals: DFSDM1_DATIN1, ETH_TXD0, FDCAN2_RX, GPIO, I2C2_SMBA, I2S2_WS, SPI2_NSS, TIM1_BKIN, TIM1_BKIN_COMP1, TIM1_BKIN_COMP2, UART5_RX, USART3_CK, USB_OTG_HS_ID, USB_OTG_HS_ULPI_D5
//------------------------------------------------------------------------------

// PB12: digital input
// PB12: digital output
// PB12: analog
// PB12: EXTI
// PB12: EVENTOUT
// PB12_TIM1_BKIN // AF1
// PB12_I2C2_SMBA // AF4
// PB12_I2S2_WS // AF5
// PB12_SPI2_NSS // AF5
// PB12_DFSDM1_DATIN1 // AF6
// PB12_USART3_CK // AF7
// PB12_FDCAN2_RX // AF9
// PB12_USB_OTG_HS_ULPI_D5 // AF10
// PB12_ETH_TXD0 // AF11
// PB12_USB_OTG_HS_ID // AF12
// PB12_TIM1_BKIN_COMP1 // AF13
// PB12_TIM1_BKIN_COMP2 // AF13
// PB12_UART5_RX // AF14

//------------------------------------------------------------------------------
// PB13
// Possible signals: DFSDM1_CKIN1, ETH_TXD1, FDCAN2_TX, GPIO, I2S2_CK, LPTIM2_OUT, SPI2_SCK, TIM1_CH1N, UART5_TX, USART3_CTS, USART3_NSS, USB_OTG_HS_ULPI_D6, USB_OTG_HS_VBUS
//------------------------------------------------------------------------------

// PB13: digital input
// PB13: digital output
// PB13: analog
// PB13: EXTI
// PB13: EVENTOUT
// PB13_TIM1_CH1N // AF1
// PB13_LPTIM2_OUT // AF3
// PB13_I2S2_CK // AF5
// PB13_SPI2_SCK // AF5
// PB13_DFSDM1_CKIN1 // AF6
// PB13_USART3_CTS // AF7
// PB13_USART3_NSS // AF7
// PB13_FDCAN2_TX // AF9
// PB13_USB_OTG_HS_ULPI_D6 // AF10
// PB13_ETH_TXD1 // AF11
// PB13_UART5_TX // AF14

//------------------------------------------------------------------------------
// PB14
// Possible signals: DFSDM1_DATIN2, GPIO, I2S2_SDI, SDMMC2_D0, SPI2_MISO, TIM12_CH1, TIM1_CH2N, TIM8_CH2N, UART4_DE, UART4_RTS, USART1_TX, USART3_DE, USART3_RTS, USB_OTG_HS_DM
//------------------------------------------------------------------------------

// PB14: digital input
// PB14: digital output
// PB14: analog
// PB14: EXTI
// PB14: EVENTOUT
// PB14_TIM1_CH2N // AF1
// PB14_TIM12_CH1 // AF2
// PB14_TIM8_CH2N // AF3
// PB14_USART1_TX // AF4
// PB14_I2S2_SDI // AF5
// PB14_SPI2_MISO // AF5
// PB14_DFSDM1_DATIN2 // AF6
// PB14_USART3_DE // AF7
// PB14_USART3_RTS // AF7
// PB14_UART4_DE // AF8
// PB14_UART4_RTS // AF8
// PB14_SDMMC2_D0 // AF9
// PB14_USB_OTG_HS_DM // AF12

//------------------------------------------------------------------------------
// PB15
// Possible signals: ADC1_EXTI15, ADC2_EXTI15, ADC3_EXTI15, DFSDM1_CKIN2, GPIO, I2S2_SDO, RTC_REFIN, SDMMC2_D1, SPI2_MOSI, TIM12_CH2, TIM1_CH3N, TIM8_CH3N, UART4_CTS, USART1_RX, USB_OTG_HS_DP
//------------------------------------------------------------------------------

// PB15: digital input
// PB15: digital output
// PB15: analog
// PB15: EXTI
// PB15: EVENTOUT
// PB15_RTC_REFIN // AF0
// PB15_TIM1_CH3N // AF1
// PB15_TIM12_CH2 // AF2
// PB15_TIM8_CH3N // AF3
// PB15_USART1_RX // AF4
// PB15_I2S2_SDO // AF5
// PB15_SPI2_MOSI // AF5
// PB15_DFSDM1_CKIN2 // AF6
// PB15_UART4_CTS // AF8
// PB15_SDMMC2_D1 // AF9
// PB15_USB_OTG_HS_DP // AF12

//------------------------------------------------------------------------------
// PC0
// Possible signals: ADC1_INP10, ADC2_INP10, ADC3_INP10, DFSDM1_CKIN0, DFSDM1_DATIN4, FMC_SDNWE, GPIO, LTDC_R5, SAI2_FS_B, USB_OTG_HS_ULPI_STP
//------------------------------------------------------------------------------

// PC0: digital input
// PC0: digital output
// PC0: analog
// PC0: EXTI
// PC0: EVENTOUT
// PC0_DFSDM1_CKIN0 // AF3
// PC0_DFSDM1_DATIN4 // AF6
// PC0_SAI2_FS_B // AF8
// PC0_USB_OTG_HS_ULPI_STP // AF10
// PC0_FMC_SDNWE // AF12
// PC0_LTDC_R5 // AF14

//------------------------------------------------------------------------------
// PC1
// Possible signals: ADC1_INN10, ADC1_INP11, ADC2_INN10, ADC2_INP11, ADC3_INN10, ADC3_INP11, DEBUG_TRACED0, DFSDM1_CKIN4, DFSDM1_DATIN0, ETH_MDC, GPIO, I2S2_SDO, MDIOS_MDC, PWR_WKUP5, RTC_TAMP3, SAI1_D1, SAI1_SD_A, SAI4_D1, SAI4_SD_A, SDMMC2_CK, SPI2_MOSI
//------------------------------------------------------------------------------

// PC1: digital input
// PC1: digital output
// PC1: analog
// PC1: EXTI
// PC1: EVENTOUT
// PC1_DEBUG_TRACED0 // AF0
// PC1_SAI1_D1 // AF2
// PC1_DFSDM1_DATIN0 // AF3
// PC1_DFSDM1_CKIN4 // AF4
// PC1_I2S2_SDO // AF5
// PC1_SPI2_MOSI // AF5
// PC1_SAI1_SD_A // AF6
// PC1_SAI4_SD_A // AF8
// PC1_SDMMC2_CK // AF9
// PC1_SAI4_D1 // AF10
// PC1_ETH_MDC // AF11
// PC1_MDIOS_MDC // AF12

//------------------------------------------------------------------------------
// PC2_C
// Possible signals: ADC3_INN1, ADC3_INP0, DFSDM1_CKIN1, DFSDM1_CKOUT, ETH_TXD2, FMC_SDNE0, GPIO, I2S2_SDI, SPI2_MISO, USB_OTG_HS_ULPI_DIR
//------------------------------------------------------------------------------

// PC2_C: digital input
// PC2_C: digital output
// PC2_C: analog
// PC2_C: EXTI
// PC2_C: EVENTOUT
// PC2_C_DFSDM1_CKIN1 // AF3
// PC2_C_I2S2_SDI // AF5
// PC2_C_SPI2_MISO // AF5
// PC2_C_DFSDM1_CKOUT // AF6
// PC2_C_USB_OTG_HS_ULPI_DIR // AF10
// PC2_C_ETH_TXD2 // AF11
// PC2_C_FMC_SDNE0 // AF12

//------------------------------------------------------------------------------
// PC3_C
// Possible signals: ADC3_INP1, DFSDM1_DATIN1, ETH_TX_CLK, FMC_SDCKE0, GPIO, I2S2_SDO, SPI2_MOSI, USB_OTG_HS_ULPI_NXT
//------------------------------------------------------------------------------

// PC3_C: digital input
// PC3_C: digital output
// PC3_C: analog
// PC3_C: EXTI
// PC3_C: EVENTOUT
// PC3_C_DFSDM1_DATIN1 // AF3
// PC3_C_I2S2_SDO // AF5
// PC3_C_SPI2_MOSI // AF5
// PC3_C_USB_OTG_HS_ULPI_NXT // AF10
// PC3_C_ETH_TX_CLK // AF11
// PC3_C_FMC_SDCKE0 // AF12

//------------------------------------------------------------------------------
// PC4
// Possible signals: ADC1_INP4, ADC2_INP4, COMP1_INM, DFSDM1_CKIN2, ETH_RXD0, FMC_SDNE0, GPIO, I2S1_MCK, OPAMP1_VOUT, SPDIFRX1_IN2
//------------------------------------------------------------------------------

// PC4: digital input
// PC4: digital output
// PC4: analog
// PC4: EXTI
// PC4: EVENTOUT
// PC4_DFSDM1_CKIN2 // AF3
// PC4_I2S1_MCK // AF5
// PC4_SPDIFRX1_IN2 // AF9
// PC4_ETH_RXD0 // AF11
// PC4_FMC_SDNE0 // AF12

//------------------------------------------------------------------------------
// PC5
// Possible signals: ADC1_INN4, ADC1_INP8, ADC2_INN4, ADC2_INP8, COMP1_OUT, DFSDM1_DATIN2, ETH_RXD1, FMC_SDCKE0, GPIO, OPAMP1_VINM, OPAMP1_VINM0, SAI1_D3, SAI4_D3, SPDIFRX1_IN3
//------------------------------------------------------------------------------

// PC5: digital input
// PC5: digital output
// PC5: analog
// PC5: EXTI
// PC5: EVENTOUT
// PC5_SAI1_D3 // AF2
// PC5_DFSDM1_DATIN2 // AF3
// PC5_SPDIFRX1_IN3 // AF9
// PC5_SAI4_D3 // AF10
// PC5_ETH_RXD1 // AF11
// PC5_FMC_SDCKE0 // AF12
// PC5_COMP1_OUT // AF13

//------------------------------------------------------------------------------
// PC6
// Possible signals: DCMI_D0, DFSDM1_CKIN3, FMC_NWAIT, GPIO, HRTIM_CHA1, I2S2_MCK, LTDC_HSYNC, SDMMC1_D0DIR, SDMMC1_D6, SDMMC2_D6, SWPMI1_IO, TIM3_CH1, TIM8_CH1, USART6_TX
//------------------------------------------------------------------------------

// PC6: digital input
// PC6: digital output
// PC6: analog
// PC6: EXTI
// PC6: EVENTOUT
// PC6_HRTIM_CHA1 // AF1
// PC6_TIM3_CH1 // AF2
// PC6_TIM8_CH1 // AF3
// PC6_DFSDM1_CKIN3 // AF4
// PC6_I2S2_MCK // AF5
// PC6_USART6_TX // AF7
// PC6_SDMMC1_D0DIR // AF8
// PC6_FMC_NWAIT // AF9
// PC6_SDMMC2_D6 // AF10
// PC6_SDMMC1_D6 // AF12
// PC6_DCMI_D0 // AF13
// PC6_LTDC_HSYNC // AF14

//------------------------------------------------------------------------------
// PC7
// Possible signals: DCMI_D1, DEBUG_TRGIO, DFSDM1_DATIN3, FMC_NE1, GPIO, HRTIM_CHA2, I2S3_MCK, LTDC_G6, SDMMC1_D123DIR, SDMMC1_D7, SDMMC2_D7, SWPMI1_TX, TIM3_CH2, TIM8_CH2, USART6_RX
//------------------------------------------------------------------------------

// PC7: digital input
// PC7: digital output
// PC7: analog
// PC7: EXTI
// PC7: EVENTOUT
// PC7_DEBUG_TRGIO // AF0
// PC7_HRTIM_CHA2 // AF1
// PC7_TIM3_CH2 // AF2
// PC7_TIM8_CH2 // AF3
// PC7_DFSDM1_DATIN3 // AF4
// PC7_I2S3_MCK // AF6
// PC7_USART6_RX // AF7
// PC7_SDMMC1_D123DIR // AF8
// PC7_FMC_NE1 // AF9
// PC7_SDMMC2_D7 // AF10
// PC7_SWPMI1_TX // AF11
// PC7_SDMMC1_D7 // AF12
// PC7_DCMI_D1 // AF13
// PC7_LTDC_G6 // AF14

//------------------------------------------------------------------------------
// PC8
// Possible signals: DCMI_D2, DEBUG_TRACED1, FMC_NCE, FMC_NE2, GPIO, HRTIM_CHB1, SDMMC1_D0, SWPMI1_RX, TIM3_CH3, TIM8_CH3, UART5_DE, UART5_RTS, USART6_CK
//------------------------------------------------------------------------------

// PC8: digital input
// PC8: digital output
// PC8: analog
// PC8: EXTI
// PC8: EVENTOUT
// PC8_DEBUG_TRACED1 // AF0
// PC8_HRTIM_CHB1 // AF1
// PC8_TIM3_CH3 // AF2
// PC8_TIM8_CH3 // AF3
// PC8_USART6_CK // AF7
// PC8_UART5_DE // AF8
// PC8_UART5_RTS // AF8
// PC8_FMC_NCE // AF9
// PC8_FMC_NE2 // AF9
// PC8_SWPMI1_RX // AF11
// PC8_SDMMC1_D0 // AF12
// PC8_DCMI_D2 // AF13

//------------------------------------------------------------------------------
// PC9
// Possible signals: DAC1_EXTI9, DCMI_D3, GPIO, I2C3_SDA, I2S_CKIN, LTDC_B2, LTDC_G3, QUADSPI_BK1_IO0, RCC_MCO_2, SDMMC1_D1, SWPMI1_SUSPEND, TIM3_CH4, TIM8_CH4, UART5_CTS
//------------------------------------------------------------------------------

// PC9: digital input
// PC9: digital output
// PC9: analog
// PC9: EXTI
// PC9: EVENTOUT
// PC9_RCC_MCO_2 // AF0
// PC9_TIM3_CH4 // AF2
// PC9_TIM8_CH4 // AF3
// PC9_I2C3_SDA // AF4
// PC9_I2S_CKIN // AF5
// PC9_UART5_CTS // AF8
// PC9_QUADSPI_BK1_IO0 // AF9
// PC9_LTDC_G3 // AF10
// PC9_SWPMI1_SUSPEND // AF11
// PC9_SDMMC1_D1 // AF12
// PC9_DCMI_D3 // AF13
// PC9_LTDC_B2 // AF14

//------------------------------------------------------------------------------
// PC10
// Possible signals: DCMI_D8, DFSDM1_CKIN5, GPIO, HRTIM_EEV1, I2S3_CK, LTDC_R2, QUADSPI_BK1_IO1, SDMMC1_D2, SPI3_SCK, UART4_TX, USART3_TX
//------------------------------------------------------------------------------

// PC10: digital input
// PC10: digital output
// PC10: analog
// PC10: EXTI
// PC10: EVENTOUT
// PC10_HRTIM_EEV1 // AF2
// PC10_DFSDM1_CKIN5 // AF3
// PC10_I2S3_CK // AF6
// PC10_SPI3_SCK // AF6
// PC10_USART3_TX // AF7
// PC10_UART4_TX // AF8
// PC10_QUADSPI_BK1_IO1 // AF9
// PC10_SDMMC1_D2 // AF12
// PC10_DCMI_D8 // AF13
// PC10_LTDC_R2 // AF14

//------------------------------------------------------------------------------
// PC11
// Possible signals: ADC1_EXTI11, ADC2_EXTI11, ADC3_EXTI11, DCMI_D4, DFSDM1_DATIN5, GPIO, HRTIM_FLT2, I2S3_SDI, QUADSPI_BK2_NCS, SDMMC1_D3, SPI3_MISO, UART4_RX, USART3_RX
//------------------------------------------------------------------------------

// PC11: digital input
// PC11: digital output
// PC11: analog
// PC11: EXTI
// PC11: EVENTOUT
// PC11_HRTIM_FLT2 // AF2
// PC11_DFSDM1_DATIN5 // AF3
// PC11_I2S3_SDI // AF6
// PC11_SPI3_MISO // AF6
// PC11_USART3_RX // AF7
// PC11_UART4_RX // AF8
// PC11_QUADSPI_BK2_NCS // AF9
// PC11_SDMMC1_D3 // AF12
// PC11_DCMI_D4 // AF13

//------------------------------------------------------------------------------
// PC12
// Possible signals: DCMI_D9, DEBUG_TRACED3, GPIO, HRTIM_EEV2, I2S3_SDO, SDMMC1_CK, SPI3_MOSI, UART5_TX, USART3_CK
//------------------------------------------------------------------------------

// PC12: digital input
// PC12: digital output
// PC12: analog
// PC12: EXTI
// PC12: EVENTOUT
// PC12_DEBUG_TRACED3 // AF0
// PC12_HRTIM_EEV2 // AF2
// PC12_I2S3_SDO // AF6
// PC12_SPI3_MOSI // AF6
// PC12_USART3_CK // AF7
// PC12_UART5_TX // AF8
// PC12_SDMMC1_CK // AF12
// PC12_DCMI_D9 // AF13

//------------------------------------------------------------------------------
// PC13
// Possible signals: GPIO, PWR_WKUP2, RTC_OUT_ALARM, RTC_OUT_CALIB, RTC_TAMP1, RTC_TS
//------------------------------------------------------------------------------

// PC13: digital input
// PC13: digital output
// PC13: analog
// PC13: EXTI
// PC13: EVENTOUT

//------------------------------------------------------------------------------
// PC14
// Possible signals: GPIO, RCC_OSC32_IN
//------------------------------------------------------------------------------

// PC14: digital input
// PC14: digital output
// PC14: analog
// PC14: EXTI
// PC14: EVENTOUT

//------------------------------------------------------------------------------
// PC15
// Possible signals: ADC1_EXTI15, ADC2_EXTI15, ADC3_EXTI15, GPIO, RCC_OSC32_OUT
//------------------------------------------------------------------------------

// PC15: digital input
// PC15: digital output
// PC15: analog
// PC15: EXTI
// PC15: EVENTOUT

//------------------------------------------------------------------------------
// PD0
// Possible signals: DFSDM1_CKIN6, FDCAN1_RX, FMC_D2, FMC_DA2, GPIO, SAI3_SCK_A, UART4_RX
//------------------------------------------------------------------------------

// PD0: digital input
// PD0: digital output
// PD0: analog
// PD0: EXTI
// PD0: EVENTOUT
// PD0_DFSDM1_CKIN6 // AF3
// PD0_SAI3_SCK_A // AF6
// PD0_UART4_RX // AF8
// PD0_FDCAN1_RX // AF9
// PD0_FMC_D2 // AF12
// PD0_FMC_DA2 // AF12

//------------------------------------------------------------------------------
// PD1
// Possible signals: DFSDM1_DATIN6, FDCAN1_TX, FMC_D3, FMC_DA3, GPIO, SAI3_SD_A, UART4_TX
//------------------------------------------------------------------------------

// PD1: digital input
// PD1: digital output
// PD1: analog
// PD1: EXTI
// PD1: EVENTOUT
// PD1_DFSDM1_DATIN6 // AF3
// PD1_SAI3_SD_A // AF6
// PD1_UART4_TX // AF8
// PD1_FDCAN1_TX // AF9
// PD1_FMC_D3 // AF12
// PD1_FMC_DA3 // AF12

//------------------------------------------------------------------------------
// PD2
// Possible signals: DCMI_D11, DEBUG_TRACED2, GPIO, SDMMC1_CMD, TIM3_ETR, UART5_RX
//------------------------------------------------------------------------------

// PD2: digital input
// PD2: digital output
// PD2: analog
// PD2: EXTI
// PD2: EVENTOUT
// PD2_DEBUG_TRACED2 // AF0
// PD2_TIM3_ETR // AF2
// PD2_UART5_RX // AF8
// PD2_SDMMC1_CMD // AF12
// PD2_DCMI_D11 // AF13

//------------------------------------------------------------------------------
// PD3
// Possible signals: DCMI_D5, DFSDM1_CKOUT, FMC_CLK, GPIO, I2S2_CK, LTDC_G7, SPI2_SCK, USART2_CTS, USART2_NSS
//------------------------------------------------------------------------------

// PD3: digital input
// PD3: digital output
// PD3: analog
// PD3: EXTI
// PD3: EVENTOUT
// PD3_DFSDM1_CKOUT // AF3
// PD3_I2S2_CK // AF5
// PD3_SPI2_SCK // AF5
// PD3_USART2_CTS // AF7
// PD3_USART2_NSS // AF7
// PD3_FMC_CLK // AF12
// PD3_DCMI_D5 // AF13
// PD3_LTDC_G7 // AF14

//------------------------------------------------------------------------------
// PD4
// Possible signals: FMC_NOE, GPIO, HRTIM_FLT3, SAI3_FS_A, USART2_DE, USART2_RTS
//------------------------------------------------------------------------------

// PD4: digital input
// PD4: digital output
// PD4: analog
// PD4: EXTI
// PD4: EVENTOUT
// PD4_HRTIM_FLT3 // AF2
// PD4_SAI3_FS_A // AF6
// PD4_USART2_DE // AF7
// PD4_USART2_RTS // AF7
// PD4_FMC_NOE // AF12

//------------------------------------------------------------------------------
// PD5
// Possible signals: FMC_NWE, GPIO, HRTIM_EEV3, USART2_TX
//------------------------------------------------------------------------------

// PD5: digital input
// PD5: digital output
// PD5: analog
// PD5: EXTI
// PD5: EVENTOUT
// PD5_HRTIM_EEV3 // AF2
// PD5_USART2_TX // AF7
// PD5_FMC_NWE // AF12

//------------------------------------------------------------------------------
// PD6
// Possible signals: DCMI_D10, DFSDM1_CKIN4, DFSDM1_DATIN1, FMC_NWAIT, GPIO, I2S3_SDO, LTDC_B2, SAI1_D1, SAI1_SD_A, SAI4_D1, SAI4_SD_A, SDMMC2_CK, SPI3_MOSI, USART2_RX
//------------------------------------------------------------------------------

// PD6: digital input
// PD6: digital output
// PD6: analog
// PD6: EXTI
// PD6: EVENTOUT
// PD6_SAI1_D1 // AF2
// PD6_DFSDM1_CKIN4 // AF3
// PD6_DFSDM1_DATIN1 // AF4
// PD6_I2S3_SDO // AF5
// PD6_SPI3_MOSI // AF5
// PD6_SAI1_SD_A // AF6
// PD6_USART2_RX // AF7
// PD6_SAI4_SD_A // AF8
// PD6_SAI4_D1 // AF10
// PD6_SDMMC2_CK // AF11
// PD6_FMC_NWAIT // AF12
// PD6_DCMI_D10 // AF13
// PD6_LTDC_B2 // AF14

//------------------------------------------------------------------------------
// PD7
// Possible signals: DFSDM1_CKIN1, DFSDM1_DATIN4, FMC_NE1, GPIO, I2S1_SDO, SDMMC2_CMD, SPDIFRX1_IN0, SPI1_MOSI, USART2_CK
//------------------------------------------------------------------------------

// PD7: digital input
// PD7: digital output
// PD7: analog
// PD7: EXTI
// PD7: EVENTOUT
// PD7_DFSDM1_DATIN4 // AF3
// PD7_I2S1_SDO // AF5
// PD7_SPI1_MOSI // AF5
// PD7_DFSDM1_CKIN1 // AF6
// PD7_USART2_CK // AF7
// PD7_SPDIFRX1_IN0 // AF9
// PD7_SDMMC2_CMD // AF11
// PD7_FMC_NE1 // AF12

//------------------------------------------------------------------------------
// PD8
// Possible signals: DFSDM1_CKIN3, FMC_D13, FMC_DA13, GPIO, SAI3_SCK_B, SPDIFRX1_IN1, USART3_TX
//------------------------------------------------------------------------------

// PD8: digital input
// PD8: digital output
// PD8: analog
// PD8: EXTI
// PD8: EVENTOUT
// PD8_DFSDM1_CKIN3 // AF3
// PD8_SAI3_SCK_B // AF6
// PD8_USART3_TX // AF7
// PD8_SPDIFRX1_IN1 // AF9
// PD8_FMC_D13 // AF12
// PD8_FMC_DA13 // AF12

//------------------------------------------------------------------------------
// PD9
// Possible signals: DAC1_EXTI9, DFSDM1_DATIN3, FMC_D14, FMC_DA14, GPIO, SAI3_SD_B, USART3_RX
//------------------------------------------------------------------------------

// PD9: digital input
// PD9: digital output
// PD9: analog
// PD9: EXTI
// PD9: EVENTOUT
// PD9_DFSDM1_DATIN3 // AF3
// PD9_SAI3_SD_B // AF6
// PD9_USART3_RX // AF7
// PD9_FMC_D14 // AF12
// PD9_FMC_DA14 // AF12

//------------------------------------------------------------------------------
// PD10
// Possible signals: DFSDM1_CKOUT, FMC_D15, FMC_DA15, GPIO, LTDC_B3, SAI3_FS_B, USART3_CK
//------------------------------------------------------------------------------

// PD10: digital input
// PD10: digital output
// PD10: analog
// PD10: EXTI
// PD10: EVENTOUT
// PD10_DFSDM1_CKOUT // AF3
// PD10_SAI3_FS_B // AF6
// PD10_USART3_CK // AF7
// PD10_FMC_D15 // AF12
// PD10_FMC_DA15 // AF12
// PD10_LTDC_B3 // AF14

//------------------------------------------------------------------------------
// PD11
// Possible signals: ADC1_EXTI11, ADC2_EXTI11, ADC3_EXTI11, FMC_A16, FMC_CLE, GPIO, I2C4_SMBA, LPTIM2_IN2, QUADSPI_BK1_IO0, SAI2_SD_A, USART3_CTS, USART3_NSS
//------------------------------------------------------------------------------

// PD11: digital input
// PD11: digital output
// PD11: analog
// PD11: EXTI
// PD11: EVENTOUT
// PD11_LPTIM2_IN2 // AF3
// PD11_I2C4_SMBA // AF4
// PD11_USART3_CTS // AF7
// PD11_USART3_NSS // AF7
// PD11_QUADSPI_BK1_IO0 // AF9
// PD11_SAI2_SD_A // AF10
// PD11_FMC_A16 // AF12

//------------------------------------------------------------------------------
// PD12
// Possible signals: FMC_A17, FMC_ALE, GPIO, I2C4_SCL, LPTIM1_IN1, LPTIM2_IN1, QUADSPI_BK1_IO1, SAI2_FS_A, TIM4_CH1, USART3_DE, USART3_RTS
//------------------------------------------------------------------------------

// PD12: digital input
// PD12: digital output
// PD12: analog
// PD12: EXTI
// PD12: EVENTOUT
// PD12_LPTIM1_IN1 // AF1
// PD12_TIM4_CH1 // AF2
// PD12_LPTIM2_IN1 // AF3
// PD12_I2C4_SCL // AF4
// PD12_USART3_DE // AF7
// PD12_USART3_RTS // AF7
// PD12_QUADSPI_BK1_IO1 // AF9
// PD12_SAI2_FS_A // AF10
// PD12_FMC_A17 // AF12

//------------------------------------------------------------------------------
// PD13
// Possible signals: FMC_A18, GPIO, I2C4_SDA, LPTIM1_OUT, QUADSPI_BK1_IO3, SAI2_SCK_A, TIM4_CH2
//------------------------------------------------------------------------------

// PD13: digital input
// PD13: digital output
// PD13: analog
// PD13: EXTI
// PD13: EVENTOUT
// PD13_LPTIM1_OUT // AF1
// PD13_TIM4_CH2 // AF2
// PD13_I2C4_SDA // AF4
// PD13_QUADSPI_BK1_IO3 // AF9
// PD13_SAI2_SCK_A // AF10
// PD13_FMC_A18 // AF12

//------------------------------------------------------------------------------
// PD14
// Possible signals: FMC_D0, FMC_DA0, GPIO, SAI3_MCLK_B, TIM4_CH3, UART8_CTS
//------------------------------------------------------------------------------

// PD14: digital input
// PD14: digital output
// PD14: analog
// PD14: EXTI
// PD14: EVENTOUT
// PD14_TIM4_CH3 // AF2
// PD14_SAI3_MCLK_B // AF6
// PD14_UART8_CTS // AF8
// PD14_FMC_D0 // AF12
// PD14_FMC_DA0 // AF12

//------------------------------------------------------------------------------
// PD15
// Possible signals: ADC1_EXTI15, ADC2_EXTI15, ADC3_EXTI15, FMC_D1, FMC_DA1, GPIO, SAI3_MCLK_A, TIM4_CH4, UART8_DE, UART8_RTS
//------------------------------------------------------------------------------

// PD15: digital input
// PD15: digital output
// PD15: analog
// PD15: EXTI
// PD15: EVENTOUT
// PD15_TIM4_CH4 // AF2
// PD15_SAI3_MCLK_A // AF6
// PD15_UART8_DE // AF8
// PD15_UART8_RTS // AF8
// PD15_FMC_D1 // AF12
// PD15_FMC_DA1 // AF12

//------------------------------------------------------------------------------
// PE0
// Possible signals: DCMI_D2, FMC_NBL0, GPIO, HRTIM_SCIN, LPTIM1_ETR, LPTIM2_ETR, SAI2_MCLK_A, TIM4_ETR, UART8_RX
//------------------------------------------------------------------------------

// PE0: digital input
// PE0: digital output
// PE0: analog
// PE0: EXTI
// PE0: EVENTOUT
// PE0_LPTIM1_ETR // AF1
// PE0_TIM4_ETR // AF2
// PE0_HRTIM_SCIN // AF3
// PE0_LPTIM2_ETR // AF4
// PE0_UART8_RX // AF8
// PE0_SAI2_MCLK_A // AF10
// PE0_FMC_NBL0 // AF12
// PE0_DCMI_D2 // AF13

//------------------------------------------------------------------------------
// PE1
// Possible signals: DCMI_D3, FMC_NBL1, GPIO, HRTIM_SCOUT, LPTIM1_IN2, UART8_TX
//------------------------------------------------------------------------------

// PE1: digital input
// PE1: digital output
// PE1: analog
// PE1: EXTI
// PE1: EVENTOUT
// PE1_LPTIM1_IN2 // AF1
// PE1_HRTIM_SCOUT // AF3
// PE1_UART8_TX // AF8
// PE1_FMC_NBL1 // AF12
// PE1_DCMI_D3 // AF13

//------------------------------------------------------------------------------
// PE2
// Possible signals: DEBUG_TRACECLK, ETH_TXD3, FMC_A23, GPIO, QUADSPI_BK1_IO2, SAI1_CK1, SAI1_MCLK_A, SAI4_CK1, SAI4_MCLK_A, SPI4_SCK
//------------------------------------------------------------------------------

// PE2: digital input
// PE2: digital output
// PE2: analog
// PE2: EXTI
// PE2: EVENTOUT
// PE2_DEBUG_TRACECLK // AF0
// PE2_SAI1_CK1 // AF2
// PE2_SPI4_SCK // AF5
// PE2_SAI1_MCLK_A // AF6
// PE2_SAI4_MCLK_A // AF8
// PE2_QUADSPI_BK1_IO2 // AF9
// PE2_SAI4_CK1 // AF10
// PE2_ETH_TXD3 // AF11
// PE2_FMC_A23 // AF12

//------------------------------------------------------------------------------
// PE3
// Possible signals: DEBUG_TRACED0, FMC_A19, GPIO, SAI1_SD_B, SAI4_SD_B, TIM15_BKIN
//------------------------------------------------------------------------------

// PE3: digital input
// PE3: digital output
// PE3: analog
// PE3: EXTI
// PE3: EVENTOUT
// PE3_DEBUG_TRACED0 // AF0
// PE3_TIM15_BKIN // AF4
// PE3_SAI1_SD_B // AF6
// PE3_SAI4_SD_B // AF8
// PE3_FMC_A19 // AF12

//------------------------------------------------------------------------------
// PE4
// Possible signals: DCMI_D4, DEBUG_TRACED1, DFSDM1_DATIN3, FMC_A20, GPIO, LTDC_B0, SAI1_D2, SAI1_FS_A, SAI4_D2, SAI4_FS_A, SPI4_NSS, TIM15_CH1N
//------------------------------------------------------------------------------

// PE4: digital input
// PE4: digital output
// PE4: analog
// PE4: EXTI
// PE4: EVENTOUT
// PE4_DEBUG_TRACED1 // AF0
// PE4_SAI1_D2 // AF2
// PE4_DFSDM1_DATIN3 // AF3
// PE4_TIM15_CH1N // AF4
// PE4_SPI4_NSS // AF5
// PE4_SAI1_FS_A // AF6
// PE4_SAI4_FS_A // AF8
// PE4_SAI4_D2 // AF10
// PE4_FMC_A20 // AF12
// PE4_DCMI_D4 // AF13
// PE4_LTDC_B0 // AF14

//------------------------------------------------------------------------------
// PE5
// Possible signals: DCMI_D6, DEBUG_TRACED2, DFSDM1_CKIN3, FMC_A21, GPIO, LTDC_G0, SAI1_CK2, SAI1_SCK_A, SAI4_CK2, SAI4_SCK_A, SPI4_MISO, TIM15_CH1
//------------------------------------------------------------------------------

// PE5: digital input
// PE5: digital output
// PE5: analog
// PE5: EXTI
// PE5: EVENTOUT
// PE5_DEBUG_TRACED2 // AF0
// PE5_SAI1_CK2 // AF2
// PE5_DFSDM1_CKIN3 // AF3
// PE5_TIM15_CH1 // AF4
// PE5_SPI4_MISO // AF5
// PE5_SAI1_SCK_A // AF6
// PE5_SAI4_SCK_A // AF8
// PE5_SAI4_CK2 // AF10
// PE5_FMC_A21 // AF12
// PE5_DCMI_D6 // AF13
// PE5_LTDC_G0 // AF14

//------------------------------------------------------------------------------
// PE6
// Possible signals: DCMI_D7, DEBUG_TRACED3, FMC_A22, GPIO, LTDC_G1, SAI1_D1, SAI1_SD_A, SAI2_MCLK_B, SAI4_D1, SAI4_SD_A, SPI4_MOSI, TIM15_CH2, TIM1_BKIN2, TIM1_BKIN2_COMP1, TIM1_BKIN2_COMP2
//------------------------------------------------------------------------------

// PE6: digital input
// PE6: digital output
// PE6: analog
// PE6: EXTI
// PE6: EVENTOUT
// PE6_DEBUG_TRACED3 // AF0
// PE6_TIM1_BKIN2 // AF1
// PE6_SAI1_D1 // AF2
// PE6_TIM15_CH2 // AF4
// PE6_SPI4_MOSI // AF5
// PE6_SAI1_SD_A // AF6
// PE6_SAI4_SD_A // AF8
// PE6_SAI4_D1 // AF9
// PE6_SAI2_MCLK_B // AF10
// PE6_TIM1_BKIN2_COMP1 // AF11
// PE6_TIM1_BKIN2_COMP2 // AF11
// PE6_FMC_A22 // AF12
// PE6_DCMI_D7 // AF13
// PE6_LTDC_G1 // AF14

//------------------------------------------------------------------------------
// PE7
// Possible signals: COMP2_INM, DFSDM1_DATIN2, FMC_D4, FMC_DA4, GPIO, OPAMP2_VOUT, QUADSPI_BK2_IO0, TIM1_ETR, UART7_RX
//------------------------------------------------------------------------------

// PE7: digital input
// PE7: digital output
// PE7: analog
// PE7: EXTI
// PE7: EVENTOUT
// PE7_TIM1_ETR // AF1
// PE7_DFSDM1_DATIN2 // AF3
// PE7_UART7_RX // AF7
// PE7_QUADSPI_BK2_IO0 // AF10
// PE7_FMC_D4 // AF12
// PE7_FMC_DA4 // AF12

//------------------------------------------------------------------------------
// PE8
// Possible signals: COMP2_OUT, DFSDM1_CKIN2, FMC_D5, FMC_DA5, GPIO, OPAMP2_VINM, OPAMP2_VINM0, QUADSPI_BK2_IO1, TIM1_CH1N, UART7_TX
//------------------------------------------------------------------------------

// PE8: digital input
// PE8: digital output
// PE8: analog
// PE8: EXTI
// PE8: EVENTOUT
// PE8_TIM1_CH1N // AF1
// PE8_DFSDM1_CKIN2 // AF3
// PE8_UART7_TX // AF7
// PE8_QUADSPI_BK2_IO1 // AF10
// PE8_FMC_D5 // AF12
// PE8_FMC_DA5 // AF12
// PE8_COMP2_OUT // AF13

//------------------------------------------------------------------------------
// PE9
// Possible signals: COMP2_INP, DAC1_EXTI9, DFSDM1_CKOUT, FMC_D6, FMC_DA6, GPIO, OPAMP2_VINP, QUADSPI_BK2_IO2, TIM1_CH1, UART7_DE, UART7_RTS
//------------------------------------------------------------------------------

// PE9: digital input
// PE9: digital output
// PE9: analog
// PE9: EXTI
// PE9: EVENTOUT
// PE9_TIM1_CH1 // AF1
// PE9_DFSDM1_CKOUT // AF3
// PE9_UART7_DE // AF7
// PE9_UART7_RTS // AF7
// PE9_QUADSPI_BK2_IO2 // AF10
// PE9_FMC_D6 // AF12
// PE9_FMC_DA6 // AF12

//------------------------------------------------------------------------------
// PE10
// Possible signals: COMP2_INM, DFSDM1_DATIN4, FMC_D7, FMC_DA7, GPIO, QUADSPI_BK2_IO3, TIM1_CH2N, UART7_CTS
//------------------------------------------------------------------------------

// PE10: digital input
// PE10: digital output
// PE10: analog
// PE10: EXTI
// PE10: EVENTOUT
// PE10_TIM1_CH2N // AF1
// PE10_DFSDM1_DATIN4 // AF3
// PE10_UART7_CTS // AF7
// PE10_QUADSPI_BK2_IO3 // AF10
// PE10_FMC_D7 // AF12
// PE10_FMC_DA7 // AF12

//------------------------------------------------------------------------------
// PE11
// Possible signals: ADC1_EXTI11, ADC2_EXTI11, ADC3_EXTI11, COMP2_INP, DFSDM1_CKIN4, FMC_D8, FMC_DA8, GPIO, LTDC_G3, SAI2_SD_B, SPI4_NSS, TIM1_CH2
//------------------------------------------------------------------------------

// PE11: digital input
// PE11: digital output
// PE11: analog
// PE11: EXTI
// PE11: EVENTOUT
// PE11_TIM1_CH2 // AF1
// PE11_DFSDM1_CKIN4 // AF3
// PE11_SPI4_NSS // AF5
// PE11_SAI2_SD_B // AF10
// PE11_FMC_D8 // AF12
// PE11_FMC_DA8 // AF12
// PE11_LTDC_G3 // AF14

//------------------------------------------------------------------------------
// PE12
// Possible signals: COMP1_OUT, DFSDM1_DATIN5, FMC_D9, FMC_DA9, GPIO, LTDC_B4, SAI2_SCK_B, SPI4_SCK, TIM1_CH3N
//------------------------------------------------------------------------------

// PE12: digital input
// PE12: digital output
// PE12: analog
// PE12: EXTI
// PE12: EVENTOUT
// PE12_TIM1_CH3N // AF1
// PE12_DFSDM1_DATIN5 // AF3
// PE12_SPI4_SCK // AF5
// PE12_SAI2_SCK_B // AF10
// PE12_FMC_D9 // AF12
// PE12_FMC_DA9 // AF12
// PE12_COMP1_OUT // AF13
// PE12_LTDC_B4 // AF14

//------------------------------------------------------------------------------
// PE13
// Possible signals: COMP2_OUT, DFSDM1_CKIN5, FMC_D10, FMC_DA10, GPIO, LTDC_DE, SAI2_FS_B, SPI4_MISO, TIM1_CH3
//------------------------------------------------------------------------------

// PE13: digital input
// PE13: digital output
// PE13: analog
// PE13: EXTI
// PE13: EVENTOUT
// PE13_TIM1_CH3 // AF1
// PE13_DFSDM1_CKIN5 // AF3
// PE13_SPI4_MISO // AF5
// PE13_SAI2_FS_B // AF10
// PE13_FMC_D10 // AF12
// PE13_FMC_DA10 // AF12
// PE13_COMP2_OUT // AF13
// PE13_LTDC_DE // AF14

//------------------------------------------------------------------------------
// PE14
// Possible signals: FMC_D11, FMC_DA11, GPIO, LTDC_CLK, SAI2_MCLK_B, SPI4_MOSI, TIM1_CH4
//------------------------------------------------------------------------------

// PE14: digital input
// PE14: digital output
// PE14: analog
// PE14: EXTI
// PE14: EVENTOUT
// PE14_TIM1_CH4 // AF1
// PE14_SPI4_MOSI // AF5
// PE14_SAI2_MCLK_B // AF10
// PE14_FMC_D11 // AF12
// PE14_FMC_DA11 // AF12
// PE14_LTDC_CLK // AF14

//------------------------------------------------------------------------------
// PE15
// Possible signals: ADC1_EXTI15, ADC2_EXTI15, ADC3_EXTI15, FMC_D12, FMC_DA12, GPIO, LTDC_R7, TIM1_BKIN, TIM1_BKIN_COMP1, TIM1_BKIN_COMP2
//------------------------------------------------------------------------------

// PE15: digital input
// PE15: digital output
// PE15: analog
// PE15: EXTI
// PE15: EVENTOUT
// PE15_TIM1_BKIN // AF1
// PE15_FMC_D12 // AF12
// PE15_FMC_DA12 // AF12
// PE15_COMP_TIM1_BKIN // AF13
// PE15_TIM1_BKIN_COMP1 // AF13
// PE15_TIM1_BKIN_COMP2 // AF13
// PE15_LTDC_R7 // AF14

//------------------------------------------------------------------------------
// PF0
// Possible signals: FMC_A0, GPIO, I2C2_SDA
//------------------------------------------------------------------------------

// PF0: digital input
// PF0: digital output
// PF0: analog
// PF0: EXTI
// PF0: EVENTOUT
// PF0_I2C2_SDA // AF4
// PF0_FMC_A0 // AF12

//------------------------------------------------------------------------------
// PF1
// Possible signals: FMC_A1, GPIO, I2C2_SCL
//------------------------------------------------------------------------------

// PF1: digital input
// PF1: digital output
// PF1: analog
// PF1: EXTI
// PF1: EVENTOUT
// PF1_I2C2_SCL // AF4
// PF1_FMC_A1 // AF12

//------------------------------------------------------------------------------
// PF2
// Possible signals: FMC_A2, GPIO, I2C2_SMBA
//------------------------------------------------------------------------------

// PF2: digital input
// PF2: digital output
// PF2: analog
// PF2: EXTI
// PF2: EVENTOUT
// PF2_I2C2_SMBA // AF4
// PF2_FMC_A2 // AF12

//------------------------------------------------------------------------------
// PF3
// Possible signals: ADC3_INP5, FMC_A3, GPIO
//------------------------------------------------------------------------------

// PF3: digital input
// PF3: digital output
// PF3: analog
// PF3: EXTI
// PF3: EVENTOUT
// PF3_FMC_A3 // AF12

//------------------------------------------------------------------------------
// PF4
// Possible signals: ADC3_INN5, ADC3_INP9, FMC_A4, GPIO
//------------------------------------------------------------------------------

// PF4: digital input
// PF4: digital output
// PF4: analog
// PF4: EXTI
// PF4: EVENTOUT
// PF4_FMC_A4 // AF12

//------------------------------------------------------------------------------
// PF5
// Possible signals: ADC3_INP4, FMC_A5, GPIO
//------------------------------------------------------------------------------

// PF5: digital input
// PF5: digital output
// PF5: analog
// PF5: EXTI
// PF5: EVENTOUT
// PF5_FMC_A5 // AF12

//------------------------------------------------------------------------------
// PF6
// Possible signals: ADC3_INN4, ADC3_INP8, GPIO, QUADSPI_BK1_IO3, SAI1_SD_B, SAI4_SD_B, SPI5_NSS, TIM16_CH1, UART7_RX
//------------------------------------------------------------------------------

// PF6: digital input
// PF6: digital output
// PF6: analog
// PF6: EXTI
// PF6: EVENTOUT
// PF6_TIM16_CH1 // AF1
// PF6_SPI5_NSS // AF5
// PF6_SAI1_SD_B // AF6
// PF6_UART7_RX // AF7
// PF6_SAI4_SD_B // AF8
// PF6_QUADSPI_BK1_IO3 // AF9

//------------------------------------------------------------------------------
// PF7
// Possible signals: ADC3_INP3, GPIO, QUADSPI_BK1_IO2, SAI1_MCLK_B, SAI4_MCLK_B, SPI5_SCK, TIM17_CH1, UART7_TX
//------------------------------------------------------------------------------

// PF7: digital input
// PF7: digital output
// PF7: analog
// PF7: EXTI
// PF7: EVENTOUT
// PF7_TIM17_CH1 // AF1
// PF7_SPI5_SCK // AF5
// PF7_SAI1_MCLK_B // AF6
// PF7_UART7_TX // AF7
// PF7_SAI4_MCLK_B // AF8
// PF7_QUADSPI_BK1_IO2 // AF9

//------------------------------------------------------------------------------
// PF8
// Possible signals: ADC3_INN3, ADC3_INP7, GPIO, QUADSPI_BK1_IO0, SAI1_SCK_B, SAI4_SCK_B, SPI5_MISO, TIM13_CH1, TIM16_CH1N, UART7_DE, UART7_RTS
//------------------------------------------------------------------------------

// PF8: digital input
// PF8: digital output
// PF8: analog
// PF8: EXTI
// PF8: EVENTOUT
// PF8_TIM16_CH1N // AF1
// PF8_SPI5_MISO // AF5
// PF8_SAI1_SCK_B // AF6
// PF8_UART7_DE // AF7
// PF8_UART7_RTS // AF7
// PF8_SAI4_SCK_B // AF8
// PF8_TIM13_CH1 // AF9
// PF8_QUADSPI_BK1_IO0 // AF10

//------------------------------------------------------------------------------
// PF9
// Possible signals: ADC3_INP2, DAC1_EXTI9, GPIO, QUADSPI_BK1_IO1, SAI1_FS_B, SAI4_FS_B, SPI5_MOSI, TIM14_CH1, TIM17_CH1N, UART7_CTS
//------------------------------------------------------------------------------

// PF9: digital input
// PF9: digital output
// PF9: analog
// PF9: EXTI
// PF9: EVENTOUT
// PF9_TIM17_CH1N // AF1
// PF9_SPI5_MOSI // AF5
// PF9_SAI1_FS_B // AF6
// PF9_UART7_CTS // AF7
// PF9_SAI4_FS_B // AF8
// PF9_TIM14_CH1 // AF9
// PF9_QUADSPI_BK1_IO1 // AF10

//------------------------------------------------------------------------------
// PF10
// Possible signals: ADC3_INN2, ADC3_INP6, DCMI_D11, GPIO, LTDC_DE, QUADSPI_CLK, SAI1_D3, SAI4_D3, TIM16_BKIN
//------------------------------------------------------------------------------

// PF10: digital input
// PF10: digital output
// PF10: analog
// PF10: EXTI
// PF10: EVENTOUT
// PF10_TIM16_BKIN // AF1
// PF10_SAI1_D3 // AF2
// PF10_QUADSPI_CLK // AF9
// PF10_SAI4_D3 // AF10
// PF10_DCMI_D11 // AF13
// PF10_LTDC_DE // AF14

//------------------------------------------------------------------------------
// PF11
// Possible signals: ADC1_EXTI11, ADC1_INP2, ADC2_EXTI11, ADC3_EXTI11, DCMI_D12, FMC_SDNRAS, GPIO, SAI2_SD_B, SPI5_MOSI
//------------------------------------------------------------------------------

// PF11: digital input
// PF11: digital output
// PF11: analog
// PF11: EXTI
// PF11: EVENTOUT
// PF11_SPI5_MOSI // AF5
// PF11_SAI2_SD_B // AF10
// PF11_FMC_SDNRAS // AF12
// PF11_DCMI_D12 // AF13

//------------------------------------------------------------------------------
// PF12
// Possible signals: ADC1_INN2, ADC1_INP6, FMC_A6, GPIO
//------------------------------------------------------------------------------

// PF12: digital input
// PF12: digital output
// PF12: analog
// PF12: EXTI
// PF12: EVENTOUT
// PF12_FMC_A6 // AF12

//------------------------------------------------------------------------------
// PF13
// Possible signals: ADC2_INP2, DFSDM1_DATIN6, FMC_A7, GPIO, I2C4_SMBA
//------------------------------------------------------------------------------

// PF13: digital input
// PF13: digital output
// PF13: analog
// PF13: EXTI
// PF13: EVENTOUT
// PF13_DFSDM1_DATIN6 // AF3
// PF13_I2C4_SMBA // AF4
// PF13_FMC_A7 // AF12

//------------------------------------------------------------------------------
// PF14
// Possible signals: ADC2_INN2, ADC2_INP6, DFSDM1_CKIN6, FMC_A8, GPIO, I2C4_SCL
//------------------------------------------------------------------------------

// PF14: digital input
// PF14: digital output
// PF14: analog
// PF14: EXTI
// PF14: EVENTOUT
// PF14_DFSDM1_CKIN6 // AF3
// PF14_I2C4_SCL // AF4
// PF14_FMC_A8 // AF12

//------------------------------------------------------------------------------
// PF15
// Possible signals: ADC1_EXTI15, ADC2_EXTI15, ADC3_EXTI15, FMC_A9, GPIO, I2C4_SDA
//------------------------------------------------------------------------------

// PF15: digital input
// PF15: digital output
// PF15: analog
// PF15: EXTI
// PF15: EVENTOUT
// PF15_I2C4_SDA // AF4
// PF15_FMC_A9 // AF12

//------------------------------------------------------------------------------
// PG0
// Possible signals: FMC_A10, GPIO
//------------------------------------------------------------------------------

// PG0: digital input
// PG0: digital output
// PG0: analog
// PG0: EXTI
// PG0: EVENTOUT
// PG0_FMC_A10 // AF12

//------------------------------------------------------------------------------
// PG1
// Possible signals: FMC_A11, GPIO, OPAMP2_VINM, OPAMP2_VINM1
//------------------------------------------------------------------------------

// PG1: digital input
// PG1: digital output
// PG1: analog
// PG1: EXTI
// PG1: EVENTOUT
// PG1_FMC_A11 // AF12

//------------------------------------------------------------------------------
// PG2
// Possible signals: FMC_A12, GPIO, TIM8_BKIN, TIM8_BKIN_COMP1, TIM8_BKIN_COMP2
//------------------------------------------------------------------------------

// PG2: digital input
// PG2: digital output
// PG2: analog
// PG2: EXTI
// PG2: EVENTOUT
// PG2_TIM8_BKIN // AF3
// PG2_TIM8_BKIN_COMP1 // AF11
// PG2_TIM8_BKIN_COMP2 // AF11
// PG2_FMC_A12 // AF12

//------------------------------------------------------------------------------
// PG3
// Possible signals: FMC_A13, GPIO, TIM8_BKIN2, TIM8_BKIN2_COMP1, TIM8_BKIN2_COMP2
//------------------------------------------------------------------------------

// PG3: digital input
// PG3: digital output
// PG3: analog
// PG3: EXTI
// PG3: EVENTOUT
// PG3_TIM8_BKIN2 // AF3
// PG3_TIM8_BKIN2_COMP1 // AF11
// PG3_TIM8_BKIN2_COMP2 // AF11
// PG3_FMC_A13 // AF12

//------------------------------------------------------------------------------
// PG4
// Possible signals: FMC_A14, FMC_BA0, GPIO, TIM1_BKIN2, TIM1_BKIN2_COMP1, TIM1_BKIN2_COMP2
//------------------------------------------------------------------------------

// PG4: digital input
// PG4: digital output
// PG4: analog
// PG4: EXTI
// PG4: EVENTOUT
// PG4_TIM1_BKIN2 // AF1
// PG4_TIM1_BKIN2_COMP1 // AF11
// PG4_TIM1_BKIN2_COMP2 // AF11
// PG4_FMC_A14 // AF12
// PG4_FMC_BA0 // AF12

//------------------------------------------------------------------------------
// PG5
// Possible signals: FMC_A15, FMC_BA1, GPIO, TIM1_ETR
//------------------------------------------------------------------------------

// PG5: digital input
// PG5: digital output
// PG5: analog
// PG5: EXTI
// PG5: EVENTOUT
// PG5_TIM1_ETR // AF1
// PG5_FMC_A15 // AF12
// PG5_FMC_BA1 // AF12

//------------------------------------------------------------------------------
// PG6
// Possible signals: DCMI_D12, FMC_NE3, GPIO, HRTIM_CHE1, LTDC_R7, QUADSPI_BK1_NCS, TIM17_BKIN
//------------------------------------------------------------------------------

// PG6: digital input
// PG6: digital output
// PG6: analog
// PG6: EXTI
// PG6: EVENTOUT
// PG6_TIM17_BKIN // AF1
// PG6_HRTIM_CHE1 // AF2
// PG6_QUADSPI_BK1_NCS // AF10
// PG6_FMC_NE3 // AF12
// PG6_DCMI_D12 // AF13
// PG6_LTDC_R7 // AF14

//------------------------------------------------------------------------------
// PG7
// Possible signals: DCMI_D13, FMC_INT, GPIO, HRTIM_CHE2, LTDC_CLK, SAI1_MCLK_A, USART6_CK
//------------------------------------------------------------------------------

// PG7: digital input
// PG7: digital output
// PG7: analog
// PG7: EXTI
// PG7: EVENTOUT
// PG7_HRTIM_CHE2 // AF2
// PG7_SAI1_MCLK_A // AF6
// PG7_USART6_CK // AF7
// PG7_FMC_INT // AF12
// PG7_DCMI_D13 // AF13
// PG7_LTDC_CLK // AF14

//------------------------------------------------------------------------------
// PG8
// Possible signals: ETH_PPS_OUT, FMC_SDCLK, GPIO, LTDC_G7, SPDIFRX1_IN2, SPI6_NSS, TIM8_ETR, USART6_DE, USART6_RTS
//------------------------------------------------------------------------------

// PG8: digital input
// PG8: digital output
// PG8: analog
// PG8: EXTI
// PG8: EVENTOUT
// PG8_TIM8_ETR // AF3
// PG8_SPI6_NSS // AF5
// PG8_USART6_DE // AF7
// PG8_USART6_RTS // AF7
// PG8_SPDIFRX1_IN2 // AF8
// PG8_ETH_PPS_OUT // AF11
// PG8_FMC_SDCLK // AF12
// PG8_LTDC_G7 // AF14

//------------------------------------------------------------------------------
// PG9
// Possible signals: DAC1_EXTI9, DCMI_VSYNC, FMC_NCE, FMC_NE2, GPIO, I2S1_SDI, QUADSPI_BK2_IO2, SAI2_FS_B, SPDIFRX1_IN3, SPI1_MISO, USART6_RX
//------------------------------------------------------------------------------

// PG9: digital input
// PG9: digital output
// PG9: analog
// PG9: EXTI
// PG9: EVENTOUT
// PG9_I2S1_SDI // AF5
// PG9_SPI1_MISO // AF5
// PG9_USART6_RX // AF7
// PG9_SPDIFRX1_IN3 // AF8
// PG9_QUADSPI_BK2_IO2 // AF9
// PG9_SAI2_FS_B // AF10
// PG9_FMC_NCE // AF12
// PG9_FMC_NE2 // AF12
// PG9_DCMI_VSYNC // AF13

//------------------------------------------------------------------------------
// PG10
// Possible signals: DCMI_D2, FMC_NE3, GPIO, HRTIM_FLT5, I2S1_WS, LTDC_B2, LTDC_G3, SAI2_SD_B, SPI1_NSS
//------------------------------------------------------------------------------

// PG10: digital input
// PG10: digital output
// PG10: analog
// PG10: EXTI
// PG10: EVENTOUT
// PG10_HRTIM_FLT5 // AF2
// PG10_I2S1_WS // AF5
// PG10_SPI1_NSS // AF5
// PG10_LTDC_G3 // AF9
// PG10_SAI2_SD_B // AF10
// PG10_FMC_NE3 // AF12
// PG10_DCMI_D2 // AF13
// PG10_LTDC_B2 // AF14

//------------------------------------------------------------------------------
// PG11
// Possible signals: ADC1_EXTI11, ADC2_EXTI11, ADC3_EXTI11, DCMI_D3, ETH_TX_EN, GPIO, HRTIM_EEV4, I2S1_CK, LPTIM1_IN2, LTDC_B3, SDMMC2_D2, SPDIFRX1_IN0, SPI1_SCK
//------------------------------------------------------------------------------

// PG11: digital input
// PG11: digital output
// PG11: analog
// PG11: EXTI
// PG11: EVENTOUT
// PG11_LPTIM1_IN2 // AF1
// PG11_HRTIM_EEV4 // AF2
// PG11_I2S1_CK // AF5
// PG11_SPI1_SCK // AF5
// PG11_SPDIFRX1_IN0 // AF8
// PG11_SDMMC2_D2 // AF10
// PG11_ETH_TX_EN // AF11
// PG11_DCMI_D3 // AF13
// PG11_LTDC_B3 // AF14

//------------------------------------------------------------------------------
// PG12
// Possible signals: ETH_TXD1, FMC_NE4, GPIO, HRTIM_EEV5, LPTIM1_IN1, LTDC_B1, LTDC_B4, SPDIFRX1_IN1, SPI6_MISO, USART6_DE, USART6_RTS
//------------------------------------------------------------------------------

// PG12: digital input
// PG12: digital output
// PG12: analog
// PG12: EXTI
// PG12: EVENTOUT
// PG12_LPTIM1_IN1 // AF1
// PG12_HRTIM_EEV5 // AF2
// PG12_SPI6_MISO // AF5
// PG12_USART6_DE // AF7
// PG12_USART6_RTS // AF7
// PG12_SPDIFRX1_IN1 // AF8
// PG12_LTDC_B4 // AF9
// PG12_ETH_TXD1 // AF11
// PG12_FMC_NE4 // AF12
// PG12_LTDC_B1 // AF14

//------------------------------------------------------------------------------
// PG13
// Possible signals: DEBUG_TRACED0, ETH_TXD0, FMC_A24, GPIO, HRTIM_EEV10, LPTIM1_OUT, LTDC_R0, SPI6_SCK, USART6_CTS, USART6_NSS
//------------------------------------------------------------------------------

// PG13: digital input
// PG13: digital output
// PG13: analog
// PG13: EXTI
// PG13: EVENTOUT
// PG13_DEBUG_TRACED0 // AF0
// PG13_LPTIM1_OUT // AF1
// PG13_HRTIM_EEV10 // AF2
// PG13_SPI6_SCK // AF5
// PG13_USART6_CTS // AF7
// PG13_USART6_NSS // AF7
// PG13_ETH_TXD0 // AF11
// PG13_FMC_A24 // AF12
// PG13_LTDC_R0 // AF14

//------------------------------------------------------------------------------
// PG14
// Possible signals: DEBUG_TRACED1, ETH_TXD1, FMC_A25, GPIO, LPTIM1_ETR, LTDC_B0, QUADSPI_BK2_IO3, SPI6_MOSI, USART6_TX
//------------------------------------------------------------------------------

// PG14: digital input
// PG14: digital output
// PG14: analog
// PG14: EXTI
// PG14: EVENTOUT
// PG14_DEBUG_TRACED1 // AF0
// PG14_LPTIM1_ETR // AF1
// PG14_SPI6_MOSI // AF5
// PG14_USART6_TX // AF7
// PG14_QUADSPI_BK2_IO3 // AF9
// PG14_ETH_TXD1 // AF11
// PG14_FMC_A25 // AF12
// PG14_LTDC_B0 // AF14

//------------------------------------------------------------------------------
// PG15
// Possible signals: ADC1_EXTI15, ADC2_EXTI15, ADC3_EXTI15, DCMI_D13, FMC_SDNCAS, GPIO, USART6_CTS, USART6_NSS
//------------------------------------------------------------------------------

// PG15: digital input
// PG15: digital output
// PG15: analog
// PG15: EXTI
// PG15: EVENTOUT
// PG15_USART6_CTS // AF7
// PG15_USART6_NSS // AF7
// PG15_FMC_SDNCAS // AF12
// PG15_DCMI_D13 // AF13

//------------------------------------------------------------------------------
// PH0
// Possible signals: GPIO, RCC_OSC_IN
//------------------------------------------------------------------------------

// PH0: digital input
// PH0: digital output
// PH0: analog
// PH0: EXTI
// PH0: EVENTOUT

//------------------------------------------------------------------------------
// PH1
// Possible signals: GPIO, RCC_OSC_OUT
//------------------------------------------------------------------------------

// PH1: digital input
// PH1: digital output
// PH1: analog
// PH1: EXTI
// PH1: EVENTOUT

//------------------------------------------------------------------------------
// GPIOA BASE ADDRESS
//------------------------------------------------------------------------------

static const uint32_t GPIO_BASE_ADDRESS = uint32_t (&REG_GPIOA_MODER) ;

//------------------------------------------------------------------------------
// DIGITAL INPUT MODE
//------------------------------------------------------------------------------
// DigitalInputPin encoding:
// Bits 15-11: unused (zero)
// Bits 10-9: 0 -> no pull, 1 -> pullup, 2 -> pulldown
// Bit 8: 0 -> no read complementation, 1 -> read value is complemented
// Bits 7-0: pin index (PA0 -> 0, PA1 -> 1, ..., PA15 -> 15, PB0 -> 16, ...)
//------------------------------------------------------------------------------

void setDigitalInputMode (const DigitalInputPin inPin) {
  const uint32_t pinIndex = uint32_t (inPin) & 0xFF ;
  if (pinIndex < uint32_t (DigitalInputPin::NONE)) {
    const uint32_t gpioIndex = pinIndex / 16 ; // 0 -> PORTA, 1 -> PORTB, ...
    const uint32_t portIndex = pinIndex % 16 ; // portIndex: 0, ..., 15
  //--- gpioAddress:
    const uint32_t gpioAddress = GPIO_BASE_ADDRESS + gpioIndex * 0x400 ;
  //--- MODER register has offset 0x0
  // Input: reset bit at (portIndex * 2 + 1), reset bit (portIndex * 2)
    volatile uint32_t & MODER = *((volatile uint32_t *) (gpioAddress + 0x00)) ;
    MODER &= ~ (uint32_t (3) << (portIndex * 2)) ;
  //--- PUPDR register has offset 0x0C
    const uint32_t pupd = (uint32_t (inPin) >> 9) & 3 ;
    volatile uint32_t & PUPDR = *((volatile uint32_t *) (gpioAddress + 0x0C)) ;
    uint32_t registerValue = PUPDR ;
    registerValue &= ~ (uint32_t (3) << (portIndex * 2)) ;
    registerValue |=    pupd << (portIndex * 2) ;
    PUPDR = registerValue ;
  }
}

//------------------------------------------------------------------------------

bool digitalRead (const DigitalInputPin inPin) {
  bool result = (uint32_t (inPin) & (1 << 8)) != 0 ;
  const uint32_t pinIndex = uint32_t (inPin) & 0xFF ;
  if (pinIndex < uint32_t (DigitalInputPin::NONE)) {
    const uint32_t gpioIndex = pinIndex / 16 ; // 0 -> PORTA, 1 -> PORTB, ...
    const uint32_t portIndex = pinIndex % 16 ; // portIndex: 0, ..., 15
  //--- gpioAddress
    const uint32_t gpioAddress = GPIO_BASE_ADDRESS + gpioIndex * 0x400 ;
  //--- IDR register has offset 0x10
    volatile uint32_t & IDR = *((volatile uint32_t *) (gpioAddress + 0x10)) ;
    result ^= (IDR & (uint32_t (1) << portIndex)) != 0 ;
  }
//---
  return result ;
}

//------------------------------------------------------------------------------
// DIGITAL OUTPUT MODE
//------------------------------------------------------------------------------
// DigitalOutputPin encoding:
// Bits 15-12: unused (zero)
// Bits 11-10: 3 -> low speed, 2 -> medium speed, 1 -> high speed, 0 -> very high speed
// Bit 9: 0 -> push-pull output, 1 -> open collector output
// Bit 8: 0 -> no complementation, 1 -> read / write value is complemented
// Bits 7-0: pin index (PA0 -> 0, PA1 -> 1, ..., PA15 -> 15, PB0 -> 16, ...)
//------------------------------------------------------------------------------

void setDigitalOutputMode (const DigitalOutputPin inPin) {
  const uint32_t pinIndex = uint32_t (inPin) & 0xFF ;
  if (pinIndex < uint32_t (DigitalOutputPin::NONE)) {
    const uint32_t gpioIndex = pinIndex / 16 ; // 0 -> PORTA, 1 -> PORTB, ...
    const uint32_t portIndex = pinIndex % 16 ; // portIndex: 0, ..., 15
  //--- gpioAddress:
    const uint32_t gpioAddress = GPIO_BASE_ADDRESS + gpioIndex * 0x400 ;
  //--- MODER register has offset 0x0
  // Output: reset bit (portIndex * 2 + 1), set bit (portIndex * 2)
    volatile uint32_t & MODER = *((volatile uint32_t *) (gpioAddress + 0x00)) ;
    uint32_t registerValue = MODER ;
    registerValue |= (uint32_t (1) << (portIndex * 2)) ;
    registerValue &= ~ (uint32_t (1) << (portIndex * 2 + 1)) ;
    MODER = registerValue ;
  //--- OPTYPER register has offset 0x04
    const bool openCollector = (uint32_t (inPin) & (1 << 9)) != 0 ;
    volatile uint32_t & OTYPER = *((volatile uint32_t *) (gpioAddress + 0x04)) ;
    registerValue = OTYPER ;
    if (openCollector) { // Open collector output
      registerValue |=   (uint32_t (1) << portIndex) ;
    }else{ // Push-pull output
      registerValue &= ~ (uint32_t (1) << portIndex) ;
    }
    OTYPER = registerValue ;
  //--- OSPEEDR register has offset 0x08
    volatile uint32_t & OSPEEDR = *((volatile uint32_t *) (gpioAddress + 0x08)) ;
    const uint32_t speed = 3 ; // Very high speed
    OSPEEDR |= speed << (portIndex * 2) ;
  //--- PUPDR register has offset 0x0C
    volatile uint32_t & PUPDR = *((volatile uint32_t *) (gpioAddress + 0x0C)) ;
    PUPDR &= ~ (uint32_t (3) << (portIndex * 2)) ;  // No pull
  }
}

//------------------------------------------------------------------------------

void digitalWrite (const DigitalOutputPin inPin,
                   const bool inValue) {
  const uint32_t pinIndex = uint32_t (inPin) & 0xFF ;
  if (pinIndex < uint32_t (DigitalOutputPin::NONE)) {
    const uint32_t gpioIndex = pinIndex / 16 ; // 0 -> PORTA, 1 -> PORTB, ...
    const uint32_t portIndex = pinIndex % 16 ; // portIndex: 0, ..., 15
  //--- gpioAddress
    const uint32_t gpioAddress = GPIO_BASE_ADDRESS + gpioIndex * 0x400 ;
  //--- BSRR register has offset 0x18
    volatile uint32_t & BSRR = *((volatile uint32_t *) (gpioAddress + 0x18)) ;
    const bool complement = (uint32_t (inPin) & (1 << 8)) != 0 ;
    if (inValue ^ complement) {
      BSRR = uint32_t (1) << portIndex ; // Set
    }else{
      BSRR = uint32_t (1) << (portIndex + 16) ; // Reset
    }
  }
}

//------------------------------------------------------------------------------

void digitalToggle_section (const DigitalOutputPin inPin) {
  const uint32_t pinIndex = uint32_t (inPin) & 0xFF ;
  if (pinIndex < uint32_t (DigitalOutputPin::NONE)) {
    const uint32_t gpioIndex = pinIndex / 16 ; // 0 -> PORTA, 1 -> PORTB, ...
    const uint32_t portIndex = pinIndex % 16 ; // portIndex: 0, ..., 15
  //--- gpioAddress
    const uint32_t gpioAddress = GPIO_BASE_ADDRESS + gpioIndex * 0x400 ;
  //--- IDR register has offset 0x10
    volatile uint32_t & IDR = *((volatile uint32_t *) (gpioAddress + 0x10)) ;
    const bool currentValue = (IDR & (uint32_t (1) << portIndex)) != 0 ;
  //--- BSRR register has offset 0x18
    volatile uint32_t & BSRR = *((volatile uint32_t *) (gpioAddress + 0x18)) ;
    if (!currentValue) {
      BSRR = uint32_t (1) << portIndex ; // Set
    }else{
      BSRR = uint32_t (1) << (portIndex + 16) ; // Reset
    }
  }
}

//------------------------------------------------------------------------------

bool digitalRead (const DigitalOutputPin inPin) {
  const DigitalInputPin pin = DigitalInputPin (inPin) ;
  return digitalRead (pin) ;
}

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

void setAlternateFunctionMode (const AlternateFunction inPin) {
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

//------------------------------------------------------------------------------

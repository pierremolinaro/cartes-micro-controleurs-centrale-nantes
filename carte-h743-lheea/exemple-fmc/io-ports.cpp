#include "io-ports.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————
//--- gpioBaseAddress:
//     PORTA -> 0x5802_0000
//     PORTB -> 0x5802_0400
//     PORTC -> 0x5802_0800
//     PORTD -> 0x5802_0C00
//     PORTE -> 0x5802_1000
//     PORTF -> 0x5802_1400
//     PORTG -> 0x5802_1800
//——————————————————————————————————————————————————————————————————————————————————————————————————

static const uint32_t GPIO_BASE_ADDRESS = 0x58020000 ;

//——————————————————————————————————————————————————————————————————————————————————————————————————
// IOMode encodes configuration values (see "Port bit configuration table" from reference manual)
// Bits 1-0: PUPD (0 -> none, 1 -> pullup, 2 -> pulldown)
// Bits 3-2: OSPEED (0 -> low speed, 1 -> medium speed, 2 -> high speed, 3 -> very high speed)
// Bit 4: OTYPER (if output: 0 -> push / pull, 1 -> open collector)
// Bit 6-5: MODER (0 -> digital input, 1 -> digital output, 2 -> alternation function, 3 -> analog)

void pinMode (const IOPin inPort, const IOMode inMode) {
  if (inPort < IOPin::True) {
    const uint32_t moder = uint32_t (inMode) >> 5 ;
    const uint32_t pupd = uint32_t (inMode) & 3 ;
    const uint32_t optyper = (uint32_t (inMode) >> 4) & 1 ;
    const uint32_t ospeed = (uint32_t (inMode) >> 2) & 3 ;
  //---
    const uint32_t gpioIndex = uint32_t (inPort) / 16 ; // 0 -> PORTA, ..., 7 -> PORTG, 8 -> PORTH
    const uint32_t portIndex = uint32_t (inPort) % 16 ; // portIndex: 0, ..., 15
  //--- gpioBaseAddress:
    const uint32_t gpioBaseAddress = GPIO_BASE_ADDRESS + gpioIndex * 0x400 ;
  //--- MODER register has offset 0x0
    volatile uint32_t & MODER = *((volatile uint32_t *) (gpioBaseAddress + 0x00)) ;
    MODER &= ~ (uint32_t (3) << (portIndex * 2)) ;
    MODER |=   (moder << (portIndex * 2)) ;
  //--- OPTYPER register has offset 0x04
    volatile uint32_t & OTYPER = *((volatile uint32_t *) (gpioBaseAddress + 0x04)) ;
    OTYPER &= ~ (uint32_t (1) << portIndex) ;
    OTYPER |=   (optyper << portIndex) ;
  //--- PUPDR register has offset 0x0C
    volatile uint32_t & PUPDR = *((volatile uint32_t *) (gpioBaseAddress + 0x0C)) ;
    PUPDR &= ~ (uint32_t (3) << (portIndex * 2)) ;
    PUPDR |=    pupd << (portIndex * 2) ;
  //--- OSPEEDR register has offset 0x08
    volatile uint32_t & OSPEEDR = *((volatile uint32_t *) (gpioBaseAddress + 0x08)) ;
    OSPEEDR &= ~(uint32_t (3) << (portIndex * 2)) ;
    OSPEEDR |=   ospeed << (portIndex * 2) ; // Very high speed
  }
}

//——————————————————————————————————————————————————————————————————————————————————————————————————

void digitalWrite (const IOPin inPort, const bool inValue) {
  if (inPort < IOPin::True) {
    const uint32_t gpioIndex = uint32_t (inPort) / 16 ; // 0 -> PORTA, ..., 7 -> PORTG, 8 -> PORTH
    const uint32_t portIndex = uint32_t (inPort) % 16 ; // portIndex: 0, ..., 15
  //--- gpioBaseAddress
    const uint32_t gpioBaseAddress = GPIO_BASE_ADDRESS + gpioIndex * 0x400 ;
  //--- BSRR register has offset 0x18
    volatile uint32_t & BSRR = *((volatile uint32_t *) (gpioBaseAddress + 0x18)) ;
    if (inValue) {
      BSRR = uint32_t (1) << portIndex ; // Set
    }else{
      BSRR = uint32_t (1) << (portIndex + 16) ; // Reset
    }
  }
}

//——————————————————————————————————————————————————————————————————————————————————————————————————

bool digitalRead (const IOPin inPort) {
  bool result = inPort == IOPin::True ;
  if (inPort < IOPin::True) {
    const uint32_t gpioIndex = uint32_t (inPort) / 16 ; // 0 -> PORTA, ..., 7 -> PORTG, 8 -> PORTH
    const uint32_t portIndex = uint32_t (inPort) % 16 ; // portIndex: 0, ..., 15
  //--- gpioBaseAddress
    const uint32_t gpioBaseAddress = GPIO_BASE_ADDRESS + gpioIndex * 0x400 ;
  //--- IDR register has offset 0x10
    volatile uint32_t & IDR = *((volatile uint32_t *) (gpioBaseAddress + 0x10)) ;
    result = (IDR & (uint32_t (1) << portIndex)) != 0 ;
  }
  return result ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————

void digitalToggle (const IOPin inPort) {
  if (inPort < IOPin::True) {
    const uint32_t gpioIndex = uint32_t (inPort) / 16 ; // 0 -> PORTA, ..., 7 -> PORTG, 8 -> PORTH
    const uint32_t portIndex = uint32_t (inPort) % 16 ; // portIndex: 0, ..., 15
  //--- gpioBaseAddress
    const uint32_t gpioBaseAddress = GPIO_BASE_ADDRESS + gpioIndex * 0x400 ;
  //--- IDR register has offset 0x10
    volatile uint32_t & IDR = *((volatile uint32_t *) (gpioBaseAddress + 0x10)) ;
    const bool currentValue = (IDR & (uint32_t (1) << portIndex)) != 0 ;
  //--- BSRR register has offset 0x18
    volatile uint32_t & BSRR = *((volatile uint32_t *) (gpioBaseAddress + 0x18)) ;
    if (!currentValue) {
      BSRR = uint32_t (1) << portIndex ; // Set
    }else{
      BSRR = uint32_t (1) << (portIndex + 16) ; // Reset
    }
  }
}

//——————————————————————————————————————————————————————————————————————————————————————————————————

void setAlternateFunction (const IOPin inPort, const APF inAlternateFunction) {
  if (inPort < IOPin::True) {
    const uint32_t gpioIndex = uint32_t (inPort) / 16 ; // 0 -> PORTA, ..., 7 -> PORTG, 8 -> PORTH
    const uint32_t portIndex = uint32_t (inPort) % 16 ; // portIndex: 0, ..., 15
  //--- gpioBaseAddress
    const uint32_t gpioBaseAddress = GPIO_BASE_ADDRESS + gpioIndex * 0x400 ;
  //--- AFRL register has offset 0x20, AFRH -> 0x24
  //--- We use byte access
  //    At offset 0 : AFR1[3:0], AFR0[3:0]
  //    At offset 1 : AFR3[3:0], AFR2[3:0]
  //    At offset 2 : AFR5[3:0], AFR4[3:0]
  //    ....
  //    At offset 7 : AFR15[3:0], AFR14[3:0]
    const uint32_t AFR_address = gpioBaseAddress + 0x20 + (portIndex / 2) ;
    volatile uint8_t & AFR_BYTE = *((volatile uint8_t *) (AFR_address)) ;
    const uint8_t mask = ((portIndex & 1) == 0) ? 0xF0 : 0x0F ;
    const uint8_t altFunc = ((portIndex & 1) == 0)
      ? uint8_t (inAlternateFunction)
      : (uint8_t (inAlternateFunction) << 4)
    ;
    AFR_BYTE &= mask ;
    AFR_BYTE |= altFunc ;
  }
}

//——————————————————————————————————————————————————————————————————————————————————————————————————

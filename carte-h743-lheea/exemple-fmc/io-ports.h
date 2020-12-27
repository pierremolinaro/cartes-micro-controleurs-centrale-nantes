#pragma once

//——————————————————————————————————————————————————————————————————————————————————————————————————

#include <stdint.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————

enum class IOPin : uint8_t {
  PinA0, PinA1, PinA2, PinA3, PinA4, PinA5, PinA6, PinA7, PinA8, PinA9, PinA10, PinA11, PinA12, PinA13, PinA14, PinA15,
  PinB0, PinB1, PinB2, PinB3, PinB4, PinB5, PinB6, PinB7, PinB8, PinB9, PinB10, PinB11, PinB12, PinB13, PinB14, PinB15,
  PinC0, PinC1, PinC2, PinC3, PinC4, PinC5, PinC6, PinC7, PinC8, PinC9, PinC10, PinC11, PinC12, PinC13, PinC14, PinC15,
  PinD0, PinD1, PinD2, PinD3, PinD4, PinD5, PinD6, PinD7, PinD8, PinD9, PinD10, PinD11, PinD12, PinD13, PinD14, PinD15,
  PinE0, PinE1, PinE2, PinE3, PinE4, PinE5, PinE6, PinE7, PinE8, PinE9, PinE10, PinE11, PinE12, PinE13, PinE14, PinE15,
  PinF0, PinF1, PinF2, PinF3, PinF4, PinF5, PinF6, PinF7, PinF8, PinF9, PinF10, PinF11, PinF12, PinF13, PinF14, PinF15,
  PinG0, PinG1, PinG2, PinG3, PinG4, PinG5, PinG6, PinG7, PinG8, PinG9, PinG10, PinG11, PinG12, PinG13, PinG14, PinG15,
//--- No port
    True, // Fictive port: no effect on write, always read true
    False // Fictive port: no effect on write, always read false
} ;

//——————————————————————————————————————————————————————————————————————————————————————————————————
// IOMode encodes configuration values (see "Port bit configuration table" from reference manual)
// Bits 1-0: PUPD (0 -> none, 1 -> pullup, 2 -> pulldown)
// Bits 3-2: OSPEED (0 -> low speed, 1 -> medium speed, 2 -> high speed, 3 -> very high speed)
// Bit 4: OTYPER (if output: 0 -> push / pull, 1 -> open collector)
// Bit 6-5: MODE (0 -> digital input, 1 -> digital output, 2 -> alternate function, 3 -> analog)

enum class IOMode : uint8_t {
    OUTPUT_MODE               = (1 << 5) | (0 << 4) | (3 << 2),
    OUTPUT_OPEN_COLLECTOR     = (1 << 5) | (1 << 4) | (3 << 2),
    INPUT_MODE                = 0,
    INPUT_PULLDOWN_MODE       = (2 << 0),
    INPUT_PULLUP_MODE         = (1 << 0),
    ANALOG                    = (3 << 5),
    ALTERNATE                 = (2 << 5) | (0 << 4) | (3 << 2),
    ALTERNATE_OPEN_COLLECTOR  = (2 << 5) | (1 << 4) | (3 << 2),
    ALTERNATE_PULLDOWN        = (2 << 5) | (2 << 0),
    ALTERNATE_PULLUP          = (2 << 5) | (1 << 0)
} ;

//——————————————————————————————————————————————————————————————————————————————————————————————————

void pinMode (const IOPin inPort, const IOMode inMode) ;

bool digitalRead (const IOPin inPort) ;

void digitalWrite (const IOPin inPort, const bool inValue) ;

void digitalToggle (const IOPin inPort) ;

//——————————————————————————————————————————————————————————————————————————————————————————————————

enum class APF : uint8_t {
  af0, af1, af2, af3, af4, af5, af6, af7, af8, af9, af10, af11, af12, af13, af14, af15
} ;

//——————————————————————————————————————————————————————————————————————————————————————————————————

void setAlternateFunction (const IOPin inPort, const APF inAlternateFunction) ;

//——————————————————————————————————————————————————————————————————————————————————————————————————

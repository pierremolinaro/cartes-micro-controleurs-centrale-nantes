#pragma once

#include <Arduino.h>

//-------------------------------------------------------------------------------------------------

#ifndef ARDUINO_ARCH_RP2040
  #error Select a Raspberry Pi RP2040 board
#endif

//-------------------------------------------------------------------------------------------------
// CHARLEPLEXING 5
//-------------------------------------------------------------------------------------------------

void charlieplexing5_add_program (PIO pio, uint offset) ;

void charlieplexing5_program_init (PIO pio, uint sm, uint offset, uint pin) ;

void pio_charlieplexing5_set_output (PIO pio, uint sm, const uint32_t inValue) ;

//-------------------------------------------------------------------------------------------------
// CHARLEPLEXING 5
//-------------------------------------------------------------------------------------------------

void charlieplexing6_add_program (PIO pio, uint offset) ;

void charlieplexing6_program_init (PIO pio, uint sm, uint offset, uint pin) ;

void pio_charlieplexing6_set_output (PIO pio, uint sm, const uint32_t inValue) ;

//-------------------------------------------------------------------------------------------------

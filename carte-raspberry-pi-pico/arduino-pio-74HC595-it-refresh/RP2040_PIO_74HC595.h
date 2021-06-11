#pragma once

//-------------------------------------------------------------------------------------------------

#ifndef ARDUINO_RASPBERRY_PI_PICO
  #error Sélectionner la carte "Raspberry Pi Pico"
#endif

//-------------------------------------------------------------------------------------------------

#include <Arduino.h>

//-------------------------------------------------------------------------------------------------

uint32_t rp2040_PIO_74HC595_add_program (const PIO pio,
                                         const uint32_t prgmOffset) ;

//-------------------------------------------------------------------------------------------------

void rp2040_PIO_74HC595_init (const PIO pio, 
                              const uint32_t stateMachine,
                              const uint32_t prgmOffset,
                              const uint32_t ctrlBasePin,
                              const uint32_t dataPin) ;

//-------------------------------------------------------------------------------------------------

void setIntensity (const uint32_t inLedIndex, const uint8_t inIntensity) ;

//-------------------------------------------------------------------------------------------------

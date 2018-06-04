#pragma once

#include <Arduino.h>

#ifndef ARDUINO_SAMD_FEATHER_M0
  #error "Ce croquis doit être compilé pour le type de carte 'Adafruit Feather M0'"
#endif

void beginIO (void) ;

const byte LED_RED = 0 ;
const byte LED_GREEN = 1 ;
const byte LED_YELLOW = 2 ;
const byte LED_BLUE = 3 ;

void ledWrite (const byte inLed, const bool inLevel) ;

const byte BUTTON_P0 = 0 ;
const byte BUTTON_P1 = 1 ;
const byte BUTTON_P2 = 2 ;
const byte ENCODER_CLIC = 3 ;

bool pushButton (const byte inButton) ;

byte encoderValue (void) ;


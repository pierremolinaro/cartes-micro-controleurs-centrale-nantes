#ifndef ARDUINO_RASPBERRY_PI_PICO
  #error Sélectionner la carte "Raspberry Pi Pico"
#endif

//-------------------------------------------------------------------------------------------------

#include <hardware/pio.h>
#include <LiquidCrystal.h>

//-------------------------------------------------------------------------------------------------

#include "RP2040_PIO_74HC595.h"

//-------------------------------------------------------------------------------------------------

static LiquidCrystal lcd (19, 18, 14, 15, 16, 17) ; // RS, E, D4, D5, D6, D7

//-------------------------------------------------------------------------------------------------
// Select the PIO you want to use (pio0 or pio1)
//-------------------------------------------------------------------------------------------------

static const PIO pio = pio0 ;

//-------------------------------------------------------------------------------------------------
// Select the state machine you want to use (0, 1, 2 or 3)
//-------------------------------------------------------------------------------------------------

static const uint32_t stateMachine = 0 ;

//-------------------------------------------------------------------------------------------------

void setup() {
  Serial.println ("Hello") ;
  lcd.begin (20,4) ;
  lcd.print ("Hello") ;
  pinMode (LED_BUILTIN, OUTPUT) ;
//--- PIO
  const uint32_t prgmOffset = 0 ;
  const uint32_t serialClockFrequency = 6 * 1000 * 1000 ;
  const uint32_t ctrlBasePin = 26 ; // GP26: LOAD, GP27 SCLK
  const uint32_t dataPin = 8 ; // GP8: DATA
  rp2040_PIO_74HC595_add_program (pio, prgmOffset) ;
  rp2040_PIO_74HC595_init (pio, stateMachine, prgmOffset, ctrlBasePin, dataPin, serialClockFrequency) ;
}

//-------------------------------------------------------------------------------------------------

static uint32_t gT1 = 0 ;

//-------------------------------------------------------------------------------------------------

void loop() {
  if (gT1 < millis ()) {
    gT1 += 1000;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
    lcd.setCursor (0, 1) ;
    lcd.print (gT1) ;
    rp2040_PIO_74HC595_set_value (pio, stateMachine, 0x55555555) ;
  }
}

//-------------------------------------------------------------------------------------------------

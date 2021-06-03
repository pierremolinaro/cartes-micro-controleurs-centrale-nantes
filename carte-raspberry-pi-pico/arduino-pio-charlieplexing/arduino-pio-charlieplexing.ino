#ifndef ARDUINO_ARCH_RP2040
  #error Select a Raspberry Pi RP2040 board
#endif

//-------------------------------------------------------------------------------------------------

#include <LiquidCrystal.h>

#include "charlieplexing.h"

//-------------------------------------------------------------------------------------------------

static LiquidCrystal lcd (19, 18, 14, 15, 16, 17) ; // RS, E, D4, D5, D6, D7

//-------------------------------------------------------------------------------------------------

static const uint stateMachine = 0 ;
static const uint outputPin = 0 ;

//-------------------------------------------------------------------------------------------------

void setup() {
  Serial.println ("Hello") ;
  lcd.begin (20,4) ;
  lcd.print ("Hello") ;
  pinMode (LED_BUILTIN, OUTPUT) ;
//--- PIO
//  charlieplexing6_program_init (pio0, stateMachine, prgmOffset, outputPin) ;
//  pio_add_program_at_offset (pio0, & charlieplexing6_program, prgmOffset) ;
  const uint prgmOffset = 0 ;
  charlieplexing5_add_program (pio0, prgmOffset) ;
  charlieplexing5_program_init (pio0, stateMachine, prgmOffset, outputPin) ;
  pio_sm_set_enabled (pio0, stateMachine, true) ;
}

//-------------------------------------------------------------------------------------------------

static uint32_t gT1 = 0 ;
static uint32_t gValue = 1 ;

//-------------------------------------------------------------------------------------------------

void loop() {
  if (gT1 < millis ()) {
    gT1 += 1000 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
    lcd.setCursor (0, 1) ;
    lcd.print (gT1) ;
    pio_charlieplexing5_set_output (pio0, stateMachine, gValue) ;
    gValue <<= 1 ;
    gValue &= 0x1F ;
    if (gValue == 0) {
      gValue = 1 ;
    }
  }
}

//-------------------------------------------------------------------------------------------------

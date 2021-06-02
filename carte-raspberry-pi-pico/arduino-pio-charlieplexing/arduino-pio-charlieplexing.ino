#ifndef ARDUINO_RASPBERRY_PI_PICO
  #error Sélectionner la carte "Raspberry Pi Pico"
#endif

//-------------------------------------------------------------------------------------------------

#include <LiquidCrystal.h>
#include <hardware/structs/pio.h>

#include "pio-charlieplexing.h"

//-------------------------------------------------------------------------------------------------

static LiquidCrystal lcd (19, 18, 14, 15, 16, 17) ; // RS, E, D4, D5, D6, D7

//-------------------------------------------------------------------------------------------------

static void charlieplexing_program_init (PIO pio, uint sm, uint offset, uint pin) {
   pio_gpio_init (pio, pin) ;
   pio_gpio_init (pio, pin + 1) ;
   pio_gpio_init (pio, pin + 2) ;
   pio_sm_config c = charlieplexing_program_get_default_config (offset) ;
   sm_config_set_out_pins (&c, 0, 3) ;
   sm_config_set_in_pins  (&c, 0) ; 
   sm_config_set_set_pins (&c, 0, 3) ; 
   pio_sm_init (pio, sm, offset, &c) ;
}

static void pio_charlieplexing_set_output (PIO pio, uint sm, const uint32_t inValue) {
  uint configuration = 0 ;
  if ((inValue & 1) != 0) {
    configuration |= 1 << 0 ;
  }
  if ((inValue & 2) != 0) {
    configuration |= 4 << 3 ;
  }
  if ((inValue & 4) != 0) {
    configuration |= 1 << 6 ;
  }
  if ((inValue & 8) != 0) {
    configuration |= 2 << 9 ;
  }
  if ((inValue & 16) != 0) {
    configuration |= 2 << 12 ;
  }
  if ((inValue & 32) != 0) {
    configuration |= 4 << 15 ;
  }
  pio_sm_put_blocking (pio, sm, configuration) ;
}

//-------------------------------------------------------------------------------------------------

  const uint stateMachine = 0 ;
  const uint prgmOffset = 0 ;
  const uint outputPin = 0 ;

//-------------------------------------------------------------------------------------------------

void setup() {
  Serial.println ("Hello") ;
  lcd.begin (20,4) ;
  lcd.print ("Hello") ;
  pinMode (LED_BUILTIN, OUTPUT) ;
//--- PIO
//  pinMode (0, OUTPUT) ;
//  pinMode (2, OUTPUT) ;
//  digitalWrite (0, HIGH) ;
  charlieplexing_program_init (pio0, stateMachine, prgmOffset, outputPin) ;
  pio_add_program_at_offset (pio0, & charlieplexing_program, prgmOffset) ;
//  pio0_hw->sm [stateMachine].clkdiv = 0 ;
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
//    digitalWrite (0, !digitalRead (0)) ;
//    digitalWrite (2, !digitalRead (2)) ;
    lcd.setCursor (0, 1) ;
    lcd.print (gT1) ;
    pio_charlieplexing_set_output (pio0, stateMachine, gValue) ;
    gValue <<= 1 ;
    gValue &= 0x3F ;
    if (gValue == 0) {
      gValue = 1 ;
    }
  }
}

//-------------------------------------------------------------------------------------------------

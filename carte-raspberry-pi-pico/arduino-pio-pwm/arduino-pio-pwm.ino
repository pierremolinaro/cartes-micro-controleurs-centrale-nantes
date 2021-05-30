#ifndef ARDUINO_RASPBERRY_PI_PICO
  #error Sélectionner la carte "Raspberry Pi Pico"
#endif

//-------------------------------------------------------------------------------------------------

#include <LiquidCrystal.h>
#include <hardware/structs/pio.h>

#include "pio-pwm.h"

//-------------------------------------------------------------------------------------------------

static LiquidCrystal lcd (19, 18, 14, 15, 16, 17) ; // RS, E, D4, D5, D6, D7

//-------------------------------------------------------------------------------------------------

static void pwm_program_init(PIO pio, uint sm, uint offset, uint pin) {
   pio_gpio_init (pio, pin) ;
   pio_sm_set_consecutive_pindirs (pio, sm, pin, 1, true);
   pio_sm_config c = pwm_program_get_default_config (offset) ;
   sm_config_set_sideset_pins (&c, pin) ;
   pio_sm_init (pio, sm, offset, &c) ;
}

static void pio_pwm_set_period (PIO pio, uint sm, uint32_t period) {
  pio_sm_set_enabled (pio, sm, false) ;
  pio_sm_put_blocking (pio, sm, period) ;
  pio_sm_exec (pio, sm, pio_encode_pull (false, false)) ;
  pio_sm_exec (pio, sm, pio_encode_out (pio_isr, 32)) ;
  pio_sm_set_enabled (pio, sm, true) ;
}

static void pio_pwm_set_level (PIO pio, uint sm, uint32_t level) { 
  pio_sm_put_blocking (pio, sm, level);
}

//-------------------------------------------------------------------------------------------------

void setup() {
  Serial.println ("Hello") ;
  lcd.begin (20,4) ;
  lcd.print ("Hello") ;
  pinMode (LED_BUILTIN, OUTPUT) ;
//--- PIO
  const uint stateMachine = 0 ;
  const uint prgmOffset = 0 ;
  const uint outputPin = 4 ;
  pwm_program_init (pio0, stateMachine, prgmOffset, outputPin) ;
  pio_add_program_at_offset (pio0, & pwm_program, prgmOffset) ;
  pio0_hw->sm [stateMachine].clkdiv = 125u << 16 ; // Horloge 1 MHz
  pio_pwm_set_period (pio0, stateMachine, 99999) ;
  pio_pwm_set_level  (pio0, stateMachine, 50000) ;
}

//-------------------------------------------------------------------------------------------------

static uint32_t gT1 = 0 ;

//-------------------------------------------------------------------------------------------------

void loop() {
  if (gT1 < millis ()) {
    gT1 += 1000 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
    lcd.setCursor (0, 1) ;
    lcd.print (gT1) ;
  }
}

//-------------------------------------------------------------------------------------------------

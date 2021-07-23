//#ifndef ARDUINO_RASPBERRY_PI_PICO
//  #error Sélectionner la carte "Raspberry Pi Pico"
//#endif

//-------------------------------------------------------------------------------------------------

//#include <LiquidCrystal.h>

#include "pio-ws2812x2.h"

//-------------------------------------------------------------------------------------------------

//static LiquidCrystal lcd (19, 18, 14, 15, 16, 17) ; // RS, E, D4, D5, D6, D7

//-------------------------------------------------------------------------------------------------

static void pwm_program_init (const PIO pio,
                              const uint32_t sm,
                              const uint32_t offset,
                              const uint32_t pin) {
  pio_sm_config c = ws2812x2_program_get_default_config (offset) ;
  sm_config_set_out_pins (&c, pin, 1) ;
  sm_config_set_set_pins (&c, pin, 1) ;
  pio_gpio_init (pio, pin) ;
  pio_sm_set_consecutive_pindirs (pio, sm, pin, 1, true);
  sm_config_set_out_shift (&c, false, false, 0); // Shift left
  const uint32_t machineFrequency = 25 * 1000 * 1000 ; // 25 MHz
  uint32_t divisor = RP2040::f_cpu () / machineFrequency ;
  uint32_t frac = (256 * machineFrequency * (RP2040::f_cpu () % machineFrequency)) / machineFrequency ;
  if (divisor >= 0x10000) {
    divisor = 0 ;
    frac = 0 ;
  }
  sm_config_set_clkdiv_int_frac (&c, uint16_t (divisor), uint8_t (frac)) ;
  pio_sm_init (pio, sm, offset, &c) ;
  pio_sm_set_enabled (pio, sm, true) ;
//    lcd.setCursor (0, 2) ;
//    lcd.print (divisor) ;
//    lcd.print (" ") ;
//    lcd.print (frac) ;
}

//-------------------------------------------------------------------------------------------------

static void pio_ws2812_set_output (const PIO pio,
                                   const uint32_t sm,
                                   const uint8_t red,
                                   const uint8_t green,
                                   const uint8_t blue) {
//--- Value to be sent
// Bits 7-0: unused, any value
// Bits 15-8: blue, reverse order
// Bits 23-16: red, reverse order
// Bits 31-24: green, reverse order
  uint32_t value = uint32_t (blue) << 8 ;
  value |= uint32_t (red) << 16 ;
  value |= uint32_t (green) << 24 ;
  pio_sm_put_blocking (pio, sm, value) ;
}

//-------------------------------------------------------------------------------------------------

static const PIO pio = pio0 ;
const uint32_t stateMachine = 0 ;

//-------------------------------------------------------------------------------------------------

void setup() {
//  Serial.println ("Hello") ;
//  lcd.begin (20,4) ;
//  lcd.print ("Hello") ;
  pinMode (LED_BUILTIN, OUTPUT) ;
//--- PIO
  const uint32_t prgmOffset = 0 ;
  const uint32_t outputPin = 25 ;
  pwm_program_init (pio, stateMachine, prgmOffset, outputPin) ;
  pio_add_program_at_offset (pio, & ws2812x2_program, prgmOffset) ;
//    lcd.setCursor (0, 3) ;
//    lcd.print (systick_hw->rvr) ;
}

//-------------------------------------------------------------------------------------------------

static uint32_t gDeadline = 0 ;
static uint32_t gEcheanceMode2 = 0 ;
static uint8_t gCouleur = 0 ;

//-------------------------------------------------------------------------------------------------

void loop() {
 if (gEcheanceMode2 < millis ()) {
    gEcheanceMode2 += 20 ;
    gCouleur += 1 ;
    gCouleur &= 0x7F ;
    pio_ws2812_set_output (pio, stateMachine, gCouleur, gCouleur, gCouleur) ;
    pio_ws2812_set_output (pio, stateMachine, 0, gCouleur, 0) ;
  }
  if (gDeadline < millis ()) {
    gDeadline += 1000 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
//    lcd.setCursor (0, 1) ;
//    lcd.print (gDeadline) ;
//    pio_ws2812_set_output (pio, stateMachine, 64, 0, 0) ;
//    pio_ws2812_set_output (pio, stateMachine, 0, 64, 0) ;
   }
 }

//-------------------------------------------------------------------------------------------------

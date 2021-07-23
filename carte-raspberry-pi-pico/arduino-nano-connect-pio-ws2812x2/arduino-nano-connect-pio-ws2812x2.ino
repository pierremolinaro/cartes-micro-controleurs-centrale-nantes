//-------------------------------------------------------------------------------------------------
// This sketch handles two WS2812 leds, for an Arduino Nano Connect
//   Arduino Nano Connect     WS2812
//        Vin              ->  +5V
//        GND              ->  GND
//        GPIO25 (D2)      ->  DI
//-------------------------------------------------------------------------------------------------

const uint32_t outputPin = 25 ; // GPIO25 is D2

//-------------------------------------------------------------------------------------------------

#ifndef ARDUINO_ARDUINO_NANO_RP2040_CONNECT
  #error Select "Arduino Nano RP2040 Connect" Board
#endif

//-------------------------------------------------------------------------------------------------

#include "pio-ws2812x2.h"

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
  pinMode (LED_BUILTIN, OUTPUT) ;
  Serial.begin (115200) ;
  delay (2000) ;
  Serial.println (D2) ;
//--- PIO
  const uint32_t prgmOffset = 0 ;
  pwm_program_init (pio, stateMachine, prgmOffset, outputPin) ;
  pio_add_program_at_offset (pio, & ws2812x2_program, prgmOffset) ;
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
  }
 }

//-------------------------------------------------------------------------------------------------

#ifndef ARDUINO_RASPBERRY_PI_PICO
  #error Sélectionner la carte "Raspberry Pi Pico"
#endif

//-------------------------------------------------------------------------------------------------

#include <hardware/dma.h>

#include "RP2040_PIO_74HC595.h"
#include "pio-74HC595.h"

//-------------------------------------------------------------------------------------------------

static uint32_t gOutputValue = 0 ;

//-------------------------------------------------------------------------------------------------

class T {
  public: volatile uint8_t mAccumulator ;
  public: volatile uint8_t mIntensity ;
} ;

static T gTab [32] ;

//-------------------------------------------------------------------------------------------------

static void pioInterruptServiceRoutine (void) {
  uint32_t result = 0 ;
  for (uint32_t i=0 ; i<32 ; i++) {
    result <<= 1 ;
    const uint32_t oldAcc = gTab [i].mAccumulator ;
    const uint32_t newAcc = oldAcc + gTab [i].mIntensity ;
    gTab [i].mAccumulator = uint8_t (newAcc) ;
    result |= (newAcc >> 8) ;
  }
  pio0->txf [0] = result ;
}

//-------------------------------------------------------------------------------------------------

uint32_t rp2040_PIO_74HC595_add_program (const PIO pio,
                                         const uint32_t prgmOffset) {
  pio_add_program_at_offset (pio, & SN74HC595_program, prgmOffset) ;
  return prgmOffset + SN74HC595_program.length ;
}

//-------------------------------------------------------------------------------------------------

void rp2040_PIO_74HC595_init (const PIO pio, 
                              const uint32_t stateMachine,
                              const uint32_t prgmOffset,
                              const uint32_t ctrlBasePin,
                              const uint32_t dataPin) {
  pio_gpio_init (pio, ctrlBasePin) ;
  pio_gpio_init (pio, ctrlBasePin + 1) ;
  pio_gpio_init (pio, dataPin) ;
  pio_sm_set_consecutive_pindirs (pio, stateMachine, ctrlBasePin, 2, true) ;
  pio_sm_set_consecutive_pindirs (pio, stateMachine, dataPin, 1, true) ;
  pio_sm_config c = SN74HC595_program_get_default_config (prgmOffset) ;
  sm_config_set_out_pins (&c, dataPin, 1) ;
  sm_config_set_sideset_pins (&c, ctrlBasePin) ;
  const uint32_t machineFrequency = 5 * 1000 * 1000 ; // 5 MHz
  uint32_t divisor = RP2040::f_cpu () / machineFrequency ;
  uint32_t frac = (256 * machineFrequency * (RP2040::f_cpu () % machineFrequency)) / machineFrequency ;
  if (divisor >= 0x10000) {
    divisor = 0 ;
    frac = 0 ;
  }
  sm_config_set_clkdiv_int_frac (&c, uint16_t (divisor), uint8_t (frac)) ;
  pio_sm_init (pio, stateMachine, prgmOffset, &c) ;

  irq_set_exclusive_handler (PIO0_IRQ_0, pioInterruptServiceRoutine) ;
  pio->inte0 = 1 << (4 + stateMachine) ;
  irq_set_enabled (PIO0_IRQ_0, true) ;

  pio_sm_set_enabled (pio, stateMachine, true) ;
  for (uint8_t i=0 ; i<32 ; i++) {
    gTab [i].mIntensity = i + 1 ;
  }
}

//-------------------------------------------------------------------------------------------------

void setIntensity (const uint32_t inLedIndex, const uint8_t inIntensity) {
  if (inLedIndex < 32) {
    gTab [inLedIndex].mIntensity = inIntensity ;
  } 
}

//-------------------------------------------------------------------------------------------------

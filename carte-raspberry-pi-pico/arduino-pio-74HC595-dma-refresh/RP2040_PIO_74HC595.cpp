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

static void dmaInterruptServiceRoutine (void) {
  dma_hw->ints0 = 1u ;
  dma_channel_start (0) ;
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
                              const uint32_t dataPin,
                              const uint32_t serialClockFrequency) {
  pio_gpio_init (pio, ctrlBasePin) ;
  pio_gpio_init (pio, ctrlBasePin + 1) ;
  pio_gpio_init (pio, dataPin) ;
  pio_sm_set_consecutive_pindirs (pio, stateMachine, ctrlBasePin, 2, true) ;
  pio_sm_set_consecutive_pindirs (pio, stateMachine, dataPin, 1, true) ;
  pio_sm_config c = SN74HC595_program_get_default_config (prgmOffset) ;
  sm_config_set_out_pins (&c, dataPin, 1) ;
  sm_config_set_sideset_pins (&c, ctrlBasePin) ;
  const uint32_t machineFrequency = serialClockFrequency * 2 ;
  uint32_t divisor = RP2040::f_cpu () / machineFrequency ;
  uint32_t frac = (256 * machineFrequency * (RP2040::f_cpu () % machineFrequency)) / machineFrequency ;
  if (divisor >= 0x10000) {
    divisor = 0 ;
    frac = 0 ;
  }
  sm_config_set_clkdiv_int_frac (&c, uint16_t (divisor), uint8_t (frac)) ;
  pio_sm_init (pio, stateMachine, prgmOffset, &c) ;
  pio_sm_set_enabled (pio, stateMachine, true) ;
//--- Use DMA timer 0
  dma_hw->timer[0] = (1 << 16) | (125 * 20) ;
//--- Configure DMA
  const uint32_t dmaChannel = 0 ; // dma_claim_unused_channel (true) ;
//  const uint32_t ctrlChannel = 1 ; // dma_claim_unused_channel (true) ;
  dma_channel_config cfg = dma_channel_get_default_config (dmaChannel) ;
  channel_config_set_read_increment (&cfg, false) ;
  channel_config_set_dreq (&cfg, DMA_CH0_CTRL_TRIG_TREQ_SEL_VALUE_TIMER0) ; // DREQ_DMA_TIMER0
//  channel_config_set_chain_to (&cfg, ctrlChannel);
  dma_channel_configure (dmaChannel, &cfg, & pio->txf [stateMachine], & gOutputValue, 1, false) ;

//  cfg = dma_channel_get_default_config (ctrlChannel) ;
//  channel_config_set_read_increment (&cfg, false) ;
//  channel_config_set_chain_to (&cfg, dmaChannel);
//  dma_channel_configure (ctrlChannel, &cfg, NULL, NULL, 1, false) ;

  irq_set_exclusive_handler (DMA_IRQ_0, dmaInterruptServiceRoutine) ;
  dma_hw->inte0 = 1u << dmaChannel ;
  irq_set_enabled (DMA_IRQ_0, true) ;

  dma_channel_start (dmaChannel) ;
}

//-------------------------------------------------------------------------------------------------

void rp2040_PIO_74HC595_set_value (const PIO pio, const uint32_t stateMachine, const uint32_t value) {
  gOutputValue = value ;
 // pio_sm_put_blocking (pio, stateMachine, value) ;
//  dma_channel_start (0) ;
}

//-------------------------------------------------------------------------------------------------

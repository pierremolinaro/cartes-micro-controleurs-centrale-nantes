//-------------------------------------------------------------------------------------------------

#include "charlieplexing.h"
#include "pio-charlieplexing5.h"
#include "pio-charlieplexing6.h"

//-------------------------------------------------------------------------------------------------
// CHARLEPLEXING 5
//-------------------------------------------------------------------------------------------------

void charlieplexing5_add_program (PIO pio, uint prgmOffset) {
  pio_add_program_at_offset (pio, & charlieplexing5_program, prgmOffset) ;
}

//-------------------------------------------------------------------------------------------------

void charlieplexing5_program_init (PIO pio, uint sm, uint offset, uint pin) {
   pio_gpio_init (pio, pin) ;
   pio_gpio_init (pio, pin + 1) ;
   pio_gpio_init (pio, pin + 2) ;
   pio_sm_config c = charlieplexing5_program_get_default_config (offset) ;
   sm_config_set_out_pins (&c, 0, 3) ;
   sm_config_set_in_pins  (&c, 0) ;
   sm_config_set_set_pins (&c, 0, 3) ;
   pio_sm_init (pio, sm, offset, &c) ;
}

//-------------------------------------------------------------------------------------------------

void pio_charlieplexing5_set_output (PIO pio, uint sm, const uint32_t inValue) {
  uint configuration = 0x05 | (0x05 << 6) | (0x3 << 12)  | (0x3 << 18) | (0x6 << 24) | (3 << 30) ;
  if ((inValue & 1) != 0) {
    configuration |= 1 << 3 ;
  }
  if ((inValue & 2) != 0) {
    configuration |= 4 << 9 ;
  }
  if ((inValue & 4) != 0) {
    configuration |= 1 << 15 ;
  }
  if ((inValue & 8) != 0) {
    configuration |= 2 << 21 ;
  }
  if ((inValue & 16) != 0) {
    configuration |= 2 << 27 ;
  }
  pio_sm_put_blocking (pio, sm, configuration) ;
}

//-------------------------------------------------------------------------------------------------
// CHARLEPLEXING 5
//-------------------------------------------------------------------------------------------------

void charlieplexing6_add_program (PIO pio, uint prgmOffset) {
  pio_add_program_at_offset (pio, & charlieplexing6_program, prgmOffset) ;
}

//-------------------------------------------------------------------------------------------------

void charlieplexing6_program_init (PIO pio, uint sm, uint offset, uint pin) {
   pio_gpio_init (pio, pin) ;
   pio_gpio_init (pio, pin + 1) ;
   pio_gpio_init (pio, pin + 2) ;
   pio_sm_config c = charlieplexing6_program_get_default_config (offset) ;
   sm_config_set_out_pins (&c, 0, 3) ;
   sm_config_set_in_pins  (&c, 0) ;
   sm_config_set_set_pins (&c, 0, 3) ;
   pio_sm_init (pio, sm, offset, &c) ;
}

//-------------------------------------------------------------------------------------------------

void pio_charlieplexing6_set_output (PIO pio, uint sm, const uint32_t inValue) {
  uint configuration = 0x05 | (0x3 << 9) | (0x6 << 18) ;
  if ((inValue & 1) != 0) {
    configuration |= 1 << 3 ;
  }
  if ((inValue & 2) != 0) {
    configuration |= 4 << 6 ;
  }
  if ((inValue & 4) != 0) {
    configuration |= 1 << 12 ;
  }
  if ((inValue & 8) != 0) {
    configuration |= 2 << 15 ;
  }
  if ((inValue & 16) != 0) {
    configuration |= 2 << 21 ;
  }
  if ((inValue & 32) != 0) {
    configuration |= 4 << 24 ;
  }
  pio_sm_put_blocking (pio, sm, configuration) ;
}

//-------------------------------------------------------------------------------------------------

// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// -------------- //
// charlieplexing //
// -------------- //

#define charlieplexing_wrap_target 0
#define charlieplexing_wrap 26

static const uint16_t charlieplexing_program_instructions[] = {
            //     .wrap_target
    0x8080, //  0: pull   noblock                    
    0xa027, //  1: mov    x, osr                     
    0xe000, //  2: set    pins, 0                    
    0xe085, //  3: set    pindirs, 5                 
    0x6083, //  4: out    pindirs, 3                 
    0x6003, //  5: out    pins, 3                    
    0xe05f, //  6: set    y, 31                      
    0x1f87, //  7: jmp    y--, 7                 [31]
    0x6003, //  8: out    pins, 3                    
    0xe05f, //  9: set    y, 31                      
    0x1f8a, // 10: jmp    y--, 10                [31]
    0xe000, // 11: set    pins, 0                    
    0xe083, // 12: set    pindirs, 3                 
    0x6003, // 13: out    pins, 3                    
    0xe05f, // 14: set    y, 31                      
    0x1f8f, // 15: jmp    y--, 15                [31]
    0x6003, // 16: out    pins, 3                    
    0xe05f, // 17: set    y, 31                      
    0x1f92, // 18: jmp    y--, 18                [31]
    0xe000, // 19: set    pins, 0                    
    0xe086, // 20: set    pindirs, 6                 
    0x6003, // 21: out    pins, 3                    
    0xe05f, // 22: set    y, 31                      
    0x1f97, // 23: jmp    y--, 23                [31]
    0x6003, // 24: out    pins, 3                    
    0xe05f, // 25: set    y, 31                      
    0x1f9a, // 26: jmp    y--, 26                [31]
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program charlieplexing_program = {
    .instructions = charlieplexing_program_instructions,
    .length = 27,
    .origin = -1,
};

static inline pio_sm_config charlieplexing_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + charlieplexing_wrap_target, offset + charlieplexing_wrap);
    return c;
}
#endif


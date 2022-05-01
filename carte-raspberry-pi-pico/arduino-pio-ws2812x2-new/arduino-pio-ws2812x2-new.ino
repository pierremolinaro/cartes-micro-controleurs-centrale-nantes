#ifndef ARDUINO_RASPBERRY_PI_PICO
  #error Sélectionner la carte "Raspberry Pi Pico"
#endif

//-------------------------------------------------------------------------------------------------

//#include <LiquidCrystal.h>

#include "pio-ws2812x2.h"

//-------------------------------------------------------------------------------------------------

//static LiquidCrystal lcd (19, 18, 14, 15, 16, 17) ; // RS, E, D4, D5, D6, D7

//-------------------------------------------------------------------------------------------------

static void pwm_program_init (const PIO inPIO,
                              const uint32_t inStateMachine,
                              const uint32_t inProgramOffset,
                              const uint32_t inPin) {
//--- Configuration à partir du code et de l'offset de l'emplacement du code
  pio_sm_config configuration = ws2812x2_program_get_default_config (inProgramOffset) ;
//--- Fixer les ports qui sont commandés en sortie par l'instruction 'out' : ici 1 pin à partir de inPin
  sm_config_set_out_pins (&configuration, inPin, 1) ;
//--- Fixer les ports de sortie qui sont affectés par l'instruction 'set' : ici 1 pin à partir de inPin
  sm_config_set_set_pins (&configuration, inPin, 1) ;
//--- Affecter à inPin la fonction 'alternate' PIO, c'est-à-dire que le PIO contrôle ce port
  pio_gpio_init (inPIO, inPin) ;
//--- Configure en entrée (dernier paramètre: false) ou en sortie (dernier paramètre : true)
//    un nombre n (avant-dernier paramètre, ici 1) ports consécutifs à partir de inPin
  pio_sm_set_consecutive_pindirs (inPIO, inStateMachine, inPin, 1, true) ;
//--- Condifure l'effet de l'instruction 'out' :
//      2e paramètre : false -> shift left, true -> shift right
//      3e paramètre : false -> pas d'autopull, true -> autopull
//      4e paramètre : seuil du 'pull' dans OSR : 0 -> quand il est vide
  sm_config_set_out_shift (&configuration, false, false, 0) ; // Shift left, pas d'autopull, seuil 0
//--- Fixer la fréquence de l'horloge de la machine d'états
  const uint32_t machineFrequency = 25 * 1000 * 1000 ; // 25 MHz
  uint32_t divisor = RP2040::f_cpu () / machineFrequency ;
  uint32_t frac = (256 * machineFrequency * (RP2040::f_cpu () % machineFrequency)) / machineFrequency ;
  if (divisor >= 0x10000) {
    divisor = 0 ;
    frac = 0 ;
  }
  sm_config_set_clkdiv_int_frac (&configuration, uint16_t (divisor), uint8_t (frac)) ;
//--- Initialiser la machine d'état avec la configuration
  pio_sm_init (inPIO, inStateMachine, inProgramOffset, &configuration) ;
//--- Démarrer la machine d'états
  pio_sm_set_enabled (inPIO, inStateMachine, true) ;
//    lcd.setCursor (0, 2) ;
//    lcd.print (divisor) ;
//    lcd.print (" ") ;
//    lcd.print (frac) ;
}

//-------------------------------------------------------------------------------------------------

static void pio_ws2812_set_output (const PIO inPIO,
                                   const uint32_t inStateMachine,
                                   const uint8_t inRed,
                                   const uint8_t inGreen,
                                   const uint8_t inBlue) {
//--- Value to be sent
// Bits 7-0: unused, any value
// Bits 15-8: blue, reverse order
// Bits 23-16: red, reverse order
// Bits 31-24: green, reverse order
  uint32_t value = uint32_t (inBlue) << 8 ;
  value |= uint32_t (inRed) << 16 ;
  value |= uint32_t (inGreen) << 24 ;
  pio_sm_put_blocking (inPIO, inStateMachine, value) ;
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
  const uint32_t outputPin = 22 ;
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
    gCouleur &= 0x3F ; // Limitation de l'amplitude
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

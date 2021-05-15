#ifndef ARDUINO_RASPBERRY_PI_PICO
  #error Sélectionner la carte "Raspberry Pi Pico"
#endif

#include <hardware/structs/systick.h>
#include <hardware/structs/iobank0.h>
#include <hardware/structs/psm.h>
#include <hardware/structs/syscfg.h>
#include <hardware/structs/resets.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd (19, 18, 14, 15, 16, 17); // RS, E, D4, D5, D6, D7

static volatile uint32_t gCount = 0 ;

static void isr (void) {
  gCount ++ ; 
}

void setup() {
  Serial.println ("Hello") ;
  lcd.begin (20,4) ;
  lcd.print ("Hello") ;
  pinMode (LED_BUILTIN, OUTPUT) ;
  pinMode (8, OUTPUT) ;
  pinMode (13, INPUT_PULLUP) ;
  attachInterrupt (13, isr, FALLING) ;
  Serial.begin (115200) ;
  while (!Serial) {
    delay (50) ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN));
  }
  Serial.print ("padsbank0_hw->io ") ;
  Serial.println (padsbank0_hw->io [13], HEX) ;
  Serial.print ("sio_hw->gpio_oe ") ;
  Serial.println (sio_hw->gpio_oe, HEX) ;
  Serial.print ("iobank0_hw->io [13].ctrl ") ;
  Serial.println (iobank0_hw->io [13].ctrl, HEX) ;
  Serial.print ("iobank0_hw->proc0_irq_ctrl.inte [13 / 8] ") ;
  Serial.println (iobank0_hw->proc0_irq_ctrl.inte [13 / 8], HEX) ; 
  Serial.print ("resets_hw->reset_done ") ;
  Serial.println (resets_hw->reset_done, HEX) ;
}

static volatile uint32_t & SIO_GPIO_OUT_SET __attribute__((unused)) = * ((volatile uint32_t *) (0xD0000000 + 20)) ;
static volatile uint32_t & SIO_GPIO_OUT_CLR __attribute__((unused)) = * ((volatile uint32_t *) (0xD0000000 + 24)) ;
static volatile uint32_t & SIO_GPIO_IN __attribute__((unused)) = * ((volatile uint32_t *) (0xD0000000 + 4)) ;
#define SCB_VTOR (* ((volatile uint32_t *) (0xE0000000 + 0xED08)))
#define SCB_ISER (* ((volatile uint32_t *) (0xE000E100)))
#define NVIC_IPR(idx) (* ((volatile uint32_t *) (0xE000E400 + 4 * (idx))))

void loop() {
  digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  digitalWrite (8, !digitalRead (13)) ;
  lcd.setCursor (0, 1) ;
  lcd.print (millis ()) ;
  lcd.setCursor (0, 2) ;
  lcd.print (gCount) ;
//  Serial.print ("SCB_ISER ") ;
//  Serial.println (SCB_ISER, HEX) ;
//  Serial.print ("PROC0_NMI_MASK ") ;
//  Serial.println (syscfg_hw->proc0_nmi_mask, HEX) ;
//  for (uint32_t i=0 ; i<8 ; i++) {
//    Serial.print ("NVIC_IPR") ;
//    Serial.print (i) ;
//    Serial.print (" ") ;
//    Serial.println (NVIC_IPR (i), HEX) ;
//  }

  delay(99);               // wait for a second


  delay(399);               // wait for a second
//  const uint32_t cvr = systick_hw->cvr ;
//  Serial.print ("SYSTICK ") ;
//  Serial.println (cvr) ;
//  const uint32_t cpuid = sio_hw->cpuid ;
//  Serial.print ("CPUID ") ;
//  Serial.println (cpuid) ;
//  Serial.println (SCB_VTOR, HEX) ;
}

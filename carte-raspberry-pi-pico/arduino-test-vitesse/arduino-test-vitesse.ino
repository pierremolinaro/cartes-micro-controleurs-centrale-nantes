#ifndef ARDUINO_RASPBERRY_PI_PICO
  #error Sélectionner la carte "Raspberry Pi Pico"
#endif

//-------------------------------------------------------------------------------------------------

#include <LiquidCrystal.h>
#include <hardware/structs/systick.h>

//-------------------------------------------------------------------------------------------------

static LiquidCrystal lcd (19, 18, 14, 15, 16, 17) ; // RS, E, D4, D5, D6, D7

//-------------------------------------------------------------------------------------------------

class T {
  public: volatile uint8_t mAccumulator ;
  public: volatile uint8_t mSpeed ;
} ;

static T gTab [32] ;

//-------------------------------------------------------------------------------------------------

static uint32_t updateTab (void) {
  uint32_t result = 0 ;
  for (uint32_t i=0 ; i<32 ; i++) {
    result <<= 1 ;
    const uint32_t oldAcc = gTab [i].mAccumulator ;
    const uint32_t newAcc = oldAcc + gTab [i].mSpeed ;
    gTab [i].mAccumulator = uint8_t (newAcc) ;
    result |= (newAcc >> 8) ;
  }
  return result ;
}

//-------------------------------------------------------------------------------------------------

void setup() {
  Serial.println ("Hello") ;
  lcd.begin (20,4) ;
  lcd.print ("Hello") ;
  pinMode (LED_BUILTIN, OUTPUT) ;
  systick_hw->rvr = 125 * 1000 - 1 ; // Underflow every ms
  systick_hw->cvr = 0 ;
  systick_hw->csr = M0PLUS_SYST_CSR_CLKSOURCE_BITS | M0PLUS_SYST_CSR_ENABLE_BITS ;
  for (uint32_t i=0 ; i<32 ; i++) {
    gTab [i].mSpeed = i+3 ;
  }
}

//-------------------------------------------------------------------------------------------------

static uint32_t gDeadline = 0 ;

//-------------------------------------------------------------------------------------------------

void loop() {
  if (gDeadline < millis ()) {
    gDeadline += 1000 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
    lcd.setCursor (0, 1) ;
    lcd.print (gDeadline) ;
    const uint32_t start = systick_hw->cvr ;
    const uint32_t result = updateTab () ;
    const uint32_t end = systick_hw->cvr ;
    const uint32_t duration = start - end ;
    lcd.setCursor (0, 2) ;
    lcd.print ("                ") ;
    lcd.setCursor (0, 2) ;
    lcd.print (float (duration) / 125.0) ;
    lcd.setCursor (0, 3) ;
    lcd.print ("                ") ;
    lcd.setCursor (0, 3) ;
    lcd.print (result, HEX) ;
   }
}

//-------------------------------------------------------------------------------------------------

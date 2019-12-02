
#ifndef ARDUINO_MH_ET_LIVE_ESP32MINIKIT
  #error "Ce croquis doit être compilé pour MH ET LIVE ESP32Minikit"
#endif

// include the library code:
#include <LiquidCrystal.h>

const byte L0 =  21 ;
const byte L1 =  12 ; // TDI


const byte P0 = 36 ;
const byte ENCODER_CLIC = 39 ; // SVN
const byte ENCODER_B = 35 ;
const byte ENCODER_A = 34 ;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const byte rs = 22 ;
const byte en = 13 ; // TCK
const byte d4 = 15 ; // TDO
const byte d5 = 14 ; // TMS
const byte d6 = 0 ;
const byte d7 = 33 ;

LiquidCrystal lcd (rs, en, d4, d5, d6, d7) ;

void setup() {
//--- Leds
  pinMode (LED_BUILTIN, OUTPUT) ;
  pinMode (L0, OUTPUT) ;
  pinMode (L1, OUTPUT) ;
//--- Poussoirs
  pinMode (P0, INPUT) ;
  pinMode (ENCODER_CLIC, INPUT) ;
  pinMode (ENCODER_A, INPUT) ;
  pinMode (ENCODER_B, INPUT) ;
 // set up the LCD's number of columns and rows:
  lcd.begin (20, 4) ;
  // Print a message to the LCD.
  lcd.print ("hello, world!");
}

static uint32_t gLedBuiltinBlinkDate ;
static uint32_t gLedL1BlinkDate ;
static uint32_t gDisplayDate ;

void loop() {
  if (gLedBuiltinBlinkDate <= millis ()) {
    gLedBuiltinBlinkDate += 1001 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
  if (gLedL1BlinkDate <= millis ()) {
    gLedL1BlinkDate += 999 ;
    digitalWrite (L1, !digitalRead (L1)) ;
  }
  digitalWrite (L0, !digitalRead (P0)) ;
 // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  if (gDisplayDate <= millis ()) {
    gDisplayDate += 500 ;
    lcd.setCursor (0, 1);
    lcd.print (millis() / 1000);
  }
}

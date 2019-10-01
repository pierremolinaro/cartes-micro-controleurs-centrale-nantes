
#ifndef ARDUINO_MH_ET_LIVE_ESP32MINIKIT
  #error "Ce croquis doit être compilé pour MH ET LIVE ESP32Minikit"
#endif

// include the library code:
//#include <LiquidCrystal.h>

const byte L0 =  3 ;
const byte L1 =  1 ;
const byte L2 = 22 ;
const byte L3 = 23 ;
const byte L4 = 12 ;


const byte P0 = 36 ;
const byte P1 = 13 ;
const byte P2 = 11 ;
const byte P3 = 35 ;
const byte P4 = 34 ;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const byte rs = 9 ;
const byte en = 8 ;
const byte d0 = 0 ;
const byte d1 = 1 ;
const byte d2 = 2 ;
const byte d3 = 3 ;
const byte d4 = 4 ;
const byte d5 = 5 ;
const byte d6 = 6 ;
const byte d7 = 7 ;
//LiquidCrystal lcd (rs, en, d0, d1, d2, d3, d4, d5, d6, d7) ;
//LiquidCrystal lcd (rs, en, d4, d5, d6, d7) ;

void setup() {
//--- Leds
  pinMode (L0, OUTPUT) ;
  pinMode (L1, OUTPUT) ;
  pinMode (L2, OUTPUT) ;
  pinMode (L3, OUTPUT) ;
  pinMode (L4, OUTPUT) ;
//--- Poussoirs
  pinMode (P0, INPUT_PULLUP) ;
  pinMode (P1, INPUT_PULLUP) ;
  pinMode (P2, INPUT_PULLUP) ;
  pinMode (P3, INPUT_PULLUP) ;
  pinMode (P4, INPUT_PULLUP) ;
  // set up the LCD's number of columns and rows:
 // lcd.begin (20, 4);
  // Print a message to the LCD.
//  lcd.print("hello, world!");
}

void loop() {
  digitalWrite (L0, !digitalRead (P0)) ;
  digitalWrite (L1, !digitalRead (P1)) ;
  digitalWrite (L2, !digitalRead (P2)) ;
  digitalWrite (L3, !digitalRead (P3)) ;
  digitalWrite (L4, !digitalRead (P4)) ;
 // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
//  lcd.setCursor (0, 1);
  // print the number of seconds since reset:
//  lcd.print (millis() / 1000);
}

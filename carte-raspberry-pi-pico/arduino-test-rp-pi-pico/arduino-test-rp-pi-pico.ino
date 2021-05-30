#ifndef ARDUINO_RASPBERRY_PI_PICO
  #error Sélectionner la carte "Raspberry Pi Pico"
#endif

//-------------------------------------------------------------------------------------------------

#include <LiquidCrystal.h>

//-------------------------------------------------------------------------------------------------

static LiquidCrystal lcd (19, 18, 14, 15, 16, 17) ; // RS, E, D4, D5, D6, D7

//-------------------------------------------------------------------------------------------------

void setup() {
  Serial.println ("Hello") ;
  lcd.begin (20,4) ;
  lcd.print ("Hello") ;
  pinMode (LED_BUILTIN, OUTPUT) ;
  pinMode (26, OUTPUT) ;
  pinMode (27, OUTPUT) ;
  pinMode ( 4, OUTPUT) ;
  pinMode ( 5, OUTPUT) ;
  pinMode ( 6, OUTPUT) ;
  pinMode ( 7, OUTPUT) ;
  pinMode ( 8, OUTPUT) ;
  pinMode ( 9, INPUT_PULLUP) ;
  pinMode (10, INPUT_PULLUP) ;
  pinMode (11, INPUT_PULLUP) ;
  pinMode (12, INPUT_PULLUP) ;
  pinMode (13, INPUT_PULLUP) ;
}

//-------------------------------------------------------------------------------------------------

static uint32_t gT1 = 0 ;
static uint32_t gT2 = 0 ;
static uint32_t gT3 = 0 ;

//-------------------------------------------------------------------------------------------------

void loop() {
  if (gT1 < millis ()) {
    gT1 += 1000 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
    lcd.setCursor (0, 1) ;
    lcd.print (gT1) ;
  }
  if (gT2 < millis ()) {
    gT2 += 1001 ;
    digitalWrite (26, !digitalRead (26)) ;
  }
  if (gT3 < millis ()) {
    gT3 += 991 ;
    digitalWrite (27, !digitalRead (27)) ;
  }
  digitalWrite (8, !digitalRead (13)) ;
  digitalWrite (7, !digitalRead (12)) ;
  digitalWrite (6, !digitalRead (11)) ;
  digitalWrite (5, !digitalRead (10)) ;
  digitalWrite (4, !digitalRead ( 9)) ;
}

//-------------------------------------------------------------------------------------------------

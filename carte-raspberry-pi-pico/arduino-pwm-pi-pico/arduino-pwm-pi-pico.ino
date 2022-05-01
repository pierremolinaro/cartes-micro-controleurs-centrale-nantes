#ifndef ARDUINO_RASPBERRY_PI_PICO
  #error Sélectionner la carte "Raspberry Pi Pico"
#endif

//-------------------------------------------------------------------------------------------------

#include <LiquidCrystal.h>
#include <hardware/structs/systick.h>

//-------------------------------------------------------------------------------------------------

static LiquidCrystal lcd (19, 18, 14, 15, 16, 17) ; // RS, E, D4, D5, D6, D7

//-------------------------------------------------------------------------------------------------

void setup() {
  lcd.begin (20,4) ;
  lcd.print ("Hello") ;
  pinMode (LED_BUILTIN, OUTPUT) ;
}

//-------------------------------------------------------------------------------------------------

static uint32_t gDeadline = 0 ;
static uint8_t gPWM = 0 ;

//-------------------------------------------------------------------------------------------------

void loop () {
  if (gDeadline <= millis ()) {
    gDeadline += 1000 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
    lcd.setCursor (0, 1) ;
    lcd.print (millis ()) ;
    lcd.setCursor (0, 2) ;
    lcd.print (gPWM) ;
    lcd.print ("  ") ;
    analogWrite (0, gPWM) ; // Point de touche MISO
    analogWrite (26, gPWM) ; // led Activité 0, Environ 998 Hz
    gPWM += 1 ;
   }
}

//-------------------------------------------------------------------------------------------------

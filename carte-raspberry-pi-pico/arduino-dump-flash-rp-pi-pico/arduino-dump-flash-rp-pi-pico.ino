#ifndef ARDUINO_RASPBERRY_PI_PICO
  #error Sélectionner la carte "Raspberry Pi Pico"
#endif

//-------------------------------------------------------------------------------------------------

//#include <LiquidCrystal.h>

//-------------------------------------------------------------------------------------------------

//static LiquidCrystal lcd (19, 18, 14, 15, 16, 17) ; // RS, E, D4, D5, D6, D7

//-------------------------------------------------------------------------------------------------

void setup () {
  pinMode (LED_BUILTIN, OUTPUT) ;
  Serial.begin (115200) ;
  while (!Serial) {
    delay (50) ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
  Serial.println ("Hello") ;
//  lcd.begin (20,4) ;
//  lcd.print ("Hello") ;
  uint32_t address = 0x1000'0000 + 4096 * 128 + 0x12B00 ;
  for (uint32_t line=0 ; line < 32 ; line++) {
    Serial.print (address, HEX) ;
    for (uint32_t col=0 ; col<16 ; col++) {
      #define ADDR *((volatile uint8_t *) (address + col))
      const uint8_t v = ADDR ;
      Serial.print (" ") ;
      Serial.print (v, HEX) ;
    }
    Serial.println () ;
    address += 16 ;
  }
}

//-------------------------------------------------------------------------------------------------

static uint32_t gT1 = 0 ;

//-------------------------------------------------------------------------------------------------

void loop () {
  if (gT1 < millis ()) {
    gT1 += 1000 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
//    lcd.setCursor (0, 1) ;
//    lcd.print (gT1) ;
  }
}

//-------------------------------------------------------------------------------------------------

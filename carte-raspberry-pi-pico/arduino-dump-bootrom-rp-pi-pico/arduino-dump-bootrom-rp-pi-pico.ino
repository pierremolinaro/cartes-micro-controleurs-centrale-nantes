#ifndef ARDUINO_RASPBERRY_PI_PICO
  #error Sélectionner la carte "Raspberry Pi Pico"
#endif

//-------------------------------------------------------------------------------------------------

#include <LiquidCrystal.h>

//-------------------------------------------------------------------------------------------------

static LiquidCrystal lcd (19, 18, 14, 15, 16, 17) ; // RS, E, D4, D5, D6, D7

//-------------------------------------------------------------------------------------------------

#define ADDR(address) *((volatile uint8_t *) (address))

//-------------------------------------------------------------------------------------------------

static void printFunctionLookupTableFromAddress (const uint32_t inTableAddress) {
  uint32_t address = inTableAddress ;
  bool endReached = false ;
  while (!endReached) {
    const uint32_t tag = (ADDR (address + 1) << 8) | ADDR (address) ;
    endReached = tag == 0 ;
    if (!endReached) {
      Serial.print ("  At 0x") ; Serial.print (address, HEX) ; Serial.print (": code ") ;
      Serial.print (char (ADDR (address))) ;
      address += 1 ;
      Serial.print (char (ADDR (address))) ;
      address += 1 ;
      Serial.print (", entry point 0x") ;
      uint32_t entryPoint = ADDR (address + 1) ;
      entryPoint <<= 8 ;
      entryPoint |= ADDR (address + 0) ;
      Serial.println (entryPoint, HEX) ;
      address += 2 ;
    }
  }
}

//-------------------------------------------------------------------------------------------------

void setup () {
  lcd.begin (20,4) ;
  lcd.print ("Hello") ;
  pinMode (LED_BUILTIN, OUTPUT) ;
  Serial.begin (115200) ;
  while (!Serial) {
    delay (50) ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
  Serial.println ("Dump bootrom") ;
  uint32_t address = 0x0 ;
  for (uint32_t line=0 ; line < 10 ; line++) {
    Serial.print ("  At 0x") ; Serial.print (address, HEX) ; Serial.print (":") ;
    for (uint32_t col=0 ; col<16 ; col++) {
      Serial.print (" ") ;
      Serial.print (ADDR (address + col), HEX) ;
    }
    Serial.println () ;
    address += 16 ;
  }
  address = 0x10 ;
  Serial.print ("At 0x") ; Serial.print (address, HEX) ; Serial.print (", magic: 0x") ; Serial.println (char (ADDR (address)), HEX) ;
  address += 1 ;
  Serial.print ("At 0x") ; Serial.print (address, HEX) ; Serial.print (", magic: 0x") ; Serial.println (char (ADDR (address)), HEX) ;
  address += 1 ;
  Serial.print ("At 0x") ; Serial.print (address, HEX) ; Serial.print (", magic: 0x") ; Serial.println (ADDR (address), HEX) ;
  address += 1 ;
  Serial.print ("At 0x") ; Serial.print (address, HEX) ; Serial.print (", bootrom version: ") ; Serial.println (ADDR (address), HEX) ;
//--- Public function lookup table
  uint32_t publicFunctionLookupTable = ADDR (0x15) ;
  publicFunctionLookupTable <<= 8 ;
  publicFunctionLookupTable |= ADDR (0x14) ;
  Serial.print ("At 0x14, public function lookuptable: 0x") ; Serial.println (publicFunctionLookupTable, HEX) ;
//--- Helper function lookup table
  uint32_t helperFunctionLookupTable = ADDR (0x19) ;
  helperFunctionLookupTable <<= 8 ;
  helperFunctionLookupTable |= ADDR (0x18) ;
  Serial.print ("At 0x18, helper function lookuptable: 0x") ; Serial.println (helperFunctionLookupTable, HEX) ;
  Serial.println ("Public function lookuptable") ;
  printFunctionLookupTableFromAddress (publicFunctionLookupTable) ;
}

//-------------------------------------------------------------------------------------------------

static uint32_t gT1 = 0 ;

//-------------------------------------------------------------------------------------------------

void loop () {
  if (gT1 < millis ()) {
    gT1 += 1000 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
    lcd.setCursor (0, 1) ;
    lcd.print (gT1) ;
  }
}

//-------------------------------------------------------------------------------------------------


#include "sram-externe.h"

//--------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin (115200) ;
  while (!Serial) {}
  pinMode (PE1, OUTPUT) ;
  configurerAccesRamExterne () ;
}

//--------------------------------------------------------------------------------------------------

static uint32_t gEcheance = 0 ;

void loop() {
  if (gEcheance < millis ()) {
    gEcheance += 1000 ;
    digitalWrite (PE1, !digitalRead (PE1)) ;
    ecritureRamExterne (0x12) ;
  }
}

//--------------------------------------------------------------------------------------------------

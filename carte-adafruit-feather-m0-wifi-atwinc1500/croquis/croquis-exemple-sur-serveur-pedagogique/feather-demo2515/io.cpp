#include "io.h"

//———————————————————————————————————————————————————————

void beginIO (void) {
  Serial1.begin (19200) ;
}

//———————————————————————————————————————————————————————

void ledWrite (const byte inLed, const bool inLevel) {
  Serial1.write ((inLed & 3) | (inLevel ? 4 : 0)) ;
}

//———————————————————————————————————————————————————————

static byte gButtons = 0 ;
static byte gEncoderValue = 0 ;

//———————————————————————————————————————————————————————

static void updateInputs (void) {
  while (Serial1.available ()) {
    const byte v = Serial1.read () ;
    gButtons = v & 0x0F ;
    if ((v & 0x30) == 0x10) {
      if (gEncoderValue < 63) {
        gEncoderValue ++ ;
      }
    }else if ((v & 0x30) == 0x20) {
      if (gEncoderValue > 0) {
        gEncoderValue -- ;
      }
    }
  }
}

//———————————————————————————————————————————————————————

bool pushButton (const byte inButton) {
  updateInputs () ;
  return (gButtons & (1 << inButton)) != 0 ;
}

//———————————————————————————————————————————————————————

byte encoderValue (void) {
  return gEncoderValue ;
}

//———————————————————————————————————————————————————————


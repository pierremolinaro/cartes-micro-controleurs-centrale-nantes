// D'abord les inclusions système (ordre quelconque)
#include <ACAN.h>
#include <LiquidCrystal.h>

// Ensuite les inclusions utilisateur
#include "tp_sysit_teensy36.h"

//-----------------------------------------------------------------

LiquidCrystal lcd (18, 17, 16, 15, 14, 19) ;

//-----------------------------------------------------------------

void setup () {
  pinMode (LED_BUILTIN, OUTPUT) ;
  lcd.begin (20,4) ;
//--- Configuration du pilote ACAN
  ACANSettings settings (125 * 1000) ; // 125 kbit/s
  settings.mUseAlternateTxPin = true ; // Obligatoire pour can0 sur la carte de TP
  settings.mUseAlternateRxPin = true ; // Obligatoire pour can0 sur la carte de TP
  settings.mLoopBackMode = true ; // Pour fonctionner en "loop back"
  settings.mSelfReceptionMode = true ; // Pour fonctionner en "loop back"
  const uint32_t codeErreur = ACAN::can0.begin (settings) ;
  if (0 == codeErreur) {
    lcd.print ("can0 ok") ;
  }else{
    lcd.print ("Error can0: 0x") ;
    lcd.print (codeErreur, HEX) ;
  }
  lcd.setCursor (0, 1) ;
  lcd.print ("Sent:") ;
  lcd.setCursor (0, 2) ;
  lcd.print ("Received:") ;
}

//-----------------------------------------------------------------

static unsigned gSendDate = 0 ;
static unsigned gSentCount = 0 ;
static unsigned gReceivedCount = 0 ;
static unsigned gToggleLedDate = 0 ;

//-----------------------------------------------------------------

void loop () {
  if (gToggleLedDate <= millis ()) {
    gToggleLedDate += 500 ;
    digitalWrite (LED_BUILTIN, ! digitalRead (LED_BUILTIN)) ;
  }
  CANMessage message ;
  if (gSendDate <= millis ()) {
    message.id = 0x542 ;
    const bool ok = ACAN::can0.tryToSend (message) ;
    if (ok) {
      gSendDate += 2000 ;
      gSentCount += 1 ;
      lcd.setCursor (6, 1) ;
      lcd.print (gSentCount) ;
    }
  }
  if (ACAN::can0.receive (message)) {
    gReceivedCount += 1 ;
    lcd.setCursor (10, 2) ;
    lcd.print (gReceivedCount) ;
  }
}


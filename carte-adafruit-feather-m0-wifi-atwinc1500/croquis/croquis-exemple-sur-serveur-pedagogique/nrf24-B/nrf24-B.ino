// First, system inclusions
#include <LiquidCrystal.h>
#include <RF24.h>

// Then, user inclusions
#include "tp_sysit_teensy36.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

LiquidCrystal lcd (18, 17, 16, 15, 14, 19) ; // For using LCD

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

RF24 gRadio (24, 25) ; // CE_PIN, CSN_PIN
const byte OTHER_ADDRESS [5] = {0x12, 0x34, 0x56, 0x78, 0x90} ;
const byte MY_ADDRESS [5] = {0xFE, 0xDC, 0xBA, 0x98, 0x76} ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void setup () {
  pinMode (LED_BUILTIN, OUTPUT) ;
  lcd.begin (20,4) ; // 20 columns (0 ... 19), 4 lines (0 ... 3)
//---- radio
// https://www.pjrc.com/teensy/td_libs_SPI.html
// Use SPI alternate pins; should be done before calling radio.begin().
  SPI.setMOSI (28) ;
  SPI.setMISO (39) ;
  SPI.setSCK (27) ;
//--- Radio module configuration
  bool ok = gRadio.begin () ;
  if (!ok) {
    lcd.print ("Radio err") ;
  }
  if (ok) {
  //--- Set emission power: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
    gRadio.setPALevel (RF24_PA_MAX) ;
  //--- Set speed: RF24_250KBPS, RF24_1MBPS (default), RF24_2MBPS
  //   gRadio.setDataRate (RF24_2MBPS) ;
  //--- Set channel: frequency is 2400 MHz + n, with 0 <= n <= 125
    gRadio.setChannel (108) ; // 2,508 GHz
  //--- Open communication pipes
    gRadio.openWritingPipe (MY_ADDRESS);
    gRadio.openReadingPipe (1, OTHER_ADDRESS);
  //--- Start the radio listening for data
    gRadio.startListening () ;
    lcd.print ("B -> A") ;
    lcd.setCursor (0, 2) ;
    lcd.print ("Rcvd:");
    lcd.setCursor (0, 3) ;
    lcd.print ("Sent:");
  }
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static unsigned gNRF24ReceiveCount = 0 ;
static unsigned gNRF24SentCount = 0 ;
static unsigned gLedToggleTime = 0 ;
static unsigned gBroadcastTime = 3000 ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void loop () {
//--- Blink led and display
  if (gLedToggleTime <= millis ()) {
    gLedToggleTime += 500 ;
    digitalWrite (LED_BUILTIN, ! digitalRead (LED_BUILTIN)) ;
    lcd.setCursor (7, 2) ;
    lcd.print (gNRF24ReceiveCount);
    lcd.setCursor (7, 3) ;
    lcd.print (gNRF24SentCount);
  }
//--- Broadcast
  if (gBroadcastTime <= millis ()) {
    gRadio.stopListening () ; // First, stop listening so we can talk.
    byte buffer [32] ;
    if (gRadio.write (buffer, 32)) {
      gNRF24SentCount += 1 ;
    }
    gRadio.startListening () ; // Now, continue listening
    gBroadcastTime = millis () + 1000 ;
  }
//--- Réception de données
  if (gRadio.available ()) {
    byte buffer [10] ;
    gRadio.read (buffer, 10) ;
    gNRF24ReceiveCount += 1 ;
    lcd.setCursor (0, 1) ;
    lcd.print (gRadio.testRPD() ? "Good signal" : "Weak signal") ;
  }
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


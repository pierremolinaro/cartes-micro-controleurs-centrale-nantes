
//——————————————————————————————————————————————————————————————————————————————
//  ACAN2517 Demo, using SPI1
//——————————————————————————————————————————————————————————————————————————————

#include <ACAN2517.h>
#include <LiquidCrystal.h>

//——————————————————————————————————————————————————————————————————————————————
//  MCP2517FD connections: adapt theses settings to your design
//  As hardware SPI is used, you should select pins that support SPI functions.
//  This sketch is designed for a Teensy 3.5, using SPI1
//  But standard Teensy 3.5 SPI1 pins are not used
//    SCK input of MCP2517 is connected to pin #32
//    SDI input of MCP2517 is connected to pin #0
//    SDO output of MCP2517 is connected to pin #1
//  CS input of MCP2517 should be connected to a digital output port
//——————————————————————————————————————————————————————————————————————————————

static const byte MCP2517_SCK = 32 ; // SCK input of MCP2517
static const byte MCP2517_SDI =  0 ; // SDI input of MCP2517
static const byte MCP2517_SDO =  1 ; // SDO output of MCP2517

static const byte MCP2517_CS  = 31 ; // CS input of MCP2517
static const byte MCP2517_INT = 38 ; // INT output of MCP2517

//——————————————————————————————————————————————————————————————————————————————
//  ACAN2517 Driver object
//——————————————————————————————————————————————————————————————————————————————

ACAN2517 can (MCP2517_CS, SPI1, MCP2517_INT) ;

//——————————————————————————————————————————————————————————————————————————————

LiquidCrystal lcd (18, 17, 16, 15, 14, 19) ;

//——————————————————————————————————————————————————————————————————————————————
//   SETUP
//——————————————————————————————————————————————————————————————————————————————

void setup () {
  lcd.begin (20,4) ;
  Serial.begin (38400) ;
//--- Switch on builtin led
  pinMode (3, OUTPUT) ;
  pinMode (4, OUTPUT) ;
  pinMode (5, OUTPUT) ;
  pinMode (6, OUTPUT) ;
  pinMode (7, OUTPUT) ;
  pinMode (2, INPUT_PULLUP) ;
  pinMode (LED_BUILTIN, OUTPUT) ;
  digitalWrite (LED_BUILTIN, HIGH) ;
//----------------------------------- Begin SPI1
  SPI1.begin () ;
//--- Configure ACAN2517
  ACAN2517Settings settings (ACAN2517Settings::OSC_40MHz, 1000 * 1000) ;
  settings.mDriverReceiveFIFOSize = 200 ;
//  settings.mControllerTransmitFIFOSize = 1 ;
//  settings.mControllerReceiveFIFOSize = 27 ;
//--- Begin
  const uint32_t errorCode = can.begin (settings, [] { can.isr () ; }) ;
    Serial.print ("Bit Rate prescaler: ") ;
    Serial.println (settings.mBitRatePrescaler) ;
    Serial.print ("Phase segment 1: ") ;
    Serial.println (settings.mPhaseSegment1) ;
    Serial.print ("Phase segment 2: ") ;
    Serial.println (settings.mPhaseSegment2) ;
    Serial.print ("SJW:") ;
    Serial.println (settings.mSJW) ;
    Serial.print ("Actual Bit Rate: ") ;
    Serial.print (settings.actualBitRate ()) ;
    Serial.println (" bit/s") ;
    Serial.print ("Exact Bit Rate ? ") ;
    Serial.println (settings.exactBitRate () ? "yes" : "no") ;
    Serial.print ("Sample point: ") ;
    Serial.print (settings.samplePointFromBitStart ()) ;
    Serial.println ("%") ;
   lcd.print ("Odd 0x") ;
  lcd.print (errorCode, HEX) ;
  lcd.setCursor (0, 2) ;
  lcd.print ("Received: ") ;
  lcd.setCursor (0, 1) ;
  lcd.print ("Sent: ") ;
}

//——————————————————————————————————————————————————————————————————————————————

static uint32_t gBlinkLedDate = 0 ;
static uint32_t gReceivedFrameCount = 0 ;
static uint32_t gSentFrameCount = 0 ;
static uint32_t gStartDate = 0 ;
static uint32_t gCompleted = false ;
static const uint32_t SEND_COUNT = 50 * 1000 ;

//——————————————————————————————————————————————————————————————————————————————

static void handleReceive (void) {
  CANMessage frame ;
  while (can.receive (frame)) {
    if (gReceivedFrameCount == 0) {
      gStartDate = millis () ;
    }
    gReceivedFrameCount ++ ;
  }
}

//——————————————————————————————————————————————————————————————————————————————

void loop () {
  handleReceive () ;
  if (gBlinkLedDate < millis ()) {
    gBlinkLedDate += 1000 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
    if (! digitalRead (2)) {
      gReceivedFrameCount = 0 ;
      gSentFrameCount = 0 ;
      gCompleted = false ;
      lcd.setCursor (10, 2) ;
      handleReceive () ;
      lcd.print ("       ") ;
      handleReceive () ;
      lcd.setCursor (6, 1) ;
      handleReceive () ;
      lcd.print ("       ") ;
      handleReceive () ;
      lcd.setCursor (14, 3) ;
      handleReceive () ;
      lcd.print ("      ") ;
    }
    lcd.setCursor (6, 1) ;
    handleReceive () ;
    lcd.print (gSentFrameCount) ;
    handleReceive () ;
    lcd.setCursor (10, 2) ;
    handleReceive () ;
    lcd.print (gReceivedFrameCount) ;
    handleReceive () ;
    lcd.setCursor (0, 3) ;
    handleReceive () ;
    lcd.print ("           ") ;
    handleReceive () ;
    lcd.setCursor (0, 3) ;
    handleReceive () ;
    lcd.print (can.errorCounters (), HEX) ;
    handleReceive () ;
    lcd.print (" ") ;
    lcd.print (can.driverReceiveBufferPeakCount ()) ;
    handleReceive () ;
    lcd.print (" ") ;
    handleReceive () ;
    lcd.print (can.hardwareReceiveBufferOverflowCount ()) ;
    handleReceive () ;
  }
  if ((gReceivedFrameCount > 0) && (gSentFrameCount < SEND_COUNT)) {
    CANMessage frame ;
    frame.id = (micros () & 0x7FE) | 1 ;
    frame.len = 8 ;
    for (uint8_t i=0 ; i<frame.len ; i++) {
      frame.data [i] = i ;
    }
    const bool ok = can.tryToSend (frame) ;
    if (ok) {
      gSentFrameCount += 1 ;
    }
  }
  if (!gCompleted && (gReceivedFrameCount == SEND_COUNT) && (gSentFrameCount == SEND_COUNT)) {
    gCompleted = true ;
    lcd.setCursor (14, 3) ;
    lcd.print (millis () - gStartDate) ;
  }
}

//——————————————————————————————————————————————————————————————————————————————

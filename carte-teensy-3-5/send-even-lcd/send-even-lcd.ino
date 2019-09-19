//——————————————————————————————————————————————————————————————————————————————
//  ACAN2517 Demo
//——————————————————————————————————————————————————————————————————————————————

#include <ACAN2517.h>
#include <LiquidCrystal.h>

//——————————————————————————————————————————————————————————————————————————————
//  MCP2517 connections: adapt theses settings to your design
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
//  ACAN2517FD Driver object
//——————————————————————————————————————————————————————————————————————————————

ACAN2517 can (MCP2517_CS, SPI1, MCP2517_INT) ;

//——————————————————————————————————————————————————————————————————————————————

LiquidCrystal lcd (18, 17, 16, 15, 14, 19); //liaison 4 bits de données

//——————————————————————————————————————————————————————————————————————————————
//   SETUP
//——————————————————————————————————————————————————————————————————————————————

void setup () {
  lcd.begin (20,4) ;
  Serial.begin (38400) ;
  pinMode (2, INPUT_PULLUP) ;
  pinMode (LED_BUILTIN, OUTPUT) ;
  digitalWrite (LED_BUILTIN, HIGH) ;
//----------------------------------- Begin SPI1
  SPI1.begin () ;
//--- Configure ACAN2517FD
  ACAN2517Settings settings (ACAN2517Settings::OSC_4MHz10xPLL, 1000 * 1000) ;
  settings.mDriverReceiveFIFOSize = 300 ;
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
  lcd.print ("Even 0x") ;
  lcd.print (errorCode, HEX) ;
  lcd.setCursor (0, 1) ;
  lcd.print ("Sent: ") ;
  lcd.setCursor (0, 2) ;
  lcd.print ("Received: ") ;
}

//——————————————————————————————————————————————————————————————————————————————

static uint32_t gBlinkLedDate = 0 ;
static uint32_t gSentFrameCount = 0 ;
static uint32_t gReceivedFrameCount = 0 ;
static const uint32_t SEND_COUNT = 50 * 1000 ;

//——————————————————————————————————————————————————————————————————————————————

static void handleReceivedMessages (void) {
  CANMessage frame ;
  while (can.receive (frame)) {
    gReceivedFrameCount ++ ;
  }
}

//——————————————————————————————————————————————————————————————————————————————

void loop () {
  handleReceivedMessages () ;
  if (gBlinkLedDate < millis ()) {
    gBlinkLedDate += 1000 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
    if (! digitalRead (2)) {
      gReceivedFrameCount = 0 ;
      lcd.setCursor (10, 2) ;
      handleReceivedMessages () ;
      lcd.print ("      ") ;
      handleReceivedMessages () ;
      gSentFrameCount = 0 ;
      lcd.setCursor (6, 1) ;
      handleReceivedMessages () ;
      lcd.print ("      ") ;
      handleReceivedMessages () ;
    }
    lcd.setCursor (6, 1) ;
    handleReceivedMessages () ;
    lcd.print (gSentFrameCount) ;
    handleReceivedMessages () ;
    lcd.setCursor (10, 2) ;
    handleReceivedMessages () ;
    lcd.print (gReceivedFrameCount) ;
    handleReceivedMessages () ;
    lcd.setCursor (0, 3) ;
    handleReceivedMessages () ;
    lcd.print ("          ") ;
    handleReceivedMessages () ;
    lcd.setCursor (0, 3) ;
    handleReceivedMessages () ;
    lcd.print (can.errorCounters (), HEX) ;
    handleReceivedMessages () ;
    lcd.print (" ") ;
    handleReceivedMessages () ;
    lcd.print (can.driverReceiveBufferPeakCount ()) ;
    handleReceivedMessages () ;
  }
  if (digitalRead (2) && (gSentFrameCount < SEND_COUNT)) {
    CANMessage frame ;
    frame.id = micros () & 0x7FE ;
    frame.len = 8 ;
    for (uint8_t i=0 ; i<frame.len ; i++) {
      frame.data [i] = i ;
    }
    const bool ok = can.tryToSend (frame) ;
    if (ok) {
      gSentFrameCount += 1 ;
    }
  }
}

//——————————————————————————————————————————————————————————————————————————————

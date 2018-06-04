#include <LiquidCrystal.h>
#include <wiring_private.h>

#include "tp_sysit_feather.h"
#include "io.h"
#include "MCP2515.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

LiquidCrystal lcd (18, 17, 16, 15, 14, 19) ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

// https://learn.adafruit.com/using-atsamd21-sercom-to-add-more-spi-i2c-serial-ports/overview

SPIClass mySPI (&sercom1, 10, 12, 11, SPI_PAD_0_SCK_3, SERCOM_RX_PAD_2);

static const byte MCP2515_CS  =  6 ; // CS input of MCP2515

MCP2515 controleurCAN (mySPI, MCP2515_CS) ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void setup() {
  pinMode (LED_BUILTIN, OUTPUT);
  digitalWrite (LED_BUILTIN, HIGH) ;
  Serial.begin (9600) ;
  beginIO () ;
  lcd.begin (20, 4); // 20 colonnes et 4 lignes

  mySPI.begin () ;
  pinPeripheral (11, PIO_SERCOM);
  pinPeripheral (12, PIO_SERCOM);
  pinPeripheral (10, PIO_SERCOM);
  const uint32_t codeErreur = controleurCAN.begin (true) ;
  if (0 == codeErreur) {
    lcd.print ("can ok") ;
  }else{
    lcd.print ("Erreur 0x") ;
    lcd.print (codeErreur, HEX) ;
  }
//---
  lcd.setCursor (0, 1) ;
  lcd.print ("Sent: ") ;
  lcd.setCursor (0, 2) ;
  lcd.print ("Received: ") ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static unsigned gDateClignotement = 0 ;
static unsigned gDateEmission = 0 ;
static unsigned gNombreEmissions = 0 ;
static unsigned gNombreReceptions = 0 ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void loop () {
  if (gDateClignotement < millis ()) {
    gDateClignotement += 500 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
  CANMessage message ;
//--- Émission ?
  if (gDateEmission <= millis ()) {
    if (controleurCAN.tryToSend (message)) {
      gDateEmission += 250 ;
      gNombreEmissions ++ ;
      lcd.setCursor (6, 1) ;
      lcd.print (gNombreEmissions) ;
    }
  }
//--- Réception ?
  if (controleurCAN.receive (message)) {
    gNombreReceptions ++ ;
    lcd.setCursor (10, 2) ;
    lcd.print (gNombreReceptions) ;
  }
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————



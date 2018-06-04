#include <LiquidCrystal.h>
#include "mcp2515.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

LiquidCrystal lcd (18, 17, 16, 15, 14, 19) ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static const byte MCP2515_CS  =  6 ; // CS input of MCP2515 
static const byte MCP2515_CLK = 12 ; // CLK input of MCP2515 
static const byte MCP2515_SI  = 11 ; // SI input of MCP2515  
static const byte MCP2515_SO  = 10 ; // SO output of MCP2515 
static const byte MCP2515_IRQ =  5 ; // IRQ output of MCP2515

MCP2515 can (MCP2515_CS, MCP2515_CLK, MCP2515_SI, MCP2515_SO, MCP2515_IRQ) ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

 
void setup() {
  pinMode (LED_BUILTIN, OUTPUT);
  digitalWrite (LED_BUILTIN, HIGH) ;
  Serial.begin (9600) ;
  Serial1.begin (19200) ;
  lcd.begin (20, 4); // Utilisation d'un écran 20 colonnes et 4 lignes
  const bool ok = can.begin () ;
  lcd.print (ok ? "CAN init ok" : "CAN init error") ;
 // lcd.print (ok) ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static unsigned gBlinkLedDate ;
static unsigned gNombreTramesRecues ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void loop () {
  if (gBlinkLedDate < millis ()) {
    gBlinkLedDate += 500 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
   }
//  if (Serial1.available () > 0) {
//    const byte nouvelEtat = Serial1.read () ;
//  }
  if (can.available ()) {
    gNombreTramesRecues ++ ;
    lcd.setCursor (12, 0) ;
    lcd.print (gNombreTramesRecues) ;
    CANFrame frame ;
    can.getReceivedMessage (frame) ;
    lcd.setCursor (0, 1) ;
    lcd.print (frame.id, 16) ;
    lcd.print (" ") ;
    lcd.print (frame.ext) ;
    lcd.print (" ") ;
    lcd.setCursor (0, 2) ;
    for (unsigned i=0 ; i<frame.len ; i++) {
      lcd.print (frame.buf [i], 16) ;
      lcd.print (" ") ;
    }
  }
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


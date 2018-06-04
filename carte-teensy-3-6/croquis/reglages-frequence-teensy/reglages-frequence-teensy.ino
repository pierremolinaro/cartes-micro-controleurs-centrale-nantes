#include "LiquidCrystal.h"

LiquidCrystal lcd (18, 17, 16, 15, 14, 19); // Liaison 4 bits de données


void setup() {
  lcd.begin (20,4); // Utilisation d'un écran 20 colonnes et 4 lignes
  pinMode (13, OUTPUT) ;
  lcd.setCursor (0, 0) ;
  lcd.print ("OUTDIV: ") ;
  lcd.print (SIM_CLKDIV1 >> 16, HEX) ;
  lcd.setCursor (0, 1) ;
  lcd.print ("PRDIV: ") ;
  lcd.print (MCG_C5 & 7) ;
  lcd.setCursor (0, 2) ;
  lcd.print ("VDIV: ") ;
  lcd.print (MCG_C6 & 0x1F) ;
}

void loop() {
  digitalWrite (13, !digitalRead (13)) ;
  delay (500) ;
}

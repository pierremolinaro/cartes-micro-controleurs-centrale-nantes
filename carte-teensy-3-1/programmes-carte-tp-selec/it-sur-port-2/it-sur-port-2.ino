#include <LiquidCrystal.h>

LiquidCrystal lcd (18, 17, 16, 15, 14, 19); //liaison 4 bits de données

void setup() {
  pinMode (13, OUTPUT) ;
  pinMode (10, INPUT_PULLUP) ;
  lcd.begin(20,4); //utilisation d'un écran 20 colonnes et 4 lignes
  attachInterrupt (digitalPinToInterrupt (10), ISR, FALLING) ;
}

volatile unsigned gCompteur = 0 ;

void ISR (void) {
  gCompteur ++ ;
}

void loop() {
  delay (500) ;
  digitalWrite (13, ! digitalRead (13)) ;
  lcd.setCursor (0, 0) ;
  lcd.print (gCompteur) ;
}

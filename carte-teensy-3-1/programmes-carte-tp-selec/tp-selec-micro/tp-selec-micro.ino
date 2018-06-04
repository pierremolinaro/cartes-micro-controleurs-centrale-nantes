#include "LiquidCrystal.h"

LiquidCrystal lcd (18, 17, 16, 15, 14, 19); // Liaison 4 bits de données

void setup() {
  pinMode (13, OUTPUT) ;
  lcd.begin(20,4); // Utilisation d'un écran 20 colonnes et 4 lignes
  lcd.print ("Hello World!");
}

int gCompteur = 0 ;

void loop() {
  delay (1000) ;
  lcd.setCursor (0, 1) ; // Colonne 0, ligne 1
  lcd.print (gCompteur) ;
  gCompteur ++ ;
  digitalWrite (13, !digitalRead (13)) ; // Led Teensy
}


#include <LiquidCrystal.h>

LiquidCrystal lcd (18, 17, 16, 15, 14, 19);

void setup() {
  pinMode (13, OUTPUT) ;
  lcd.begin(20,4); //utilisation d'un écran 20 colonnes et 4 lignes
  lcd.write ("Hello!");
}

void loop() {
  delay (200) ;
  digitalWrite (13, !digitalRead (13)) ;
}


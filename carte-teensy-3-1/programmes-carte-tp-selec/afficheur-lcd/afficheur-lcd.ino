#include "LiquidCrystal.h"

LiquidCrystal lcd (18, 17, 16, 15, 14, 19); //liaison 4 bits de données

void setup() {
  pinMode (3, OUTPUT) ;
  pinMode (4, OUTPUT) ;
  pinMode (5, OUTPUT) ;
  pinMode (6, OUTPUT) ;
  pinMode (7, OUTPUT) ;
  pinMode (13, OUTPUT) ;
  lcd.begin(20,4); //utilisation d'un écran 20 colonnes et 4 lignes
  lcd.write ("Hello World!"); //petit test pour vérifier que tout marche
}

void loop() {
  delay (100) ;
  digitalWrite (3, HIGH) ;
  delay (100) ;
  digitalWrite (4, HIGH) ;
  delay (100) ;
  digitalWrite (5, HIGH) ;
  delay (100) ;
  digitalWrite (6, HIGH) ;
  delay (100) ;
  digitalWrite (7, HIGH) ;
  delay (100) ;
  digitalWrite (13, HIGH) ;
  delay (100) ;
  digitalWrite (3, LOW) ;
  delay (100) ;
  digitalWrite (4, LOW) ;
  delay (100) ;
  digitalWrite (5, LOW) ;
  delay (100) ;
  digitalWrite (6, LOW) ;
  delay (100) ;
  digitalWrite (7, LOW) ;
  delay (100) ;
  digitalWrite (13, LOW) ;
}


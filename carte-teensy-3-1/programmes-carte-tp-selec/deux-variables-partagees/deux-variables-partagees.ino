#include "TimerOne.h"
#include "LiquidCrystal.h"

LiquidCrystal lcd (18, 17, 16, 15, 14, 19); // Liaison 4 bits de données
volatile int gVariablePartagee1 = 0 ;
volatile int gVariablePartagee2 = 0 ;
volatile bool compter = true ;

void setup() {
  lcd.begin(20,4); // Utilisation d'un écran 20 colonnes et 4 lignes
  Timer1.initialize (1000) ; // 1ms
  Timer1.attachInterrupt (isr);
}

void isr () {
  if (compter) {
    gVariablePartagee1 ++ ;
    gVariablePartagee2 ++ ;
  }
}

void loop() {
 // https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html
  __atomic_fetch_add (& gVariablePartagee1, 1, __ATOMIC_ACQ_REL) ;
  __atomic_fetch_add (& gVariablePartagee2, 1, __ATOMIC_ACQ_REL) ;
//  gVariablePartagee1 ++ ;
//  gVariablePartagee2 ++ ;
  if (compter && (millis () >= 5000)) {
    compter = false ;
    lcd.setCursor (0, 0) ; // Colonne 0, ligne 0
    lcd.print (gVariablePartagee1) ;
    lcd.setCursor (0, 1) ; // Colonne 0, ligne 1
    lcd.print (gVariablePartagee2) ;
  }
}

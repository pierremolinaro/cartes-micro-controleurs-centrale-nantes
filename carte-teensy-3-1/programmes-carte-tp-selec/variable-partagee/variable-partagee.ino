#include "TimerOne.h"

volatile int gVariablePartagee = 0 ;

void setup() {
  Timer1.initialize (1000) ; // 1ms
  Timer1.attachInterrupt (isr);
  pinMode (13, OUTPUT) ;
  while (gVariablePartagee < 5000) { }
}

void isr () {
  gVariablePartagee ++ ;
}

void loop() {
  digitalWrite (13, HIGH) ;
}

#include "TimerOne.h"

void setup() {
  pinMode (5, OUTPUT) ;
  pinMode (10, INPUT_PULLUP) ;
  pinMode (13, OUTPUT) ;
  Timer1.initialize (200000) ; // 200 ms
  Timer1.attachInterrupt (isr);
}

// int delai = 0 ;

void isr () {
    digitalWrite (13, !digitalRead (13)) ;
/*  if (delai == 0) {
    delai = 100 ;
    digitalWrite (13, !digitalRead (13)) ;
  }else{
    delai -- ;
  } */
}

void loop() {
  delay (10) ; // 10 ms
  if (digitalRead (10)) {
    digitalWrite (5, LOW) ;
  }else{
    digitalWrite (5, HIGH) ;
  }
}

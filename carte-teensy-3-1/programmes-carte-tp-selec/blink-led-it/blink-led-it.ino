#include <TimerOne.h>

void setup() {
  pinMode (13, OUTPUT) ;
  Timer1.initialize (1000) ; // 1ms
  Timer1.attachInterrupt (isr);
}

int delai = 0 ;

void isr () {
  if (delai == 0) {
    delai = 100 ;
    digitalWrite (13, !digitalRead (13)) ;
  }else{
    delai -- ;
  }
}

void loop() {
}

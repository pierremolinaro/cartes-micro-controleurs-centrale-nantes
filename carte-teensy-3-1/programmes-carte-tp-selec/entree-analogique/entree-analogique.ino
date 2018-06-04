void setup() {
  pinMode (13, OUTPUT) ;
}

void loop() {
  delay (10) ; // 10 ms
  if (analogRead (14) > 465) {
    digitalWrite (13, HIGH) ;
  }else{
    digitalWrite (13, LOW) ;
  }
}

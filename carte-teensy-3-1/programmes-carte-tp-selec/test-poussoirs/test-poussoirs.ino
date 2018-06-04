void setup() {
  pinMode (3, OUTPUT) ;
  pinMode (4, OUTPUT) ;
  pinMode (5, OUTPUT) ;
  pinMode (6, OUTPUT) ;
  pinMode (7, OUTPUT) ;
  pinMode (13, OUTPUT) ;
  pinMode (8, INPUT_PULLUP) ;
  pinMode (9, INPUT_PULLUP) ;
  pinMode (10, INPUT_PULLUP) ;
  pinMode (11, INPUT_PULLUP) ;
  pinMode (12, INPUT_PULLUP) ;
  pinMode (2, INPUT_PULLUP) ; // ENCODER CLIC
}

void loop() {
  delay (100) ;
  digitalWrite (3, digitalRead (8)) ;
  digitalWrite (4, digitalRead (9)) ;
  digitalWrite (5, digitalRead (10)) ;
  digitalWrite (6, digitalRead (11)) ;
  digitalWrite (7, digitalRead (12)) ;
  digitalWrite (13, digitalRead (2)) ;
}

void setup() {
  pinMode (13, OUTPUT) ;
}

const int delai = 100 ;

void loop() {
  digitalWrite (13, HIGH) ;
  delay (delai) ;
  digitalWrite (13, LOW) ;
  delay (delai) ;
}

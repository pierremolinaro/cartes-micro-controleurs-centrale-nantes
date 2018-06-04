void setup() {
  pinMode (10, INPUT_PULLUP) ;
  pinMode (13, OUTPUT) ;
}

const int delai = 100 ;
byte gFiltre  = 0 ;

void loop() {
  delay (delai) ;
  gFiltre = (gFiltre << 1) | digitalRead (10) ;
  if (gFiltre == 0) {
    digitalWrite (13, HIGH) ;
  }else if (gFiltre == 0xFF) {
    digitalWrite (13, LOW) ;
  }
}

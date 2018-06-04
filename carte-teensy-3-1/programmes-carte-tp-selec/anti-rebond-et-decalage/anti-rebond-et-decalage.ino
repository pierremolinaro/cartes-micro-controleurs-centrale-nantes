void setup() {
  pinMode (10, INPUT_PULLUP) ;
  pinMode (3, OUTPUT) ;
  pinMode (4, OUTPUT) ;
  pinMode (5, OUTPUT) ;
  pinMode (6, OUTPUT) ;
  pinMode (7, OUTPUT) ;
  pinMode (13, OUTPUT) ;
}

const int delai = 300 ;
byte gFiltre  = 0 ;

void loop() {
  delay (delai) ;
  gFiltre = (gFiltre << 1) | digitalRead (10) ;
  if (gFiltre == 0) {
    digitalWrite (13, HIGH) ;
  }else if (gFiltre == 0xFF) {
    digitalWrite (13, LOW) ;
  }
  digitalWrite (7, (gFiltre & 0x80) == 0) ;
  digitalWrite (6, (gFiltre & 0x40) == 0) ;
  digitalWrite (5, (gFiltre & 0x20) == 0) ;
  digitalWrite (4, (gFiltre & 0x10) == 0) ;
  digitalWrite (3, (gFiltre & 0x08) == 0) ;
}

void setup() {
  pinMode (5, OUTPUT) ;
  pinMode (10, INPUT_PULLUP) ;
 // pinMode (13, OUTPUT) ;
}

const int delai = 100 ;
//int compteur  = 0 ;

void loop() {
  delay (delai) ;
  if (digitalRead (10)) {
    digitalWrite (5, LOW) ;
  }else{
    digitalWrite (5, HIGH) ;
  }
 /* compteur ++ ; // compteur = compteur + 1 ;
  if (compteur == 10) {
    compteur = 0 ;
    digitalWrite (13, ! digitalRead (13)) ;
  }*/
//  digitalWrite (5, ! digitalRead (10)) ;
}

void setup() {
  pinMode (3, OUTPUT) ;
  pinMode (4, OUTPUT) ;
  pinMode (5, OUTPUT) ;
  pinMode (6, OUTPUT) ;
  pinMode (7, OUTPUT) ;
  pinMode (13, OUTPUT) ;
}

const int delai = 100 ; // 100 ms

void loop() {
  digitalWrite (3, HIGH) ;
  delay (delai) ;
  digitalWrite (4, HIGH) ;
  delay (delai) ;
  digitalWrite (5, HIGH) ;
  delay (delai) ;
  digitalWrite (6, HIGH) ;
  delay (delai) ;
  digitalWrite (7, HIGH) ;
  delay (delai) ;
  digitalWrite (13, HIGH) ;
  delay (delai) ;
  digitalWrite (3, LOW) ;
  delay (delai) ;
  digitalWrite (4, LOW) ;
  delay (delai) ;
  digitalWrite (5, LOW) ;
  delay (delai) ;
  digitalWrite (6, LOW) ;
  delay (delai) ;
  digitalWrite (7, LOW) ;
  delay (delai) ;
  digitalWrite (13, LOW) ;
  delay (delai) ;
}

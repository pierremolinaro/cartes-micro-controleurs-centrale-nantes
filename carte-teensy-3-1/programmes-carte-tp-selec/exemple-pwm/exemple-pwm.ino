void setup() {
  analogWriteFrequency (23, 25000); // PWM Frequency 25 kHz
  analogWriteResolution (6);  // analogWrite value 0 to 63
}

int gCompteur = 0 ;

void loop() {
  delay (50) ;
  gCompteur = (gCompteur + 1) % 64 ;
  analogWrite (23, gCompteur) ;
}


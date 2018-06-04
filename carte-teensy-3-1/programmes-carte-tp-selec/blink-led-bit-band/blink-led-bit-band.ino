// La led builtin siur la Teensy 3.1 est le port PTC5
// Écrire sur le port C peut s'effectuer via le registre GPIOC_PDOR, d'adresse 0x400F_F080

//--- On peut accéder au bit n°5 de ce port via une opération bit-band:
//    Offset du registre : 0x000F_F080
//    Numéro du bit : 5
//    L'adresse bit-band est = 0x4200_0000 + (0x000F_F080 * 32) + (5 * 4)

static const uint32_t adresseBitBand = 0x42000000 + (0x000FF080 * 32) + (5 * 4) ;
#define BIT_BAND_ADDR (* ((volatile uint32_t *) adresseBitBand))

void setup() {
  pinMode (LED_BUILTIN, OUTPUT) ;
}

const int delai = 100 ;

void loop() {
 // digitalWrite (LED_BUILTIN, HIGH) ;
  BIT_BAND_ADDR = 1 ;
  delay (500) ;
//  digitalWrite (LED_BUILTIN, LOW) ;
  BIT_BAND_ADDR = 0 ;
  delay (500) ;
}

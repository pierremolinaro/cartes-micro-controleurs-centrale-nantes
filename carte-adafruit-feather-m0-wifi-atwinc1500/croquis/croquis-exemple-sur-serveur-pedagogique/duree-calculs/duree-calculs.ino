#include "fonctionVide.h"
#include "division-entiere.h"
#include "division-flottante.h"
#include "division-double.h"

static const uint32_t NOMBRE_ITERATIONS = 100000 ;

void setup() {
  pinMode (LED_BUILTIN, OUTPUT);
  digitalWrite (LED_BUILTIN, HIGH) ;
  Serial.begin(9600);
  delay (5000) ;
  Serial.println ("C'est parti") ;
//---  Fonction vide
  delay (100) ;
  const uint32_t t0 = millis () ;
  for (uint32_t i=0 ; i < NOMBRE_ITERATIONS ; i++) {
    fonctionVide () ;
  }
  const uint32_t dureeAppelsFonctionVide = millis () - t0 ;
  Serial.print ("Fonction vide : ") ;
  Serial.print (dureeAppelsFonctionVide) ;
  Serial.println (" ms") ;
 //--- Division entière 32 bits
  delay (100) ;
  const uint32_t t1 = millis () ;
  uint32_t cumul = 0 ;  
  for (uint32_t i=0 ; i < NOMBRE_ITERATIONS ; i++) {
    cumul += divisionEntiere32bits (i) ;
  }
  const uint32_t dureeAppelsDivisionEntiere = millis () - t1 ;
  Serial.print ("Division entière 32 bits : ") ;
  Serial.print (dureeAppelsDivisionEntiere) ;
  Serial.print (" ms (cumul ") ;
  Serial.print (cumul) ;
  Serial.println (")") ;
//--- Division flottante 32 bits
  delay (100) ;
  const uint32_t t2 = millis () ;
  float fcumul = 0.0 ;  
  for (uint32_t i=0 ; i < NOMBRE_ITERATIONS ; i++) {
    fcumul += divisionFlottante ((float) i) ;
  }
  const uint32_t dureeAppelsDivisionFlottante = millis () - t2 ;
  Serial.print ("Division flottante : ") ;
  Serial.print (dureeAppelsDivisionFlottante) ;
  Serial.print (" ms (cumul ") ;
  Serial.print (fcumul) ;
  Serial.println (")") ;
//--- Division flottante 64 bits
  delay (100) ;
  const uint32_t t3 = millis () ;
  double dcumul = 0.0 ;  
  for (uint32_t i=0 ; i < NOMBRE_ITERATIONS ; i++) {
    dcumul += divisionDouble ((double) i) ;
  }
  const uint32_t dureeAppelsDivisionDouble = millis () - t3 ;
  Serial.print ("Division double : ") ;
  Serial.print (dureeAppelsDivisionDouble) ;
  Serial.print (" ms (cumul ") ;
  Serial.print (dcumul) ;
  Serial.println (")") ;
}


void loop () {
  delay (500) ;
  digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
}


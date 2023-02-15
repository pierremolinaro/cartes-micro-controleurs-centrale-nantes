#ifndef ARDUINO_RASPBERRY_PI_PICO
  #error Select "Raspberry Pi Pico" board
#endif

//-------------------------------------------------------------------------------------------------
//  AFFECTATION DES PORTS DE LA RASPBERRY PI PICO
// GP0, GP1, GP2 et GP3 : sorties leds, actives haut
// GP14 : sortie commande moteur IN1
// GP15 : sortie commande moteur IN2
// GP16 : entrée DIP switch 1, OFF -> entrée au niveau haut, ON -> entrée au niveau bas
// GP17 : entrée DIP switch 2, OFF -> entrée au niveau haut, ON -> entrée au niveau bas
// GP18 : entrée DIP switch 3, OFF -> entrée au niveau haut, ON -> entrée au niveau bas
// Les autres ports sont disponibles sur les connecteurs
//-------------------------------------------------------------------------------------------------

#include "pwm.h"

//-------------------------------------------------------------------------------------------------

const uint32_t fréquenceHorlogePWM = 5 * 1000 ; // En Hz
const uint32_t nombreNiveauxPWM = 256 ; // La rapport cyclique va de 0 à nombreNiveauxPWM-1

//-------------------------------------------------------------------------------------------------

void setup () {
  pinMode (LED_BUILTIN, OUTPUT) ;
  // Serial.begin (115200) ;
  // while (!Serial) {
  //   delay (50) ;
  //   digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  // }
  pinMode (0, OUTPUT) ; // Led GP0
  pinMode (1, OUTPUT) ; // Led GP1
  pinMode (2, OUTPUT) ; // Led GP2
  pinMode (3, OUTPUT) ; // Led GP3
  pinMode (16, INPUT_PULLUP) ; // DIP SWITCH 1
  pinMode (17, INPUT_PULLUP) ; // DIP SWITCH 2
  pinMode (18, INPUT_PULLUP) ; // DIP SWITCH 3
  // Serial.print ("Fréquence CPU : ") ;
  // Serial.print (F_CPU) ;
  // Serial.println (" Hz") ;
   configurerPWM (fréquenceHorlogePWM, nombreNiveauxPWM) ;
}

//-------------------------------------------------------------------------------------------------

static uint32_t gBlink = 0 ;
static uint8_t gPhase = 0 ;

//-------------------------------------------------------------------------------------------------

void loop () {
  if ((millis () - gBlink) > 500) {
    gBlink += 500 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
    for (uint8_t i=0 ; i<4 ; i++) {
      digitalWrite (i, (gPhase & 3) == i) ;
    }
    gPhase += 1 ;
  }
  if ((digitalRead (16) == LOW) && (digitalRead (17) == HIGH)) {
    marcheAvant (255) ;
  }else if ((digitalRead (16) == HIGH) && (digitalRead (17) == LOW)) {
    marcheArriere (255) ;
  }else{
    arret () ;
  }
}

//-------------------------------------------------------------------------------------------------

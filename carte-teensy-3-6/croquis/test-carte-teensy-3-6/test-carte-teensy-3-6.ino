//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
//  Programme de test de la carte Teensy 3.6 pour vérifier que tout marche
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#ifndef __MK66FX1M0__
  #error "Ce sketch doit être compilé pour la Teensy 3.6"
#endif

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <LiquidCrystal.h>
#include <TimerOne.h>

#include <ACAN.h>

// https://www.pjrc.com/teensy/td_libs_SPI.html
// /Users/pierremolinaro/Documents/Arduino/libraries/RF24-master
#include <SPI.h>
#include <RF24.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

LiquidCrystal lcd (18, 17, 16, 15, 14, 19) ; // Liaison 4 bits de données

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

const byte CE_PIN = 24 ;
const byte CSN_PIN = 25 ;

RF24 radio (CE_PIN, CSN_PIN);

const byte addresses[][6] = {"1Node","2Node"};

// Set this radio as radio number 0 or 1
bool radioNumber = 1;

// Used to control whether this node is sending or receiving
const bool role = 0 ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

const byte ENCODER_CLIC = 2 ;
const byte ENCODER_A = 0 ;
const byte ENCODER_B = 1 ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void setup() {
  Serial.begin (115200) ;
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
  pinMode (ENCODER_CLIC, INPUT_PULLUP) ; // ENCODER CLIC
  pinMode (ENCODER_B, INPUT_PULLUP) ; // ENCODER B
  pinMode (ENCODER_A, INPUT_PULLUP) ; // ENCODER A
  lcd.begin(20,4); //utilisation d'un écran 20 colonnes et 4 lignes
  lcd.write ("Test"); //petit test pour vérifier que tout marche

  analogWriteFrequency (23, 25000); // PWM Frequency 25 kHz
  analogWriteResolution (6);  // analogWrite value 0 to 63
//--- CAN
  ACANSettings settings (125 * 1000) ;
  ACAN::can1.begin (settings) ;
  settings.mUseAlternateTxPin = true ;
  settings.mUseAlternateRxPin = true ;
  ACAN::can0.begin (settings) ;
//----------------------------------------------- radio
// https://www.pjrc.com/teensy/td_libs_SPI.html
// Utiliser les pins « alternate »; doit être placé avant radio.begin().
  SPI.setMOSI (28) ;
  SPI.setMISO (39) ;
  SPI.setSCK (27) ;
//---
  const bool ok = radio.begin () ;
  Serial.println (ok ? "Radio ok" : "Radio err") ;
// Set the PA Level low to prevent power supply related issues since this is a
// getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel (RF24_PA_LOW) ;
  radio.setDataRate (RF24_250KBPS) ;
  radio.setChannel (108) ; // 2.508 GHz
  if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
// Start the radio listening for data
  radio.startListening () ;
  radio.printDetails () ;
 //---
  Timer1.initialize (1000) ; // 1000 micro s.
  Timer1.attachInterrupt (encoderHandler);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

volatile int gEncodeur = 0 ;
bool gEncoderA = false ;
int gClignotement = 0 ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void encoderHandler (void) {
  const bool encoderA = digitalRead (ENCODER_A) ;
  if (encoderA && !gEncoderA) {
    if ((gEncodeur < 63) && !digitalRead (ENCODER_B)) {
      gEncodeur ++ ;
    }else if ((gEncodeur > 0) && digitalRead (ENCODER_B)) {
      gEncodeur -- ;
    }
  }
  gEncoderA = encoderA ;
  gClignotement ++ ;
  if (gClignotement == 250) {
    gClignotement = 0 ;
    digitalWrite (13, !digitalRead (13)) ;
  }
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

int gTramesEnvoyeesCAN0 = 0 ;
int gTramesRecuesCAN0 = 0 ;
bool gAfficherCAN0 = true ;

int gTramesEnvoyeesCAN1 = 0 ;
int gTramesRecuesCAN1 = 0 ;
bool gAfficherCAN1 = true ;

int gTramesEnvoyeesNRF24 = 0 ;
int gTramesRecuesNRF24 = 0 ;
bool gAfficherNRF24 = true ;

int gPWM = 0 ;
int gEncodeurCache = -1 ; // Pour forcer l'affichage initial

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void loop() {
  CANMessage message ;
  digitalWrite (3, ! digitalRead (8)) ;
  digitalWrite (4, ! digitalRead (9)) ;
  digitalWrite (5, ! digitalRead (10)) ;
  digitalWrite (6, ! digitalRead (11)) ;
  digitalWrite (7, ! digitalRead (12)) ;
//--- Clic
  lcd.setCursor (16, 0) ;
  lcd.print (digitalRead (ENCODER_CLIC) ? "    " : "CLIC") ;
//--- Encodeur
  if (gEncodeurCache != gEncodeur) {
    gEncodeurCache = gEncodeur ;
    lcd.setCursor (10, 0) ;
    lcd.print ("  ") ;
    lcd.setCursor (10, 0) ;
    lcd.print (gEncodeurCache) ;
  }
 //--- PWM
  analogWrite (23, gPWM) ;
  gPWM = (gPWM + 3) % 64 ;
//--- Réception de message CAN0 ?
  if (ACAN::can0.receive (message)) {
    gTramesRecuesCAN0 += 1 ;
    gAfficherCAN0 = true ;
  }
//--- Réception de message CAN1 ?
  if (ACAN::can1.receive (message)) {
    gTramesRecuesCAN1 += 1 ;
    gAfficherCAN1 = true ;
  }
//--- Appuie sur P0 : CAN0 envoie une trame standard
  if (!digitalRead (8)) {
    CANMessage m ;
    m.id = millis () & 0x7FE ; // Bit 0 à 0 : pour éviter des collisions
    const bool ok = ACAN::can0.tryToSend (m) ;
    if (ok) {
      gTramesEnvoyeesCAN0 += 1 ;
      gAfficherCAN0 = true ;
    }
  }
//--- Appuie sur P1 : CAN1 envoie une trame standard
  if (!digitalRead (9)) {
    CANMessage m ;
    m.id = (millis () & 0x7FE) | 1 ; // Bit 0 à 1 : pour éviter des collisions
    const bool ok = ACAN::can1.tryToSend (m) ;
    if (ok) {
      gTramesEnvoyeesCAN1 += 1 ;
      gAfficherCAN1 = true ;
    }
  }
//--- Appuie sur P2 : envoyer une trame sur NRF24
//  if (!digitalRead (10)) {
//    radio.stopListening() ; // First, stop listening so we can talk.
//    const unsigned long start_time = micros () ; // Take the time, and send it.  This will block until complete
//    if (radio.write (&start_time, sizeof(unsigned long))) {
//      gTramesEnvoyeesNRF24 += 1 ;
//      gAfficherNRF24 = true ;
//    }
//    radio.startListening () ; // Now, continue listening
//  }
//--- Afficher CAN0
  if (gAfficherCAN0) {
    gAfficherCAN0 = false ;
    lcd.setCursor (0, 1) ;
    lcd.print ("CAN0:") ;
    lcd.print (gTramesEnvoyeesCAN0) ;
    lcd.print (", ") ;
    lcd.print (gTramesRecuesCAN0) ;
  }
//--- Afficher CAN1
  if (gAfficherCAN1) {
    gAfficherCAN1 = false ;
    lcd.setCursor (0, 2) ;
    lcd.print ("CAN1:") ;
    lcd.print (gTramesEnvoyeesCAN1) ;
    lcd.print (", ") ;
    lcd.print (gTramesRecuesCAN1) ;
  }
//--- Afficher NRF24
  if (gAfficherNRF24) {
    gAfficherNRF24 = false ;
    lcd.setCursor (0, 3) ;
    lcd.print ("NRF24:") ;
    lcd.print (gTramesEnvoyeesNRF24) ;
    lcd.print (", ") ;
    lcd.print (gTramesRecuesNRF24) ;
  }
/****************** Ping Out Role ***************************/  
  if (role == 1) {
    radio.stopListening();                                    // First, stop listening so we can talk.
    Serial.println(F("Now sending"));
    const unsigned long start_time = micros();                             // Take the time, and send it.  This will block until complete
    if (!radio.write( &start_time, sizeof(unsigned long) )) {
      Serial.println(F("failed"));
    }
    radio.startListening();                                    // Now, continue listening
    unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
    while (!radio.available() ){                             // While nothing is received
      if ((micros() - started_waiting_at) > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
        timeout = true;
        break;
      }      
    }
    if (timeout) {                                             // Describe the results
        Serial.println(F("Failed, response timed out."));
    }else{
      unsigned long got_time;                                 // Grab the response, compare, and send to debugging spew
      radio.read( &got_time, sizeof(unsigned long) );
      unsigned long end_time = micros();
    // Spew it
      Serial.print(F("Sent "));
      Serial.print(start_time);
      Serial.print(F(", Got response "));
      Serial.print(got_time);
      Serial.print(F(", Round-trip delay "));
      Serial.print(end_time-start_time);
      Serial.println(F(" microseconds"));
    }
    // Try again 1s later
    delay(1000);
  }
/****************** Pong Back Role ***************************/
  if ( role == 0 ) {
    if (radio.available()) {
      unsigned long got_time; // Variable for the received timestamp
      while (radio.available()) {                                   // While there is data ready
        radio.read (&got_time, sizeof(unsigned long)) ;             // Get the payload
      }
      radio.stopListening();                                        // First, stop listening so we can talk   
      radio.write( &got_time, sizeof(unsigned long) );              // Send the final one back.      
      radio.startListening();                                       // Now, resume listening so we catch the next packets.     
      Serial.print(F("Sent response "));
      Serial.println (got_time);  
    }else{
      Serial.println (F("Rien reçu"));
    }
    delay (1000) ;
  }
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


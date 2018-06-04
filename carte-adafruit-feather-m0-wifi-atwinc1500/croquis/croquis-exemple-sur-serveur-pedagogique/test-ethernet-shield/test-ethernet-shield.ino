#include <SPI.h>
#include <Ethernet2.h> // OBLIGATOIRE: Utiliser cette librairie (la librairie Ethernet n'est pas compatible)
#include <LiquidCrystal.h>
#include "tp_sysit_feather.h" // Placer après les #include <...>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

LiquidCrystal lcd (18, 17, 16, 15, 14, 19) ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//--- Écrire ici l'adresse Mac de votre carte
static byte adresseEthernet [] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED} ;

//--- Adresse IP: choisir une adresse locale non routée
static const IPAddress monIP (192, 168, 0, 14) ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void setup() {
  pinMode (LED_BUILTIN, OUTPUT) ;
  digitalWrite (LED_BUILTIN, HIGH) ;
  lcd.begin (20, 4) ; // Utilisation d'un écran 20 colonnes et 4 lignes
  Ethernet.init (9) ; // Le CS est le port n°9
  Ethernet.begin (adresseEthernet, monIP) ; // Masque réseau implicite
  lcd.print ("IP ");
  lcd.print (Ethernet.localIP());
  lcd.setCursor (0, 1) ;
  lcd.print ("Masque ");
  lcd.print (Ethernet.subnetMask());
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

unsigned tick = 1000 ;

void loop() {
  if (tick <= millis ()) {
    tick += 500 ;
    digitalWrite (LED_BUILTIN, ! digitalRead (LED_BUILTIN)) ;
  }
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————



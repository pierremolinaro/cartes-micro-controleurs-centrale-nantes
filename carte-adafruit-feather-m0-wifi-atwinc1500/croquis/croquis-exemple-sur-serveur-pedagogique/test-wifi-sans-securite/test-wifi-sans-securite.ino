#include <SPI.h>
#include <WiFi101.h> // Utiliser obligatoirement Wifi101, ne pas utiliserr Wifi
#include <LiquidCrystal.h>
#include "tp_sysit_feather.h" // Placer après les #include <...>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

LiquidCrystal lcd (18, 17, 16, 15, 14, 19) ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

unsigned tick = 0 ; // Utilisé pour faire clignoter la led

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

const char SSID_RESEAU [] = "MacBookProPierre"; //  C'est le nom du réseau

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void setup() {
  pinMode (LED_BUILTIN, OUTPUT) ;
  lcd.begin (20, 4) ;
  bool ok = true ;
//--- Configurer les broches pour la carte Adafruit ATWINC1500 Feather
  WiFi.setPins (8, 7, 4, 2) ;
//--- Vérifier la présence du shield Wifi
  int etatWifi = WiFi.status () ;
  if (etatWifi == WL_NO_SHIELD) {
    lcd.print ("Pas de shield Wifi");
    ok = false ;
  }
//--- Vérifier la version du firmware
  if (ok) {
    const String versionFirmware = WiFi.firmwareVersion () ;
    if (versionFirmware != "19.5.2") {
      lcd.print ("MAJ ");
      lcd.print (versionFirmware);
      ok = false ;
    }
  }
//--- Démarrage de la connexion au réseau
  if (ok) {
    lcd.print ("Connexion...");
    while (WiFi.begin (SSID_RESEAU) != WL_CONNECTED) {
      delay (10000) ;
    }
    lcd.setCursor (0, 0) ;
//    etatWifi = WiFi.begin (SSID_RESEAU) ;
//    ok = etatWifi == WL_DISCONNECTED ;
//    if (! ok) {
//      lcd.print ("Echec creation ");
//      lcd.print (etatWifi);
//    }
  }
//--- Attendre la connexion
//  if (ok) {
//    lcd.print ("Connexion...");
//    delay (10000) ;
//    lcd.print (WiFi.status ());
//
//    
//  }
//--- Afficher les caractéristiques
  if (ok) {
    byte adresseMAC [6] ; WiFi.macAddress (adresseMAC) ;
    for (int i=5 ; i>=0 ; i--) {
      if (i < 5) {
        lcd.print (":") ;
      }
      lcd.print (adresseMAC [i], HEX) ;
    }
    lcd.setCursor (0, 1) ;
    lcd.print ("IP ");
    lcd.print (IPAddress (WiFi.localIP())) ;
    lcd.setCursor (0, 2) ;
    lcd.print ("Masque ");
    lcd.print (IPAddress (WiFi.subnetMask())) ;
  }
//--- Ainsi, la led s'allume aussitôt
  tick = millis () ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void loop() {
//--- Faire clignoter la led
  if (tick <= millis ()) {
    tick += 500 ;
    digitalWrite (LED_BUILTIN, ! digitalRead (LED_BUILTIN)) ;
  }
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


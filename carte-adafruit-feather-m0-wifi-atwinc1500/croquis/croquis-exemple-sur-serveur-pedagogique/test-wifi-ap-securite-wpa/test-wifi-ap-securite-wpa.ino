#include <SPI.h>
#include <WiFi101.h> // Utiliser obligatoirement Wifi101, ne pas utiliserr Wifi
#include <LiquidCrystal.h>
#include "tp_sysit_feather.h" // Placer après les #include <...>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// Ce croquis configure le module Wifi en point d'accès.
// La sécurité de la connexion est WPA2.
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

LiquidCrystal lcd (18, 17, 16, 15, 14, 19) ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

unsigned tick = 0 ; // Utilisé pour faire clignoter la led

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// Le mot de passe WPA doit comporter au moins 13 caractères
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

const char SSID_RESEAU [] = "yourNetwork" ;   //  C'est le nom du réseau
const char MOT_DE_PASSE_WPA2 [] = "ABCDEFGHIJKLMNOPQRSTUVWXY" ; // Le mot de passe (secret) du réseau (au moins 13 caractères)
const byte WIFI_CHANNEL = 11 ; // Canal Wifi (entre 1 et 11)

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
//--- Création du point d'accès (avec sécurité WPA)
  if (ok) {
    etatWifi = WiFi.beginAP (SSID_RESEAU, MOT_DE_PASSE_WPA2, WIFI_CHANNEL) ;
    ok = etatWifi == WL_AP_LISTENING ;
    if (! ok) {
      lcd.print ("Echec creation ");
      lcd.print (etatWifi);
    }
  }
//--- Afficher les caractéristiques
  if (ok) {
    byte adresseMAC [6] ; WiFi.macAddress (adresseMAC) ;
    lcd.setCursor (0, 0) ;
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


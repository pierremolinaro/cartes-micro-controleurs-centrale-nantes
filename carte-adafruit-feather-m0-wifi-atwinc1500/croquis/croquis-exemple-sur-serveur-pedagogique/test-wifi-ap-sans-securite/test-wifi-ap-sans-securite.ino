#include <SPI.h>
#include <WiFi101.h> // Utiliser obligatoirement Wifi101, ne pas utiliserr Wifi
#include <LiquidCrystal.h>
#include "tp_sysit_feather.h" // Placer après les #include <...>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

LiquidCrystal lcd (18, 17, 16, 15, 14, 19) ;

extern "C" void PRINT (const uint32_t inValue) ;

void PRINT (const uint32_t inValue) {
  lcd.setCursor (0, 3) ;
  lcd.print (inValue, HEX) ;
  lcd.setCursor (0, 0) ;

}
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

unsigned tick = 0 ; // Utilisé pour faire clignoter la led

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

const char SSID_RESEAU [] = "yourNetwork"; //  C'est le nom du réseau
const byte CANAL_WIFI = 1 ; // Entre 1 et 12

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void setup() {
  Serial.begin (115200) ;
  while (!Serial) {}
  Serial.println ("Hello !") ;
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
//--- Création du point d'accès
  if (ok) {
    etatWifi = WiFi.beginAP (SSID_RESEAU, CANAL_WIFI) ;
    ok = etatWifi == WL_AP_LISTENING ;
    if (! ok) {
      lcd.print ("Echec creation");
    }
  }
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


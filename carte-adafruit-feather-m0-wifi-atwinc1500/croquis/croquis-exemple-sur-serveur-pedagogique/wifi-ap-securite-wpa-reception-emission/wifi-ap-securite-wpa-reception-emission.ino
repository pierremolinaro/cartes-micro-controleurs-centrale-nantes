#include <SPI.h>
#include <WiFi101.h> // Utiliser obligatoirement Wifi101, ne pas utiliserr Wifi
#include <LiquidCrystal.h>
#include "tp_sysit_feather.h" // Placer après les #include <...>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

LiquidCrystal lcd (18, 17, 16, 15, 14, 19) ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

unsigned tick = 0 ; // Utilisé pour faire clignoter la led

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

const char SSID_RESEAU [] = "yourNetwork"; //  C'est le nom du réseau
const char MOT_DE_PASSE_WPA2 [] = "ABCDEFGHIJKLMNOPQRSTUVWXY" ; // Le mot de passe (secret) du réseau (au moins 13 caractères)
const byte CANAL_WIFI = 1 ; // Entre 1 et 12
WiFiServer gServeur (16009) ;

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
//--- Création du point d'accès
  if (ok) {
    etatWifi = WiFi.beginAP (SSID_RESEAU, MOT_DE_PASSE_WPA2, CANAL_WIFI) ;
    ok = etatWifi == WL_AP_LISTENING ;
    if (! ok) {
      lcd.print ("Echec creation");
    }
  }
//--- Démarrer le serveur
  if (ok) {
    gServeur.begin() ;
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
    lcd.setCursor (11, 2) ;
    lcd.print ("<SERVEUR>") ;
    lcd.setCursor (0, 3) ;
    lcd.print ("Recus");
    lcd.setCursor (10, 3) ;
    lcd.print ("Emis");
  }
//--- Ainsi, la led s'allume aussitôt
  tick = millis () ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

unsigned gNombreOctetsRecus = 0 ;
unsigned gNombreOctetsEmis = 0 ;
WiFiClient gClient ;
bool gClientConnecte = false ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void loop() {
//--- Faire clignoter la led
  if (tick <= millis ()) {
    tick += 500 ;
    digitalWrite (LED_BUILTIN, ! digitalRead (LED_BUILTIN)) ;
  }
//--- Gestion du serveur
  if (gClient.connected ()) { // Un client est connecté ?
    if (gClient.available() > 0) { // Des données en provenance du client ?
      const byte donneeRecue = gClient.read () ;
      gNombreOctetsRecus += 1 ;
      lcd.setCursor (6, 3) ;
      lcd.print (gNombreOctetsRecus);
     // Si la donnée est paire, on la renvoie
      if ((donneeRecue & 1) == 0) {
        gClient.write (donneeRecue) ;
        gNombreOctetsEmis += 1 ;
        lcd.setCursor (15, 3) ;
        lcd.print (gNombreOctetsEmis);
      }
    }
  }else{ // Aucun client connecté
    if (gClientConnecte) { // Le client vient de se déconnecter
      gClientConnecte = false ;
      lcd.setCursor (0, 2) ;
      lcd.print ("      ");
    }
    gClient = gServeur.available () ; // Nouveau client connecté ayant envoyé des données ?
    if (gClient.connected ()) {
      gClientConnecte = true ;
      lcd.setCursor (0, 2) ;
      lcd.print ("Client");
    }
  }
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


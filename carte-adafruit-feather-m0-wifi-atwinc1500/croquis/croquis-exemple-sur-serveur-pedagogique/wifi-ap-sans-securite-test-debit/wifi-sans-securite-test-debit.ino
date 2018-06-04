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
    etatWifi = WiFi.beginAP (SSID_RESEAU, CANAL_WIFI) ;
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
    lcd.setCursor (0, 2) ;
    lcd.print ("Recus:");
    lcd.setCursor (0, 3) ;
    lcd.print ("Emis:");
  }
//--- Ainsi, la led s'allume aussitôt
  tick = millis () ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

WiFiClient gClient ;
bool gClientConnecte = false ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

const unsigned TAILLE_BUFFER = 2000 ;

static byte gBuffer [TAILLE_BUFFER] ;
static unsigned gOccupationBuffer = 0 ;
static unsigned gNombreRecus = 0 ;
static unsigned gNombreEmis = 0 ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void loop() {
//--- Faire clignoter la led
  if (tick <= millis ()) {
    tick += 500 ;
    digitalWrite (LED_BUILTIN, ! digitalRead (LED_BUILTIN)) ;
    lcd.setCursor (6, 2) ;
    lcd.print (gNombreRecus);
    lcd.setCursor (6, 3) ;
    lcd.print (gNombreEmis);
  }
//--- Gestion du serveur
  if (gClient.connected ()) { // Un client est connecté ?
    if ((gClient.available () > 0) && (gOccupationBuffer < TAILLE_BUFFER)) { // Des données en provenance du client ?
      const int nombreRecus = gClient.read (& gBuffer [gOccupationBuffer], TAILLE_BUFFER - gOccupationBuffer) ;
      if (nombreRecus > 0) {
        gOccupationBuffer += (unsigned) nombreRecus ;
        gNombreRecus += (unsigned) nombreRecus ;
      }
    }
    if (gOccupationBuffer > 0) {
      const unsigned nombreEnvoyes = gClient.write (& gBuffer [0], gOccupationBuffer) ;
//      gClient.write (gBuffer [0]) ;
//      const unsigned nombreEnvoyes = 1 ;
      if (nombreEnvoyes > 0) {
        for (unsigned i=0 ; i< (gOccupationBuffer - nombreEnvoyes) ; i++) {
          gBuffer [i] = gBuffer [i + nombreEnvoyes] ;
        }
        gOccupationBuffer -= nombreEnvoyes ;
        gNombreEmis += nombreEnvoyes ;
      }
    }
  }else{ // Aucun client connecté
    if (gClientConnecte) { // Le client vient de se déconnecter
      gClientConnecte = false ;
      lcd.setCursor (19, 0) ;
      lcd.print (" ");
    }
    gClient = gServeur.available () ; // Nouveau client connecté ayant envoyé des données ?
    if (gClient.connected ()) {
      gClientConnecte = true ;
      lcd.setCursor (19, 0) ;
      lcd.print ("*");
    }
  }
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


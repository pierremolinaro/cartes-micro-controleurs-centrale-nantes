#include <LiquidCrystal.h>
#include <TimerOne.h>

//-----------------------------------------------------------------------------

LiquidCrystal lcd (18, 17, 16, 15, 14, 19); // Liaison 4 bits de données

//-----------------------------------------------------------------------------

void setup() {
  pinMode (3, OUTPUT) ;
  pinMode (4, OUTPUT) ;
  pinMode (5, OUTPUT) ;
  pinMode (6, OUTPUT) ;
  pinMode (7, OUTPUT) ;
  pinMode (13, OUTPUT) ;
  pinMode (0, INPUT_PULLUP) ;
  pinMode (1, INPUT_PULLUP) ;
  lcd.begin (20,4) ; //utilisation d'un écran 20 colonnes et 4 lignes
  lcd.write ("Hello World!"); //petit test pour vérifier que tout marche
  Timer1.initialize (1000) ; // 1 ms.
  Timer1.attachInterrupt (encoderHandler);
  analogWriteFrequency (23, 25000); // PWM Frequency 25 kHz
  analogWriteResolution (6);  // analogWrite value 0 to 63
}

//-----------------------------------------------------------------------------

volatile int32_t gEncodeur = 0 ;
int32_t gEncodeurCache = 0 ;
bool gEncoderA = false ;
int32_t gClignotement = 0 ;
int32_t gPhase = 0 ;
volatile int32_t gMesureVitesse = 0 ;
static const int32_t gainProportionnel = 40 ;
static const int32_t gainIntegral = 4 ;
static int32_t gCumulIntegral = 0 ;

//-----------------------------------------------------------------------------

void encoderHandler (void) {
//--- Encodeur numérique
  const bool encoderA = digitalRead (0) ;
  if (encoderA && !gEncoderA) {
    if ((gEncodeur < 255) && !digitalRead (1)) {
      gEncodeur ++ ;
    }else if ((gEncodeur > 0) && digitalRead (1)) {
      gEncodeur -- ;
    }
  }
  gEncoderA = encoderA ;
//--- Clignotement
  gClignotement ++ ;
  if (gClignotement == 500) {
    gClignotement = 0 ;
    digitalWrite (13, !digitalRead (13)) ;
  }
//--- Regulateur
  gPhase ++ ;
  if (gPhase == 1) {
    analogWrite (23, 0) ; // Arret 
  }else if (gPhase == 2) {
    int32_t mesureVitesse = 0 ;
    for (uint32_t i=0 ; i<6 ; i++) {
      mesureVitesse += analogRead (22) ;
    }
    gMesureVitesse = mesureVitesse / 6 ;
    const int32_t difference = gEncodeur - gMesureVitesse ;
    gCumulIntegral += gainIntegral * difference ;
    if (gCumulIntegral < 0) {
      gCumulIntegral = 0 ;
    }else if (gCumulIntegral > 0x3FF) {
      gCumulIntegral = 0x3FF ;
    }
    int32_t commande = (gCumulIntegral + gainProportionnel * difference) >> 8 ;
    if (commande < 0) {
      commande = 0 ;
    }else if (commande > 63) {
      commande = 63 ;
    }
    analogWrite (23, commande) ;
  }else if (gPhase == 10) {
    gPhase = 0 ;
  }
}

//-----------------------------------------------------------------------------

static int32_t gMesureVitesseCache = 0 ;

//-----------------------------------------------------------------------------

void loop() {
  delay (200) ;
  if (gEncodeurCache != gEncodeur) {
    gEncodeurCache = gEncodeur ;
    lcd.setCursor (0, 0) ;
    lcd.print ("  ") ;
    lcd.setCursor (0, 0) ;
    lcd.print (gEncodeurCache) ;
  }
  if (gMesureVitesseCache != gMesureVitesse) {
    gMesureVitesseCache = gMesureVitesse ;
    lcd.setCursor (0, 1) ;
    lcd.print ("      ") ;
    lcd.setCursor (0, 1) ;
    lcd.print (gMesureVitesseCache) ;
  }
}

//-----------------------------------------------------------------------------

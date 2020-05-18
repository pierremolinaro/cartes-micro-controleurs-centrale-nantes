#include <LiquidCrystal.h>
#include <TimerOne.h>

LiquidCrystal lcd (18, 17, 16, 15, 14, 19); //liaison 4 bits de données

void setup() {
  pinMode (3, OUTPUT) ;
  pinMode (4, OUTPUT) ;
  pinMode (5, OUTPUT) ;
  pinMode (6, OUTPUT) ;
  pinMode (7, OUTPUT) ;
  pinMode (LED_BUILTIN, OUTPUT) ;
  pinMode (8, INPUT_PULLUP) ;
  pinMode (9, INPUT_PULLUP) ;
  pinMode (10, INPUT_PULLUP) ;
  pinMode (11, INPUT_PULLUP) ;
  pinMode (12, INPUT_PULLUP) ;
  pinMode (2, INPUT_PULLUP) ; // ENCODER CLIC
  pinMode (1, INPUT_PULLUP) ; // ENCODER B
  pinMode (0, INPUT_PULLUP) ; // ENCODER A
  lcd.begin(20,4); //utilisation d'un écran 20 colonnes et 4 lignes
  lcd.write ("Programme de test"); //petit test pour vérifier que tout marche
  analogWriteFrequency (23, 25000); // PWM Frequency 25 kHz
  analogWriteResolution (6);  // analogWrite value 0 to 63
  Timer1.initialize (1000) ; // 1000 micro s.
  Timer1.attachInterrupt (encoderHandler);
}

volatile int gEncodeur = 0 ;
int gEncodeurCache = 0 ;
bool gEncoderA = false ;
int gClignotement = 0 ;

void encoderHandler (void) {
  const bool encoderA = digitalRead (0) ;
  if (encoderA && !gEncoderA) {
    if ((gEncodeur < 63) && !digitalRead (1)) {
      gEncodeur ++ ;
    }else if ((gEncodeur > 0) && digitalRead (1)) {
      gEncodeur -- ;
    }
  }
  gEncoderA = encoderA ;
  gClignotement ++ ;
  if (gClignotement == 250) {
    gClignotement = 0 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
}

int gPWM = 0 ;

void loop() {
  delay (100) ;
  digitalWrite (3, ! digitalRead (8)) ;
  digitalWrite (4, ! digitalRead (9)) ;
  digitalWrite (5, ! digitalRead (10)) ;
  digitalWrite (6, ! digitalRead (11)) ;
  digitalWrite (7, ! digitalRead (12)) ;
  lcd.setCursor (0, 3) ;
  if (!digitalRead (2)) {
    lcd.print ("CLIC") ;
  }else{
    lcd.print ("    ") ;
  }
  if (gEncodeurCache != gEncodeur) {
    gEncodeurCache = gEncodeur ;
    lcd.setCursor (0, 1) ;
    lcd.print (gEncodeurCache) ;
    lcd.print (" ") ;
  }
  analogWrite (23, gPWM) ;
  gPWM = (gPWM + 3) % 64 ;
}

#include <LiquidCrystal.h>
#include <TimerOne.h>

LiquidCrystal lcd (18, 17, 16, 15, 14, 19); // Liaison 4 bits de données

void setup() {
  pinMode (13, OUTPUT) ;
  pinMode (0, INPUT_PULLUP) ;
  pinMode (1, INPUT_PULLUP) ;
  lcd.begin (20,4); // Utilisation d'un écran 20 colonnes et 4 lignes
  lcd.write ("Hello World!") ;
  Timer1.initialize (1000) ; // 1000 micro s.
  Timer1.attachInterrupt (encoderHandler);
}

volatile int gEncodeur = 0 ;
bool gEncoderA = true ;
int gClignotement = 0 ;

void encoderHandler () {
  const bool encoderA = digitalRead (0) ;
  if (encoderA && !gEncoderA) {
    gEncodeur ++ ;
  }
  gEncoderA = encoderA ;
  gClignotement ++ ;
  if (gClignotement == 500) {
    gClignotement = 0 ;
    digitalWrite (13, !digitalRead (13)) ;
  }
}

int gEncodeurCache = -1 ;

void loop() {
  delay (100) ;
  if (gEncodeurCache != gEncodeur) {
    gEncodeurCache = gEncodeur ;
    lcd.setCursor (0, 1) ;
    lcd.print ("  ") ;
    lcd.setCursor (0, 1) ;
    lcd.print (gEncodeurCache) ;
  }
}


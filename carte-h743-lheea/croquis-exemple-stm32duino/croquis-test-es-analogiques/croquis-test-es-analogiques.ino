#include "STM32H743-configuration-lheea.h"
#include "STM32H743-control-registers.h"

//--------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin (38400) ;
  pinMode (PE1, OUTPUT) ;
  configurerCarteH743LHEEA () ;
  fixerGammeEncodeur (0, 255) ;
  lcd.print ("Test ES analogiques") ;
  lcd.setCursor (0, 1) ;
  lcd.print ("SA:") ;
  lcd.setCursor (0, 2) ;
  lcd.print ("EA0:") ;
  lcd.setCursor (10, 2) ;
  lcd.print ("EA1:") ;
  lcd.setCursor (0, 3) ;
  lcd.print ("EA2:") ;
  lcd.setCursor (10, 3) ;
  lcd.print ("EA3:") ;
}

//--------------------------------------------------------------------------------------------------

static uint32_t gEcheance = 0 ;
static int32_t gValeurEncodeur = -1 ;

//--------------------------------------------------------------------------------------------------

void loop() {
  if (gEcheance < millis ()) {
    gEcheance += 1000 ;
    digitalWrite (PE1, !digitalRead (PE1)) ;
    const uint16_t ea0 = adc_read_value (PA_6, 12) ;
    lcd.setCursor (5, 2) ;
    lcd.print ("    ") ;
    lcd.setCursor (5, 2) ;
    lcd.print (ea0) ;
    const uint16_t ea1 = analogRead (PB1) ;
    lcd.setCursor (15, 2) ;
    lcd.print ("    ") ;
    lcd.setCursor (15, 2) ;
    lcd.print (ea1) ;
    const uint16_t ea2 = analogRead (PC3) ;
    lcd.setCursor (5, 3) ;
    lcd.print ("    ") ;
    lcd.setCursor (5, 3) ;
    lcd.print (ea2) ;
    const uint16_t ea3 = analogRead (PF11) ;
    lcd.setCursor (15, 3) ;
    lcd.print ("    ") ;
    lcd.setCursor (15, 3) ;
    lcd.print (ea3) ;
   }
//--- Encodeur
  const int32_t v = valeurEncodeur () ;
  if (gValeurEncodeur != v) {
    gValeurEncodeur = v ;
    lcd.setCursor (4, 1) ;
    lcd.print ("             ") ;
    lcd.setCursor (4, 1) ;
    lcd.print (v) ;
    const float tensionSortie = float (v) * 3.3 / 255.0 ;
    lcd.print (" -> ") ;
    lcd.print (tensionSortie) ;
    lcd.print (" V") ;
    analogWrite (PA4, uint8_t (v)) ;   
  }
}

//--------------------------------------------------------------------------------------------------

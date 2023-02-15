#include "pwm.h"
#include <hardware/pwm.h>
#include <Arduino.h>

//-------------------------------------------------------------------------------------------------
// GP14 : sortie commande moteur IN1
// GP15 : sortie commande moteur IN2
//-------------------------------------------------------------------------------------------------
// Le RP 2040 contient 8 PWM indépendantes (slice 0 à slice 7)
//  GP14 est conduit par le slice 7, sortie A
//  GP15 est conduit par le slice 7, sortie B
//-------------------------------------------------------------------------------------------------

static const uint32_t slice7 = 7 ;

//-------------------------------------------------------------------------------------------------

void configurerPWM (const uint32_t inFrequenceHorlogePWM,
                    const uint32_t inNombreNiveauxPWM) {
//--- Fixer la sortance
  gpio_set_drive_strength (14, GPIO_DRIVE_STRENGTH_12MA) ;
  gpio_set_drive_strength (15, GPIO_DRIVE_STRENGTH_12MA) ;
//--- GP14 et GP15 sont conduits par la PWM
  gpio_set_function (14, GPIO_FUNC_PWM) ;
  gpio_set_function (15, GPIO_FUNC_PWM) ;
//--- Appliquer le diviseur au canal 7
  const uint32_t diviseur = F_CPU / (inFrequenceHorlogePWM * inNombreNiveauxPWM) ;
  // Serial.print ("Diviseur : ") ;
  // Serial.println (diviseur) ;
  pwm_set_clkdiv_int_frac (slice7, diviseur, 0) ;
//--- Fixer la valeur où le compteur est remis à 0 (période = valeur + 1)
  pwm_set_wrap (slice7, inNombreNiveauxPWM - 1) ;
//--- Fixer les rapports cycliques à 0 au départ
  pwm_set_chan_level (slice7, PWM_CHAN_A, 0) ;
  pwm_set_chan_level (slice7, PWM_CHAN_B, 0) ;
//--- Démarrer la PWM
  pwm_set_enabled (slice7, true) ;
}

//-------------------------------------------------------------------------------------------------

void marcheAvant (const uint32_t inRapportCyclique) {
//--- Fixer le rapport cyclique de GP15 (IN2) à 0
  pwm_set_chan_level (slice7, PWM_CHAN_B, 0) ;
//--- Actionner GP14 (IN1)
  pwm_set_chan_level (slice7, PWM_CHAN_A, inRapportCyclique) ;
}

//-------------------------------------------------------------------------------------------------

void marcheArriere (const uint32_t inRapportCyclique) {
//--- Fixer le rapport cyclique de GP14 (IN1) à 0
  pwm_set_chan_level (slice7, PWM_CHAN_A, 0) ;
//--- Actionner GP15 (IN2)
  pwm_set_chan_level (slice7, PWM_CHAN_B, inRapportCyclique) ;
}

//-------------------------------------------------------------------------------------------------

void arret (void) {
//--- Fixer les rapports cycliques à 0
  pwm_set_chan_level (slice7, PWM_CHAN_A, 0) ;
  pwm_set_chan_level (slice7, PWM_CHAN_B, 0) ;
}

//-------------------------------------------------------------------------------------------------

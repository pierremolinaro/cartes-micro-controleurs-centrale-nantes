#pragma once

#include <stdint.h>

//-------------------------------------------------------------------------------------------------

void configurerPWM (const uint32_t inFrequenceHorlogePWM,
                    const uint32_t inNombreNiveauxPWM) ;

void marcheAvant (const uint32_t inRapportCyclique) ; // Entre 0 et inNombreNiveauxPWM

void marcheArriere (const uint32_t inRapportCyclique) ; // Entre 0 et inNombreNiveauxPWM

void arret (void) ;

//-------------------------------------------------------------------------------------------------

#pragma once

#include <stdint.h>

//-------------------------------------------------------------------------------------------------

void configurerPWM (const uint32_t inFrequenceHorlogePWM,
                    const uint32_t inNombreNiveauxPWM) ;

void marcheAvant (const uint32_t inRapportCyclique) ;

void marcheArriere (const uint32_t inRapportCyclique) ;

void arret (void) ;

//-------------------------------------------------------------------------------------------------

//
//  calcul-resistances-pour-4-frequences
//
//  Created by Pierre Molinaro on 07/07/2022.
//
//----------------------------------------------------------------------------------------

#include <vector>
#include <limits>
#include <math.h>

//----------------------------------------------------------------------------------------
// Intervalle des fréquences
//----------------------------------------------------------------------------------------

static const double FREQUENCE_CIBLE_BASSE =  400.0 ;
static const double FREQUENCE_CIBLE_HAUTE = 4000.0 ;

//----------------------------------------------------------------------------------------
// Valeur des condensateurs
//----------------------------------------------------------------------------------------

static const double C1 = 4.7e-9 ;
static const double C2 = 4.7e-9 ;

//----------------------------------------------------------------------------------------
// Calcul de la résistance é&quivalente à deux résistances en parallèle
//----------------------------------------------------------------------------------------

static double par (const double inRa, const double inRb) {
  return 1.0 / (1.0 / inRa + 1.0 / inRb) ;
}

//----------------------------------------------------------------------------------------
// Calcul de toutes les résistances de 1kΩ à 1MΩ de la série E24
//----------------------------------------------------------------------------------------

static std::vector <double> gammeResistances (void) {
  const double SERIE_E24 [22] = {
    100, 120, 150, 160, 180, 200, 220, 240, 270, 300, 330,
    360, 390, 430, 470, 510, 560, 620, 680, 750, 820, 910
  } ;
  std::vector <double> result ;
  for (int i=0 ; i<22 ; i++) {
    result.push_back (10.0 * double (SERIE_E24 [i])) ;
  }
  for (int i=0 ; i<22 ; i++) {
    result.push_back (100.0 * double (SERIE_E24 [i])) ;
  }
  result.push_back (100000.0) ;
  return result ;
}

//----------------------------------------------------------------------------------------
// Class Resultat
//----------------------------------------------------------------------------------------

class Resultat {
  public: double R1H ;
  public: double R1L ;
  public: double R2H ;
  public: double R2L ;
  public: double fc0 ;
  public: double fc1 ;
  public: double fc2 ;
  public: double fc3 ;
  public: double ecart ;

  public: Resultat (void) :
  R1H (0.0),
  R1L (0.0),
  R2H (0.0),
  R2L (0.0),
  fc0 (0.0),
  fc1 (0.0),
  fc2 (0.0),
  fc3 (0.0),
  ecart (std::numeric_limits <double>::max ()) {
  }

  public: Resultat (const double inR1H,
                    const double inR1L,
                    const double inR2H,
                    const double inR2L,
                    const double infc0,
                    const double infc1,
                    const double infc2,
                    const double infc3,
                    const double inEcart) :
  R1H (inR1H),
  R1L (inR1L),
  R2H (inR2H),
  R2L (inR2L),
  fc0 (infc0),
  fc1 (infc1),
  fc2 (infc2),
  fc3 (infc3),
  ecart (inEcart) {
  }

} ;


//----------------------------------------------------------------------------------------
//  main
//----------------------------------------------------------------------------------------

int main (void) {
//--- Résistances
  const std::vector <double> RESISTANCES = gammeResistances () ;
//--- Fréquences cible
  const double FREQUENCES [2] = {
    FREQUENCE_CIBLE_BASSE,
    FREQUENCE_CIBLE_HAUTE
  } ;
  printf ("Fréquences cibles :\n") ;
  for (int i=0 ; i<2 ; i++) {
    printf ("  %g Hz\n", FREQUENCES [i]) ;
  }
//--- Initialisation du tableau des résultats
  std::vector <Resultat> tableauResultats ;
  for (int i = 0 ; i < 10 ; i++) {
    tableauResultats.push_back (Resultat ()) ;
  }
//--- Calcul de toutes les combinaisons de résistances
  for (int i = 1 ; i < RESISTANCES.size () ; i++) {
    const double R1H = RESISTANCES [i] ;
    for (int j = 0 ; j < i ; j++) {
      const double R1L = RESISTANCES [j] ;
      for (int k = 1 ; k <= i ; k++) {
        const double R2H = RESISTANCES [k] ;
        for (int m = 0 ; m < k ; m++) {
          const double R2L = RESISTANCES [m] ;
        //--- Calcul des 2 fréquences
          const double candidates [2] = {
            1.0 / (2.0 * M_PI * sqrt (R1H * R2H * C1 * C2)),
            1.0 / (2.0 * M_PI * sqrt (par (R1H, R1L) * par (R2H, R2L) * C1 * C2))
          } ;
        //--- Calcul de l'écart
          double ecart = 0.0 ;
          for (int w = 0 ; w < 2 ; w++) {
            const double e = (FREQUENCES [w] - candidates [w]) / FREQUENCES [w] ;
            ecart += e * e ;
          }
        //--- Résultat
          Resultat resultat (
            R1H, R1L, R2H, R2L,
            candidates [0],
            1.0 / (2.0 * M_PI * sqrt (par (R1H, R1L) * R2H * C1 * C2)),
            1.0 / (2.0 * M_PI * sqrt (R1H * par (R2H, R2L) * C1 * C2)),
            candidates [1],
            ecart
          ) ;
        //--- Insérer le résultat
          for (int w = 0 ; w < tableauResultats.size () ; w++) {
            if (resultat.ecart < tableauResultats [w].ecart) {
              const Resultat temp = resultat ;
              resultat = tableauResultats [w] ;
              tableauResultats [w] = temp ;
            }
          }
        }
      }
    }
  }
//--- Affichage des résultats
  printf ("*----------------------------------------------------------------------------------*\n") ;
  printf ("|   Écart  |   F0  |    F1   |   F2   |   F3   |   R1H  |   R1L  |   R2H  |   R2L  |\n") ;
  printf ("*----------------------------------------------------------------------------------*\n") ;
  for (int i = 0 ; i < tableauResultats.size () ; i++) {
    printf (
      "| %0.6f | %6.1f | %6.1f | %6.1f | %6.1f | %6.0f | %6.0f | %6.0f | %6.0f |\n",
      tableauResultats [i].ecart,
      tableauResultats [i].fc0, tableauResultats [i].fc1,
      tableauResultats [i].fc2, tableauResultats [i].fc3,
      tableauResultats [i].R1H, tableauResultats [i].R1L,
      tableauResultats [i].R2H, tableauResultats [i].R2L
    ) ;
  }
  printf ("*----------------------------------------------------------------------------------*\n") ;
}

//----------------------------------------------------------------------------------------


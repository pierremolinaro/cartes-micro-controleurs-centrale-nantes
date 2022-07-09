//
//  calcul-pontage-pour-frequence-donnee
//
//  Created by Pierre Molinaro on 07/07/2022.
//
//----------------------------------------------------------------------------------------

#include <vector>
#include <limits>
#include <math.h>

//----------------------------------------------------------------------------------------
// Nombre de résultats calculés
//----------------------------------------------------------------------------------------

static const int NOMBRE_RESULTATS = 5 ;

//----------------------------------------------------------------------------------------
// Calculer les résultats obtenus avec deux résistances ?
//  true  --> calcul avec R1x seule, R2x seule, R1x et R2x
//  false --> calcul avec R1x seule, R2x seule
//----------------------------------------------------------------------------------------

static const bool CALCULER_POUR_R1X_ET_R2X = true ;

//----------------------------------------------------------------------------------------
// Valeur des résistances et condensateurs
//----------------------------------------------------------------------------------------

static const double R1H = 91000.0 ;
static const double R1L = 24000.0 ;
static const double R2H = 82000.0 ;
static const double R2L = 3900.0 ;
static const double C1 = 4.7e-9 ;
static const double C2 = 4.7e-9 ;

//----------------------------------------------------------------------------------------
// Calcul de la résistance équivalente à deux résistances en parallèle
//----------------------------------------------------------------------------------------

static double par (const double inRa, const double inRb) {
  return 1.0 / (1.0 / inRa + 1.0 / inRb) ;
}

//----------------------------------------------------------------------------------------
// Calcul de la résistance équivalente à trois résistances en parallèle
//----------------------------------------------------------------------------------------

static double par (const double inRa, const double inRb, const double inRc) {
  return 1.0 / (1.0 / inRa + 1.0 / inRb + 1.0 / inRc) ;
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
  for (int i=0 ; i<22 ; i++) {
    result.push_back (1000.0 * double (SERIE_E24 [i])) ;
  }
  result.push_back (1000.0 * 1000.0) ;
  return result ;
}

//----------------------------------------------------------------------------------------
// Class Resultat
//----------------------------------------------------------------------------------------

class Resultat {
  public: double R1x ; // 0 --> résistance absente
  public: double R2x ; // 0 --> résistance absente
  public: bool strapR1L ; // true --> le strap est présent, false --> il est absent
  public: bool strapR2L ; // true --> le strap est présent, false --> il est absent
  public: double fc ; // Fréquence réelle
  public: double ecart ;

  public: Resultat (void) :
  R1x (0.0),
  R2x (0.0),
  strapR1L (false),
  strapR2L (false),
  fc (0.0),
  ecart (std::numeric_limits <double>::max ()) {
  }

  public: Resultat (const double inR1x,
                    const double inR2x,
                    const bool inStrapR1L,
                    const bool inStrapR2L,
                    const double inFc,
                    const double inEcart) :
  R1x (inR1x),
  R2x (inR2x),
  strapR1L (inStrapR1L),
  strapR2L (inStrapR2L),
  fc (inFc),
  ecart (inEcart) {
  }

} ;

//----------------------------------------------------------------------------------------
//  Meilleur choix pour une fréquence donnée
//----------------------------------------------------------------------------------------

void afficherMeilleurChoixPourFrequence (const int inFrequence) {
//---------- Résistances
  const std::vector <double> RESISTANCES = gammeResistances () ;
//---------- Initialisation de la variable contiendra le meilleur choix
  Resultat resultat ;
//---------- Pas de résistance externe, que les straps
//--- Aucun strap
  { const double f = 1.0 / (2.0 * M_PI * sqrt (R1H * R2H * C1 * C2)) ;
    const double ecart = abs (f - double (inFrequence)) / double (inFrequence) ;
    const Resultat r = Resultat (0.0, 0.0, false, false, f, ecart) ;
    if (resultat.ecart > r.ecart) {
      resultat = r ;
    }
  }
//--- Strap R1L
  { const double f = 1.0 / (2.0 * M_PI * sqrt (par (R1H, R1L) * R2H * C1 * C2)) ;
    const double ecart = abs (f - double (inFrequence)) / double (inFrequence) ;
    const Resultat r = Resultat (0.0, 0.0, true, false, f, ecart) ;
    if (resultat.ecart > r.ecart) {
      resultat = r ;
    }
  }
//--- Strap R2L
  { const double f = 1.0 / (2.0 * M_PI * sqrt (R1H * par (R2H, R2L) * C1 * C2)) ;
    const double ecart = abs (f - double (inFrequence)) / double (inFrequence) ;
    const Resultat r = Resultat (0.0, 0.0, false, true, f, ecart) ;
    if (resultat.ecart > r.ecart) {
      resultat = r ;
    }
  }
//--- Straps R1L et R2L
  { const double f = 1.0 / (2.0 * M_PI * sqrt (par (R1H, R1L) * par (R2H, R2L) * C1 * C2)) ;
    const double ecart = abs (f - double (inFrequence)) / double (inFrequence) ;
    const Resultat r = Resultat (0.0, 0.0, true, true, f, ecart) ;
    if (resultat.ecart > r.ecart) {
      resultat = r ;
    }
  }
//---------- Uniquement R1x, R2X absente
  for (int i=0 ; i < RESISTANCES.size () ; i++) {
    const double R1x = RESISTANCES [i] ;
  //--- Aucun strap
    { const double f = 1.0 / (2.0 * M_PI * sqrt (par (R1H, R1x) * R2H * C1 * C2)) ;
      const double ecart = abs (f - double (inFrequence)) / double (inFrequence) ;
      const Resultat r = Resultat (R1x, 0.0, false, false, f, ecart) ;
      if (resultat.ecart > r.ecart) {
        resultat = r ;
      }
    }
  //--- Strap R1L
    { const double f = 1.0 / (2.0 * M_PI * sqrt (par (R1H, R1L, R1x) * R2H * C1 * C2)) ;
      const double ecart = abs (f - double (inFrequence)) / double (inFrequence) ;
      const Resultat r = Resultat (R1x, 0.0, true, false, f, ecart) ;
      if (resultat.ecart > r.ecart) {
        resultat = r ;
      }
    }
  //--- Strap R2L
    { const double f = 1.0 / (2.0 * M_PI * sqrt (par (R1H, R1x) * par (R2H, R2L) * C1 * C2)) ;
      const double ecart = abs (f - double (inFrequence)) / double (inFrequence) ;
      const Resultat r = Resultat (R1x, 0.0, false, true, f, ecart) ;
      if (resultat.ecart > r.ecart) {
        resultat = r ;
      }
    }
  //--- Straps R1L et R2L
    { const double f = 1.0 / (2.0 * M_PI * sqrt (par (R1H, R1L, R1x) * par (R2H, R2L) * C1 * C2)) ;
      const double ecart = abs (f - double (inFrequence)) / double (inFrequence) ;
      const Resultat r = Resultat (R1x, 0.0, true, true, f, ecart) ;
      if (resultat.ecart > r.ecart) {
        resultat = r ;
      }
    }
  }
//---------- Uniquement R2x, R1X absente
  for (int i=0 ; i < RESISTANCES.size () ; i++) {
    const double R2x = RESISTANCES [i] ;
  //--- Aucun strap
    { const double f = 1.0 / (2.0 * M_PI * sqrt (R1H * par (R2H, R2x) * C1 * C2)) ;
      const double ecart = abs (f - double (inFrequence)) / double (inFrequence) ;
      const Resultat r = Resultat (0.0, R2x, false, false, f, ecart) ;
      if (resultat.ecart > r.ecart) {
        resultat = r ;
      }
    }
  //--- Strap R1L
    { const double f = 1.0 / (2.0 * M_PI * sqrt (par (R1H, R1L) * par (R2H, R2x) * C1 * C2)) ;
      const double ecart = abs (f - double (inFrequence)) / double (inFrequence) ;
      const Resultat r = Resultat (0.0, R2x, true, false, f, ecart) ;
      if (resultat.ecart > r.ecart) {
        resultat = r ;
      }
    }
  //--- Strap R2L
    { const double f = 1.0 / (2.0 * M_PI * sqrt (R1H * par (R2H, R2L, R2x) * C1 * C2)) ;
      const double ecart = abs (f - double (inFrequence)) / double (inFrequence) ;
      const Resultat r = Resultat (0.0, R2x, false, true, f, ecart) ;
      if (resultat.ecart > r.ecart) {
        resultat = r ;
      }
    }
  //--- Straps R1L et R2L
    { const double f = 1.0 / (2.0 * M_PI * sqrt (par (R1H, R1L) * par (R2H, R2L, R2x) * C1 * C2)) ;
      const double ecart = abs (f - double (inFrequence)) / double (inFrequence) ;
      const Resultat r = Resultat (0.0, R2x, true, true, f, ecart) ;
      if (resultat.ecart > r.ecart) {
        resultat = r ;
       }
    }
  }
//---------- Résistances R1x et R2x
  if (CALCULER_POUR_R1X_ET_R2X) {
    for (int i=0 ; i < RESISTANCES.size () ; i++) {
      const double R1x = RESISTANCES [i] ;
      for (int j=0 ; j < RESISTANCES.size () ; j++) {
        const double R2x = RESISTANCES [j] ;
      //--- Aucun strap
        { const double f = 1.0 / (2.0 * M_PI * sqrt (par (R1H, R1x) * par (R2H, R2x) * C1 * C2)) ;
          const double ecart = abs (f - double (inFrequence)) / double (inFrequence) ;
          const Resultat r = Resultat (R1x, R2x, false, false, f, ecart) ;
          if (resultat.ecart > r.ecart) {
            resultat = r ;
          }
        }
      //--- Strap R1L
        { const double f = 1.0 / (2.0 * M_PI * sqrt (par (R1H, R1L, R1x) * par (R2H, R2x) * C1 * C2)) ;
          const double ecart = abs (f - double (inFrequence)) / double (inFrequence) ;
          const Resultat r = Resultat (R1x, R2x, true, false, f, ecart) ;
          if (resultat.ecart > r.ecart) {
            resultat = r ;
          }
        }
      //--- Strap R2L
        { const double f = 1.0 / (2.0 * M_PI * sqrt (par (R1H, R1x) * par (R2H, R2L, R2x) * C1 * C2)) ;
          const double ecart = abs (f - double (inFrequence)) / double (inFrequence) ;
          const Resultat r = Resultat (R1x, R2x, false, true, f, ecart) ;
          if (resultat.ecart > r.ecart) {
            resultat = r ;
          }
        }
      //--- Straps R1L et R2L
        { const double f = 1.0 / (2.0 * M_PI * sqrt (par (R1H, R1L, R1x) * par (R2H, R2L, R2x) * C1 * C2)) ;
          const double ecart = abs (f - double (inFrequence)) / double (inFrequence) ;
          const Resultat r = Resultat (R1x, R2x, true, true, f, ecart) ;
          if (resultat.ecart > r.ecart) {
            resultat = r ;
          }
        }
      }
    }
  }
//--- Afficher résultat
  printf (
    "| %5d Hz | %3.3f%% | %6.1f Hz |    %s    |    %s    | %7.0f | %7.0f |\n",
    inFrequence,
    resultat.ecart * 100.0,
    resultat.fc,
    resultat.strapR1L ? " on" : "off",
    resultat.strapR2L ? " on" : "off",
    resultat.R1x,
    resultat.R2x
  ) ;
}

//----------------------------------------------------------------------------------------
//  main
//----------------------------------------------------------------------------------------

int main (void) {
  printf ("*---------------------------------------------------------------------------*\n") ;
  printf ("|  F Cible |  Écart |    F réel | Strap R1L | Strap R2L |    R1x  |    R2x  |\n") ;
  printf ("*---------------------------------------------------------------------------*\n") ;
  for (int f = 400 ; f <= 1000 ; f += 50) {
    afficherMeilleurChoixPourFrequence (f) ;
  }
  for (int f = 1500 ; f <= 4000 ; f += 500) {
    afficherMeilleurChoixPourFrequence (f) ;
  }
  printf ("*---------------------------------------------------------------------------*\n") ;
}

//----------------------------------------------------------------------------------------


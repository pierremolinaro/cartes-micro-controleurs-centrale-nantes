//
//  main.swift
//  calcul-resistances-pour-8-frequences
//
//  Created by Pierre Molinaro on 06/07/2022.
//

import Foundation

let FRÉQUENCE_CIBLE_BASSE : Double =  400.0
let FRÉQUENCE_CIBLE_HAUTE : Double = 8000.0

func par (_ left : Double, _ middle : Double, _ right : Double) -> Double {
  return 1.0 / (1.0 / left + 1.0 / middle + 1.0 / right)
}

func par (_ left : Double, _ right : Double) -> Double {
  return 1.0 / (1.0 / left + 1.0 / right)
}

let SERIE_E24 = [
  100, 120, 150, 160, 180, 200, 220, 240, 270, 300, 330,
  360, 390, 430, 470, 510, 560, 620, 680, 750, 820, 910
]

func gammeRésistances () -> [Double] {
  var result = [Double] ()
  for v in SERIE_E24 {
    result.append (10.0 * Double (v))
  }
  for v in SERIE_E24 {
    result.append (100.0 * Double (v))
  }
  result.append (100_000.0)
  return result
}

let RÉSISTANCES = gammeRésistances ()
//--- Condensateurs
let C1 : Double = 4.7e-9
let C2 : Double = 4.7e-9

struct Résultat {
  let R1H : Double
  let R1M : Double
  let R1L : Double
  let R2H : Double
  let R2L : Double
  let fc : [Double]
  let écart : Double
}

let FRÉQUENCES : [Double]
do{
  let facteur = pow (FRÉQUENCE_CIBLE_HAUTE / FRÉQUENCE_CIBLE_BASSE, 1.0 / 7.0)
  var fréquences = [FRÉQUENCE_CIBLE_BASSE]
  for i in 1 ..< 8 {
    fréquences.append (fréquences [i-1] * facteur)
  }
  FRÉQUENCES = fréquences
}
Swift.print ("Fréquences cibles :")
for f in FRÉQUENCES {
  Swift.print ("  \(f) Hz")
}
let defRes = Résultat (R1H: 0.0, R1M: 0.0, R1L: 0.0, R2H: 0.0, R2L: 0.0, fc: [], écart: .greatestFiniteMagnitude)
var tableauRésultats = [Résultat] (repeating: defRes, count: 10)

for i in 2 ..< RÉSISTANCES.count {
  let R1H = RÉSISTANCES [i]
  for j in 1 ..< i {
    let R1M = RÉSISTANCES [j]
    for k in 0 ..< j {
      let R1L = RÉSISTANCES [k]
      for m in 1 ..< RÉSISTANCES.count {
        let R2H = RÉSISTANCES [m]
        for n in 0 ..< m {
          let R2L = RÉSISTANCES [n]
//          let candidates = [
//            1.0 / (2.0 * .pi * (R1L * R2L * C1 * C2).squareRoot ()),
//            1.0 / (2.0 * .pi * (R1L * (R2H + R2L) * C1 * C2).squareRoot ()),
//            1.0 / (2.0 * .pi * ((R1M + R1L) * R2H * C1 * C2).squareRoot ()),
//            1.0 / (2.0 * .pi * ((R1M + R1L) * (R2H + R2L) * C1 * C2).squareRoot ()),
//            1.0 / (2.0 * .pi * ((R1H + R1L) * R2L * C1 * C2).squareRoot ()),
//            1.0 / (2.0 * .pi * ((R1H + R1L) * (R2H + R2L) * C1 * C2).squareRoot ()),
//            1.0 / (2.0 * .pi * ((R1H + R1M + R1L) * R2H * C1 * C2).squareRoot ()),
//            1.0 / (2.0 * .pi * ((R1H + R1M + R1L) * (R2H + R2L) * C1 * C2).squareRoot ()),
//          ].sorted ()
          let candidates = [
            1.0 / (2.0 * .pi * (R1H * R2H * C1 * C2).squareRoot ()),
            1.0 / (2.0 * .pi * (R1H * par (R2H, R2L) * C1 * C2).squareRoot ()),
            1.0 / (2.0 * .pi * (par (R1H, R1L) * R2H * C1 * C2).squareRoot ()),
            1.0 / (2.0 * .pi * (par (R1H, R1L) * par (R2H, R2L) * C1 * C2).squareRoot ()),
            1.0 / (2.0 * .pi * (par (R1H, R1M) * R2H * C1 * C2).squareRoot ()),
            1.0 / (2.0 * .pi * (par (R1H, R1M) * par (R2H, R2L) * C1 * C2).squareRoot ()),
            1.0 / (2.0 * .pi * (par (R1H, R1M, R1L) * R2H * C1 * C2).squareRoot ()),
            1.0 / (2.0 * .pi * (par (R1H, R1M, R1L) * par (R2H, R2L) * C1 * C2).squareRoot ())
          ].sorted ()
          var écart = 0.0
          for i in 0 ..< 7 {
            let e = (FRÉQUENCES [i] - candidates [i]) / FRÉQUENCES [i]
            écart += e * e
          }
          var résultat = Résultat (
            R1H: R1H, R1M: R1M, R1L: R1L, R2H: R2H, R2L: R2L,
            fc: candidates,
            écart: écart
          )
          for i in 0 ..< tableauRésultats.count {
            if résultat.écart < tableauRésultats [i].écart {
              (résultat, tableauRésultats [i]) = (tableauRésultats [i], résultat)
            }
          }
        }
      }
    }
  }
}

for résultat in tableauRésultats {
  var s = "Écart \(résultat.écart), fréquences :"
  for f in résultat.fc {
    s += " \(Int (f))"
  }
  s += " pour R1H = \(Int (résultat.R1H)), R1M = \(Int (résultat.R1M)), R1L = \(Int (résultat.R1L)), R2H = \(Int (résultat.R2H)), R2L = \(Int (résultat.R2L))"
  Swift.print (s)
}

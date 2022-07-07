//
//  main.swift
//  calcul-resistances-pour-4-frequences
//
//  Created by Pierre Molinaro on 06/07/2022.
//

import Foundation

let FRÉQUENCE_CIBLE_BASSE : Double =  400.0
let FRÉQUENCE_CIBLE_HAUTE : Double = 4_000.0

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
  let R1L : Double
  let R2H : Double
  let R2L : Double
  let fc0 : Double
  let fc1 : Double
  let fc2 : Double
  let fc3 : Double
  let écart : Double
}

let factor = pow (FRÉQUENCE_CIBLE_HAUTE / FRÉQUENCE_CIBLE_BASSE, 1.0 / 3.0)
let FRÉQUENCES  = [FRÉQUENCE_CIBLE_BASSE, FRÉQUENCE_CIBLE_BASSE * factor, FRÉQUENCE_CIBLE_BASSE * factor * factor, FRÉQUENCE_CIBLE_HAUTE]
Swift.print ("Fréquences cibles :")
for f in FRÉQUENCES {
  Swift.print ("  \(f) Hz")
}
let defRes = Résultat (R1H: 0.0, R1L: 0.0, R2H: 0.0, R2L: 0.0, fc0: 0.0, fc1: 0.0, fc2: 0.0, fc3: 0.0, écart: .greatestFiniteMagnitude)
var tableauRésultats = [Résultat] (repeating: defRes, count: 10)

for i in 1 ..< RÉSISTANCES.count {
  let R1H = RÉSISTANCES [i]
  for j in 0 ..< i {
    let R1L = RÉSISTANCES [j]
    for k in 1 ... i {
      let R2H = RÉSISTANCES [k]
      for m in 0 ..< k {
        let R2L = RÉSISTANCES [m]
        let candidates = [
          1.0 / (2.0 * .pi * (R1H * R2H * C1 * C2).squareRoot ()),
          1.0 / (2.0 * .pi * (R1H * par (R2H, R2L) * C1 * C2).squareRoot ()),
          1.0 / (2.0 * .pi * (par (R1H, R1L) * R2H * C1 * C2).squareRoot ()),
          1.0 / (2.0 * .pi * (par (R1H, R1L) * par (R2H, R2L) * C1 * C2).squareRoot ())
        ].sorted ()
        var écart = 0.0
        for w in 0 ..< 3 {
          let e = (FRÉQUENCES [w] - candidates [w]) / FRÉQUENCES [w]
          écart += e * e
        }
        var résultat = Résultat (
          R1H: R1H, R1L: R1L, R2H: R2H, R2L: R2L,
          fc0: candidates [0], fc1: candidates [1], fc2: candidates [2], fc3: candidates [3],
          écart: écart
        )
        for w in 0 ..< tableauRésultats.count {
          if résultat.écart < tableauRésultats [w].écart {
            (résultat, tableauRésultats [w]) = (tableauRésultats [w], résultat)
          }
        }
      }
    }
  }
}

for résultat in tableauRésultats {
  print("Écart \(résultat.écart), fc \(Int (résultat.fc0)), \(Int (résultat.fc1)), \(Int (résultat.fc2)), \(Int (résultat.fc3)) pour R1H = \(Int (résultat.R1H)), R1L = \(Int (résultat.R1L)), R2H = \(Int (résultat.R2H)), R2L = \(Int (résultat.R2L))")
}

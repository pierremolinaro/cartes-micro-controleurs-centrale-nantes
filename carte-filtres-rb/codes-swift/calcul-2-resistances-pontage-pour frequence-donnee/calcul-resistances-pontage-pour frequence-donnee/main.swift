//
//  main.swift
//  calcul-resistances-pontage-pour frequence-donnee
//
//  Created by Pierre Molinaro on 07/07/2022.
//

import Foundation

let FRÉQUENCE_BASSE : Int = 400
let FRÉQUENCE_HAUTE : Int = 1_000

let FRÉQUENCE_CIBLE : Double = 2_000.0

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
  for v in SERIE_E24 {
    result.append (1_000.0 * Double (v))
  }
  for v in SERIE_E24 {
    result.append (10_000.0 * Double (v))
  }
  result.append (10_000_000.0)
  result.append (1_000_000_000.0)
  return result
}

let RÉSISTANCES = gammeRésistances ()
//--- Condensateurs
let R1H = 91_000.0
let R1L = 24_000.0
let R2H = 82_000.0
let R2L = 3_900.0
let C1 : Double = 4.7e-9
let C2 : Double = 4.7e-9

struct Résultat {
  let R1x : Double
  let R1Lon : Bool
  let R2x : Double
  let R2Lon : Bool
  let fCible  : Double
  let fc  : Double
  let écart : Double
}

func meilleursRésultats (_ inFréquence : Double, _ nombreRésulats : Int) -> [Résultat] {
  let defRes = Résultat (R1x: 0.0, R1Lon: false, R2x: 0.0, R2Lon: false, fCible: 0.0, fc: 0.0, écart: .greatestFiniteMagnitude)
  var tableauRésultats = [Résultat] (repeating: defRes, count: nombreRésulats)

  for i in 0 ..< RÉSISTANCES.count {
    let R1x = RÉSISTANCES [i]
    for j in 0 ..< RÉSISTANCES.count {
      let R2x = RÉSISTANCES [j]
    //---
      let fréquenceCoupures = [
        (1.0 / (2.0 * .pi * (par (R1H, R1x) * par (R2H, R2x) * C1 * C2).squareRoot ()), false, false),
        (1.0 / (2.0 * .pi * (par (R1H, R1L, R1x) * par (R2H, R2x) * C1 * C2).squareRoot ()), true, false),
        (1.0 / (2.0 * .pi * (par (R1H, R1x) * par (R2H, R2L, R2x) * C1 * C2).squareRoot ()), false, true),
        (1.0 / (2.0 * .pi * (par (R1H, R1L, R1x) * par (R2H, R2L, R2x) * C1 * C2).squareRoot ()), true, true)
      ]
      for (f, r1lOn, r2lOn) in fréquenceCoupures {
        let écart = 100.0 * abs (f - inFréquence) / inFréquence
        var résultat = Résultat (
          R1x: R1x, R1Lon: r1lOn, R2x: R2x, R2Lon: r2lOn,
          fCible: inFréquence, fc: f,
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
  return tableauRésultats
}

for résultat in meilleursRésultats (FRÉQUENCE_CIBLE, 50) {
  print("Cible \(résultat.fCible), écart \(résultat.écart) %, fc \(Int (résultat.fc)) pour R1x = \(Int (résultat.R1x)), R1Lon \(résultat.R1Lon), R2x = \(Int (résultat.R2x)), R2Lon \(résultat.R2Lon)")
}

Swift.print ("Balayage...")
let defRes = Résultat (R1x: 0.0, R1Lon: false, R2x: 0.0, R2Lon: false, fCible: 0.0, fc: 0.0, écart: 0.0)
var tableauRésultats = [Résultat] (repeating: defRes, count: 20)

for f in FRÉQUENCE_BASSE ... FRÉQUENCE_HAUTE {
  var résultat = meilleursRésultats (Double (f), 1) [0]
  for i in 0 ..< tableauRésultats.count {
    if résultat.écart > tableauRésultats [i].écart {
      (résultat, tableauRésultats [i]) = (tableauRésultats [i], résultat)
    }
  }
}

for résultat in tableauRésultats {
  print("Cible \(résultat.fCible), écart \(résultat.écart) %, fc \(Int (résultat.fc)) pour R1x = \(Int (résultat.R1x)), R1Lon \(résultat.R1Lon), R2x = \(Int (résultat.R2x)), R2Lon \(résultat.R2Lon)")
}

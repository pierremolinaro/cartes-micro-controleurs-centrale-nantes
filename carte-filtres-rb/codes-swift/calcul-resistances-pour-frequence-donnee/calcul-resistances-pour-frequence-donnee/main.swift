//
//  main.swift
//  frequence-coupure
//
//  Created by Pierre Molinaro on 03/05/2023.
//
//-------------------------------------------------------------------------------------------------

import Foundation

//-------------------------------------------------------------------------------------------------

func fréquenceCoupure (R1 inR1 : Double,
                       R2 inR2: Double,
                       C1 inC1 : Double,
                       C2 inC2 : Double) -> (Double, Double, Double) {
  let Fc = 1.0 / (2.0 * Double.pi * sqrt (inR1 * inR2 * inC1 * inC2))
  let Q = sqrt (inR1 * inR2 * inC1 * inC2) / ((inR1 + inR2) * inC1)
  let Q2 = Q * Q
  let Q4 = Q2 * Q2
  let F_COUPURE = Fc * sqrt (2.0 * Q2 - 1.0 + sqrt (1.0 - 4.0 * Q2 + 8 * Q4)) / (Q * sqrt (2.0))
  return (F_COUPURE, Fc, Q)
}

//-------------------------------------------------------------------------------------------------

enum STRAP : CaseIterable {
  case off
  case on
}

//-------------------------------------------------------------------------------------------------

struct CONFIG {
  let r1x : Int?
  let strap1 : STRAP
  let r2x : Int?
  let strap2 : STRAP
  let écartPourCent : Double
  let fréquenceCorner : Double
  let Q : Double
}

//-------------------------------------------------------------------------------------------------

func r1eq (R1X inR1X : Int?, strap1 inStrap1 : STRAP) -> Double {
  var y = 1.0 / 91_000.0 // résistance fixe
  if let r1x = inR1X {
    y += 1.0 / Double (r1x)
  }
  if inStrap1 == .on {
    y += 1.0 / 24_000.0  // résistance fixe
  }
  return 1.0 / y
}

//-------------------------------------------------------------------------------------------------

func r2eq (R2X inR2X : Int?, strap2 inStrap2 : STRAP) -> Double {
  var y = 1.0 / 82_000.0 // résistance fixe
  if let r2x = inR2X {
    y += 1.0 / Double (r2x)
  }
  if inStrap2 == .on {
    y += 1.0 / 3_900.0  // résistance fixe
  }
  return 1.0 / y
}

//-------------------------------------------------------------------------------------------------

let C1 = 4.7e-9
let C2 = 4.7e-9

let (F_COUPURE, Fc, Q) = fréquenceCoupure (R1: 91_000, R2: 82_000, C1: C1, C2: C2)
//let (F_COUPURE, Fc, Q) = fréquenceCoupure (R1: 15_420, R2: 37_173, C1: C1, C2: C2)
print ("Sans composant ajouté")
print ("  F_COUPURE \(F_COUPURE)")
print ("  Fc \(Fc)")
print ("  Gain à Fc \(Q) -> \(20.0 * log10 (Q))")

let RÉSISTANCES : [Int?] = [
  3_900, 24_000, 30_000, 47_000, 68_000, 82_000, 91_000,
  150_000, 180_000, 270_000, 510_000, 680_000,
  nil // Pas de résistance
]

let fréquenceCoupureDepart = 350
let fréquenceCoupureFin    = 900
let pas                    =  25

var f = fréquenceCoupureDepart
while f <= fréquenceCoupureFin {
  var meilleureConfig = CONFIG (r1x: 0, strap1: .off, r2x: 0, strap2: .off, écartPourCent: 1_000_000.0, fréquenceCorner: 0.0, Q: 0.0)
  for r1x in RÉSISTANCES {
    for r2x in RÉSISTANCES {
      for strap1 in STRAP.allCases {
        for strap2 in STRAP.allCases {
          let (ff, fc, Q) = fréquenceCoupure (R1: r1eq (R1X: r1x, strap1: strap1), R2: r2eq (R2X: r2x, strap2: strap2), C1: C1, C2: C2)
          let écart = 100.0 * abs (ff - Double (f)) / Double (f)
          if écart < meilleureConfig.écartPourCent {
            meilleureConfig = CONFIG (r1x: r1x, strap1: strap1, r2x: r2x, strap2: strap2, écartPourCent: écart, fréquenceCorner: fc, Q: Q)
          }
        }
      }
    }
  }
  var s = "\(f) Hz ; \(ceil (meilleureConfig.écartPourCent * 1000.0) / 1000.0) % ; "
  if let r1x = meilleureConfig.r1x {
    s += "\(r1x) Ω"
  }else{
    s += "-"
  }
  s += " ; " + ((meilleureConfig.strap1 == .on) ? "ON" : "OFF") + " ; "
  if let r2x = meilleureConfig.r2x {
    s += "\(r2x) Ω"
  }else{
    s += "-"
  }
  s += " ; " + ((meilleureConfig.strap2 == .on) ? "ON" : "OFF")
  s += " ; \(ceil (meilleureConfig.fréquenceCorner * 1000.0) / 1000.0) Hz"
  s += " ; \(ceil (meilleureConfig.Q * 1000.0) / 1000.0)"
  s += " ; \(ceil (20_000.0 * log10 (meilleureConfig.Q)) / 1000.0) dB"
  print (s)

//  print ("Pour f_COUPURE = \(f)")
//  print ("  R1X = \(meilleureConfig.r1x) Ω")
//  print ("  strap1 = \(meilleureConfig.strap1)")
//  print ("  R2X = \(meilleureConfig.r2x) Ω")
//  print ("  strap2 = \(meilleureConfig.strap2)")
//  print ("  écart = \(meilleureConfig.écartPourCent) %")
//  print ("  fréquence « corner » = \(meilleureConfig.fréquenceCorner) Hz")
//  print ("  Gain à cette fréquence = \(meilleureConfig.Q) -> \(20.0 * log10 (meilleureConfig.Q))")
  f += pas
}

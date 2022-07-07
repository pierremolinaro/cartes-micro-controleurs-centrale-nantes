//
//  main.swift
//  calcul-frequences-coupure
//
//  Created by Pierre Molinaro on 06/07/2022.
//

import Foundation

func par (_ left : Double, _ right : Double) -> Double {
  return 1.0 / (1.0 / left + 1.0 / right)
}

func par (_ left : Double, _ middle : Double, _ right : Double) -> Double {
  return 1.0 / (1.0 / left + 1.0 / middle + 1.0 / right)
}

//--- Résistances R1
let R1H : Double = 120_000.0
let R1M : Double = 12_000.0
let R1L : Double = 1_200.0
//--- Résistances R2
let R2H : Double = 68_000.0
let R2L : Double = 22_000.0
//--- Condensateurs
let C1 : Double = 4.7e-9
let C2 : Double = 4.7e-9
//---
let R1s = [R1H, par (R1H, R1L), par (R1H, R1M), par (R1H, R1M, R1L)]
let R2s = [R2H, par (R2L, R2H)]
for r1 in R1s {
  for r2 in R2s {
    let wc = (r1 * r2 * C1 * C2).squareRoot ()
    let fc = 1.0 / (2.0 * .pi * wc)
    Swift.print ("r1 \(r1), r2 \(r2) -> fc \(fc)")
  }
}

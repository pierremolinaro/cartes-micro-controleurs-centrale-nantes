#pragma once

#include <Arduino.h>

#ifndef ARDUINO_SAMD_FEATHER_M0
  #error "Ce croquis doit être compilé pour le type de carte 'Adafruit Feather M0'"
#endif

#pragma GCC diagnostic error "-Wsign-conversion"
#pragma GCC diagnostic error "-Wsign-compare"
#pragma GCC diagnostic error "-Wunused-value"
#pragma GCC diagnostic error "-Wunused-parameter"
#pragma GCC diagnostic error "-Wmissing-prototypes"
#pragma GCC diagnostic error "-Wparentheses"
#pragma GCC diagnostic error "-Wall"
#pragma GCC diagnostic error "-Wpointer-arith"
#pragma GCC diagnostic error "-Wundef"


#! /usr/bin/env python3
# -*- coding: UTF-8 -*-
#-------------------------------------------------------------------------------

import sys, os, subprocess

#-------------------------------------------------------------------------------

#--- Get script absolute path
scriptDir = os.path.dirname (os.path.abspath (sys.argv [0]))
os.chdir (scriptDir)
#---
toolDir = os.path.expanduser ("~/Library/Arduino15/packages/rp2040/tools/pqt-pioasm")
found = False
for aDir in sorted (os.listdir (toolDir)) :
  pioasmTool = (toolDir + "/" + aDir + "/pioasm")
  if os.path.exists (pioasmTool) :
    found = True
    returncode = subprocess.call ([pioasmTool, "ws2812x2.pioasm", "pio-ws2812x2.h"])
    #--- Wait for subprocess termination
    if returncode != 0 :
      sys.exit (returncode)
if not found :
  print (RED () + BOLD () + "Cannot find pioasm" + ENDC ())

#-------------------------------------------------------------------------------

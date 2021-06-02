#! /usr/bin/env python3
# -*- coding: UTF-8 -*-
#---------------------------------------------------------------------------------------------------

import sys, os, subprocess

#---------------------------------------------------------------------------------------------------

#--- Get script absolute path
scriptDir = os.path.dirname (os.path.abspath (sys.argv [0]))
os.chdir (scriptDir)
#---
pioasmTool = os.path.expanduser ("~/Library/Arduino15/packages/rp2040/tools/pqt-pioasm/1.1.0-a-81a1771/pioasm")
returncode = subprocess.call ([pioasmTool, "charlieplexing.pioasm", "pio-charlieplexing.h"])
#--- Wait for subprocess termination
if returncode != 0 :
  sys.exit (returncode)

#---------------------------------------------------------------------------------------------------

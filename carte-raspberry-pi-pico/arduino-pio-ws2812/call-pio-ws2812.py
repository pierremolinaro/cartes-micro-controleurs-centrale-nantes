#! /usr/bin/env python3
# -*- coding: UTF-8 -*-
#---------------------------------------------------------------------------------------------------

import sys, os, subprocess

#---------------------------------------------------------------------------------------------------

#--- Get script absolute path
scriptDir = os.path.dirname (os.path.abspath (sys.argv [0]))
os.chdir (scriptDir)
#---
pioasmTool = os.path.expanduser ("~/Library/Arduino15/packages/rp2040/tools/pqt-pioasm/1.2.0-a-407f016/pioasm")
returncode = subprocess.call ([pioasmTool, "ws2812.pioasm", "pio-ws2812.h"])
#--- Wait for subprocess termination
if returncode != 0 :
  sys.exit (returncode)

#---------------------------------------------------------------------------------------------------

#pragma once

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Arduino.h>
#include <SPI.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include "CANMessage.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

class MCP2515 {
//--- Constructor
  public : MCP2515 (SPIClass & inSPI, const byte inMCP2515_CS) ;

//--- begin
  public : uint32_t begin (const bool inLoopBack) ;

//--- Send a frame
  public : bool tryToSend (const CANMessage & inMessage) ;

//--- Receive a frame
  public : bool receive (CANMessage & outMessage) ;

//------- Internal
//--- MCP2515 register access
  private : void writeRegister (const byte inRegisterAddress, const byte inValue) ;
  private : byte readRegister (const byte inRegisterAddress) ;
  private : byte readStatus (void) ;
  private : byte readReceptionStatus (void) ;
  private : void writeRegisterBit (const byte inRegisterAddress, const byte inBitIndex, const bool inValue) ;
  private : void requestToSend (const byte inBufferIndex) ;

//--- Configure
  private : void configure (const bool inLoopBack) ;

//--- No copy
  private : MCP2515 (const MCP2515 &) ;
  private : MCP2515 & operator = (const MCP2515 &) ;

//--- Properties
  private : SPIClass & mSPI ;
  private : const byte mMCP2515_CS ;
} ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


#ifndef MCP2515_h
#define MCP2515_h

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Arduino.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

class CANFrame {
  public : uint32_t id = 0 ;
  public : bool ext = false ;
  public : bool rtr = false ;
  public : uint8_t len = 0 ;
  public : union {
    uint64_t buf64 = 0 ;
    uint32_t buf32 [2] ;
    uint16_t buf16 [4] ;
    uint8_t  buf   [8] ;
  } ;
} ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

class MCP2515 {
//--- Constructor
  public : MCP2515 (const byte inCS,  // CS input of MCP2515
                    const byte inCLK, // CLK input of MCP2515
                    const byte inSI,  // SI input of MCP2515
                    const byte inSO,  // SO output of MCP2515
                    const byte inIRQ) ; // IRQ output of MCP2515

 //--- Initialisation: return true if ok
   public : bool begin (void) ;

 //--- Receiving messages
   public : bool available (void) ;
   public : bool getReceivedMessage (CANFrame & outFrame) ;

 //--- Sending message
   public : bool sendMessage (const CANFrame & inFrame) ;
   
 //--- Properties
  private : const byte mCS ;
  private : const byte mCLK ;
  private : const byte mSI ;
  private : const byte mSO ;
  private : const byte mIRQ ;

//--- Private methods
  private : void sendByte (const byte inByte) ;
  private : byte readByte (void) ;
  private : void writeRegister (const byte inRegister, const byte inValue) ;
  private : byte readRegister (const byte inRegister) ;
  private : byte readStatus (void) ;
  private : byte readRxStatus (void) ;
  private : void bitModifyRegister (const uint8_t inRegister, const uint8_t inMask, const uint8_t inData) ;

//--- No Copy
  private : MCP2515 (const MCP2515 &) ;
  private : MCP2515 & operator = (const MCP2515 &) ;
} ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#endif

#include "MCP2515.h"
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static const unsigned SPIClockFrequency = 10 * 1000 * 1000 ; // 10 MHz

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

MCP2515::MCP2515 (SPIClass & inSPI, const byte inMCP2515_CS) :
  mSPI (inSPI),
  mMCP2515_CS (inMCP2515_CS) {
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

uint32_t MCP2515::begin (const bool inLoopBack) {
  uint32_t result = 0 ; // Means no error
  pinMode (mMCP2515_CS, OUTPUT) ;
  digitalWrite (mMCP2515_CS, HIGH) ;
//--- Check register access
  for (int i=0 ; i<256 ; i++) {
    writeRegister (0x36, (byte) i) ;
    const byte b = readRegister (0x36) ;
    if (b != (byte) i) {
      result |= 1 ;
    }
  }
//--- If ok, configure to 125 kbit/s, assume a 16 MHz quartz
  if (0 == result) {
    configure (inLoopBack) ;   
  }
//---
  return result ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
//   MCP2515 register addresses

static const byte RXF0SIDH = 0x00 ;
static const byte RXF0SIDL = 0x01 ;
static const byte RXF0EID8 = 0x02 ;
static const byte RXF0EID0 = 0x03 ;
static const byte CANSTAT  = 0x0E ;
static const byte CANCTRL  = 0x0F ;
static const byte CNF3     = 0x28 ;
static const byte CNF2     = 0x29 ;
static const byte CNF1     = 0x2A ;
static const byte CANINTF  = 0x2C ;
static const byte TXB0CTRL = 0x30 ;
static const byte TXB0SIDH = 0x31 ;
static const byte TXB0SIDL = 0x32 ;
static const byte TXB0EID8 = 0x33 ;
static const byte TXB0EID0 = 0x34 ;
static const byte TXB0DLC  = 0x35 ;
static const byte TXB0D0   = 0x36 ;
static const byte RXB0CTRL = 0x60 ;
static const byte RXB0SIDH = 0x61 ;
static const byte RXB0SIDL = 0x62 ;
static const byte RXB0EID8 = 0x63 ;
static const byte RXB0EID0 = 0x64 ;
static const byte RXB0DLC  = 0x65 ;
static const byte RXB0D0   = 0x66 ;
static const byte RXB1CTRL = 0x70 ;
static const byte RXB1SIDH = 0x71 ;
static const byte RXB1SIDL = 0x72 ;
static const byte RXB1EID8 = 0x73 ;
static const byte RXB1EID0 = 0x74 ;
static const byte RXB1DLC  = 0x75 ;
static const byte RXB1D0   = 0x76 ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void MCP2515::configure (const bool inLoopBack) {
//--- Request configuration mode
  writeRegister (CANCTRL, 0x80) ;
//--- Wait the MCP2515 is actually in configuration mode
  while ((readRegister (CANSTAT) & 0xE0) != 0x80) {}
//--- Bit rate and quartz frequency
  const unsigned bitRate = 125 * 1000 ;
  const unsigned quartzFrequency = 16 * 1000 * 1000 ; // 16 MHz
//--- Time quantum TQ: TQ = (quartzFrequency / 2) / BRP
//--- Bit rate: bitRate = TQ * B
//    So: BRP = quartzFrequency / (bitRate * 2 * B)
  const unsigned B = 16 ;
  const unsigned BRP = quartzFrequency / (bitRate * 2 * B) ;
//--- Bit decomposition: B = 16, with the requirements
//  B = 1 + PropSeg + PS1 + PS2
//  PropSeg+PS1 >= PS2
//  PropSeg+PS1 >= TDELAY
//  PS2 > SJW
//--- We choose
   const byte PropSeg = 5 ;
   const byte PS1 = 5 ;
   const byte PS2 = 5 ;
   const byte SJW = 3 ;
//--- Register CNF1
// Bits 7 and 6: SJW - 1
// Bits 5 to 0: BaudRatePrescaler - 1
  writeRegister (CNF1, ((SJW - 1) << 6) | (((byte) BRP) - 1)) ;
//--- Register CNF2
// Bit 7: 1 (BLTMODE, we use PS2 value)
// Bit 6: 1 (SAM, triple sampling)
// Bits 5 to 3 : PS1 - 1
// Bits 2 to 0 : PropSeg - 1
  writeRegister (CNF2, (1 << 7) | (1 << 6) | ((PS1 - 1) << 3) | (PropSeg - 1)) ;
//--- Register CNF3
// Bit 7: 0 (Don't care, as CANCTRL<2> == 0)
// Bit 6: 0 (Wake-up filter is disabled)
// Bits 2 to 0 : PS2 - 1
  writeRegister (CNF3, PS2 - 1) ;
//--- Configure RXB0 to receive any message
  writeRegister (RXB0CTRL, 0) ;
//--- Configure RXB1 to receive any message
  writeRegister (RXB1CTRL, 0) ;
//--- Activate in loopback mode or normal mode
  const byte mode = inLoopBack ? 0x40 : 0x00 ;
  writeRegister (CANCTRL, mode) ;
//--- Wait the MCP2515 is actually in configuration mode
  while ((readRegister (CANSTAT) & 0xE0) != mode) {}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void MCP2515::writeRegister (const byte inRegisterAddress, const byte inValue) {
  digitalWrite (mMCP2515_CS, LOW) ;
  mSPI.beginTransaction (SPISettings (SPIClockFrequency, MSBFIRST, SPI_MODE0)) ;
  mSPI.transfer (0x02) ; // Write register
  mSPI.transfer (inRegisterAddress) ;
  mSPI.transfer (inValue) ;
  mSPI.endTransaction () ;
  digitalWrite (mMCP2515_CS, HIGH) ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void MCP2515::requestToSend (const byte inBufferIndex) {
  digitalWrite (mMCP2515_CS, LOW) ;
  mSPI.beginTransaction (SPISettings (SPIClockFrequency, MSBFIRST, SPI_MODE0)) ;
  mSPI.transfer (0x80 | (1 << inBufferIndex)) ; // Request to send instruction
  mSPI.endTransaction () ;
  digitalWrite (mMCP2515_CS, HIGH) ;   
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

byte MCP2515::readRegister (const byte inRegisterAddress) {
  digitalWrite (mMCP2515_CS, LOW) ;
  mSPI.beginTransaction (SPISettings (SPIClockFrequency, MSBFIRST, SPI_MODE0)) ;
  mSPI.transfer (0x03) ; // Read register
  mSPI.transfer (inRegisterAddress) ;
  const byte result = mSPI.transfer (0x00) ;
  mSPI.endTransaction () ;
  digitalWrite (mMCP2515_CS, HIGH) ;
  return result ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

byte MCP2515::readStatus (void) {
  digitalWrite (mMCP2515_CS, LOW) ;
  mSPI.beginTransaction (SPISettings (SPIClockFrequency, MSBFIRST, SPI_MODE0)) ;
  mSPI.transfer (0xA0) ; // Read status instruction
  const byte status = mSPI.transfer (0x00) ;
  mSPI.endTransaction () ;
  digitalWrite (mMCP2515_CS, HIGH) ;
  return status ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

byte MCP2515::readReceptionStatus (void) {
  digitalWrite (mMCP2515_CS, LOW) ;
  mSPI.beginTransaction (SPISettings (SPIClockFrequency, MSBFIRST, SPI_MODE0)) ;
  mSPI.transfer (0xB0) ; // Read RX status instruction
  const byte status = mSPI.transfer (0x00) ;
  mSPI.endTransaction () ;
  digitalWrite (mMCP2515_CS, HIGH) ;
  return status ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void MCP2515::writeRegisterBit (const byte inRegisterAddress, const byte inBitIndex, const bool inValue) {
  digitalWrite (mMCP2515_CS, LOW) ;
  mSPI.beginTransaction (SPISettings (SPIClockFrequency, MSBFIRST, SPI_MODE0)) ;
  mSPI.transfer (0x05) ; // Bit modify register
  mSPI.transfer (inRegisterAddress) ;
  mSPI.transfer (1 << inBitIndex) ; // Mask
  mSPI.transfer (inValue ? 0xFF : 0x00) ; // Value
  mSPI.endTransaction () ;
  digitalWrite (mMCP2515_CS, HIGH) ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool MCP2515::tryToSend (const CANMessage & inMessage) {
//--- Try to send throught TXB0: first check if it is free, by testing TXREQ bit (bit 3)
  const bool ok = (readRegister (TXB0CTRL) & (1 << 3)) == 0 ;
//--- If ok, send the frame
  if (ok) {
    const unsigned frameLength = (inMessage.len <= 8) ? inMessage.len : 8 ;
    if (inMessage.ext) {
    //--- SIDH
      writeRegister (TXB0SIDH, (byte) (inMessage.id >> 21)) ;
    //--- SIDL (bit 3 is EXT bit)
      const unsigned sidl = ((inMessage.id >> 16) & 3) | (1 << 3) | ((inMessage.id >> 18) & 7) ;
      writeRegister (TXB0SIDL, (byte) sidl) ;
    //--- EID8
      writeRegister (TXB0EID8, (byte) (inMessage.id >> 8)) ;
    //--- EID0
      writeRegister (TXB0EID0, (byte) inMessage.id) ;
    }else{ // Standard frame
    //--- SIDH
      writeRegister (TXB0SIDH, (byte) (inMessage.id >> 3)) ;
    //--- SIDL
      writeRegister (TXB0SIDL, (byte) (inMessage.id << 5)) ;
    }
  //--- DLC (bit 6 is RTR bit)
    writeRegister (TXB0DLC, frameLength | (inMessage.rtr ? 0x40 : 0x00)) ;
  //--- Copy data
    if (!inMessage.rtr) {
      for (unsigned i=0 ; i<frameLength ; i++) {
        writeRegister (TXB0D0 + i, inMessage.data [i]) ;    
      }
    }
  //--- Request to send frame
    requestToSend (0) ;
  }
//---
  return ok ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

 bool MCP2515::receive (CANMessage & outMessage) {
   bool received = false ; // By default, ne received message
 //--- Read reception status
   const byte receptionStatus = readReceptionStatus () ;
 //--- Message in RXB0 ?
   if ((receptionStatus & (1 << 6)) != 0) {
     received = true ;
     outMessage.ext = (receptionStatus & (1 << 3)) != 0 ;
     outMessage.rtr = (receptionStatus & (1 << 4)) != 0 ;
  //--- Read RXB0SIDH
     outMessage.id = readRegister (RXB0SIDH) ;
   //--- Read RXB0SIDL, and RXB0EID8, RXB0EID0 if extended frame
     const byte SIDL = readRegister (RXB0SIDL) ;
     outMessage.id <<= 3 ;
     outMessage.id |= (SIDL >> 5) ;
     if (outMessage.ext) {
       outMessage.id <<= 2 ;
       outMessage.id |= SIDL & 3 ;
       outMessage.id <<= 8 ;
       outMessage.id |= readRegister (RXB0EID8) ;
       outMessage.id <<= 8 ;
       outMessage.id |= readRegister (RXB0EID0) ;
     }
   //--- Read RXB0DLC
     const byte DLC = readRegister (RXB0DLC) ;
     outMessage.len = DLC & 0x0F ;
   //--- Read data
     if (!outMessage.rtr) {
       for (unsigned i=0 ; i<outMessage.len ; i++) {
         outMessage.data [i] = readRegister (RXB0D0 + i) ;
       }
     }
   //--- Clear read interrupt
     writeRegisterBit (CANINTF, 0, false) ;
 //--- Message in RXB1 ?
   }else if ((receptionStatus & (1 << 7)) != 0) {
     received = true ;
     outMessage.ext = (receptionStatus & (1 << 3)) != 0 ;
     outMessage.rtr = (receptionStatus & (1 << 4)) != 0 ;
  //--- Read RXB0SIDH
     outMessage.id = readRegister (RXB1SIDH) ;
   //--- Read RXB1SIDL, and RXB1EID8, RXB1EID0 if extended frame
     const byte SIDL = readRegister (RXB1SIDL) ;
     outMessage.id <<= 3 ;
     outMessage.id |= (SIDL >> 5) ;
     if (outMessage.ext) {
       outMessage.id <<= 2 ;
       outMessage.id |= SIDL & 3 ;
       outMessage.id <<= 8 ;
       outMessage.id |= readRegister (RXB1EID8) ;
       outMessage.id <<= 8 ;
       outMessage.id |= readRegister (RXB1EID0) ;
     }
   //--- Read RXB0DLC
     const byte DLC = readRegister (RXB1DLC) ;
     outMessage.len = DLC & 0x0F ;
   //--- Read data
     if (!outMessage.rtr) {
       for (unsigned i=0 ; i<outMessage.len ; i++) {
         outMessage.data [i] = readRegister (RXB1D0 + i) ;
       }
     }
   //--- Clear read interrupt
     writeRegisterBit (CANINTF, 1, false) ;
   }
 //---
   return received ;
 }

 //——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


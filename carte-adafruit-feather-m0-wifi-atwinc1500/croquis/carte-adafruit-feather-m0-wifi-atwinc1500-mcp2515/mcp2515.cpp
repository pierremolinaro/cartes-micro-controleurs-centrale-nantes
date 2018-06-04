#include "mcp2515.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

const byte RESET_COMMAND = 0xC0 ;
const byte WRITE_COMMAND = 0x02 ;
const byte READ_COMMAND  = 0x03 ;
const byte BIT_MODIFY_COMMAND  = 0x05 ;
const byte LOAD_TX_BUFFER_COMMAND = 0x40 ;
const byte SEND_COMMAND = 0x80 ;
const byte READ_FROM_RXB0SIDH_COMMAND = 0x90 ;
const byte READ_FROM_RXB1SIDH_COMMAND = 0x94 ;
const byte READ_STATUS_COMMAND = 0xA0 ;
const byte RX_STATUS_COMMAND = 0xB0 ;

const byte BFPCTRL_REGISTER   = 0x0C ;
const byte TXRTSCTRL_REGISTER = 0x0D ;
const byte CANCTRL_REGISTER   = 0x0F ;
const byte CNF3_REGISTER      = 0x28 ;
const byte CNF2_REGISTER      = 0x29 ;
const byte CNF1_REGISTER      = 0x2A ;
const byte CANINTF_REGISTER   = 0x2C ;
const byte RXB0CTRL_REGISTER  = 0x60 ;
const byte RXB1CTRL_REGISTER  = 0x70 ;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

MCP2515::MCP2515 (const byte inCS,
                  const byte inCLK,
                  const byte inSI,
                  const byte inSO,
                  const byte inIRQ) :
mCS (inCS),
mCLK (inCLK),
mSI (inSI),
mSO (inSO),
mIRQ (inIRQ) {
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool MCP2515::begin (void) {
//----------------------------------- Configure ports
  pinMode (mCS,  OUTPUT) ;
  pinMode (mCLK, OUTPUT) ;
  pinMode (mSI,  OUTPUT) ;
  pinMode (mSO,  INPUT_PULLUP) ;
  pinMode (mIRQ, INPUT_PULLUP) ;
  digitalWrite (mCLK, LOW) ;  // CLK is low outside a command
  digitalWrite (mCS,  HIGH) ; // CS is high outside a command
  digitalWrite (mSI, LOW) ;
//----------------------------------- Send software reset to MCP2515
  delayMicroseconds (1) ;
  digitalWrite (mCS,  LOW) ;
  sendByte (RESET_COMMAND) ;
  delayMicroseconds (1) ;
  digitalWrite (mCS,  HIGH) ;
 //--- 
  delayMicroseconds (10) ;
//----------------------------------- Check if MCP2515 is accessible 
  writeRegister (CNF1_REGISTER, 0x55) ;
  bool ok = readRegister (CNF1_REGISTER) == 0x55 ;
  if (ok) {
    writeRegister (CNF1_REGISTER, 0xAA) ;
    ok = readRegister (CNF1_REGISTER) == 0xAA ;
  }
//----------------------------------- If ok, perform configuration
  if (ok) {
  //----------------------------------- Set CNF3, CNF2, CNF1 and CANINTE registers
    digitalWrite (mCS,  LOW) ;
    sendByte (WRITE_COMMAND) ;
    sendByte (CNF3_REGISTER) ;
  //--- Register CNF3:
  //  Bit 7: SOF
  //  bit 6: WAKFIL
  //  Bit 5-3: -
  //  Bit 2-0: PHSEG2
    sendByte (0x02) ;
  //--- Register CNF2:
  //  Bit 7 --> 1: BLTMODE
  //  bit 6 --> 0: SAM
  //  Bit 5-3 --> 2: PHSEG1
  //  Bit 2-0 --> 0: PRSEG
    sendByte (0x80 /* BLTMODE */ | (2 << 3) /* PHSEG1 */) ;
  //--- Register CNF1:
  //  Bit 7-6 --> 0: SJW == 1
  //  Bit 5-0 --> 3: BRP (250 kbit/s), 7: 125 kbit/s
    sendByte (7) ;
  //--- Register CANINTE: activate receive interrupts
  //  Bit 7 --> 0: MERRE
  //  Bit 6 --> 0: WAKIE
  //  Bit 5 --> 0: ERRIE
  //  Bit 4 --> 0: TX2IE
  //  Bit 3 --> 0: TX1IE
  //  Bit 2 --> 0: TX0IE
  //  Bit 1 --> 1: RX1IE
  //  Bit 0 --> 1: RX0IE
    sendByte (0x03) ;
    digitalWrite (mCS,  HIGH) ;
  //----------------------------------- Deactivate the RXnBF Pins (High Impedance State)
    writeRegister (BFPCTRL_REGISTER, 0) ;
  //----------------------------------- Set TXnRTS as inputs
    writeRegister (TXRTSCTRL_REGISTER, 0);
  //----------------------------------- Turn off filters => receive any message
    writeRegister (RXB0CTRL_REGISTER, 0x60) ;
    writeRegister (RXB1CTRL_REGISTER, 0x60) ;
  //----------------------------------- Reset device to normal mode
    writeRegister (CANCTRL_REGISTER, 0) ;
  }
//-----------------------------------
  return ok ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool MCP2515::available (void) {
  const byte status = readRxStatus () ; // Bit 6: message in RXB0, bit 7: message in RXB1
  return (status & 0xC0) != 0 ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool MCP2515::getReceivedMessage (CANFrame & outFrame) {
  const byte rxStatus = readRxStatus () ; // Bit 0: message in RXB0, bit 1: message in RXB1
  const bool ok = (rxStatus & 0xC0) != 0 ;
  if (ok) { // Message in RXB0 and / or RXB1
    const bool accessRXB0 = (rxStatus & 0x40) != 0 ;
    outFrame.rtr = (rxStatus & 0x10) != 0 ;
    outFrame.ext = (rxStatus & 0x08) != 0 ;
    delayMicroseconds (1) ;
    digitalWrite (mCS,  LOW) ;
    sendByte (accessRXB0 ? READ_FROM_RXB0SIDH_COMMAND : READ_FROM_RXB1SIDH_COMMAND) ;
  //--- SIDH
    outFrame.id = readByte () ; // Read SIDH
  //--- SIDL
    const uint8_t sidl = readByte () ; // Read SIDL
    outFrame.id <<= 3 ;
    outFrame.id |= sidl >> 5 ;
    outFrame.ext = (sidl & 0x08) != 0 ;
  //--- EID8
    const uint8_t eid8 = readByte () ; // Read EID8
    if (outFrame.ext) {
      outFrame.id <<= 8 ;
      outFrame.id |= eid8 ;
    }
  //--- EID0
    const uint8_t eid0 = readByte () ; // Read EID0
    if (outFrame.ext) {
      outFrame.id <<= 8 ;
      outFrame.id |= eid0 ;
    }
  //--- DLC
    const uint8_t dlc = readByte () ; // Read DLC
    outFrame.len = dlc & 0x0F ;
  //--- Read data
    for (int i=0 ; i<outFrame.len ; i++) {
      outFrame.buf [i] = readByte () ;
    }
  //---
    delayMicroseconds (1) ;
    digitalWrite (mCS,  HIGH) ;
  //--- Free receive buffer command
    bitModifyRegister (CANINTF_REGISTER, accessRXB0 ? 0x01 : 0x02, 0) ;
  }
//--- 
  return ok ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool MCP2515::sendMessage (const CANFrame & inFrame) {
//--- Get status (bit 2, 4 and 6 are related to send buffer 0, 1 and 2)
  const byte status = readStatus () ;
//--- Find a free send buffer 
  bool ok = true ;
  byte loadTxBuffer = LOAD_TX_BUFFER_COMMAND ;
  byte sendCommand = SEND_COMMAND ;
  if ((status & 0x04) == 0) { // Send buffer 0 is free
    sendCommand |= 0x01 ;
  }else if ((status & 0x10) == 0) { // Send buffer 1 is free
    loadTxBuffer = LOAD_TX_BUFFER_COMMAND | 0x02 ;
    sendCommand |= 0x02 ;
  }else if ((status & 0x40) == 0) { // Send buffer 2 is free
    loadTxBuffer = LOAD_TX_BUFFER_COMMAND | 0x04 ;
    sendCommand |= 0x04 ;
  }else{
    ok = false ; // No free buffer
  }
//--- Send message if a free buffer has been found
  if (ok) {
    delayMicroseconds (1) ;
    digitalWrite (mCS,  LOW) ;
    sendByte (loadTxBuffer) ;
    if (inFrame.ext) { // Extended frame
      uint32_t v = inFrame.id >> 21 ;
      sendByte ((byte) v) ; // ID28 ... ID21 --> SIDH
      v  = (inFrame.id >> 13) & 0xE0 ; // ID20, ID19, ID18 in bits 7, 6, 5
      v |= (inFrame.id >> 16) & 0x03 ; // ID17, ID16 in bits 1, 0
      v |= 0x08 ; // Extended bit
      sendByte ((byte) v) ; // ID20, ID19, ID18, -, 1, -, ID17, ID16 --> SIDL
      v  = (inFrame.id >> 8) & 0xFF ; // ID15, ..., ID8
      sendByte ((byte) v) ; // ID15, ID14, ID13, ID12, ID11, ID10, ID9, ID8 --> EID8
      v  = inFrame.id & 0xFF ; // ID7, ..., ID0
      sendByte ((byte) v) ; // ID7, ID6, ID5, ID4, ID3, ID2, ID1, ID0 --> EID0
    }else{ // Standard frame
      uint32_t v = inFrame.id >> 3 ;
      sendByte ((byte) v) ; // ID10 ... ID3 --> SIDH
      v  = (inFrame.id << 5) & 0xE0 ; // ID2, ID1, ID0 in bits 7, 6, 5
      sendByte ((byte) v) ; // ID2, ID1, ID0, -, 0, -, 0, 0 --> SIDL
      sendByte (0x00) ; // any value --> EID8
      sendByte (0x00) ; // any value --> EID0
    }
  //--- DLC
    byte v = inFrame.len & 0x0F ;
    if (inFrame.rtr) {
      v |= 0x40 ;
    }
    sendByte (v) ;
  //--- Send data
    if (!inFrame.rtr) {
      for (unsigned i=0 ; i<inFrame.len ; i++) {
        sendByte (inFrame.buf [i]) ;
      }
    }
    delayMicroseconds (1) ;
    digitalWrite (mCS,  HIGH) ;
  //--- Write send command
    delayMicroseconds (1) ;
    digitalWrite (mCS,  LOW) ;
    sendByte (sendCommand) ;
    delayMicroseconds (1) ;
    digitalWrite (mCS,  HIGH) ;
  }
//--- Return
  return ok ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void MCP2515::sendByte (const byte inByte) {
  byte v = inByte ;
  for (int i=0 ; i<8 ; i++) {
    delayMicroseconds (1) ;
    digitalWrite (mSI, (v & 0x80) != 0) ;
    delayMicroseconds (1) ;
    digitalWrite (mCLK, HIGH) ;
    delayMicroseconds (1) ;
    digitalWrite (mCLK, LOW) ;
    v <<= 1 ;
  }
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void MCP2515::writeRegister (const byte inRegister, const byte inValue) {
  delayMicroseconds (1) ;
  digitalWrite (mCS,  LOW) ;
  sendByte (WRITE_COMMAND) ;
  sendByte (inRegister) ;
  sendByte (inValue) ;
  delayMicroseconds (1) ;
  digitalWrite (mCS,  HIGH) ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

byte MCP2515::readByte (void) {
  byte readValue = 0 ;
  for (int i=0 ; i<8 ; i++) {
    delayMicroseconds (1) ;
    readValue <<= 1 ;
    readValue |= digitalRead (mSO) ;
    delayMicroseconds (1) ;
    digitalWrite (mCLK, HIGH) ;
    delayMicroseconds (1) ;
    digitalWrite (mCLK, LOW) ;
  }
  return readValue ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

byte MCP2515::readRegister (const byte inRegister) {
  delayMicroseconds (1) ;
  digitalWrite (mCS,  LOW) ;
  sendByte (READ_COMMAND) ;
  sendByte (inRegister) ;
  const byte readValue = readByte () ;
  delayMicroseconds (1) ;
  digitalWrite (mCS,  HIGH) ;
  return readValue ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

byte MCP2515::readStatus (void) {
  delayMicroseconds (1) ;
  digitalWrite (mCS,  LOW) ;
  sendByte (READ_STATUS_COMMAND) ;
  const byte readValue = readByte () ;
  delayMicroseconds (1) ;
  digitalWrite (mCS,  HIGH) ;
  return readValue ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

byte MCP2515::readRxStatus (void) {
  delayMicroseconds (1) ;
  digitalWrite (mCS,  LOW) ;
  sendByte (RX_STATUS_COMMAND) ;
  const byte readValue = readByte () ;
  delayMicroseconds (1) ;
  digitalWrite (mCS,  HIGH) ;
  return readValue ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void MCP2515::bitModifyRegister (const uint8_t inRegister, const uint8_t inMask, const uint8_t inData) {
  delayMicroseconds (1) ;
  digitalWrite (mCS,  LOW) ;
  sendByte (BIT_MODIFY_COMMAND) ;
  sendByte (inRegister) ;
  sendByte (inMask) ;
  sendByte (inData) ;
  delayMicroseconds (1) ;
  digitalWrite (mCS,  HIGH) ;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


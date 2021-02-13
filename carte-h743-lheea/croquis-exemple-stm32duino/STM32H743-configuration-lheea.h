#pragma once
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SPI.h>

//--------------------------------------------------------------------------------------------------

extern LiquidCrystal lcd ;

//--------------------------------------------------------------------------------------------------

void configurerCarteH743LHEEA (void) ;

//--------------------------------------------------------------------------------------------------
//   LEDS
//--------------------------------------------------------------------------------------------------

static const uint8_t LED_0_VERTE = PA0 ;
static const uint8_t LED_1_JAUNE = PA3 ;
static const uint8_t LED_2_ROUGE = PB2 ;
static const uint8_t NUCLEO_LD1_VERTE = PB0 ;
static const uint8_t NUCLEO_LD2_JAUNE = PE1 ;
static const uint8_t NUCLEO_LD3_ROUGE = PB14 ;

//--------------------------------------------------------------------------------------------------
//   INTERRUPTEURS DIL
//--------------------------------------------------------------------------------------------------

static const uint8_t INTER_DIL_1 = PG14 ;
static const uint8_t INTER_DIL_2 = PB11 ;
static const uint8_t INTER_DIL_3 = PB9 ;
static const uint8_t INTER_DIL_4 = PB8 ;

//--------------------------------------------------------------------------------------------------
//   POUSSOIRS
//--------------------------------------------------------------------------------------------------

static const uint8_t POUSSOIR_P0_BLANC = PE0 ;
static const uint8_t POUSSOIR_P1_ROSE  = PE2 ;
static const uint8_t POUSSOIR_P2_JAUNE = PE5 ;
static const uint8_t POUSSOIR_P3_ROUGE = PE6 ;
static const uint8_t POUSSOIR_NUCLEO_BLEU = PC13 ;

//-------------------------------------------------------------------------------------------------
// ENCODEUR NUMÉRIQUE
//-------------------------------------------------------------------------------------------------

static const uint8_t ENCODEUR_CLIC = PC6 ;

void fixerGammeEncodeur (const int32_t inBorneInf, const int32_t inBorneSup) ;

int32_t valeurEncodeur (void) ;

//-------------------------------------------------------------------------------------------------
// SORTIES TOR
//-------------------------------------------------------------------------------------------------

void activerSortieTOR (const uint32_t inIndex, const bool inValue) ;

//-------------------------------------------------------------------------------------------------
// SORTIE ANALOGIQUE
// Sortie directe :
//   0 -> 0V
//   255 -> 3,3V
//   inValue -> 3,3V *  inValue / 255
// Sortie amplifiée : dépend du réglage du potentiomètre
//-------------------------------------------------------------------------------------------------

void commanderSortieAnalogique (const uint8_t inValue) ;

//-------------------------------------------------------------------------------------------------
// ENTRÉES ANALOGIQUES
// Attention, la tension qui parvient au micro-contrôleur est réglable par potentiomètre :
//   0V -> 0
//   3,3V -> 4095
//-------------------------------------------------------------------------------------------------

uint16_t lireEntreeAnalogique (const uint32_t inNumeroEntree) ; // 0 ... 3

//--------------------------------------------------------------------------------------------------
// SRAM EXTERNE
//--------------------------------------------------------------------------------------------------

static const uint32_t EXTERNAL_SRAM_SIZE = 4 * 512 * 1024 ;
static const uint32_t EXTERNAL_SRAM_BASE_ADDRESS = 0x6000'0000 ;

//--------------------------------------------------------------------------------------------------

inline uint8_t readByteAtIndex (const uint32_t inIndex) { // Entre 0 et 2097151
  uint8_t resultat = 0 ;
  if (inIndex < EXTERNAL_SRAM_SIZE) {
    uint8_t * address = (uint8_t *) (EXTERNAL_SRAM_BASE_ADDRESS + inIndex) ;
    resultat = *address ;
  }
  return resultat ;
}

//--------------------------------------------------------------------------------------------------

inline void writeByteAtIndex (const uint8_t inValue, const uint32_t inIndex) { // Entre 0 et 2097151
  if (inIndex < EXTERNAL_SRAM_SIZE) {
    uint8_t * address = (uint8_t *) (EXTERNAL_SRAM_BASE_ADDRESS + inIndex) ;
    *address = inValue ;
  }
}

//--------------------------------------------------------------------------------------------------

template <typename T>
inline T readAtIndex (const uint32_t inIndex) { // Entre 0 et 2097151
  T resultat = T () ;
  if ((inIndex < EXTERNAL_SRAM_SIZE) && ((inIndex % sizeof (T)) == 0)) {
    T * address = (T *) (EXTERNAL_SRAM_BASE_ADDRESS + inIndex) ;
    resultat = *address ;
  }
  return resultat ;
}

//--------------------------------------------------------------------------------------------------

template <typename T>
inline void writeAtIndex (const T & inValue, const uint32_t inIndex) { // Entre 0 et 2097151
  if ((inIndex < EXTERNAL_SRAM_SIZE) && ((inIndex % sizeof (T)) == 0)) {
    T * address = (T *) (EXTERNAL_SRAM_BASE_ADDRESS + inIndex) ;
    *address = inValue ;
  }
}

//--------------------------------------------------------------------------------------------------
// SPI
//--------------------------------------------------------------------------------------------------

enum class MySPI { spi1, spi2, spi3, spi5} ;

//--------------------------------------------------------------------------------------------------
// EEPROM EXTERNE
//--------------------------------------------------------------------------------------------------

enum class SPI_EEPROM_TYPE {
  MCP25LC256, // 512 pages de 64 octets
  MCP25LC512  // 512 pages de 128 octets
} ;

//--------------------------------------------------------------------------------------------------
// EEPROM EXTERNE
//--------------------------------------------------------------------------------------------------

class SPIEEPROM {

//--- Constructor
  public: SPIEEPROM (const MySPI inSPI,
                     const SPI_EEPROM_TYPE inEEPROMType) ;

//--- Begin
  public: void begin (void) ;

//--- Private properties
  private: const SPISettings mSPISettings ;
  private: MySPI mSPI ;
  private: const SPI_EEPROM_TYPE mEEPROMType ;

//--- Read EEPROM
  public: void eepromRead (const uint32_t inAddress,
                           uint8_t outBuffer[],
                           const uint32_t inLength) ;

//--- status
  public: uint8_t eepromStatus (void) ;

//--- isBusy
  public: bool eepromIsBusy (void) ;

//--- Enable Write EEPROM
  protected: void eepromWriteEnable (void) ;

//--- Write EEPROM
  public: void eepromWrite (const uint32_t inAddress,
                            const uint8_t inBuffer[],
                            const uint32_t inLength) ;

//---
  public: uint32_t eepromPageSize (void) const ;

//--- Private method
  private: SPIClass* spiPtr (void) ;

//--- No copy
  private: SPIEEPROM (const SPIEEPROM &) = delete ;
  private: SPIEEPROM & operator = (const SPIEEPROM &) = delete ;
} ;

//--------------------------------------------------------------------------------------------------
// CLASSE GÉNÉRIQUE "VarInEEPROM"
// Inspirée de la librairie EEPROM-Storage de Daniel Porrey
// https://github.com/porrey/EEPROM-Storage
//--------------------------------------------------------------------------------------------------

template <typename T> class VarInEEPROM {

 //--- Constructor
   public: VarInEEPROM (SPIEEPROM & inEEPROM,  const uint32_t inAddress) :
   mEEPROM (&inEEPROM),
   mAddress (inAddress),
   mValue (),
   mLoaded (false) {
   }

//--- Primary getter
  public: T get (void) {
    if (!this->mLoaded) {
      this->mEEPROM->eepromRead (this->mAddress, (uint8_t *) &(this->mValue), sizeof (T)) ;
      this->mLoaded = true ;
    }
    T result = this->mValue ;
    return result ;
  }

//--- Primary setter
  public: void set (const T & inValue) {
    this->mValue = inValue ;
    this->mEEPROM->eepromWrite (this->mAddress, (uint8_t *) &(this->mValue), sizeof (T)) ;
    this->mLoaded = true ;
  }

//--- IsLoaded ?
  public: bool IsLoaded (void) const { return this->mLoaded ; }
    
//    // ***
//    // *** Allows the variable to be used on the left side of
//    // *** the equal sign.
//    // ***
//    T operator = (T const& value) const
//    {
//      this->set(value);
//      return this->get();
//    }
//
//    // ***
//    // *** Allows the variable to be used on the right side of
//    // *** the equal sign.
//    // ***
//    operator T()
//    {
//      return this->get();
//    }
//
//    // ***
//    // *** ++ postfix
//    // ***
//    T operator ++ (int)
//    {
//      T oldValue = this->get();
//      T newValue = oldValue + 1;
//      this->set(newValue);
//      return oldValue;
//    }
//
//    // ***
//    // *** ++ prefix
//    // ***
//    T operator ++ ()
//    {
//      T newValue = this->get() + 1;
//      this->set(newValue);
//      return newValue;
//    }
//
//    // ***
//    // *** -- postifx
//    // ***
//    T operator -- (int)
//    {
//      T oldValue = this->get();
//      T newValue = oldValue - 1;
//      this->set(newValue);
//      return oldValue;
//    }
//
//    // ***
//    // *** -- prefix
//    // ***
//    T operator -- ()
//    {
//      T newValue = this->get() - 1;
//      this->set(newValue);
//      return newValue;
//    }
//
//    // ***
//    // *** += operator
//    // ***
//    T operator += (T const& value) const
//    {
//      T newValue = this->get() + value;
//      this->set(newValue);
//      return newValue;
//    }
//
//    // ***
//    // *** -= operator
//    // ***
//    T operator -= (T const& value) const
//    {
//      T newValue = this->get() - value;
//      this->set(newValue);
//      return newValue;
//    }
//
//    // ***
//    // *** *= operator
//    // ***
//    T operator *= (T const& value) const
//    {
//      T newValue = this->get() * value;
//      this->set(newValue);
//      return newValue;
//    }
//
//    // ***
//    // *** /= operator
//    // ***
//    T operator /= (T const& value) const
//    {
//      T newValue = this->get() / value;
//      this->set(newValue);
//      return newValue;
//    }
//
//    // ***
//    // *** %= operator
//    // ***
//    T operator %= (T const& value) const
//    {
//      T newValue = this->get() % value;
//      this->set(newValue);
//      return newValue;
//    }
//
//    // ***
//    // *** &= operator
//    // ***
//    T operator &= (T const& value) const
//    {
//      T newValue = this->get() & value;
//      this->set(newValue);
//      return newValue;
//    }
//
//    // ***
//    // *** |= operator
//    // ***
//    T operator |= (T const& value) const
//    {
//      T newValue = this->get() | value;
//      this->set(newValue);
//      return newValue;
//    }
//
//    // ***
//    // *** > operator
//    // ***
//    bool operator > (T const& value) const
//    {
//      return this->get() > value;
//    }
//
//    // ***
//    // *** < operator
//    // ***
//    bool operator < (T const& value) const
//    {
//      return this->get() < value;
//    }
//
//    // ***
//    // *** >= operator
//    // ***
//    bool operator >= (T const& value) const
//    {
//      return this->get() >= value;
//    }
//
//    // ***
//    // *** <= operator
//    // ***
//    bool operator <= (T const& value) const
//    {
//      return this->get() <= value;
//    }
//
//    // ***
//    // *** == operator
//    // ***
//    bool operator == (T const& value) const
//    {
//      return this->get() == value;
//    }
//
//    // ***
//    // *** Get the value from EEPROM.
//    // ***
//    T get()
//    {
//      T returnValue;
//
//      // ***
//      // *** Check if the variable has been set or not
//      // *** by comparing the value to the not set value
//      // *** specified in the constructor.
//      // ***
//      if (this->isInitialized())
//      {
//        // ***
//        // *** Get the variable from EEPROM
//        // *** using the address this->mAddress.
//        // ***
//        EEPROM.get(this->mAddress, returnValue);
//      }
//      else
//      {
//        // ***
//        // *** Return the default value specified in
//        // *** the constructor.
//        // ***
//        returnValue = this->_defaultValue;
//      }
//
//      return returnValue;
//    }
//
//    // ***
//    // *** Save the value to EEPROM.
//    // ***
//    void set(T const& value) const
//    {
//      // ***
//      // *** Set the value in EEPROM using the
//      // *** update method.
//      // ***
//      EEPROM.put(this->mAddress, value);
//
//      // ***
//      // *** Write the checksum.
//      // ***
//      uint8_t checksum = Checksum<T>::get(value);
//      EEPROM.update(this->checksumAddress(), checksum);
//    }
//
//    // ***
//    // *** Determines if the variable has been
//    // *** initialized or not by comparing the
//    // *** stored hecksum to the actual checksum
//    // *** of the bytes stored.
//    // ***
//    bool isInitialized()
//    {
//      return (this->checksum() == this->checksumByte());
//    }
//
//    // ***
//    // *** Returns the number of EEPROM bytes
//    // *** used by this instance.
//    // ***
//    uint16_t length()
//    {
//      // ***
//      // *** The extra byte is the checksum byte.
//      // ***
//      return sizeof(T) + 1;
//    }
//
//    // ***
//    // *** Unset the variable (return the EEPROM values
//    // *** back to 0xff).
//    // ***
//    void unset(byte unsetValue = 0xff)
//    {
//      for ( int i = 0; i < this->length(); i++)
//      {
//        EEPROM.update(this->mAddress + i, unsetValue);
//      }
//    }
//
//    // ***
//    // *** Gets the address of the checksum byte.
//    // ***
//    uint16_t checksumAddress()
//    {
//      return this->mAddress + this->length() - 1;
//    }
//
//    // ***
//    // *** Gets the stored checksum byte.
//    // ***
//    uint16_t checksumByte()
//    {
//      return EEPROM.read(this->checksumAddress());
//    }
//
//    // ***
//    // *** Calcuate the checksum of the
//    // *** data in the EEPROM for this instance.
//    // ***
//    uint8_t checksum()
//    {
//      byte data[MAX_VARIABLE_LENGTH];
//      this->copyTo(data, sizeof(T));
//      return Checksum<T>::get(data, sizeof(T));
//    }
//
//    // ***
//    // *** Copy the EEPROM bytes of this instance to
//    // *** a byte array.
//    // ***
//    void copyTo(byte* data, uint32_t length)
//    {
//      for (int i = 0; i < length; i++)
//      {
//        data[i] = EEPROM[this->mAddress + i];
//      }
//    }
//
//    uint16_t getAddress()
//    {
//      return this->mAddress;
//    }
//
//    T getDefaultValue()
//    {
//      return this->_defaultValue;
//    }

//--- No copy
  private: VarInEEPROM (const VarInEEPROM <T> &) = delete ;
  private: VarInEEPROM & operator = (const VarInEEPROM <T> &) = delete ;
  
//--- Private properties
  private: SPIEEPROM * mEEPROM ;
  private: uint32_t mAddress ;
  private: T mValue ;
  private: bool mLoaded ;
} ;

//--------------------------------------------------------------------------------------------------

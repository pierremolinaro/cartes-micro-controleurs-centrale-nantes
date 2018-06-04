
#include "MMA_7455.h"
#include <Wire.h>

#define MMA_7455_ADDRESS (0x1D) //I2C Address for the sensor

#define MMA_7455_MODE_CONTROLL (0x16) //Call the sensors Mode Control
#define MMA_7455_2G_MODE (0x05) //Set Sensitivity to 2g
#define MMA_7455_4G_MODE (0x09) //Set Sensitivity to 4g
#define MMA_7455_8G_MODE (0x01) //Set Sensitivity to 8g

#define X_OUT (0x06) //Register for reading the X-Axis
#define Y_OUT (0x07) //Register for reading the Y-Axis
#define Z_OUT (0x08) //Register for reading the Z-Axis

MMA_7455::MMA_7455 () {
}

void MMA_7455::begin()
{
   Wire.begin ();
   Wire.setClock (400 * 1000) ;
}

void MMA_7455::initSensitivity (int sensitivity) {
  Wire.beginTransmission (MMA_7455_ADDRESS) ;
  Wire.write (MMA_7455_MODE_CONTROLL);
  if (sensitivity == 2) {
    Wire.write (MMA_7455_2G_MODE);  //Set Sensitivity to 2g Detection
  }else if(sensitivity == 4) {
    Wire.write (MMA_7455_4G_MODE);  //Set Sensitivity to 4g Detection
  }else if(sensitivity == 8) {
    Wire.write (MMA_7455_8G_MODE);  //Set Sensitivity to 8g Detection
  }
  Wire.endTransmission (true);
}

void MMA_7455::calibrateOffset(float x_axis_offset, float y_axis_offset, float z_axis_offset)
{
  _x_axis_offset = x_axis_offset;
  _y_axis_offset = y_axis_offset;
  _z_axis_offset = z_axis_offset;
}

int8_t MMA_7455::readXAxis(void) {
  Wire.beginTransmission (MMA_7455_ADDRESS);
  Wire.write (X_OUT) ;
  Wire.endTransmission (false) ;
  Wire.requestFrom (MMA_7455_ADDRESS, 1);
  while (!Wire.available ()) {}
  return (int8_t) Wire.read () ;
}

int8_t MMA_7455::readYAxis(void) {
  Wire.beginTransmission(MMA_7455_ADDRESS);
  Wire.write (Y_OUT) ;
  Wire.endTransmission (false);
  Wire.requestFrom (MMA_7455_ADDRESS, 1);
  while (!Wire.available ()) {}
  return (int8_t) Wire.read () ;
}

int8_t MMA_7455::readZAxis (void) {
  Wire.beginTransmission (MMA_7455_ADDRESS) ;
  Wire.write (Z_OUT) ;
  Wire.endTransmission (false) ;
  Wire.requestFrom (MMA_7455_ADDRESS, 1);
  while (!Wire.available ()) {}
  return (int8_t) Wire.read () ;
}

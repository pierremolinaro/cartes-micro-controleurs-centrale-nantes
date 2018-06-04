// MMA_7455.h - 3 Axis Accelerometer Library
// Moritz Kemper, IAD Physical Computing Lab
// moritz.kemper@zhdk.ch
// ZHdK, 03/04/2012
// Released under Creative Commons Licence

#ifndef MMA_7455_h
#define MMA_7455_h

#include "Arduino.h"
#include <Wire.h>


class MMA_7455
{
  public:
    MMA_7455();
    void begin();
    void initSensitivity(int sensitivity);
    void calibrateOffset(float x_axis_offset, float y_axis_offset, float z_axis_offset);
    int8_t readXAxis (void);
    int8_t readYAxis (void);
    int8_t readZAxis (void);

	float _x_axis_offset;
	float _y_axis_offset;
	float _z_axis_offset;
};

#endif

/*
AMS5812.h
Brian R Taylor
brian.taylor@bolderflight.com
2016-09-22

Copyright (c) 2016 Bolder Flight Systems

Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef AMS5812_h
#define AMS5812_h

#include "Arduino.h"

// min and max pressures, PSI
#define AMS5812_0000_D_P_MIN 0.0
#define AMS5812_0000_D_P_MAX 0.075
#define AMS5812_0001_D_P_MIN 0.0
#define AMS5812_0001_D_P_MAX 0.15
#define AMS5812_0000_D_B_P_MIN -0.075
#define AMS5812_0000_D_B_P_MAX 0.075
#define AMS5812_0001_D_B_P_MIN -0.15
#define AMS5812_0001_D_B_P_MAX 0.15
#define AMS5812_0003_D_P_MIN 0.0
#define AMS5812_0003_D_P_MAX 0.3
#define AMS5812_0008_D_P_MIN 0.0
#define AMS5812_0008_D_P_MAX 0.8
#define AMS5812_0015_D_P_MIN 0.0
#define AMS5812_0015_D_P_MAX 1.5
#define AMS5812_0003_D_B_P_MIN -0.3
#define AMS5812_0003_D_B_P_MAX 0.3
#define AMS5812_0008_D_B_P_MIN -0.8
#define AMS5812_0008_D_B_P_MAX 0.8
#define AMS5812_0015_D_B_P_MIN -1.5
#define AMS5812_0015_D_B_P_MAX 1.5
#define AMS5812_0030_D_P_MIN 0.0
#define AMS5812_0030_D_P_MAX 3.0
#define AMS5812_0050_D_P_MIN 0.0
#define AMS5812_0050_D_P_MAX 5.0
#define AMS5812_0150_D_P_MIN 0.0
#define AMS5812_0150_D_P_MAX 15.0
#define AMS5812_0300_D_P_MIN 0.0
#define AMS5812_0300_D_P_MAX 30.0
#define AMS5812_0600_D_P_MIN 0.0
#define AMS5812_0600_D_P_MAX 60.0
#define AMS5812_1000_D_P_MIN 0.0
#define AMS5812_1000_D_P_MAX 100.0
#define AMS5812_0030_D_B_P_MIN -3.0
#define AMS5812_0030_D_B_P_MAX 3.0
#define AMS5812_0050_D_B_P_MIN -5.0
#define AMS5812_0050_D_B_P_MAX 5.0
#define AMS5812_0150_D_B_P_MIN -15.0
#define AMS5812_0150_D_B_P_MAX 15.0
#define AMS5812_0150_B_P_MIN 11.0
#define AMS5812_0150_B_P_MAX 17.5
#define AMS5812_0150_A_P_MIN 0.0
#define AMS5812_0150_A_P_MAX 15.0
#define AMS5812_0300_A_P_MIN 0.0
#define AMS5812_0300_A_P_MAX 30.0

// temperature ranges, C
#define AMS5812_T_MIN -25.0
#define AMS5812_T_MAX 85.0

class AMS5812{
  public:
    AMS5812(int address, int bus, String type);
    void begin();
    float getPressure();
    float getTemperature();
    void getData(float* pressure, float* temperature);
  private:
    int _address;
    int _bus;
    String _type;
    float _pMin;
    float _pMax;
    float _tMin;
    float _tMax;
    const float _psi2pa = 4.4482216152605f/(0.0254f*0.0254f); // conversion PSI to PA
    void getTransducer();
    uint16_t readPressureBytes();
    void readBytes(uint16_t* pressureCounts, uint16_t* temperatureCounts);
};

#endif
